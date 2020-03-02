#include "Scanner.h"


Scanner::Scanner() : file(), tokenList(), index(0), newLineCount(1) {}


Scanner::Scanner(string inpFile) {
  file = inpFile;
  index = 0;
  newLineCount = 1;
}


vector<Token> Scanner::GetTokenList() {
    return tokenList;
}


void Scanner::SetToken(TokenType T) {
  string output;
  output += ch;
  tokenList[index].SetType(T);
  tokenList[index].SetValue(output);
}


bool Scanner::CheckNewLine() {
  if (ch == '\n') {
    newLineCount++;
    tokenList[index].SetLineNum(newLineCount);
    return true;
  }
  return false;
}


bool Scanner::ScanWhiteSpace() {
  if (isspace(ch)) {
    CheckNewLine();
    ch = inpStream.get();
    return true;
  }
  return false;
}


void Scanner::ScanPunctuation() {
  if (ch == '(')
    SetToken(LEFT_PAREN);
  else if (ch == ')')
    SetToken(RIGHT_PAREN);
  else if (ch == '?')
    SetToken(Q_MARK);
  else if (ch == '*')
    SetToken(MULTIPLY);
  else if (ch == '+')
    SetToken(ADD);
  else if (ch == ',')
    SetToken(COMMA);
  else if (ch == '.')
    SetToken(PERIOD);
  else if (ch == ':') {
    if (inpStream.peek() == '-') {
      tokenList[index].SetType(COLON_DASH);
      tokenList[index].SetValue(":-");
      ch = inpStream.get();
      return;
    }
    else
      SetToken(COLON);
  }
  else if (ch == '\'')
    ScanString();
  else if (ch == '#')
    ScanComment();
  else
    SetToken(UNDEFINED);
}


void Scanner::ScanString() {
  int strNL = 0;
  string output;
  output += ch;
  ch = inpStream.get();

  while (ch != EOF) {
    if (CheckNewLine()) {
      newLineCount--;
      strNL++;
    }
    if (ch == '\'') {
      if (inpStream.peek() != '\'')
        break;
      else {
        output += ch;
        ch = inpStream.get();
        output += ch;
        ch = inpStream.get();
        continue;
      }
    }
    if (inpStream.peek() == EOF) {
      output += '\n';
      tokenList[index].SetType(UNDEFINED);
      tokenList[index].SetValue(output);
      tokenList[index].SetLineNum(newLineCount);
      newLineCount = newLineCount + strNL;
      newLineCount--;
      return;
    }

    output += ch;
    ch = inpStream.get();
  }

  output += ch;

  tokenList[index].SetType(STRING);
  tokenList[index].SetValue(output);
  tokenList[index].SetLineNum(newLineCount);
  newLineCount = newLineCount + strNL;
}


void Scanner::ScanComment() {
  int strNL = 0;

  if (inpStream.peek() == '|') {
    while (ch != '|' || inpStream.peek() != '#') {
      if (CheckNewLine()) {
        newLineCount--;
        strNL++;
      }
      if (inpStream.eof()) {
        tokenList[index].SetType(UNDEFINED);
        tokenList[index].SetLineNum(newLineCount);
        newLineCount = newLineCount + strNL;
        newLineCount--;
        return;
      }
      ch = inpStream.get();
    }
    ch = inpStream.get();
  }
  else {
    ch = inpStream.get();
    while (inpStream.peek() != '\n') {
      ch = inpStream.get();
    }
  }

  tokenList.erase(tokenList.end() - 1);
  newLineCount = newLineCount + strNL;
}


void Scanner::ScanID() {

  string output;

  while (isalnum(inpStream.peek())) {
    output += ch;
    ch = inpStream.get();
  }

  output += ch;

  if (output == "Schemes") {
    tokenList[index].SetType(SCHEMES);
    tokenList[index].SetValue(output);
  }
  else if (output == "Facts") {
    tokenList[index].SetType(FACTS);
    tokenList[index].SetValue(output);
  }
  else if (output == "Rules") {
    tokenList[index].SetType(RULES);
    tokenList[index].SetValue(output);;
  }
  else if (output == "Queries") {
    tokenList[index].SetType(QUERIES);
    tokenList[index].SetValue(output);
  }
  else {
    tokenList[index].SetType(ID);
    tokenList[index].SetValue(output);
  }

}


void Scanner::ScanEOF() {

  if (newLineCount != 1) {
      newLineCount++;
  }
  index = tokenList.size() - 1;
  tokenList[index].SetType(END_OF_FILE);
  tokenList[index].SetValue("");
  tokenList[index].SetLineNum(newLineCount);
}


void Scanner::PrintTokens() {

  for (size_t i = 0; i < tokenList.size(); i++) {
    cout << tokenList[i].ToString() << endl;
  }

  cout << "Total Tokens = " << tokenList.size() << endl;
}


void Scanner::Scan(string inpFile) {

  inpStream.open(inpFile);

  ch = inpStream.get();
  currToken = Token(newLineCount);
  tokenList.push_back(currToken);

  while (inpStream.peek() != EOF) {

    if (ScanWhiteSpace())
      continue;

    if (ispunct(ch))
      ScanPunctuation();
    else if (isalpha(ch))
      ScanID();
    else {

      SetToken(UNDEFINED);
    }

    ch = inpStream.get();
    currToken = Token(newLineCount);
    tokenList.push_back(currToken);
    index = tokenList.size() - 1;

  }

	if (ch == '?') {
		index = tokenList.size() - 1;
		tokenList[index].SetType(Q_MARK);
		tokenList[index].SetValue("?");
		tokenList[index].SetLineNum(newLineCount);

		currToken = Token(newLineCount);
		tokenList.push_back(currToken);
	}

  ScanEOF();


  inpStream.close();

  //PrintTokens();
}
