#include "Table.h"


Table::~Table()
{
    // clear columns first, then rows;
    for (auto &[key, value] : storage)
    {
        value.clear();
    }

    storage.clear();
}

// calculate expressions in cells
void Table::Inialize()
{

    for (auto &[row, value1] : storage)
    {

        for (auto &[col, value2] : value1)
        {

            try
            {
                TableParser::checkCell(row, col, storage);
            }
            catch (string error)
            {
                throw error;
            }
        }
    }
}

Table::Table(std::ifstream &file_stream)
{
    std::string line;
    stringstream sstr;

    getline(file_stream, line);
    sstr << line;

    // check table format:: first element in first row should be comma
    getline(sstr, line, ',');

    if (line != "") {
        throw "invalid table format, first element should be comma";
    }
    // fill vector by columns names
    while (sstr.good())
    {
        std::string substr;
        getline(sstr, substr, ',');
        try
        {
            //if str without digits, stoi should throw expection,
            // else name is incorrect
            stoi(substr);
            throw "invalid table format, incorrect col name";
        }
        catch (std::invalid_argument const &ex){
            //no digits in col name
        }
        
        columns.push_back(substr);
    }

    /////others row;
    size_t row_num;

    // fill storage in cycle
    while (getline(file_stream, line))
    {

        col_map columns_map;

        sstr.clear();

        sstr << line;

        std::string substr3;


        getline(sstr, substr3, ',');
        // get row number from first element of row

        

        try
        {
            row_num = stoi(substr3);
        }
        catch (std::invalid_argument const &ex)
        {

            throw "invalid table format, incorrent row name";
        }

        rows.push_back(row_num);

        // fill  column map
        for (auto n : columns)
        {
            if (sstr.good())
            {

                std::string substr;
                getline(sstr, substr, ',');

                columns_map.insert(std::make_pair(n, substr));
            }
            else
            {

                columns_map.insert(std::make_pair(n, "0"));
            }
        }

        // fill storage
        storage.insert(std::make_pair(row_num, columns_map));
    }

    try
    {
        Inialize();
    }
    catch (string error)
    {
        throw error;
    }
}

// should be divided into two methods
void Table::printTable()
{
    // print names of columns
    for (auto col : columns)
    {
        cout << "," << col;
    }
    cout << std::endl;
    // print rows with commas
    for (auto row : rows)
    {
        cout << row;
        for (auto col : columns)
        {
            cout << "," << storage[row][col];
        }
        cout << std::endl;
    }
}
