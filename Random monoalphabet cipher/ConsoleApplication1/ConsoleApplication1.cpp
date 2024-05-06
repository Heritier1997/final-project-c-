#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_map>

#ifdef _WIN32
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#include "ConsoleApplication1.h"
#define GetCurrentDir getcwd
#endif

#include <direct.h> // For _getcwd
#include <filesystem>
#include <cstring>

#include <sstream>
#include <cctype>

using namespace std;

string getParentDirectory() {
    char buff[FILENAME_MAX];
    if (GetCurrentDir(buff, sizeof(buff))) {
        // Convert backslashes to forward slashes on Windows
        for (char* p = buff; *p; ++p) {
            if (*p == '\\') *p = '/';
        }

        // Find the last occurrence of directory separator
        char* lastSlash = strrchr(buff, '/');
        if (lastSlash != nullptr) {
            *lastSlash = '\0'; // Null-terminate at the last slash
            return string(buff);
        }
        else {
            cerr << "Cannot get parent directory." << endl;
            return "";
        }
    }
    else {
        cerr << "Cannot get current directory." << endl;
        return "";
    }
}

string generateCipherAlphabet(const string& keyword) {
    string alphabetInReverse;

    // Fill alphabetInReverse with letters from Z to A
    for (char ch = 'Z'; ch >= 'A'; ch--) {
        alphabetInReverse += ch;
    }

    // Remove letters from alphabetInReverse that are in the keyword
    for (char ch : keyword) {
        alphabetInReverse.erase(remove(alphabetInReverse.begin(), alphabetInReverse.end(), ch), alphabetInReverse.end());
    }

    // Return the concatenated string of keyword and alphabetInReverse
    return keyword + alphabetInReverse;
}


int main(int argc, char* argv[]) {

    // Get location of the file I want to open
    string filename = getParentDirectory() + "/worldpop.txt";

    string keyword = "";

    while (keyword.empty()) {
        cout << "Enter a non-empty keyword: ";
        cin >> keyword;
    }
    
    // Make the keyword in Uppercase letters
    transform(keyword.begin(), keyword.end(), keyword.begin(), ::toupper);

    // Generate the cipher alphabet based on the keyword
    string cipherAlphabet = generateCipherAlphabet(keyword);

    // ENCRYPT the Kyword
    cout << endl;
    cout << "------------------------------------ " << endl << endl;
    cout << "KEYWORD: " << endl << endl;
    cout << keyword << " = " << cipherAlphabet << endl;
    cout << "------------------------------------ " << endl << endl;
    

    ifstream file(filename);
    char ch;

    if (!file.is_open()) {
        cerr << "Error: Unable to open the file." << endl;
        return 1;
    }

    string line;
    string word;

    cout << "FILE: " << endl << endl;
    while (getline(file, line)) { // Read each line
        for (char ch : line) { // Iterate over each character in the line
            if (!isspace(ch) && !isdigit(ch)) { // Check if the character is not whitespace
                cout << ch; // Output the character
                word += ch;
            }
        }
        
        // Make it uppercase
        transform(word.begin(), word.end(), word.begin(), ::toupper);

        // Encript the name of the country
        cipherAlphabet = generateCipherAlphabet(word);
        
        // Reinitiallize word
        word = "";

        // Print them
        cout << " = " << cipherAlphabet << endl;
    }

    file.close(); // Close the file
    return 0;
}
