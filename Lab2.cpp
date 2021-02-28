#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include<fstream>
#include <windows.h>
#include <tchar.h>
#include<vector>



using namespace std;
struct toThread {
	vector<int> mas;
	int numbers[5];
};
LPWSTR ConvertString(const std::string& instr)
{
int bufferlen = ::MultiByteToWideChar(CP_ACP, 0, instr.c_str(), instr.size(), NULL, 0);
	if (bufferlen == 0)
	{	
		return 0;
	}
	LPWSTR widestr = new WCHAR[bufferlen + 1];
	::MultiByteToWideChar(CP_ACP, 0, instr.c_str(), instr.size(), widestr, bufferlen);
	widestr[bufferlen] = 0;
	return widestr;
}
DWORD WINAPI average(LPVOID lpParam)
{
	toThread* buf = (toThread*)lpParam;
	vector<int> mas;
	mas = buf->mas;
	int sum = 0;
	for (int i = 0; i < mas.size(); i++) {
		sum += mas[i];
		Sleep(12);
	}
	buf->numbers[0] = sum/mas.size();
	return 0;
}
DWORD WINAPI min_max(LPVOID lpParam)
{
	toThread* buf = (toThread*)lpParam;
	vector<int> mas;
	mas = buf->mas;
	int min = mas[0];
	int max = mas[0];
	for (int i = 1; i < mas.size(); i++) {
		if (mas[i] > max) {
			Sleep(7);
			max = mas[i];
		}
		if (mas[i]< min) {
			Sleep(7);
			min = mas[i];
		}
	}
	buf->numbers[0] = min;
	buf->numbers[1] = max;
	return 0;
}

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "Введите размер массива ";
	int size;
	cin >> size;
	vector<int> mas;
	for (int i = 0; i < size; i++) {
		int buf;
		cout << "Введите число " + to_string(i + 1) << endl;
		cin >> buf;
		mas.push_back(buf);
	}
	toThread* toMinMaxThr=new toThread();
	toMinMaxThr->mas = mas;
	toThread* toAverageThr = new toThread();
	toAverageThr->mas = mas;
	DWORD dwThreadId, dwThreadId2;
	HANDLE hThread1 = CreateThread(
		NULL,         // атрибуты безопасности по умолчанию
		0,            // размер стека используется по умолчанию
		min_max,   // функция потока
		toMinMaxThr, // аргумент функции потока
		0,            // флажки создания используются по умолчанию
		&dwThreadId);
	HANDLE hThread2 = CreateThread(
		NULL,         // атрибуты безопасности по умолчанию
		0,            // размер стека используется по умолчанию
		average,   // функция потока
		toAverageThr, // аргумент функции потока
		0,            // флажки создания используются по умолчанию
		&dwThreadId2);
	WaitForSingleObject(hThread1, INFINITE);
	WaitForSingleObject(hThread2, INFINITE);
	cout << endl << "min= " + to_string(toMinMaxThr->numbers[0]) + " max= " + to_string(toMinMaxThr->numbers[1]) << endl;
	cout << "average= " + to_string(toAverageThr->numbers[0]) << endl <<endl<< "mas:" << endl;
	for (int i = 0; i < mas.size(); i++) {
		if (mas[i] == toMinMaxThr->numbers[0] || mas[i] == toMinMaxThr->numbers[1]) {
			mas[i] = toAverageThr->numbers[0];
		}
		cout << to_string(mas[i])+" ";
	}	
	system("pause");
	return 0;
}