#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>


void checkForValidation(const std::map<std::string, std::string> &, int *);
void validateThePassportsFields(const std::map<std::string, std::string> &, int *);
void splitInputToMap(std::map<std::string, std::string> *, std::string);
bool checkPID(const std::string &);
bool checkIYR(const std::string &);
bool checkEYR(const std::string &);
bool checkECL(const std::string &);
bool checkHCL(const std::string &);
bool checkHGT(const std::string &);
bool checkBYR(const std::string &);

int main()
{
    int num{}; //Used so that the cmd window will not close

    std::fstream inFile;
    std::fstream outFile;
    inFile.open("./txtFiles/input4AOCf.txt");
    outFile.open("./txtFiles/output4AOCf.txt", std::ios::app);

    if (!inFile || !outFile)
    {
        std::cout << "Infile " << inFile.fail() << " outFile " << outFile.fail() << std::endl;
        return 1;
    }

    std::istringstream iss{};
    std::ostringstream oss {};
    std::string input{};
    std::map<std::string, std::string> passport{};

    int validPassports{};

    std::string word{};//Used for the istringstream

    while (!inFile.eof())
    {
        while (std::getline(inFile, input))
        {
            iss.clear(); //Important to clear the iss to get new data with each iteration
            iss.str(input);
            // std::cout << iss.str() << std::endl; //Verify the data that iss is taking

            //Get the data and split them into keys and values
            while (iss >> word)
            {
                splitInputToMap(&passport, word);
            }

            //Used to separate the data - the data will be given on one line or multiline
            //so checking for an empty input will let me see what data I should check
            if (input == "")
            {
                validateThePassportsFields(passport, &validPassports);
                // checkForValidation(passport, &validPassports); //This was used for first part
                break;
            }
        }
        if (inFile.eof())
        {
            validateThePassportsFields(passport, &validPassports);
            // checkForValidation(passport, &validPassports); //This was used for first part
        }

        //Clears the values of the passports
        passport.clear();
    }
    
    outFile << validPassports << std::endl;

    
    inFile.close();
    outFile.close();

    std::cin >> num;
    return 0;
}


void splitInputToMap(std::map<std::string, std::string> *tempMap, std::string input)
{
    int semicolon = 0;
    std::string key{};
    std::string value{};

    for (size_t i = 0; i < input.size(); i++)
    {
        if (input.at(i) == ':')
        {
            semicolon = i;
        }
    }

    key = input.substr(0, semicolon);
    value = input.substr(semicolon + 1);

    (*tempMap).insert(std::pair<std::string, std::string>(key, value));
}

void checkForValidation(const std::map<std::string, std::string> &tempMap, int *validPass)
{
    bool byr = false;
    bool iyr = false;
    bool eyr = false;
    bool hgt = false;
    bool ecl = false;
    bool pid = false;
    bool hcl = false;
    bool cid = false;

    //Check to see if the passport contains all the fields
    if (tempMap.find("byr") != tempMap.end())
        byr = true;
    if (tempMap.find("iyr") != tempMap.end())
        iyr = true;
    if (tempMap.find("eyr") != tempMap.end())
        eyr = true;
    if (tempMap.find("hgt") != tempMap.end())
        hgt = true;
    if (tempMap.find("ecl") != tempMap.end())
        ecl = true;
    if (tempMap.find("pid") != tempMap.end())
        pid = true;
    if (tempMap.find("hcl") != tempMap.end())
        hcl = true;
    if (tempMap.find("cid") != tempMap.end())
        cid = true;


    if (byr && iyr && eyr && hgt && ecl && pid && hcl)
    {
        *validPass += 1;
        std::cout << "VALID PASSPORTS = " << *validPass << std::endl;
    }
    else
    {
        std::cout << "INVALID PASSPORT BECAUSE OF ";
        if (tempMap.find("byr") == tempMap.end())
            std::cout << " byr ";
        if (tempMap.find("iyr") == tempMap.end())
            std::cout << " iyr ";
        if (tempMap.find("eyr") == tempMap.end())
            std::cout << " eyr ";
        if (tempMap.find("hgt") == tempMap.end())
            std::cout << " hgt ";
        if (tempMap.find("ecl") == tempMap.end())
            std::cout << " ecl ";
        if (tempMap.find("pid") == tempMap.end())
            std::cout << " pid ";
        if (tempMap.find("hcl") == tempMap.end())
            std::cout << " hcl ";
        if (tempMap.find("cid") == tempMap.end())
            std::cout << " cid ";
        std::cout << std::endl;
    }
}

