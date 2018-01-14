#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "PatternRecognizer.cpp"
using namespace std;

string Date[10000];
string Time[10000];
double Open[10000];
double High[10000];
double Low[10000];
double Close[10000];
double Volume[10000];


void readGraphHistory(string filename) {
	ifstream file(filename);
	string line;
	int i = 0;
	while (file.good()) {
		getline(file, line, ',');
		Date[i] = line;

		getline(file, line, ',');
		Time[i] = line;

		getline(file, line, ',');
		Open[i] = atof(line.c_str());

		getline(file, line, ',');
		High[i] = atof(line.c_str());

		getline(file, line, ',');
		Low[i] = atof(line.c_str());

		getline(file, line, ',');
		Close[i] = atof(line.c_str());

		getline(file, line, '\n');
		Volume[i] = atof(line.c_str());

		i++;
	}
}


int main() {
	readGraphHistory("USDJPYm60.csv");

	PatternRecognizer P;
	P.passBarValues(Date, Time, Open, High, Low, Close, Volume);
	P.detectPattern();

	return 0;
}
