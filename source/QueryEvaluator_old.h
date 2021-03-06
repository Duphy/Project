#pragma once
#include "QueryPreprocessor.h"

#include "PKB.h"
#include "string.h"
#include <vector>
#include <list>
#include <sstream>
#include <set>
using namespace std;
class QueryEvaluator
{
public:
	QueryEvaluator(PKB* a);
	//QueryEvaluator(ModifyTable m, FollowsTable f, CallTable c, varTable v, ProcTable p, UseTable u);
	string getQuery();
	
	template<class T>
	struct Colunm{
		string header;
		string type;
		set<int> cell;
	};
	template<typename T>
	int compare(T a, T b);


	template<class T>
	struct Table{
		vector<Colunm<T>> colunms;
	};

	bool compareAST(TNode* ast, QueryPreprocessor::pattern pattern);
	string getType(string synonym);

	list<string> processQuery(string query);
	Colunm<int> evaluate_modify_uses(int evaluate_position,string select_type, string evaluate_type,
		Colunm<int> pattern_result,int pattern_position, string relation);

	QueryPreprocessor::entityReff getEntity(string synonym);
	Colunm<int> evaluatePattern();
	Colunm<int> evaluateRelation(int evaluate_position,string select_type, string evaluate_type,
		QueryEvaluator::Colunm<int> pattern_result,int pattern_position);
	Colunm<int> evaluate_parents_follows(int evaluate_position,string select_type, string evaluate_type,
	QueryEvaluator::Colunm<int> pattern_result,int pattern_position, string relation);
	Colunm<int> getAll(string type);
	bool isConstant(string a);
	void compareAST_Node(TNode* ast, QueryPreprocessor::pattern);

	Colunm<int> evaluate_follows(
	int evaluate_position,string select_type, string evaluate_type,
	QueryEvaluator::Colunm<int> pattern_result,int pattern_position, string relation);



	Colunm<int> evaluate_a_b_pattern_a();
private:
	vector<QueryPreprocessor::entityReff> entity;
	vector<QueryPreprocessor::designAbstraction> desAbstr;
	vector<QueryPreprocessor::pattern> pattern;
	vector<string> result;
	PKB* pkb;
	bool has_pattern;
	bool has_relation;
	bool has_pattern_result;
	QueryPreprocessor Qprocessor;
	bool flag;
};



