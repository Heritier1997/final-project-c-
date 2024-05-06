

#ifdef _WIN32
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#include "ConsoleApplication1.h"
#define GetCurrentDir getcwd
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <direct.h> // For _getcwd
#include <filesystem>
#include <cstring>

#include <sstream>
#include <cctype>

using namespace std;

/*
    This function open gives me the parent repository
    because I was having trouble knowing the location of the file.
    So, I have to get the parent location of where I'm right now.
    I copied and pasted the worldpop provides by the teacher in the same directory.
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

int main() {

    // Get the location of my project
    string filename = getParentDirectory()+"/worldpop.txt";

    // Open the file for reading
    ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return 1;
    }

    // Variables to store country name and population
    string countryName;
    int population;

    // Total population count
    int totalPopulation = 0;

    // Read each character from the file
    char ch;
    while (file.get(ch)) {
        // Process each line
        if (ch != '\n') {
            // Read characters until the first non-white space character
            while (isspace(ch))
                file.get(ch);

            // If the first character is not a digit, it's part of the country name
            if (!isdigit(ch)) {
                ostringstream oss;
                oss << ch;

                // Read characters until the next white space or digit
                while (file.get(ch) && !isspace(ch)) {
                    oss << ch;
                }

                // Store the country name
                countryName = oss.str();
            }

            // If the first character is a digit, it's the population
            if (isdigit(ch)) {
                // Unget the digit character to be read as part of the population
                file.unget();
                file >> population;

                // Print the country name and population
                cout << "Country: " << countryName << ", Population: " << population << endl;

                // Add population to total population count
                if (countryName != "European Union") {
                    totalPopulation += population;
                }
            }
        }
    }

    // Print the total population
    cout << endl;
    cout << "Total Population (excluding European Union): " << totalPopulation << endl;

    // Close the file
    file.close();

    return 0;
}
