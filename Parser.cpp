#include "Parser.h"

Parser::Parser() {
  count = 0;
}

Parser::Parser(vector<Token> list) {
  count = 0;
  tokenList = list;
}


DatalogProgram Parser::Parse() {
  try {

    DatalogProgramParse();
		cout << "Success!" << endl;
    //cout << program.toString();

  } catch (Token error) {
    cout << "Failure!" << endl << "  " << error.ToString() << endl;
  }

  return program;
}


void Parser::DatalogProgramParse() {
  Match(SCHEMES);
  Match(COLON);
  SchemeParse();
  SchemeListParse();

  program.SetSchemeList(predicateList);
  vector<Predicate>().swap(predicateList);

  Match(FACTS);
  Match(COLON);
  FactListParse();

  program.SetFactList(predicateList);
  vector<Predicate>().swap(predicateList);

  Match(RULES);
  Match(COLON);
  RuleListParse();

  program.SetRuleList(ruleList);

  Match(QUERIES);
  Match(COLON);
  QueryParse();
  QueryListParse();

  program.SetQueryList(predicateList);
  vector<Predicate>().swap(predicateList);

  Match(END_OF_FILE);

}


void Parser::SchemeListParse() {
  if (tokenList[count].GetType() == ID) {
    SchemeParse();
    SchemeListParse();
  }
}


void Parser::FactListParse() {
  if (tokenList[count].GetType() == ID) {
    FactParse();
    FactListParse();
  }
}


void Parser::RuleListParse() {
  if (tokenList[count].GetType() == ID) {
    RuleParse();
    RuleListParse();
  }
}


void Parser::QueryListParse() {
  if (tokenList[count].GetType() == ID) {
    QueryParse();
    QueryListParse();
  }
}


void Parser::SchemeParse() {
	name = tokenList[count].GetValue();
  predicate = Predicate(name);
	Match(ID);

  Match(LEFT_PAREN);
  expression = tokenList[count].GetValue();
  parameter = Parameter(expression);
  Match(ID);
  parameterList.push_back(parameter);
  IDListParse();
  Match(RIGHT_PAREN);

  predicate.SetParameterList(parameterList);
  predicateList.push_back(predicate);
  vector<Parameter>().swap(parameterList);
}


void Parser::FactParse() {
  name = tokenList[count].GetValue();
  predicate = Predicate(name);
  Match(ID);

  Match(LEFT_PAREN);
  expression = tokenList[count].GetValue();
  parameter = Parameter(expression);
  program.SetDomain(expression);
  Match(STRING);
  parameterList.push_back(parameter);
  StringListParse();
  Match(RIGHT_PAREN);
  Match(PERIOD);

  predicate.SetParameterList(parameterList);
  predicateList.push_back(predicate);
  vector<Parameter>().swap(parameterList);
}


void Parser::RuleParse() {
  HeadPredicateParse();
  rule = Rule(predicate);

  Match(COLON_DASH);
  PredicateParse();
  PredicateListParse();
  Match(PERIOD);

  rule.SetBodyPredicates(predicateList);
  ruleList.push_back(rule);
  vector<Predicate>().swap(predicateList);
}


void Parser::QueryParse() {
  PredicateParse();
  Match(Q_MARK);
}


void Parser::HeadPredicateParse() {
  name = tokenList[count].GetValue();
  predicate = Predicate(name);
  Match(ID);

  Match(LEFT_PAREN);
  expression = tokenList[count].GetValue();
  parameter = Parameter(expression);
  Match(ID);
  parameterList.push_back(parameter);
  IDListParse();
  Match(RIGHT_PAREN);

  predicate.SetParameterList(parameterList);
  vector<Parameter>().swap(parameterList);
}


void Parser::PredicateParse() {
  name = tokenList[count].GetValue();
  predicate = Predicate(name);

  Match(ID);

  Match(LEFT_PAREN);
  ParameterParse();
  ParameterListParse();///////////////////////////////////////////////////////
  Match(RIGHT_PAREN);

  predicate.SetParameterList(parameterList);
  predicateList.push_back(predicate);
  vector<Parameter>().swap(parameterList);
}


void Parser::PredicateListParse() {
  if (tokenList[count].GetType() == COMMA) {
    Match(COMMA);
    PredicateParse();
    PredicateListParse();
  }
}


void Parser::ParameterListParse() {
  if (tokenList[count].GetType() == COMMA) {
    Match(COMMA);
    ParameterParse();
    ParameterListParse();
  }
}


void Parser::StringListParse() {
  if (tokenList[count].GetType() == COMMA) {
    Match(COMMA);
    expression = tokenList[count].GetValue();
    parameter = Parameter(expression);
    program.SetDomain(expression);
    Match(STRING);
    parameterList.push_back(parameter);

    StringListParse();
  }
}


void Parser::IDListParse() {
  if (tokenList[count].GetType() == COMMA) {
    Match(COMMA);
    expression = tokenList[count].GetValue();
    parameter = Parameter(expression);
    Match(ID);
    parameterList.push_back(parameter);

    IDListParse();
  }
}


void Parser::ParameterParse() {
  type = tokenList[count].GetType();
  if (type == STRING || type == ID || type == LEFT_PAREN) {
    if (type == LEFT_PAREN) {
      ExpressionParse();
      parameter = Parameter(xp);
      parameterList.push_back(parameter);
    }
    else {
      expression = tokenList[count].GetValue();
      parameter = Parameter(expression);
      Match(type);
      parameterList.push_back(parameter);
      //expression = "";
    }
  }
  else {
    throw tokenList[count];
  }
}


void Parser::ExpressionParse() {
  Match(LEFT_PAREN);
  xp += "(";
  ParameterParse();
  xp += expression;
  parameterList.pop_back();
  OperatorParse();
  ParameterParse();

  if (tokenList[count + 1].GetValue() == ")") {
    xp += expression;
  }
  parameterList.pop_back();
  Match(RIGHT_PAREN);
  xp += ")";
  //expression = xp;
}


void Parser::OperatorParse() {
  type = tokenList[count].GetType();
  if (type == ADD) {
    Match(type);
    xp += "+";
  }
	else if (type == MULTIPLY) {
		Match(type);
    xp += "*";
	}
  else {
    throw tokenList[count];
  }
}


void Parser::Match(TokenType T) {
  if (T != tokenList[count].GetType()) {
    throw tokenList[count];
  }
  count++;
}
