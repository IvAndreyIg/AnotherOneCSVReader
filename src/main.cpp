#include "lib/Table.h"

void run(string);

int main(int argc, char **argv)
{

    run(argv[1]);

    return EXIT_SUCCESS;
}

void run(string path)
{

    std::string line;

    // open file
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
        catch (char const *error)
        {
            delete table;
            cout << "error:" << error << std::endl;
        }
    }
    else
    {
        cout << "error:cant open file" << std::endl;
    }
    in.close();

    delete table;
}
