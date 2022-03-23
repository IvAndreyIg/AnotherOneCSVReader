#include "TableParser.h"

const std::regex TableParser::expression_regex("^[=]{1}[A-Za-z]+[0-9]+[(+),(-),(*),(\\)]{1}[A-Za-z]+[0-9]+$");
const std::regex TableParser::arguments_regex("[A-Za-z]+|[0-9]+|([(+),(-),(*),(\\)]{1})");

int do_operation(int leftV, int rightV, string sign);

bool TableParser::checkMatch(string str)
{
    std::sregex_iterator currentMatch(str.begin(),
                                      str.end(), expression_regex);

    std::sregex_iterator lastMatch;

    if (currentMatch != lastMatch)
    {
        std::smatch match = *currentMatch;
        return match.str() == str;
    }
    else
        return false;
}

std::vector<std::string> TableParser::getMathes(std::string str)
{
    std::vector<string> matches;

    std::sregex_iterator currentMatch(str.begin(),
                                      str.end(), arguments_regex);

    std::sregex_iterator lastMatch;

    while (currentMatch != lastMatch)
    {
        std::smatch match = *currentMatch;

        // put matches in queue
        matches.push_back(match.str());

        currentMatch++;
    }

    return matches;
}

void TableParser::checkCell(int row, string col, rows_map &map_ref)
{

    static int recursion_counter = 0;

    string cell_value = map_ref[row][col];

    if (checkMatch(cell_value))
    {
        // check recursion in table cells expressions
        if (recursion_counter > 15)
        {
            throw "error:invalid table format";
        }

        recursion_counter++;

        auto mathes = getMathes(cell_value);

        try
        {
            // check left operand
            checkCell(stoi(mathes.at(1)), mathes.at(0), map_ref);
            auto firstValue = map_ref[stoi(mathes.at(1))][mathes.at(0)];

            // check right operand
            checkCell(stoi(mathes.at(4)), mathes.at(3), map_ref);
            auto secondValue = map_ref[stoi(mathes.at(4))][mathes.at(3)];
            map_ref[row].at(col) = std::to_string(do_operation(stoi(firstValue), stoi(secondValue), mathes.at(2)));
        }
        catch (string error)
        {
            throw error;
        }
        catch (std::invalid_argument const &ex)
        {

            throw "invalid expression in cell,unreachable arguments";
        }

        recursion_counter--;
    }
    else
    {
        try
        {
            if ((std::to_string(stoi(cell_value))) != cell_value)
                throw "invalid expression in cell,not enough arguments";
        }
        catch (std::invalid_argument const &ex)
        {

            throw "invalid expression in cell,unreachable arguments or not enough arguments";
        }
    }
}

//....
int do_operation(int leftV, int rightV, string sign)
{
    switch (sign[0])
    {
    case '+':
        return leftV + rightV;
        break;
    case '-':
        return leftV - rightV;
        break;
    case '*':
        return leftV * rightV;
        break;
    case '/':
        return leftV / rightV;
        break;
    case '%':
        return leftV % rightV;
        break;
    default:
        return 0;
    }
}