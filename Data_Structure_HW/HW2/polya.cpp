#include <iostream>
#include "polya.h"
using namespace std;

istream& operator>> (istream& is, Polynomial& p) {
    // #terms and (coefficoent, exponent)�� pair���� �о���δ�.
    // ���������� �׺��� ����Ǿ��ٰ� �����Ѵ�.
    int noofterms; float coef; int exp;
    is >> noofterms;
    for (int i = 0; i < noofterms; i++) {
        is >> coef >> exp; // ����� ���� pair�� �о���δ�.
        p.NewTerm(coef, exp);
    }
    return is;
}

ostream& operator<< (ostream& os, Polynomial& p) {
    if (p.termArray[0].coef < 0) { //ù ���� ��� +�� ǥ����������
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
    {//termArray�� ũ�⸦ �� ��� Ȯ��
        capacity *= 2;
        Term* temp = new Term[capacity]; // ���ο� �迭
        copy(termArray, termArray + terms, temp);
        delete[] termArray; // ���� �޸𸮸� ��ȯ
        termArray = temp;
    }
    termArray[terms].coef = theCoeff;
    termArray[terms++].exp = theExp;
}
Polynomial Polynomial::operator+(Polynomial& b)
{
    Polynomial c; // ���� ����
    int aPos = 0, bPos = 0;
    while ((aPos < terms) && (bPos < b.terms)) //�ϳ��� ���׽��� ��� ���� ���� �� ����
        if (termArray[aPos].exp == b.termArray[bPos].exp) { //������ ���� �� ������� ����
            float t = termArray[aPos].coef + b.termArray[bPos].coef;
            if (t) c.NewTerm(t, termArray[aPos].exp); //t�� 0�϶��� ���� ����.
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
    // ���� �� ���� ����
    for (; aPos < terms; aPos++)
        c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
    for (; bPos < b.terms; bPos++)
        c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
    return c;
}