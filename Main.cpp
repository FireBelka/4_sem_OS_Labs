#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include<fstream>
#include <windows.h>
#include <tchar.h>
#include<vector>



using namespace std;
struct employee
{
	int num; 
	char name[10]; 
	double hours;
};
vector<employee> readBinFile(string filename,int count_of_lines) {
	vector<employee> buf;
	ifstream input(filename, ios_base::binary);
	for (int i = 0; i < count_of_lines; i++) {
		employee emp;
		input.read((char*)&emp.num, sizeof(emp.num));
		input.read((char*)&emp.name, sizeof(emp.name));
		input.read((char*)&emp.hours, sizeof(emp.hours));
		
		buf.push_back(emp);
	}
	return buf;
}
LPWSTR ConvertString(const std::string& instr)
{
	// Assumes std::string is encoded in the current Windows ANSI codepage
	int bufferlen = ::MultiByteToWideChar(CP_ACP, 0, instr.c_str(), instr.size(), NULL, 0);

	if (bufferlen == 0)
	{
		// Something went wrong. Perhaps, check GetLastError() and log.
		return 0;
	}

	// Allocate new LPWSTR - must deallocate it later
	LPWSTR widestr = new WCHAR[bufferlen + 1];

	::MultiByteToWideChar(CP_ACP, 0, instr.c_str(), instr.size(), widestr, bufferlen);

	// Ensure wide string is null terminated
	widestr[bufferlen] = 0;

	// Do something with widestr
	return widestr;
	//delete[] widestr;
}
int main()
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	setlocale(LC_ALL, "rus");
    cout << "Введите имя бинарного файла"<<endl;
	string binFileName;
	cin >> binFileName;
	cout << "Введите количество записей в бинарном файле" << endl;
	string countOfBlocks;
	cin >> countOfBlocks;

	string CommandLine =   binFileName + " "+countOfBlocks;
	LPCTSTR cmdProg = _tcsdup(TEXT("Util_1_4.exe"));
	wstring wstr(CommandLine.begin(),CommandLine.end());
	LPWSTR cmdArgs=ConvertString(CommandLine);
	
	if (CreateProcessW(cmdProg,cmdArgs,	NULL,NULL,FALSE,0,NULL,	NULL,&si,&pi))
	{
		WaitForSingleObject(pi.hProcess, INFINITE);
	}
	else {
		cout << "Process Util_1 crushed";
	}
	WaitForSingleObject(pi.hProcess, INFINITE);
	vector<employee> buf = readBinFile(binFileName, atoi(countOfBlocks.c_str()));
	for (int i = 0; i < buf.size(); i++) {
		cout << to_string(buf[i].num) + " " + (string)buf[i].name + " " + to_string(buf[i].hours) << endl;
	}
	string reportName;
	cout << "Введите название файла отчета" << endl;
	cin >> reportName;
	double pricePerHour;
	cout << "Введите зп за час" << endl;
	cin >> pricePerHour;
	cmdProg = _tcsdup(TEXT("Util_2.exe"));
	CommandLine = binFileName + " " + reportName+" "+to_string(pricePerHour);
	wstring wstr1(CommandLine.begin(), CommandLine.end());
	 cmdArgs = ConvertString(CommandLine);
	 STARTUPINFO si1;
	 PROCESS_INFORMATION pi1;
	 ZeroMemory(&si1, sizeof(si1));
	 si1.cb = sizeof(si1);
	 ZeroMemory(&pi1, sizeof(pi1));
	 if (CreateProcessW(cmdProg, cmdArgs, NULL, NULL, FALSE, 0, NULL, NULL, &si1, &pi1))
	 {
		 WaitForSingleObject(pi1.hProcess, INFINITE);
	 }
	 else {
		 cout << "Process Util_2 crushed";
	 }
	 WaitForSingleObject(pi1.hProcess, INFINITE);
	 cout << endl << "Success!" << endl;
	 system("pause");
	 return 0;
}