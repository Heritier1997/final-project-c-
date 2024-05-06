#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <direct.h> // For _getcwd
#include <filesystem>
#include <cstring>

#ifdef _WIN32
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#include "ConsoleApplication1.h"
#define GetCurrentDir getcwd
#endif

using namespace std;

/*
    This function open gives me the parent repository
    because I was having trouble knowing the location of the file.
    So, I have to get the parent location of where I'm right now.
    I copied and pasted both the /usr/share/dict/words that I download online on GitHub and the worldpop provides by the teacher.
*/
string getParentDirectory() {
    char buff[FILENAME_MAX];
    if (GetCurrentDir(buff, sizeof(buff))) {
        // Convert backslashes to forward slashes on Windows
        for (char* p = buff; *p; ++p) {
            if (*p == '\\') *p = '/';
        }

        // Find the last occurrence of directory separator
        char* lastSlash = std::strrchr(buff, '/');
        if (lastSlash != nullptr) {
            *lastSlash = '\0'; // Null-terminate at the last slash
            return std::string(buff);
        }
        else {
            std::cerr << "Cannot get parent directory." << std::endl;
            return "";
        }
    }
    else {
        std::cerr << "Cannot get current directory." << std::endl;
        return "";
    }
}

// This function read every words from wordpop.txt and store them in the vector called words
void readWordsFromFile(const string& filename, vector<string>& words) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string word;
    while (file >> word) {
        words.push_back(word);
    }

    file.close();
}

// This function checked and print out all words that it cannot find in the vector words
int checkFunction(string fileToOpen, vector<string>& words) {
    // Open file to be checked
    ifstream inputFile(fileToOpen);
    if (!inputFile.is_open()) {
        cerr << "Error opening input file." << endl;
        return -1;
    }

    string word;
    cout << "Here are the words not found in vector:" << endl;
    // Check each word in the input file
    while (inputFile >> word) {
        // Check if word is not contained in the words
        if (find(words.begin(), words.end(), word) == words.end()) {
            cout << word << endl;
        }
    }

    inputFile.close();
    return 0;
}

int main() {

    // Get the location of my project
    string parentDirectory = getParentDirectory();

    // Define vector to store words from words
    vector<string> words;

    // Read words from words file
    readWordsFromFile(parentDirectory +"/words.txt", words);

    // Now begin to check
    checkFunction(parentDirectory+"/worldpop.txt", words);

    return 0;
}
