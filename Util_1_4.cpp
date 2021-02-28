#define  _CRT_NON_CONFORMING_WCSTOK
#define STRLEN(x) (sizeof(x)/sizeof(TCHAR) - 1)
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <shellapi.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <fcntl.h>
#include  <io.h>
using namespace std;

struct employee
{
    int num; // идентификационный номер сотрудника
   char name[10]; // имя сотрудника
    double hours; // количество отработанных часов
};
void writeBinFile(wstring path, vector<employee> vec) {
    ofstream out;
    out.open(path, ios::binary);
    for (int i = 0; i < vec.size(); i++) {
        out.write((char*)&vec[i].num, sizeof(int));
        out.write((char*)&vec[i].name, sizeof(vec[i].name));
        out.write((char*)&vec[i].hours, sizeof(double));
    }
    out.close();
}
bool RedirectConsoleIO()
{
    AllocConsole();
    bool result = true;
    FILE* fp;

    // Redirect STDIN if the console has an input handle
    if (GetStdHandle(STD_INPUT_HANDLE) != INVALID_HANDLE_VALUE)
        if (freopen_s(&fp, "CONIN$", "r", stdin) != 0)
            result = false;
        else
            setvbuf(stdin, NULL, _IONBF, 0);

    // Redirect STDOUT if the console has an output handle
    if (GetStdHandle(STD_OUTPUT_HANDLE) != INVALID_HANDLE_VALUE)
        if (freopen_s(&fp, "CONOUT$", "w", stdout) != 0)
            result = false;
        else
            setvbuf(stdout, NULL, _IONBF, 0);

    // Redirect STDERR if the console has an error handle
    if (GetStdHandle(STD_ERROR_HANDLE) != INVALID_HANDLE_VALUE)
        if (freopen_s(&fp, "CONOUT$", "w", stderr) != 0)
            result = false;
        else
            setvbuf(stderr, NULL, _IONBF, 0);

    // Make C++ standard streams point to console as well.
    ios::sync_with_stdio(true);

    // Clear the error state for each of the C++ standard streams.
    std::wcout.clear();
    std::cout.clear();
    std::wcerr.clear();
    std::cerr.clear();
    std::wcin.clear();
    std::cin.clear();

    return result;
}
int WINAPI WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst, LPSTR lpszArgs, int nWinMode) {
    LPWSTR* argv;
    RedirectConsoleIO();    
    int argc;
    wstring str = GetCommandLineW();
    TCHAR* s = new TCHAR[str.length() + 1];
    wcscpy(s, str.c_str());
    wchar_t * ptr = wcstok(s, L" ");
    wstring binName = ptr;
    ptr = wcstok(NULL, L" ");
    int countOfEmps = stoi(ptr);
    wcin.clear();
    wcout << L"Total emps: " + to_wstring(countOfEmps) << endl;
    vector<employee> emps ;
    wstring text = L"";
    for (int i = 0; i < countOfEmps; i++) {       
        employee buf;
        wstring b = L"Input id of emp #" + to_wstring(i)+L"\n";
        wcout << b;
        wcin >> buf.num;
        b = L"Input name of emp #" + to_wstring(i) + L"\n";
        wcout << b;
        cin >> buf.name;
        b = L"Input hours of emp #" + to_wstring(i) + L"\n";
        wcout << b;
        wcin >> buf.hours;
        emps.push_back(buf);
    }
    
    writeBinFile(binName, emps);
    system("pause");
        return 0;
}