void validateThePassportsFields(const std::map<std::string, std::string> &tempMap, int *validPass){
    bool byr = false;
    bool iyr = false;
    bool eyr = false;
    bool hgt = false;
    bool ecl = false;
    bool pid = false;
    bool hcl = false;
    bool cid = false;


    for(const auto &m: tempMap){
       if(m.first == "pid"){
           if(checkPID(m.second)){
               pid = true;
           }
       }else if(m.first == "byr"){
           if(checkBYR(m.second)){
               byr = true;
           }
       }else if(m.first == "iyr"){
           if (checkIYR(m.second))
           {
               iyr = true;
           }
       }else if (m.first == "eyr")
       {
           if (checkEYR(m.second))
           {
               eyr = true;
           }
       }else if (m.first == "hgt")
       {
           if (checkHGT(m.second))
           {
               hgt = true;
           }
       }
       else if (m.first == "hcl")
       {
           if (checkHCL(m.second))
           {
               hcl = true;
           }
       }
       else if (m.first == "ecl")
       {
           if (checkECL(m.second))
           {
               ecl = true;
           }
       }
    }

    if (byr && iyr && eyr && hgt && ecl && pid && hcl)
    {
        *validPass += 1;
        std::cout << "VALID PASSPORTS = " << *validPass << std::endl;
    }
}

bool checkPID(const std::string &val)
{
    if(val.size() == 9){
        for(size_t i = 0; i < val.size(); i++){
            if(!isdigit(val.at(i))){
                return false;
            }
        }
        return true;
    }
    return false;
}

bool checkBYR(const std::string &val)
{
    int year {};
    if(val.size() == 4){
        year = std::stoi(val);
        if(year >= 1920 && year <= 2002)
            return true;
    }
    return false;
}

bool checkIYR(const std::string &val)
{
    int year{};
    if (val.size() == 4)
    {
        year = std::stoi(val);
        if (year >= 2010 && year <= 2020)
            return true;
    }
    return false;
}

bool checkEYR(const std::string &val)
{
    int year{};
    if (val.size() == 4)
    {
        year = std::stoi(val);
        if (year >= 2020 && year <= 2030)
            return true;
    }
    return false;
}

bool checkHGT(const std::string &val)
{
    std::string measurement = val.substr(val.size()-2);
    std::string strHeight = val.substr(0);
    //stoi will get all the digits until a letter or a symbol
    int height = std::stoi(strHeight);

    if(measurement == "in"){
        if(height < 59 || height > 76 ){
            return false;
        }
    }else if(measurement == "cm"){
        if(height < 150 || height > 193){
            return false;
        }
    }else{
        std::cout << "Something went wrong with height " << std::endl;
        std::cout << "Measurement " << measurement << " height " << height << std::endl;
        return false;
    }
    return true;
}

bool checkECL(const std::string &val)
{
    std::vector<std::string> eyeColors {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
    for(size_t i = 0; i < eyeColors.size(); i++){
        if(val == eyeColors.at(i)){
            return true;
        }
    }
    return false;
}

bool checkHCL(const std::string &val)
{
    if(val.at(0)!= '#' || val.size() != 7){
        return false;
    }
    for(size_t i = 1; i < val.size(); i++){
        if(!isdigit(val.at(i))){
            if(val.at(i) > 'g'){
                return false;
            }
        }
    }
    return true;
}