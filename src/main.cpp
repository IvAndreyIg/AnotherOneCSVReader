#include <iostream>
#include <fstream>
#include <string>
#include "lib/Table.h"

using std::cout;
using std::ifstream;
using std::string;

void run(string);

int main(int argc, char **argv)
{

    run(argv[1]);

    return EXIT_SUCCESS;
}

void run(string path)
{

    std::string line;

    std::ifstream in(path);

    rows_map someStorage;

    stringstream sstr;
    std::vector<std::string> v;

    Table *table = nullptr;

    if (in.is_open())
    {

        try 
        {
            table = new Table(in);
            table->printTable();
        }
        catch (char const* error) 
        {
            cout << "error:" << error;
        }
    }
    else
    {
        cout << "error:cant open file";
    }
    in.close();

    delete table;
}
