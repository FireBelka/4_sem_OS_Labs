//#include <Windows.h>
//#include <iostream>
//#include <string>
//#include <stdlib.h>
//#include <fstream>
//
//
//int main(int argc, char* argv[])
//{
//    if (argc != 2) {
//        return 0;
//    }
//    setlocale(LC_ALL, "Rus");
//  
//    int bufferSize = atoi(argv[1]);
//    bool connect;
//    char* resp = new char[atoi(argv[1])];
//    std::string toPipe;
//    bool a = true;
//    while (a) {
//       
//        std::cout << "1 ��� ������ ��������\n2 ��������������\n(����� �����)\n";
//        int command;
//        std::cin >> command;
//        switch (command) {
//        case 1:
//            std::cout << "������� id ��������\n";
//            std::cin >> command;
//            
//            
//                toPipe = "1" + std::to_string(command);
//                int bytesRead;
//                connect = CallNamedPipeA(argv[0], (LPVOID)toPipe.c_str(), bufferSize,
//                    resp, bufferSize, (LPDWORD)&bytesRead, NMPWAIT_WAIT_FOREVER);
//                if (resp[0] == '1') {
//                    char* next_token = NULL;
//                    char* word = strtok_s(resp, " ", &next_token);
//                    word = strtok_s(NULL, " ", &next_token);
//                    std::cout << "��� ��������: " << word << std::endl;
//                    word = strtok_s(NULL, " ", &next_token);
//                    std::cout << "���������� �����: " << word << std::endl;
//                }
//                else {
//                    if (resp[0] == '0') {
//                        std::cout << "�������� ���\n";
//                    }
//                    else {
//                        std::cout << "Updating data...\n";
//                    }
//                }  
//            break;
//        case 2:
//            //not done
//            std::cout << "������� ����������������� ����� ��������\n";
//            std::cin >> command;
//           
//                 toPipe = "2" + std::to_string(command);
//                int bytesRead2;
//                connect = CallNamedPipeA(argv[0], (LPVOID)toPipe.c_str(), bufferSize,
//                    resp, bufferSize, (LPDWORD)&bytesRead, NMPWAIT_WAIT_FOREVER);
//                if (resp[0] == '1') {
//                    char* next_token = NULL;
//                    char* word = strtok_s(resp, " ", &next_token);
//                    word = strtok_s(NULL, " ", &next_token);
//                    std::cout << "��� ��������: " << word << std::endl;
//                    word = strtok_s(NULL, " ", &next_token);
//                    std::cout << "���������� �����: " << word << std::endl;
//                    std::cout << "������� ����� ��� ��������\n";
//                    std::string newName;
//                    std::cin >> newName;
//                    std::cout << "������� ����� ���������� �����.\n";
//                    double newHours;
//                    std::cin >> newHours;
//                    toPipe = "0" + std::to_string(command) + " " + newName + " " + std::to_string(newHours);
//                    connect = CallNamedPipeA(argv[0], (LPVOID)toPipe.c_str(), bufferSize,
//                        resp, bufferSize, (LPDWORD)&bytesRead, NMPWAIT_WAIT_FOREVER);
//                    if (resp[0] == '1')
//                        std::cout << "������ ��������.\n";
//                    else
//                        std::cout << "������ �� ���� ��������, ���: " << resp[0] << std::endl;
//                }
//                else {
//                    if (resp[0] == '0') {
//                        std::cout << "�������� � ����� id �� ����������.\n";
//                    }
//                    else {
//                        std::cout << "� ������� ��������, ���: " << resp[0] << std::endl;
//                    }
//                }
//            
//            break;
//        default:
//            a = false;
//            break;
//        }
//    }
//
//
//    return 0;
//}
