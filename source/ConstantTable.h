#pragma once

#ifndef CONSTANTTABLE_H
#define CONSTANTTABLE_H

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <assert.h>

using namespace std;

typedef struct const_row_t{
	int stmt_no;
	int number;
} const_row;

class ConstantTable
{
private:
	vector<const_row> Const_Table;

public:
	ConstantTable(void);
	~ConstantTable(void);

	// Insert constant with the corresponding stmt number to the table
	void insertConst(int stmtNo, int number);

	// Print ConstantTable
	void printConstTable();

	// Return all constants in table
	set<string> getAllConstants();

	/*************************************** Unused APIs *******************************************/
	// Returns the list of all constants in the given stmt
	vector<int> getConst(int stmtNo);

	// Return the list of all stmt having the given constant
	vector<int> getStmt(int number);

	// Return the list of all stmt having constant
	vector<int> getAllStmt();
};
#endif