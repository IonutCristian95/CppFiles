#include <iostream>
#include <fstream>
#include <sstream>

/*
Example input:
1-3 a: abcde
1-3 b: cdefg
2-9 c: ccccccccc

Must have at least i or j occurrences of the letter.
First and third example are correct, the second one is not.

*/
bool checkLetterOccurrences(int, int, char, std::string);
bool checkOrderOccurrence(int, int, char, std::string);

int main()
{
    std::fstream inFile;
    inFile.open("./txtFiles/input2AOC.txt");
    std::fstream outFile;
    outFile.open("./txtFiles/output2AOCpart2.txt", std::ios::app);

    std::string buffer {};
    int lowLimit {};
    int highLimit {};
    char letter {};
    std::string password {};
    std::istringstream iss {};
    int counterCorrectPasswords{};

    if(inFile && outFile){
        while(!inFile.eof()){

            std::getline(inFile, buffer);
            // for (char c : buffer){
            //     if(c == '-' || c == ':'){
            //         c = ' ';
            //     }
            // }
            for(size_t i = 0; i < buffer.size(); i++){
                if (buffer.at(i) == '-' || buffer.at(i) == ':')
                {
                    buffer.at(i) = ' ';
                }
            }
            iss.str(buffer);
            
            // std::cout << iss.str() << std::endl; //this is correct
            iss >> lowLimit >> highLimit >> letter >> password;
            std::cout << "l: " << lowLimit << " h: " << highLimit << " letter: " << letter << " pass: " << password << std::endl;
            // if(checkLetterOccurrences(lowLimit, highLimit, letter, password)){
            if(checkOrderOccurrence(lowLimit, highLimit, letter, password)){
                counterCorrectPasswords++;
            }
            iss.clear();
        }
    }else{
        std::cout << "No file input" << std::endl;
    }

    std::ostringstream oss {};
    oss << "The number of correct passwords is " << counterCorrectPasswords << std::endl;
    std::cout << oss.str() << std::endl;
    outFile << oss.str();     //Save it for later


    inFile.close();
    outFile.close();

    std::cin >> counterCorrectPasswords;

    return 0;
}

bool checkLetterOccurrences(int lowLimit, int highLimit, char letter, std::string password){
    //If the letter has the occurrences between including the low limit or high limit, it will be valid.
    int occurrences {};
    for (auto c : password){
        if(c == letter) occurrences++;
    }

    if(occurrences>= lowLimit && occurrences <=highLimit){
        return true;
    }
    return false;
}

bool checkOrderOccurrence(int firstPos, int secondPos, char letter, std::string password){
    bool fPos = false;
    bool sPos = false;

    if(password.at(firstPos-1) == letter){
        fPos = true;
    }
    if (password.at(secondPos-1) == letter){
        sPos = true;
    }


    if( fPos==sPos ) return false;
    return true;
}