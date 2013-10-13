#ifndef PKB_H
#define PKB_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm> 
#include <set>

#include "VarTable.h"
#include "ProcTable.h"
#include "StmtTable.h"
#include "ConstantTable.h"
#include "ModifyTable.h"
#include "UseTable.h"
#include "FollowTable.h"
#include "ParentTable.h"
#include "CallTable.h"
#include "AST.h"
#include "CFG.h"

using namespace std;
typedef short PROC;

class PKB {
private:
	VarTable varTable;
	ProcTable procTable;
	StmtTable stmtTable;
	ConstantTable constTable;
	ModifyTable modifyTable;
	UseTable useTable;
	FollowTable followTable;
	ParentTable parentTable;
	CallTable callTable;
	AST ast;

	//CFG -ZHAO yang
	CFG cfg;

public:
	PKB();

	/************************************************** AST *************************************************/
	TNode* createRootNode(string type, int content, int lineNo);
	TNode* createNode(string type, int content, int lineNo);
	void makeLeftChild(TNode* parent, TNode* leftChild);
	void makeRightChild(TNode* parent, TNode* rightChild);
	TNode* getLeftChild(TNode* parent);
	TNode* getRightChild(TNode* parent);
	int getContent(TNode* node);
	int getLineNo(TNode* node);
	string getType(TNode* node);
	vector<TNode*> getAST();
	void printAST();

	/************************************************** CallTable *************************************************/
	vector<pair<string, string>> getCalls(set<string>* arg1_set, string arg1Type, set<string>* arg2_set, string arg2Type);
	vector<pair<string, string>> getCallsT(set<string>* arg1_set, string arg1Type, set<string>* arg2_set, string arg2Type);
	bool checkCalls(string arg1, string arg1Type, string arg2, string arg2Type);
	bool checkCallsT(string arg1, string arg1Type, string arg2, string arg2Type);
	void insert(int stmNo, string proc1, string proc2);
	bool isCalled(string proc1, string proc2);
	vector<string> getCallsList(string procName);
	vector<string> getCalledList(string procName);
	vector<int> getCallsStmT(int procIndex);
	void printCallTable();
	vector<int> getCallsList(int procIndex);
	vector<int> getCallsT(int procIndex);
	vector<int> getCalledT(int procIndex);
	/************************************************** ParentTable *************************************************/
	vector<pair<string, string>> getParent(set<string>* arg1_set, string arg1Type, set<string>* arg2_set, string arg2Type);
	vector<pair<string, string>> getParentT(set<string>* arg1_set, string arg1Type, set<string>* arg2_set, string arg2Type);
	vector<int> getParentT(int stmt);
	bool checkParent(string arg1, string arg1Type, string arg2, string arg2Type);
	bool checkParentT(string arg1, string arg1Type, string arg2, string arg2Type);
	void insert(int stm1, string DE1, int stm2, string DE2);
	int getParent (int stm);
	
	vector<int> getChildren(int stm, string DE);
	vector<int> getChildrenT(int stmt,string DE);
	void printParentTable(); 

	/************************************************** FollowTable *************************************************/
	//for DE
	//1. "assign"
	//2. "while"
	//3. "stmt"
	vector<pair<string, string>> getFollow(set<string>* arg1_set, string arg1Type, set<string>* arg2_set, string arg2Type);
	vector<pair<string, string>> getFollowT(set<string>* arg1_set, string arg1Type, set<string>* arg2_set, string arg2Type);
	bool checkFollow(string arg1, string arg1Type, string arg2, string arg2Type);
	bool checkFollowT(string arg1, string arg1Type, string arg2, string arg2Type);
	void insertFollow(int stm1, string DE1, int stm2, string DE2);
	int findFollowed(int stm);
	vector<int> findFollowedT(int stmt);
	int findFollows(int stm);
	vector<int> findFollowsT(int stmt);
	bool isFollowed(int stm1,int stm2);
	void printFollowTable();

	/************************************************** ModifyTable *************************************************/
	vector<pair<string, string>> getModify(set<string>* arg1List, string arg1Type, set<string>* arg2List, string arg2Type);
	bool checkModify(string arg1, string arg1Type, string arg2, string arg2Type);
	void updateModify();

	int insertModifyStmt(int stmtNo, int varIndex, string DE);
	int insertModifyProc(int procIndex, int varIndex);
	vector<int> getModifiedStmt(int stmtNo);
	vector<int> getModifiedProc(int procIndex);
	vector<int> getModifiedList(int varIndex, string DE);
	void printModifyTable();

