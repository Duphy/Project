#ifndef CALLTABLE_H
#define CALLTABLE_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "procTable.h"
#include <utility>

using namespace std;
typedef struct call_row_t{
	string callingProc;
	vector<string> calledProcs;
	vector<int> callStmNo;
}call_row;
class CallTable
{
private:
	vector<call_row> callTable;
public:
	CallTable(void);
	void insert(int stmNo, string proc1, string proc2);
	bool isCalled(string proc1, string proc2);
	vector<string> getCallsList(string procName);
	vector<string> getCalledList(string procName);
	vector<string> getCall(string procName);
	vector<string> getCalled(string procName);
	vector<string> getCalledT(string proc);
	vector<string> getCallsT(string proc);
	vector<int> getCallsStmT(string proc);
	vector<int> getCallsStmtList(string procName);
	void getTopoCallRecur(string startProc);
	vector<string> getTopoCall();
	bool checkCall(vector<string> set1, vector<string> set2);
	int getSize();
	void print();
};

#endif