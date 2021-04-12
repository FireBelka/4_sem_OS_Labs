#include <Windows.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <charconv>
using namespace std;
CRITICAL_SECTION cs;
int main()
{
    setlocale(LC_ALL, "Russian");
    std::cout << "Введите название исходного файла\n";
    std::string fileName;
    std::cin >> fileName;
    std::cout << "Введите количество процессов Sender\n";
    int count_of_sender;
    cin >> count_of_sender;
    InitializeCriticalSection(&cs);
    STARTUPINFOA* sendersSI = new STARTUPINFOA[count_of_sender];
    PROCESS_INFORMATION* sendersPI = new PROCESS_INFORMATION[count_of_sender];
    HANDLE* SenderEventsToSync = new HANDLE[count_of_sender];
    HANDLE* senders = new HANDLE[count_of_sender];
    fstream fin(fileName, std::ios_base::trunc | std::ios_base::out | std::ios_base::binary | std::ios_base::in);
    const char* appName = "F:\\Учеба\\4 сем Операционные Системы\\практика\\lab4\\sender.exe";
    SECURITY_ATTRIBUTES securityAttributes = { sizeof(SECURITY_ATTRIBUTES), nullptr, TRUE };
    HANDLE Event_to_start = CreateEventA(&securityAttributes, TRUE, FALSE, "SenderStartEvent");
    for (int i = 0; i < count_of_sender; i++) {
        ZeroMemory(&sendersSI[i], sizeof(STARTUPINFO));
        sendersSI[i].cb = sizeof(STARTUPINFO);
        ZeroMemory(&sendersPI[i], sizeof(PROCESS_INFORMATION));
        SenderEventsToSync[i] = CreateEventA(&securityAttributes, FALSE, FALSE, ("Event" + to_string(i)).c_str());
        
        string arguments = fileName + " Event" + to_string(i);
        if (!CreateProcessA(appName, (char*)arguments.c_str(), NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &sendersSI[i], &sendersPI[i])) {
            std::cout << GetLastError();
            ExitProcess(0);
        }
        senders[i] = sendersPI[i].hProcess;
    }
    WaitForMultipleObjects(count_of_sender, SenderEventsToSync, TRUE, INFINITE);
    SetEvent(Event_to_start);
 
    while (WaitForMultipleObjects(count_of_sender, senders, TRUE, 0) == WAIT_TIMEOUT) {
        cout << "Введите 0 для попытки чтения сообщений из файла.\n";
        string text;
        cin>>text;
        if (text.compare("0") != 0) {
            break;
        }
        string message;
        EnterCriticalSection(&cs);
        fin.sync();
        if (!(std::getline(fin, message))) {
            cout << "No messages"<<endl;
            fin.clear();
        }
        else {
           cout << message << std::endl;
        }
        while (std::getline(fin, message)) {
            cout << message << std::endl;
        }
        fin.clear();
        LeaveCriticalSection(&cs);
    }
    for (int i = 0; i < count_of_sender; i++) {
        CloseHandle(sendersPI[i].hThread);
        CloseHandle(sendersPI[i].hProcess);
        CloseHandle(SenderEventsToSync[i]);
    }
    CloseHandle(Event_to_start);
    fin.close();
    return 0;
}
