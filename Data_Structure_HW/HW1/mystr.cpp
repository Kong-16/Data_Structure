#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include "mystr.h"

using namespace std;
Mystring::Mystring(const char* str = "default") {
	len = strlen(str);
	string = new char[len+1];
	strcpy(string, str);
}
bool Mystring::operator ==(const Mystring& str) {
	int isSame;
	isSame = strcmp(string, str.string);
	if (isSame == 0) 
		return true;
	else
		return false;
}
Mystring& Mystring::operator =(const Mystring& str) {
	delete[] string;
	len = str.len;
	string = new char[len+1];
	strcpy(string, str.string); 
	return *this;
}

Mystring Mystring ::operator *(const Mystring& str) {
	int newlen = len + str.len;
	char* tmp = new char[newlen + 1];
	memset(tmp, '\0', newlen + 1);
	if (len > str.len) {
		for (int i = 0; i < str.len; i++) { 
			tmp[2 * i] = string[i];
			tmp[2 * i + 1] = str.string[i];
		}
		for (int i = 2*str.len; i < newlen; i++) {
			tmp[i] = string[i-str.len];
		}
	}
	else {
		for (int i = 0; i < len; i++) {
			tmp[2 * i] = string[i];
			tmp[2 * i + 1] = str.string[i];
		}
		for (int i = 2 * len; i < newlen; i++) {
				tmp[i] = str.string[i-len];
		}
	}
	Mystring* newString = new Mystring(tmp);
	delete[]tmp;
	return *newString;
}

Mystring Mystring::operator +(const Mystring& str) {
		char* tmp = new char[len + str.len +1];
		strcpy(tmp, string);
		strcat(tmp, str.string);
		Mystring* newString =new Mystring(tmp);
		delete[]tmp;
		return *newString;
}
ostream& operator <<(ostream& out, const Mystring& str) {
	out << str.string;
	return out;
}

Mystring::~Mystring() {delete[] string; }