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
#include <algorithm>
using namespace std;
struct employee
{
    int num; // идентификационный номер сотрудника
    char name[10]; // имя сотрудника
    double hours; // количество отработанных часов
};
vector<employee> readBinFile(wstring filename) {
	vector<employee> buf;
    employee emp;
	ifstream input(filename, ios_base::binary);
	while(input.read((char*)&emp.num, sizeof(emp.num))) {		
		input.read((char*)&emp.name, sizeof(emp.name));
		input.read((char*)&emp.hours, sizeof(emp.hours));
		buf.push_back(emp);
	}
	return buf;
}
bool comp( employee a, employee b) {
	return a.num<b.num;
}
void writeReport(wstring path, vector<employee> vec,double pricePerHour,wstring binName) {
    ofstream out;
    out.open(path);
	sort(vec.begin(), vec.end(), comp);
    string buf(binName.begin(), binName.end());
    out << " Отчет по файлу " + buf+ "\n";
    for (int i = 0; i < vec.size(); i++) {
        out << to_string(vec[i].num) + " " + vec[i].name + " " + to_string(vec[i].hours) + " " + to_string(vec[i].hours * pricePerHour) + "\n";
    }
    out.close();
}
int WINAPI WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst, LPSTR lpszArgs, int nWinMode) {
    LPWSTR* argv;
    setlocale(LC_ALL, "rus");
    int argc;
    wstring str = GetCommandLineW();
    TCHAR* s = new TCHAR[str.length() + 1];
    wcscpy(s, str.c_str());
    wchar_t* ptr = wcstok(s, L" ");
    wstring binName = ptr;
    ptr = wcstok(NULL, L" ");
    wstring reportName = ptr;
    ptr = wcstok(NULL, L" ");
    int pricePerHour = stoi(ptr);
    vector<employee> emps;
    emps = readBinFile(binName);
   writeReport(reportName,emps,pricePerHour, binName);
    return 0;
}