	/************************************************** UseTable *************************************************/
	vector<pair<string, string>> getUse(set<string>* arg1_set, string arg1Type, set<string>* arg2_set, string arg2Type);
	bool checkUse(string arg1, string arg1Type, string arg2, string arg2Type);
	void updateUse();

	int insertUseStmt(int stmtNo, int varIndex, string DE);
	int insertUseProc(int procIndex, int varIndex);
	vector<int> getUsedStmt(int stmtNo);
	vector<int> getUsedProc(int procIndex);
	vector<int> getUsedList(int varIndex, string DE);
	void printUseTable();

	/************************************************** VarTable *************************************************/
	int insertVar(string varName);
	string getVarName(int index);
	int getVarIndex(string varName);
	int getSizeVarTable();
	void printVarTable();
	set<string> getAllVars();

	/************************************************** ProcTable *************************************************/
	int insertProc(string procName);	
	string getProcName(int index);
	int getProcIndex(string procName);
	int getSizeProcTable();
	void printProcTable();
	set<string> getAllProcs(); 

	/************************************************** StmtTable *************************************************/
	int insertStmt(int stmtNo, string type);
	vector<int> getStmtNo(string type);
	int getSizeStmtTable();
	string getStmtType(int stmtNo);
	void printStmtTable();
	set<string> getAllStmts();

	/************************************************** ConstantTable *************************************************/
	void insertConst(int stmtNo, int number);
	vector<int> getConst(int stmtNo);
	vector<int> getStmtForConst(int number);
	vector<int> getAllStmtForConst();
	void printConstTable();
	set<string> getAllConstants();

	/************************************************** CFG - Zhao Yang *************************************************/
	void buildCFG();
	void buildTree(int procIndex);
	CFGNode* buildLink(int stmtNum);
	int currentIndex;
	vector<int> visited;
	CFGNode* findNext(int stmtNo);
	void printCFG();
	void printfTree(CFGNode *node);

	/************************************************** Next - Zhao Yang *************************************************/
	// utilities
	vector<int> getNext(int stmtNo);
	vector<int> getPrev(int stmtNo);
	vector<int> v;
	vector<int> getNextT(int stmtNo);
	vector<int> getPrevT(int stmtNo);
	bool isNext(int stmtNo1,int stmtNo2);
	bool isNextT(int stmtNo1, int stmtNo2);
	bool contains(vector<int> list, int stmtNo);
	bool intersect(vector<int> list1, vector<int> list2);
	// API for QE

	bool checkNext(string arg1, string arg1Type, string arg2, string arg2Type);
	bool checkNextT(string arg1, string arg1Type, string arg2, string arg2Type);

	vector<pair<string, string>> getNext(set<string>* arg1_set, string arg1Type, set<string>* arg2_set, string arg2Type);
	vector<pair<string,string>> getNextT(set<string>* arg1_set, string arg1Type, set<string>* arg2_set, string arg2Type);
	
	string toString(int num);
	/************************************************** Affect - Zhao Yang *************************************************/
	vector<int> affectList; // for internal usage
	vector<int> affectTList; // for internal usage
	void recusiveBuildAffectList(int stmtNo, int varIndex);
	void recusiveBuildAffectTList(int stmtNo, vector<int> varIndexList);
	vector<int> getAffectList(int stmtNo);
	vector<int> getAffectTList(int stmtNo);
	//API for QE
	vector<pair<string, string>> getAffects(set<string>* arg1_set, string arg1Type, set<string>* arg2_set, string arg2Type);
	vector<pair<string, string>> getAffectsT(set<string>* arg1_set, string arg1Type, set<string>* arg2_set, string arg2Type);
	bool checkAffects(string arg1, string arg1Type, string arg2, string arg2Type);
	bool checkAffectsT(string arg1, string arg1Type, string arg2, string arg2Type);
	struct postfixNode{
		string type;// if/while/assig
		int lineNum; 
		string varRef; //'a' as control variable ...bla
		string postfixExpr; //  2 5 *
		postfixNode(string typeInput,int lineNumInput,string varRefInput, string postfixExprInput){
			type=typeInput;
			lineNum=lineNumInput;
			varRef=varRefInput;
			postfixExpr=postfixExprInput;
		}
	};

	/************************************************** Flatten - Zhao Yang *************************************************/
	map<int,postfixNode*> postfixExprList;
	void flattenAST();
	string createPostfix(TNode *node);

	/************************************/
	/*               Testing next/nextT/affects/affectT   -zy                                                   */
	/************************************/
	void printNext();
	void printNextT();
	void printAffects();
	void printAffectsT();
};
#endif
