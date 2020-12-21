#include <iostream>
#include "polya.h"
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