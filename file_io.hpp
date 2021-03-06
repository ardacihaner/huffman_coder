#include <fstream>
#include <algorithm>
#include <iostream>
#include <vector>

using std::ofstream; using std::ifstream;
using std::count; using std::string;
using std::vector;

/**
 * This header is responsible from the file I/O jobs.
 */

bool does_file_exist(string fileName)
{
    ifstream file(fileName);
    return file.good();
}

int getLineCount(string filePath) {
    ifstream inFile(filePath); 
    return std::count(std::istreambuf_iterator<char>(inFile), 
                std::istreambuf_iterator<char>(), '\n');
}


vector<string> readFile(string filePath) {
    vector<string> fileVec = vector<string>();
    string line;
    ifstream inFile(filePath);
    int counter = 0;

    if (inFile.is_open()) {
        while (getline (inFile, line)) {
            fileVec.push_back(line);
        }
        inFile.close();
    }
    else 
        std::cout << "Unable to open file"; 
    return fileVec;
}

void writeFile(string filePath, string writeContent) {
    ofstream inFile;
    inFile.open (filePath);
    inFile << writeContent;
    inFile.close();
}