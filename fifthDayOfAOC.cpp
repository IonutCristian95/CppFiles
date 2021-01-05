#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <map>
#include <set>
#include <vector>

int getRow(std::string);
int getColumn(std::string);
void printPossibleRow(const std::map<std::string, int> &);

int main()
{
    int keepOpen{};
    std::cout << "test" << std::endl;

    std::ifstream inFile;
    std::ofstream outFile;
    inFile.open("./txtFiles/input5AOC.txt");
    outFile.open("./txtFiles/output5AOC.txt", std::ios::trunc);

    if (!inFile || !outFile)
    {
        std::cout << "Error - " << ((!inFile) ? " no input file detected" : " no output file detected") << std::endl;
    }

    int highestSeatID{};
    std::string lineInput;

    int row{};
    int column{};
    int seatID{};
    int mySeatID{};
    std::map<std::string, int> boardingList{};
    while (!inFile.eof())
    {
        std::getline(inFile, lineInput);

        row = getRow(lineInput);
        column = getColumn(lineInput);

        seatID = row * 8 + column;

        if (seatID > highestSeatID)
        {
            highestSeatID = seatID;
        }

        boardingList.insert(std::pair<std::string, int>(lineInput, seatID));
    }

    // for (auto elem : boardingList)
    // {
    //     std::cout << elem.first << " " << elem.second << std::endl;
    // }

    printPossibleRow(boardingList);

    outFile << "Highest seat ID is " << highestSeatID << std::endl;
    outFile << "My seat ID is " << mySeatID << std::endl;
    inFile.close();
    outFile.close();

    std::cin >> keepOpen;
    return 0;
}

//  First part of the riddle

int getRow(std::string input)
{
    std::string rowInput;
    rowInput = input.substr(0, input.size() - 3);

    int low = 0;
    int high = 127;
    int row{};
    for (unsigned i = 0; i < rowInput.size(); i++)
    {
        if (rowInput[i] == 'F')
        {
            high = round((low + high) / 2) - 1;
            row = high;
        }
        else
        {
            low = round((low + high) / 2) + 1;
            row = low;
        }
    }

    if (rowInput[rowInput.size() - 1] == 'F')
    {
        row = high;
    }
    else
    {
        row = low;
    }

    return row;
}

int getColumn(std::string input)
{
    std::string columnInput;
    columnInput = input.substr(input.size() - 3);

    int left = 0;
    int right = 7;
    int column{};
    for (unsigned i = 0; i < columnInput.size(); i++)
    {
        if (columnInput[i] == 'L')
        {
            right = round((left + right) / 2) - 1;
            column = right;
        }
        else
        {
            left = round((left + right) / 2) + 1;
            column = left;
        }
    }

    if (columnInput[columnInput.size() - 1] == 'L')
    {
        column = right;
    }
    else
    {
        column = left;
    }

    return column;
}

void printPossibleRow(const std::map<std::string, int> &tempMap){
    std::set<std::string> rows;
    std::vector<std::string> rowsMultiple {};
    std::string rowInput {};

    for(auto elem : tempMap){

        rowInput = elem.first.substr(0, elem.first.size() - 3);
        rows.insert(rowInput);
        rowsMultiple.push_back(elem.first);
    }

    for(auto elem : rows){
        std::cout << elem << std::endl;
    }
}