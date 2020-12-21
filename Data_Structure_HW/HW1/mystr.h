#ifndef MYSTR_H
#define MYSTR_H
using namespace std;
class Mystring {
private:char* string;
	   int len;
public:
	Mystring(const char*);
	bool operator == (const Mystring&);
	Mystring& operator = (const Mystring&);
	Mystring operator *(const Mystring&);
	Mystring operator +(const Mystring&);
	friend ostream& operator <<(ostream&, const Mystring&);
	~Mystring();
};
#endif