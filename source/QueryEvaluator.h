//
//  QueryEvaluator.h
//  cs3202
//
//  Created by Zhao Weixiang on 16/9/13.
//  Copyright (c) 2013 Zhao Weixiang. All rights reserved.
//
#pragma once
#include "QueryPreprocessor.h"
#include <iostream>
#include "PKB.h"
#include "string.h"
#include <vector>
#include <list>
#include <sstream>
#include <set>
#include "baseRelation.h"
using namespace std;


class QueryEvaluator{
public:
    template<class T>
	struct rated_desAbstr{
		QueryPreprocessor::designAbstraction desAbstr;
		int rating;
	};
	struct value_set{
		string ref;
		set<int> values;
	};
    QueryEvaluator();
    string getQuery();
    list<string> processQuery(string query);
    vector<designAbstraction> sort_desAbstr(designAbstraction desAbstr);
    vector<value_set>valueSet;
    /*
     priority:
     1. with unselected entity
     2. pattern unselected entity
     3. modify, follow, parent with 2 constant
     4. affect, next with 2 constant
     5. modify*, follow*, parent* with 2 constant
     6. affect*, next* with 2 constant
     7. modify, follow, parent with 1 constant and unselected entity
     8. modify*, follow*, parent* with 1 constant and unselected entity
     9. affect, next* with 1 constant and unselected entity
     10. affect*, next* with 1 constant and unselected entity
     11-20. same order with selected entityf
     */
     /*
      rating:
        desAbstr:
            with: 1
            pattern: 2
            modify Use follow parent: 3
            next affect: 4
            follow* parent*: 30
            next*: 40
            affect*: 50
        parameter:
      
            1 constant: 0
            2 constant: 1
            1 unselected enity: 10
            2 unselected entity: 50
            1 selected entity: 100
            2 selected eneity: 200
      */
    /*
      1. sort the desAbstr and eliminate duplicate desAbstr
      2. Querying all the desAbstr with only constants
      3. group the desAbstr with common entities with sorted order
      4. In each group find out the chains
     */
    
private:

	map<string, set<string>> valueTable;
    vector<QueryPreprocessor::entityReff> entity;
	vector<string> result;
	list<baseRelation*> constant_relations;
	list<list<baseRelation*>> * grouped_relations;
	PKB* pkb;
	bool has_pattern;
	bool has_relation;
	bool has_pattern_result;
	QueryPreprocessor Qprocessor;
	bool flag;
    void processAttrParis(vector<attr_compare> attr_pairs);
    void initialzeValueTable(vector<QueryPreprocessor::entityReff> entity);
    void processPattern(vector<pattern> pattern);
    void processRelations(vector<designAbstraction> desAbstr);
    bool processConstantRelations()
};