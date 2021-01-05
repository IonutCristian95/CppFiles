#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int checkForTree(int, std::string);

int main()
{
    int position {};
    std::fstream inFile;
    inFile.open("./txtFiles/input3AOC.txt");
    std::fstream outFile;
    outFile.open("./txtFiles/output3AOC.txt", std::ios::app);

    // std::istringstream iss {};
    std::string buffer;
    int currentPos {};
    bool start = true;
    int treesEncountered {};
    int searchPos {}; // Use this variable only if the currentPos exceeds the size of the buffer
    int stepsToRight = 1; //Change only these two variables
    int stepsDown = 1;    //


    if(inFile && outFile){
        while(!inFile.eof()){
            //If just starting, we have to go 3 columns to the right and one row down, so we have to skip the first line
            if(start){
                std::getline(inFile, buffer);
                start = false;
            }
            for(size_t i = 0;i < stepsDown;i++)
                std::getline(inFile, buffer);

            currentPos+=stepsToRight;

            if(currentPos >= buffer.size()){
                searchPos = currentPos % buffer.size();
                treesEncountered += checkForTree(searchPos, buffer);
            }else{
                treesEncountered += checkForTree(currentPos, buffer);
            }
        }

    }else{
        std::cout << "No input or output files." << std::endl;
    }

    std::ostringstream oss;
    oss << "Trees encountered: " << treesEncountered << std::endl;
    outFile << oss.str();

    inFile.close();
    outFile.close();

    std::cin >> treesEncountered;

    return 0;
}

int checkForTree(int pos, std::string map){
    return (map.at(pos) == '#') ? 1 : 0;
}