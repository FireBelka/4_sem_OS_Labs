#include <Windows.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <map>
#define FREE 0
#define READ 1
#define WRITTEN 2
struct employee
{
    int num;
    std::string name;
    double hours;
};
struct toThread {
    std::map<int, std::tuple<int, std::string, double>>& employees;
    HANDLE pipe;
    int bufferSize;
    toThread(std::map<int, std::tuple<int, std::string, double>>& _employees, HANDLE _pipe, int _bufferSize) : pipe(_pipe), employees(_employees) {
        bufferSize = _bufferSize;
        pipe = _pipe;
    }
};
DWORD WINAPI connect_to_cl(LPVOID lpParam) {
    toThread* pointer = (toThread*)lpParam;
    char* response = new char[pointer->bufferSize];
    bool successful = ReadFile(pointer->pipe, response, pointer->bufferSize, NULL, NULL);
    if (successful) {
        int id = atoi(response + 1);
        std::string toPipe;
        auto employee = pointer->employees.find(id);
        if (employee != pointer->employees.end()) {
            switch (response[0]) {
            case '1':
                if (std::get<0>(employee->second) != WRITTEN) {
                    std::get<0>(employee->second) = READ;
                    toPipe = "1 " + std::get<1>(employee->second) + " " + std::to_string(std::get<2>(employee->second));
                }
                else {
                    toPipe = "2";
                }
                std::get<0>(employee->second) = FREE;
                break;
            case '2':
                if (std::get<0>(employee->second) == FREE) {
                    std::get<0>(employee->second) = WRITTEN;
                    toPipe = "1 " + std::get<1>(employee->second) + " " + std::to_string(std::get<2>(employee->second));
                }
                else {
                    toPipe = "3";
                }
                break;
            case '0':
                if (std::get<0>(employee->second) == WRITTEN) {
                    char* next_token = NULL;
                    char* word = strtok_s(response, " ", &next_token);
                    word = strtok_s(NULL, " ", &next_token);
                    std::get<1>(employee->second) = word;
                    word = strtok_s(NULL, " ", &next_token);
                    std::get<2>(employee->second) = atof(word);
                    toPipe = "1";
                    std::get<0>(employee->second) = FREE;
                }
                else {
                    toPipe = "4";
                }
                break;
            default:
                toPipe = "5";
                break;
            }
        }
        else {
            toPipe = "0";
        }
        WriteFile(pointer->pipe, (LPVOID)toPipe.c_str(), pointer->bufferSize, NULL, NULL);
    }
    DisconnectNamedPipe(pointer->pipe);
    CloseHandle(pointer->pipe);
    return 0;
}
int main()
{
    setlocale(LC_ALL, "Russian");
    std::cout << "Введите название исходного файла\n";
    std::string fileName;
    std::cin >> fileName;
    std::fstream fin(fileName, std::ios_base::trunc | std::ios_base::out | std::ios_base::binary | std::ios_base::in);
    std::map<int, std::tuple<int, std::string, double>> employees;

    int num, rewrite;
    std::string name;
    double hours;
    std::cout << "Введите количество студентов" << std::endl;
    int buf;
    std::cin >> buf;
    for (int i = 0; i < buf; i++) {
        std::cout << "Введите имя студента №";
        std::cout << (i + 1);
        std::cout << std::endl;
        std::cin >> name;
        std::cout << "Введите id студента\n";
        std::cin >> num;
        std::cout << "Введите часы студента\n";
        std::cin >> hours;
        if (employees.find(num) == employees.end()) {
            employees.insert(std::pair<int, std::tuple<int, std::string, double>>(num, std::tuple<int, std::string, double>(FREE, name, hours)));
        }
        else {
            std::cout << "WD\n";
        }
    }
    int clientsCount;
    std::cout << "Введите количество процессов client\n";
    std::cin >> clientsCount;
    HANDLE* clients = new HANDLE[clientsCount];
    int bufferSize = sizeof(double) + sizeof(double) + sizeof(char) * 256;
    std::string pipeName = "\\\\.\\pipe\\clientPipe";
    STARTUPINFOA* clientsSI = new STARTUPINFOA[clientsCount];
    PROCESS_INFORMATION* clientsPI = new PROCESS_INFORMATION[clientsCount];
    const char* appName = "client.exe";
    for (int i = 0; i < clientsCount; i++) {
        ZeroMemory(&clientsSI[i], sizeof(STARTUPINFO));
        clientsSI[i].cb = sizeof(STARTUPINFO);
        ZeroMemory(&clientsPI[i], sizeof(PROCESS_INFORMATION));
        std::string arguments = pipeName + " " + std::to_string(bufferSize);
        if (!CreateProcessA(appName, (char*)arguments.c_str(), NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &clientsSI[i], &clientsPI[i])) {
            std::cout << GetLastError();
            ExitProcess(0);
        }
        clients[i] = clientsPI[i].hProcess;
    }
    BOOL successful = FALSE;
    while (WaitForMultipleObjects(clientsCount, clients, TRUE, 10) == WAIT_TIMEOUT) {
        HANDLE pipe = CreateNamedPipeA((char*)pipeName.c_str(), PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
            PIPE_UNLIMITED_INSTANCES, bufferSize, bufferSize, NMPWAIT_USE_DEFAULT_WAIT, 0);
        if (!pipe)
        {
            continue;
        }
        successful = ConnectNamedPipe(pipe, NULL);
        if (successful) {
            CreateThread(NULL, 0, connect_to_cl, new toThread(employees, pipe, bufferSize), 0, NULL);
        }
        else {
            std::cout << "Pipe doesn't exist\n";
            CloseHandle(pipe);
        }
    }
    for (auto it = employees.begin(); it != employees.end(); ++it)
    {
        fin << "ID: " << it->first << std::endl << "\tИмя: " << std::get<1>(it->second) << std::endl << "\tКол-во отработанных часов: " << std::get<2>(it->second) << std::endl;
        std::cout << "ID: " << it->first << std::endl << "\tИмя: " << std::get<1>(it->second) << std::endl << "\tКол-во отработанных часов: " << std::get<2>(it->second) << std::endl;
    }
    fin.close();
    for (int i = 0; i < clientsCount; i++) {
        CloseHandle(clients[i]);
    }
    return 0;
}