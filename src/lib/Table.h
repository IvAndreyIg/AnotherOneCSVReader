#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "TableParser.h"

using std::string;
using std::ifstream;
using std::cout;
using std::unordered_map;
using std::stringstream;
using std::vector;




class Table
{	public:
	rows_map storage;
	std::vector<std::string> columns;
	std::vector<size_t> rows;
	

	~Table();
	void Inialize();
	

	Table(std::ifstream &file_stream);

	void printTable();


};

