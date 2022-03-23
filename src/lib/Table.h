#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

using std::string;
using std::ifstream;
using std::cout;
using std::unordered_map;
using std::stringstream;
using std::vector;



typedef std::unordered_map<string, string> col_map;

typedef std::unordered_map< int, col_map> rows_map;


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

