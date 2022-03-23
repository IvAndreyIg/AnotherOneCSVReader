#pragma once
#include <vector>
#include <string>
#include <regex>
#include <unordered_map>

using std::string;

typedef std::unordered_map<string, string> col_map;

typedef std::unordered_map< int, col_map> rows_map;

class TableParser
{
	static const std::regex expression_regex;
	static const std::regex arguments_regex;

public:

	static bool checkMatch(string);

	static std::vector<string> getMathes(string);

	static void checkCell(int row, string col, rows_map& map_ref);

};

