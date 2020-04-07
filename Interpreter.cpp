#include "Interpreter.h"


Interpreter::Interpreter() {
}


Interpreter::Interpreter(DatalogProgram dp) {
	program = dp;
}


void Interpreter::Interpret() {
	SchemeInterpreter();
	FactInterpreter();
	RuleInterpreter();
	QueryInterpreter();
}


void Interpreter::SchemeInterpreter() {
	for (size_t i = 0; i < program.GetSchemeList().size(); i++) {
		relationTemp = Relation(program.GetSchemeList()[i].GetName());
		schemeTemp = Scheme();
		for (size_t j = 0; j < program.GetSchemeList()[i].GetParameterList().size(); j++) {
			schemeTemp.AddAttribute(program.GetSchemeList()[i].GetParameterList()[j].GetExpression());
		}
		relationTemp.SetScheme(schemeTemp);
		database.AddRelation(relationTemp.GetName(), relationTemp);
	}
}


void Interpreter::FactInterpreter() {
	for (size_t i = 0; i < program.GetFactList().size(); i++) {
		tupleTemp = Tuple();
		for (size_t j = 0; j < program.GetFactList()[i].GetParameterList().size(); j++) {
			tupleTemp.AddValue(program.GetFactList()[i].GetParameterList()[j].GetExpression());
		}
		relationTemp = database.GetRelation(program.GetFactList()[i].GetName());
		relationTemp.AddTuple(tupleTemp);
		database.ResetRelation(relationTemp.GetName(), relationTemp);
	}
}


//void Interpreter::RuleInterpreter() {
//	cout << "Rule Evaluation" << endl;
//
//	int preCount = 0;
//	for (auto it_d : database) {
//		preCount += it_d.second.GetTupleSet().size();
//	}
//	int postCount = 0;
//	int loopCount = 0;
//	while (preCount != postCount) {
//		if (loopCount > 0) {
//			preCount = postCount;
//		}
//		for (size_t i = 0; i < program.GetRuleList().size(); i++) {
//			PrintRule(program.GetRuleList()[i]);
//			EvaluateRule(program.GetRuleList()[i]);
//		}
//		postCount = 0;
//		for (auto it_d : database) {
//			postCount += it_d.second.GetTupleSet().size();
//		}
//		loopCount++;
//	} 
//
//	cout << endl << "Schemes populated after ";
//	cout << loopCount;
//	cout << " passes through the Rules." << endl << endl;
//}


void Interpreter::RuleInterpreter() {
	BuildDependencyGraphs(program.GetRuleList());
	FindSCCs();
}


void Interpreter::BuildDependencyGraphs(vector<Rule> ruleList) {
	BuildGraphNodes(ruleList);
	BuildGraphEdges(ruleList);
	PrintDependencyGraph();
}


void Interpreter::BuildGraphNodes(vector<Rule> ruleList) {
	for (size_t i = 0; i < ruleList.size(); i++) {
		Node newNode = Node(i);
		forwardGraph.AddNode(i, newNode);
		reverseGraph.AddNode(i, newNode);
	}
}


void Interpreter::BuildGraphEdges(vector<Rule> ruleList) {
	for (size_t i = 0; i < ruleList.size(); i++) {
		for (size_t j = 0; j < ruleList[i].GetBodyPredicates().size(); j++) {
			for (size_t k = 0; k < ruleList.size(); k++) {
				if (ruleList[i].GetBodyPredicates()[j].GetName() == ruleList[k].GetHeadPredicate().GetName()) {
					forwardGraph.AddEdge(i, k);
					reverseGraph.AddEdge(k, i);
					if (i == k) {
						forwardGraph.GetNode(i).SetIsSelfDep(true);
						reverseGraph.GetNode(i).SetIsSelfDep(true);
					}
				}
			}
		}
	}
}


void Interpreter::PrintDependencyGraph() {
	cout << "Dependency Graph" << endl;
	for (auto it_n : forwardGraph.GetNodeMap()) {
		cout << "  R" << it_n.first << " :";
		for (auto it_a : it_n.second.GetAdjacentNodes()) {
			cout << " R" << it_a;
		}
		cout << endl;
	}
	cout << endl;
}


void Interpreter::FindSCCs() {
	reverseGraph.DFS_Forest();

	cout << "Reverse Topological Sort" << endl;
	while (!reverseGraph.GetPostOrderNums().empty()) {
		forwardGraph.DFS(reverseGraph.GetPostOrderNums().top());
		cout << reverseGraph.GetPostOrderNums().top() << endl;
		reverseGraph.PopPostOrderNum();
	}
	cout << endl;

	cout << "Forward Topological Sort" << endl;
	while (!forwardGraph.GetPostOrderNums().empty()) {
		cout << forwardGraph.GetPostOrderNums().top() << endl;
		forwardGraph.PopPostOrderNum();
	}
	cout << endl;
}


