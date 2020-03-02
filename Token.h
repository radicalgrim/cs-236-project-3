#pragma once
#include <string>
using namespace std;

enum TokenType
{
	COMMA,
	PERIOD,
	Q_MARK,
	LEFT_PAREN,
	RIGHT_PAREN,
	COLON,
	COLON_DASH,
	MULTIPLY,
	ADD,
	SCHEMES,
	FACTS,
	RULES,
	QUERIES,
	ID,
	STRING,
	COMMENT,
	UNDEFINED,
	END_OF_FILE
};

class Token
{
private:
	TokenType type;
  string value;
  int lineNum;
	string TokenTypeToString(TokenType type);
	friend class Scanner;
	friend class Parser;
public:
	Token();
	Token(int n);
	Token(TokenType T, string v, int n);
	string ToString();
	TokenType GetType();
	string GetValue();
	int GetLineNum();
	void SetType(TokenType t);
	void SetValue(string v);
	void SetLineNum(int ln);
};
