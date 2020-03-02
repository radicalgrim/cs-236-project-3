#include "Token.h"

Token::Token() {
	type = UNDEFINED;
	value = "";
	lineNum = 1;
}

Token::Token(int n) {
	type = UNDEFINED;
	value = "";
	lineNum = n;
}

Token::Token(TokenType T, string v, int n) {
	type = T;
	value = v;
	lineNum = n;
}

string Token::TokenTypeToString(TokenType type)
{
	switch (type) {
		case COMMA: return "COMMA"; break;
		case PERIOD: return "PERIOD"; break;
		case Q_MARK: return "Q_MARK"; break;
		case LEFT_PAREN: return "LEFT_PAREN"; break;
		case RIGHT_PAREN: return "RIGHT_PAREN"; break;
		case COLON: return "COLON"; break;
		case COLON_DASH: return "COLON_DASH"; break;
		case MULTIPLY: return "MULTIPLY"; break;
		case ADD: return "ADD"; break;
		case SCHEMES: return "SCHEMES"; break;
		case FACTS: return "FACTS"; break;
		case RULES: return "RULES"; break;
		case QUERIES: return "QUERIES"; break;
		case ID: return "ID"; break;
		case STRING: return "STRING"; break;
		case COMMENT: return "COMMENT";	break;
		case UNDEFINED: return "UNDEFINED";	break;
		case END_OF_FILE: return "EOF";	break;
	}
	return "ERROR"; // a string MUST be returned by the end
}

string Token::ToString()
{
	string output;
	output = "(" + TokenTypeToString(type) + ",\"" + value + "\","
		+ to_string(lineNum) + ")";
	return output;
}

TokenType Token::GetType() {
	return type;
}

string Token::GetValue() {
	return value;
}

int Token::GetLineNum() {
	return lineNum;
}

void Token::SetType(TokenType t) {
	type = t;
}

void Token::SetValue(string v) {
	value = v;
}

void Token::SetLineNum(int ln) {
	lineNum = ln;
}