void Interpreter::EvaluateRule(Rule rule) {
	EvaluatePredicate(rule.GetBodyPredicates()[0]);
	Relation R1 = relationTemp;
	if (rule.GetBodyPredicates().size() > 1) {
		for (size_t i = 1; i < rule.GetBodyPredicates().size(); i++) {
			EvaluatePredicate(rule.GetBodyPredicates()[i]);
			Join(R1, relationTemp);
			R1 = relationTemp;
		}
	}
	relationTemp.SetName(rule.GetHeadPredicate().GetName());

	vector<int> columnList;
	columnList = ConstructColumnList(rule.GetHeadPredicate().GetParameterList(), relationTemp.GetScheme().GetAttributeList());
	Project(columnList);	
	UniteWithDatabase(relationTemp);
}


vector<int> Interpreter::ConstructColumnList(vector<Parameter> headScheme, vector<string> relationScheme) {
	vector<int> columnList = vector<int>();

	for (size_t i = 0; i < headScheme.size(); i++) {
		for (size_t j = 0; j < relationScheme.size(); j++) {
			if (headScheme[i].GetExpression() == relationScheme[j]) {
					columnList.push_back(j);
			}
		}
	}

	return columnList;
}


void Interpreter::PrintRule(Rule rule) {
	cout << rule.GetHeadPredicate().GetName() << "(";
	for (size_t i = 0; i < rule.GetHeadPredicate().GetParameterList().size(); i++) {
		cout << rule.GetHeadPredicate().GetParameterList()[i].GetExpression();
		if (i < rule.GetHeadPredicate().GetParameterList().size() - 1) {
			cout << ",";
		}
	}
	cout << ") :- ";

	for (size_t i = 0; i < rule.GetBodyPredicates().size(); i++) {
		cout << rule.GetBodyPredicates()[i].GetName() << "(";
		for (size_t j = 0; j < rule.GetBodyPredicates()[i].GetParameterList().size(); j++) {
			cout << rule.GetBodyPredicates()[i].GetParameterList()[j].GetExpression();
			if (j < rule.GetBodyPredicates()[i].GetParameterList().size() - 1) {
				cout << ",";
			}
		}
		if (i < rule.GetBodyPredicates().size() - 1) {
			cout << "),";
		}
	}
	cout << ")." << endl;
}


void Interpreter::EvaluatePredicate(Predicate predicate) {
	map<string, int> variableTracker = map<string, int>();
	vector<int> columnList = vector<int>();
	vector<string> nameList = vector<string>();
	relationTemp = database.GetRelation(predicate.GetName());

	for (size_t i = 0; i < predicate.GetParameterList().size(); i++) {
		string expression = predicate.GetParameterList()[i].GetExpression();

		if (predicate.GetParameterList()[i].GetConstant()) {
			SelectSpecificValue(i, expression);
		}
		else {
			if (variableTracker.count(expression) > 0) {
				SelectMatchingColumns(i, variableTracker.at(expression));
			}
			else {
				variableTracker.insert(pair<string, int>(expression, i));
				columnList.push_back(i);
				nameList.push_back(expression);
			}
		}
	}

	Project(columnList);
	Rename(nameList);
}


void Interpreter::SelectSpecificValue(int index, string value) {
	Relation newRelation = Relation(relationTemp.GetName(), relationTemp.GetScheme());
	for (auto it : relationTemp.GetTupleSet()) {
		if (it.GetValue(index) == value) {
			newRelation.AddTuple(it);
		}
	}
	relationTemp = newRelation;
}


void Interpreter::SelectMatchingColumns(int index_1, int index_2) {
	Relation newRelation = Relation(relationTemp.GetName(), relationTemp.GetScheme());
	for (auto it : relationTemp.GetTupleSet()) {
		if (it.GetValue(index_1) == it.GetValue(index_2)) {
			newRelation.AddTuple(it);
		}
	}
	relationTemp = newRelation;
}


void Interpreter::Project(vector<int> indexList) {
	Relation newRelation = Relation(relationTemp.GetName());
	Scheme newScheme = Scheme();
	for (size_t i = 0; i < indexList.size(); i++) {
		string attr = relationTemp.GetScheme().GetAttribute(indexList[i]);
		newScheme.AddAttribute(attr);
	}
	newRelation.SetScheme(newScheme);
	for (auto it : relationTemp.GetTupleSet()) {
		Tuple newTuple = Tuple();
		for (size_t i = 0; i < indexList.size(); i++) {
			string value = it.GetValue(indexList[i]); //FIX THIS
			newTuple.AddValue(value);
		}
		newRelation.AddTuple(newTuple);
	}
	relationTemp = newRelation;
}


