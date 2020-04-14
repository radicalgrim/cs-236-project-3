#pragma once
#include "DatalogProgram.h"
#include "Database.h"
#include "Graph.h"

class Interpreter {
private:
	DatalogProgram program;
	Database database;
	Relation relationTemp;
	Scheme schemeTemp;
	Tuple tupleTemp;
	Graph forwardGraph;
	Graph reverseGraph;
	void SchemeInterpreter();
	void FactInterpreter();
	void RuleInterpreter();
	void BuildDependencyGraphs(vector<Rule> ruleList);
	void BuildGraphNodes(vector<Rule> ruleList);
	void BuildGraphEdges(vector<Rule> ruleList);
	void PrintDependencyGraph();
	void FindSCCs();
	void EvaluateSCCs();
	void PrintComponent(set<int> component);
	void EvaluateRule(Rule rule);
	vector<int> ConstructColumnList(vector<Parameter> headScheme, vector<string> relationScheme);
	void PrintRule(Rule rule);
	void EvaluatePredicate(Predicate predicate);
	void SelectSpecificValue(int index, string value);
	void SelectMatchingColumns(int index_1, int index_2);
	void Project(vector<int> indexList);
	void Rename(vector<string> nameList);
	void Join(Relation relation_1, Relation relation_2);
	Scheme CombineSchemes(Scheme scheme_1, Scheme scheme_2);
	bool Joinable(Tuple tuple_1, Tuple tuple_2, Scheme scheme_1, Scheme scheme_2);
	Tuple CombineTuples(Tuple tuple_1, Tuple tuple_2, Scheme scheme_1, Scheme scheme_2);
	void UniteWithDatabase(Relation joinedRelation);
	void QueryInterpreter();
	void PrintQuery(Predicate predicate);
public:
	Interpreter();
	Interpreter(DatalogProgram dp);
	void Interpret();
};
