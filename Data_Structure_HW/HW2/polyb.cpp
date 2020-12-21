#include <iostream>
#include "polyb.h"
using namespace std;

istream& operator>> (istream& is, Polynomial& p) {
    // #terms and (coefficoent, exponent)의 pair들을 읽어들인다.
    // 높은차수의 항부터 저장되었다고 가정한다.
    int noofterms; float coef; int exp;
    is >> noofterms;
    for (int i = 0; i < noofterms; i++) {
        is >> coef >> exp; // 계수와 지수 pair를 읽어들인다.
        p.NewTerm(coef, exp);
    }
    return is;
}

ostream& operator<< (ostream& os, Polynomial& p) {
    if (p.termArray[0].coef < 0) { //첫 항의 경우 +는 표시하지않음
        if (p.termArray[0].coef != -1) os << p.termArray[0].coef;
        else os << '-';
    }
    else {
        if (p.termArray[0].coef != 1) os << p.termArray[0].coef;
    }
    os << 'x';
    if (p.termArray[0].exp != 1) os << '^' << p.termArray[0].exp;

    for (int i = 1; i < p.terms; i++) {
        if (p.termArray[i].coef < 0) {
            if (p.termArray[i].coef != -1) os << ' ' << p.termArray[i].coef;
            else os << ' ' << '-';
        }
        else {
            os << ' ' << '+';
            if (p.termArray[i].coef != 1) os << p.termArray[i].coef;
        }


        if (p.termArray[i].exp != 0) {
            os << 'x';
            if (p.termArray[i].exp != 1) {
                os << '^' << p.termArray[i].exp;
            }
        }
    }
    os << endl;
    return os;
}

Polynomial::Polynomial() :capacity(1), terms(0)
{
    termArray = new Term[capacity];
}
void Polynomial::NewTerm(const float theCoeff, const int theExp)
{
    if (terms == capacity)
    {//termArray의 크기를 두 배로 확장
        capacity *= 2;
        Term* temp = new Term[capacity]; // 새로운 배열
        copy(termArray, termArray + terms, temp);
        delete[] termArray; // 그전 메모리를 반환
        termArray = temp;
    }
    termArray[terms].coef = theCoeff;
    termArray[terms++].exp = theExp;
}
Polynomial Polynomial::operator+(Polynomial& b)
{
    Polynomial c; // 합을 저장
    int aPos = 0, bPos = 0;
    while ((aPos < terms) && (bPos < b.terms)) //하나의 다항식의 모든 항이 끝날 때 까지
        if (termArray[aPos].exp == b.termArray[bPos].exp) { //지수가 같을 때 계수끼리 더함
            float t = termArray[aPos].coef + b.termArray[bPos].coef;
            if (t) c.NewTerm(t, termArray[aPos].exp); //t가 0일때는 실행 안함.
            aPos++; bPos++;
        }
        else if (termArray[aPos].exp < b.termArray[bPos].exp) {
            c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
            bPos++;
        }
        else {
            c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
            aPos++;
        }
    // 남은 항 집어 넣음
    for (; aPos < terms; aPos++)
        c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
    for (; bPos < b.terms; bPos++)
        c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
    return c;
}


Polynomial Polynomial::operator/(Polynomial& b)
{
    Polynomial c;  // *this와 b의 나눗셈의 결과를 c에 저장하려고 한다.
    Polynomial a; // *this 의 사본
    for (int i = 0; i < terms; i++) {
        a.NewTerm(termArray[i].coef, termArray[i].exp);
    }
    int expDiff,cpos = 0;
    float coefDiff;
    while (a.termArray[0].exp >= b.termArray[0].exp) { //나눌 다항식의 최고차항 지수가 나누는 다항식의 최고차항 지수보다 작을 때 종료.
        Polynomial* copyb = new Polynomial; //b의 사본
        expDiff = a.termArray[0].exp - b.termArray[0].exp;
        coefDiff = a.termArray[0].coef / b.termArray[0].coef;
        c.NewTerm(coefDiff, expDiff); //지수와 계수 c에 저장.
        for (int i = 0; i < b.terms; i++) { //b의 값 복사함.
            copyb->NewTerm(b.termArray[i].coef, b.termArray[i].exp);
        }
        for (int i = 0; i < b.terms; i++) { 
            copyb->termArray[i].exp += expDiff; //지수의 차이만큼 더해서 최고차항 지수 맞춤.
            copyb->termArray[i].coef *= -coefDiff; //계수의 차이만큼 곱해서 최고차항 계수 맞추고 뺄셈 위해 역수 취함.
        }
        a = a + *copyb; // 뺄셈 진행. 최고차항은 삭제되고 나머지는 a에 다시 저장.
        delete copyb;
    }
    return c;
}