void Interpreter::Rename(vector<string> nameList) {
	Relation newRelation = Relation(relationTemp.GetName(), relationTemp.GetTupleSet());
	Scheme newScheme = Scheme();
	for (size_t i = 0; i < nameList.size(); i++) {
		newScheme.AddAttribute(nameList[i]);
	}
	newRelation.SetScheme(newScheme);
	relationTemp = newRelation;
}


void Interpreter::Join(Relation relation_1, Relation relation_2) {
	Scheme newScheme = Scheme();
	newScheme = CombineSchemes(relation_1.GetScheme(), relation_2.GetScheme());
	Relation newRelation = Relation(relationTemp.GetName(), newScheme);

	for (auto it_1 : relation_1.GetTupleSet()) {
		for (auto it_2 : relation_2.GetTupleSet()) {
			if (Joinable(it_1, it_2, relation_1.GetScheme(), relation_2.GetScheme())) {
				Tuple newTuple = Tuple();
				newTuple = CombineTuples(it_1, it_2, relation_1.GetScheme(), relation_2.GetScheme()); /* OPTIMIZE */
				newRelation.AddTuple(newTuple);
			}
		}
	}

	relationTemp = newRelation;
}


Scheme Interpreter::CombineSchemes(Scheme scheme_1, Scheme scheme_2) {
	Scheme newScheme = Scheme();
	for (size_t i = 0; i < scheme_1.GetAttributeList().size(); i++) {
		newScheme.AddAttribute(scheme_1.GetAttribute(i));
	}
	bool found = false;
	for (size_t i = 0; i < scheme_2.GetAttributeList().size(); i++) {
		for (size_t j = 0; j < newScheme.GetAttributeList().size(); j++) {
			if (scheme_2.GetAttribute(i) == newScheme.GetAttribute(j)) {
				found = true;
				break;
			}
		}
		if (!found) {
			newScheme.AddAttribute(scheme_2.GetAttribute(i));
		}
		found = false;
	}

	return newScheme;
}


bool Interpreter::Joinable(Tuple tuple_1, Tuple tuple_2, Scheme scheme_1, Scheme scheme_2) {
	for (size_t i = 0; i < scheme_1.GetAttributeList().size(); i++) {
		for (size_t j = 0; j < scheme_2.GetAttributeList().size(); j++) {
			if ((scheme_1.GetAttribute(i) == scheme_2.GetAttribute(j))
				&& (tuple_1.GetValue(i) != tuple_2.GetValue(j))) {
				return false;
			}
		}
	}
	return true;
}


Tuple Interpreter::CombineTuples(Tuple tuple_1, Tuple tuple_2, Scheme scheme_1, Scheme scheme_2) {
	Tuple newTuple = Tuple();
	for (size_t i = 0; i < tuple_1.GetValueList().size(); i++) {
		newTuple.AddValue(tuple_1.GetValue(i));
	}

	bool found = false;
	for (size_t i = 0; i < tuple_2.GetValueList().size(); i++) {
		for (size_t j = 0; j < tuple_1.GetValueList().size(); j++) {
			if (scheme_2.GetAttribute(i) == scheme_1.GetAttribute(j)) {
				found = true;
				break;
			}
		}
		if (!found) {
			newTuple.AddValue(tuple_2.GetValue(i));
		}
		found = false;
	}

	return newTuple;
}


void Interpreter::UniteWithDatabase(Relation joinedRelation) {
	Relation newRelation = database.GetRelation(joinedRelation.GetName());
	for (auto it : joinedRelation.GetTupleSet()) {
		if (newRelation.AddTuple(it)) {
			newRelation.PrintTuple(it);
		}
	}
	database.ResetRelation(newRelation.GetName(), newRelation);
	
}


void Interpreter::QueryInterpreter() {
	cout << "Query Evaluation" << endl;
	for (size_t i = 0; i < program.GetQueryList().size(); i++) {
		EvaluatePredicate(program.GetQueryList()[i]);
		PrintQuery(program.GetQueryList()[i]);
	}
}


void Interpreter::PrintQuery(Predicate predicate) {
	cout << relationTemp.GetName() << "(";
	for (size_t i = 0; i < predicate.GetParameterList().size(); i++) {
		cout << predicate.GetParameterList()[i].GetExpression();
		if (i < predicate.GetParameterList().size() - 1) {
			cout << ",";
		}
	}
	cout << ")? ";
	if (relationTemp.GetTupleSet().empty()) {
		cout << "No";
	}
	else {
		cout << "Yes(" << relationTemp.GetTupleSet().size() << ")";
	}
	cout << endl;
	relationTemp.PrintRelation();
}