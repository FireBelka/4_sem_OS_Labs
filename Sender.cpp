#include <Windows.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
using namespace std;
CRITICAL_SECTION cs;

int main(int argc, char* argv[])
{
    InitializeCriticalSection(&cs);
    if (argc == 2) {
        setlocale(LC_ALL, "Russian");
        HANDLE Event = OpenEventA(EVENT_MODIFY_STATE, FALSE, argv[1]);
        HANDLE startEvent = OpenEventA(SYNCHRONIZE, FALSE, "SenderStartEvent");
        ofstream fout(argv[0], std::ios_base::binary | std::ios_base::out | std::ios_base::app);
        string message;
        SignalObjectAndWait(Event, startEvent, INFINITE, FALSE);
        while (true) {
            cout << "¬ведите сообщение дл€ передачи или введите 0 дл€ прекращени€ работы.\n";
            cin >> message;
            if (message.compare("0") == 0)
                break;
            EnterCriticalSection(&cs);
            fout << message << std::endl;
            SetEvent(Event);
            LeaveCriticalSection(&cs);
        }
        CloseHandle(startEvent);
        fout.close();
        CloseHandle(Event);
    }
    return 0;
}