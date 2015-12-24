//	CollatzConjecture.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//
//	Load dependencies
//
#include <iostream>
#include <windows.h> 
#include <string>
#include <fstream>


using namespace std;
//
// Create global variables
//
unsigned long long number = 1;
unsigned long long max = 0;
unsigned long long maxat = 0;

bool isEven(unsigned long long integer)
{

	if (integer % 2 == 0)
		return true;
	else
		return false;
}

unsigned long long doCollatz(unsigned long long start)
{
	unsigned long long current = start;
	unsigned long long steps = 0;
	while (current != 1)
	{
		if (isEven(current))
		{
			current = current / 2; // Even / 2
		}
		else
		{
			current = 3 * current + 1; // Odd * 3 + 1
		}
		steps++;
	}
	return steps;
}
void ctrlchandler(int s){
	ofstream file("ln.txt");
	if (file.is_open())
	{
		file << number << endl << max << endl << maxat; // Save current position and maximum value in save file
	}
	else
	{
		cout << "error accessing ln.txt!";
	}
	file.close();
}
int _tmain(int argc, _TCHAR* argv[])
{
	SetConsoleCtrlHandler((PHANDLER_ROUTINE)ctrlchandler, TRUE);
	cout << "starting at ";

	ifstream file("ln.txt"); //load save file
	if (file.is_open() && file.good())
	{
		char j[] ="";
		string i;
		getline(file, i);
		strcpy(j, i.c_str()); // Unsafe, consider changing!
		number = strtoull(j, nullptr, 10);
		getline(file, i);
		strcpy(j, i.c_str()); // Unsafe, consider changing!
		max = strtoull(j, nullptr, 10);
		getline(file, i);
		strcpy(j, i.c_str()); // Unsafe, consider changing!
		maxat = strtoull(j, nullptr, 10);
		cout << number << " with current maximum at "<< maxat << " with value " << max << endl;
	}
	else
	{
		cout << "starting position" << endl;
	}
	file.close();
	//
	//	Start loop
	//
	while (true) {
		unsigned long long a = doCollatz(number);
		if (a > max) // If amount of steps higher than the highest previous one
		{
			// Save to save file
			max = a;
			maxat = number;
			cout << "New longest at " << maxat << " with length of " << max << endl;
			ofstream file("ln.txt");
			if (file.is_open())
			{
				file << maxat << endl << max << endl << maxat;
			}
			else
			{
				cout << "error accessing ln.txt!";
				break;
			}
			file.close();
			// Append to record history
			ofstream filer("results.txt", ios_base::app);
			if (filer.is_open())
			{
				filer << "new record: " << endl << "  length: " << max << endl << "  position: " << maxat << endl << "----------------" << endl;
			}
			else
			{
				cout << "error accessing results.txt!";
				break;
			}
			filer.close();
		}
		number++;
	}
	return 0;
}

