#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include<fstream>
#include <windows.h>
#include <tchar.h>
#include<vector>
#include<thread>
#include <mutex>
#include <exception>
using namespace std;
int* mas;
int MasSize;
vector<bool> masOfStates;
int countOfThreads;
condition_variable condition;
mutex mt;
int numbToEnd = -1;
bool consistMetk(vector<int> vec, int a) {
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i] == a) {
			return true;
		}
	}
	return false;
}
bool checkAllThreadsStop() {
	for (int i = 0; i < countOfThreads; i++) {
		if (masOfStates[i] == true) {
			return false;
		}
	}
	return true;
}
void FThread(int x) {
	srand(x);
	vector<int> metki;
	while (true) {
		unique_lock<mutex> ul(mt);
		if (numbToEnd == x) {
			masOfStates[x] = false;
			for (int i = 0; i < metki.size(); i++) {
				mas[metki[i]] = 0;
			}
			countOfThreads--;
			condition.notify_all();
			ul.unlock();
			return;
		}
		
		
		int ch = rand()%(MasSize-1);
		
		
		if (mas[ch] == 0) {
			Sleep(5);
			mas[ch] = x+1;
			if (!consistMetk(metki, ch)) {
				metki.push_back(ch);
				//cout << "Ch[" + to_string(x) + "]=" << ch << endl;
			}
			Sleep(5);
			//cout << "Ch["+to_string(x)+"]=" << ch << endl;
		}
		else {
			masOfStates[x] = false;
			cout << "Thread #" << x << endl;
			for (int i = 0; i < metki.size(); i++) {
				cout << metki[i] << " ";
			}
			cout << endl << MasSize + 1 << endl;
			condition.notify_all();
			condition.wait(ul, [=]() {return masOfStates[x] == true; });
			}
		ul.unlock();
	}
}
bool allThreadsEnded(bool* mas, int size) {
	for (int i = 0; i < size; i++) {
		if (mas[i] == true) {
			return false;
		}
	}
	return true;
}
int main(void) {

	setlocale(LC_ALL, "rus");
	cout << "Введите размер массива" << endl;
	cin >> MasSize;
	mas = new int[MasSize];
	for (int i = 0; i < MasSize; i++) {
		mas[i] = 0;
	}
	cout << "Введите количество потоков maker" << endl;
	cin >> countOfThreads;

	vector<thread> Threads;
	for (int i = 0; i < countOfThreads; i++) {
		Threads.push_back(thread(&FThread, i));
		masOfStates.push_back(true);
	}
	for (int i = 0; i < countOfThreads; i++) {
		Threads[i].detach();

	}
	vector<int> endedThreads;
	while (countOfThreads > 0) {
		unique_lock<mutex> ul(mt);
		condition.wait(ul, [=]() {return checkAllThreadsStop(); });

		cout << "mas: ";
		for (int i = 0; i < MasSize; i++) {
			cout << mas[i] << " ";
		}
		cout << "Номер потока для завершения: " << endl;
		int numb;
		cin >> numb;	
		if (numb >= Threads.size()) {
			numb = 0;
		}
		endedThreads.push_back(numb);
		masOfStates[numb] = true;
		numbToEnd = numb;
		for (int i = 0; i < countOfThreads; i++) {
			if (!consistMetk(endedThreads, i)) {
				masOfStates[i] = true;
			}
		}
		condition.wait(ul, [=]() {return checkAllThreadsStop(); });
		condition.notify_all();
		ul.unlock();

	}


	return 0;
}