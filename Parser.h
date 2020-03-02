#pragma once
#include <cctype>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "Token.h"
#include "Predicate.h"
#include "Parameter.h"
#include "Rule.h"
#include "DatalogProgram.h"

using namespace std;

class Parser
{
private:
	int count;
	string name;
  string expression;
	string xp;
	TokenType type;
  vector<Token> tokenList;
	Predicate predicate;
	vector<Predicate> predicateList;
	Parameter parameter;
	vector<Parameter> parameterList;
	Rule rule;
	vector<Rule> ruleList;
  DatalogProgram program;


  void DatalogProgramParse();
  void SchemeListParse();
  void FactListParse();
  void RuleListParse();
  void QueryListParse();
  void SchemeParse();
  void FactParse();
  void RuleParse();
  void QueryParse();
  void HeadPredicateParse();
  void PredicateParse();
  void PredicateListParse();
  void ParameterListParse();
  void StringListParse();
  void IDListParse();
  void ParameterParse();
  void ExpressionParse();
  void OperatorParse();
  void Match(TokenType T);


public:
  Parser();
  Parser(vector<Token> list);
  DatalogProgram Parse();
};
