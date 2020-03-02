#pragma once
#include <cctype>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "Token.h"

using namespace std;

class Scanner
{
private:
	string file;
	vector<Token> tokenList;
	Token currToken;
	int index;
	int newLineCount;
	ifstream inpStream;
	char ch;
	void SetToken(TokenType T);
	bool CheckNewLine();
	bool ScanWhiteSpace();
	void ScanPunctuation();
	void ScanString();
	void ScanComment();
	void ScanID();
	void ScanEOF();
	void PrintTokens();
public:
	Scanner();
	Scanner(string inpFile);
	void Scan(string inpFile);
	vector<Token> GetTokenList();
};
