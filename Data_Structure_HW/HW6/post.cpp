#include <iostream>
#include <stack>
#include "post.h"
using namespace std;
bool Token::operator==(char b) { return len == 1 && str[0] == b; }
bool Token::operator!=(char b) { return len != 1 || str[0] != b; }
Token::Token() {}
Token::Token(char c) : len(1), type(c)
{
	str = new char[1];
	str[0] = c;
} // default type = c itself
Token::Token(char c, char c2, int ty) : len(2), type(ty)
{
	str = new char[2];
	str[0] = c;
	str[1] = c2;
}
Token::Token(char* arr, int l, int ty = ID) : len(l), type(ty)
{
	str = new char[len + 1];
	for (int i = 0; i < len; i++) str[i] = arr[i];
	str[len] = '\0';
	if (type == NUM)
	{
		ival = arr[0] - '0';
		for (int i = 1; i < len; i++) ival = ival * 10 + arr[i] - '0';
	}
	else if (type == ID) ival = 0;
	else throw "must be ID or NUM";
}
bool Token::IsOperand()
{
	return type == ID || type == NUM;
}
ostream& operator<<(ostream& os, Token t) {
	if (t.type == UMINUS) os << "-u";
	else if (t.type == NUM) os << t.ival;
	else for (int i = 0; i < t.len; i++) os << t.str[i];
	os << " ";
	return os;
}
bool GetID(Expression& e, Token& tok) {
	char arr[MAXLEN]; int idlen = 0;
	char c = e.str[e.pos];
	if (!(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')) return false;
	arr[idlen++] = c;
	e.pos++;
	while ((c = e.str[e.pos]) >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0' && c <= '9')
	{
		arr[idlen++] = c; e.pos++;
	}
	arr[idlen] = '\0';
	tok = Token(arr, idlen, ID); // return an ID
	return true;
}
bool GetInt(Expression& e, Token& tok)
{
	char arr[MAXLEN]; int idlen = 0;
	char c = e.str[e.pos];
	if (!(c >= '0' && c <= '9')) return false;
	arr[idlen++] = c;
	e.pos++;
	while ((c = e.str[e.pos]) >= '0' && c <= '9')
	{
		arr[idlen++] = c; e.pos++;
	}
	arr[idlen] = '\0';
	tok = Token(arr, idlen, NUM); // return an NUM
	return true;
}
void SkipBlanks(Expression& e) {
	char c;
	while (e.pos < e.len && ((c = e.str[e.pos]) == ' ' || c == '\t'))
		e.pos++;
}
bool TwoCharOp(Expression& e, Token& tok) {
	// 7가지 두글자 토큰들 <= >= == != && || -u을 처리
	char c = e.str[e.pos]; char c2 = e.str[e.pos + 1];
	int op; // LE GE EQ NE AND OR UMINUS
	if (c == '<' && c2 == '=') op = LE;
	else if (c == '>' && c2 == '=') op = GE; // .각 두글자 토큰에 대해 알맞은 type값을 op에 저장
	else if (c == '=' && c2 == '=') op = EQ;
	else if (c == '!' && c2 == '=') op = NE;
	else if (c == '&' && c2 == '&') op = AND;
	else if (c == '|' && c2 == '|') op = OR;
	else if (c == '-' && c2 == 'u') op = UMINUS;
	else return false; // 맞는 두글자 토큰이 아니면 false를 return
	tok = Token(c, c2, op); e.pos += 2;
	return true;
}
bool OneCharOp(Expression& e, Token& tok) {
	char c = e.str[e.pos];
	if (c == '-' || c == '!' || c == '*' || c == '/' || c == '%' ||
		c == '+' || c == '<' || c == '>' || c == '(' || c == ')' || c == '=')
	{
		tok = Token(c); e.pos++; return true;
	}
	return false;
}


Token NextToken(Expression& e) {
	static bool oprrFound = true; // 종전에 연산자 발견되었다고 가정.
	Token tok;
	SkipBlanks(e); // skip blanks if any
	if (e.pos == e.len) // No more token left in this expression
	{
		return Token('#');
	}
	if (GetID(e, tok) || GetInt(e, tok))
	{
		oprrFound = false;
		return tok;
	}
	if (TwoCharOp(e, tok) || OneCharOp(e, tok)) {
		if (tok.type == '-' && oprrFound) //operator후 -발견
			tok = Token('-', 'u', UMINUS); // unary minus(-u)로바꾸시오
		oprrFound = true;
		return tok;
	}
	throw "Illegal Character Found";
}
int icp(Token& t) { // in-coming priority
	int ty = t.type;
	switch (ty) {
	case '(' :
		return 0;
	case UMINUS: case '!' :
		return 1;
	case '*' : case '/' :
	case '%' :
		return 2;
	case '+' : case '-' :
		return 3;
	case '<' : case '>' :
	case LE: case GE:
		return 4;
	case EQ: case NE :
		return 5;
	case AND:
		return 6;
	case OR:
		return 7;
	case '=':
		return 8;
	case '#':
		return 10;
	}

}
int isp(Token& t) // in-stack priority
{
	int ty = t.type;
	if (ty == '(') return 9;
	else return icp(t);
}
void Postfix(Expression e)
{
	stack<Token> stack;
	stack.push('#');
	for (Token x = NextToken(e); x != '#'; x = NextToken(e))
		if (x.IsOperand())cout << x;
		else if (x == ')') {
			for (; stack.top() != '('; stack.pop())
				cout << stack.top();
			stack.pop();
		}
		else { // operator 일 때
			for (; isp(stack.top()) <= icp(x); stack.pop()) {//우선순위 높으면 이전 스택 모두 pop 한 뒤 새 operator push
				if (x == '=' && stack.top() == '=') break;
				cout << stack.top();
			}
			stack.push(x);
		}
	for (; stack.top() != '#'; cout << stack.top(), stack.pop());
	stack.pop();
	cout << endl;
}