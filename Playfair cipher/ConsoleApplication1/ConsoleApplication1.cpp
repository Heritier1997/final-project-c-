#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int MATRIX_SIZE = 5;

// Function to generate the Playfair matrix from the keyword
void generatePlayfairMatrix(char matrix[MATRIX_SIZE][MATRIX_SIZE], const string& keyword) {
    // Initialize matrix with keyword
    string key = keyword;
    transform(key.begin(), key.end(), key.begin(), ::toupper);
    key.erase(remove_if(key.begin(), key.end(), [](char c) { return !isalpha(c); }), key.end());
    key.erase(remove_if(key.begin(), key.end(), [&key](char c) { return key.find(c) != key.find_last_of(c); }), key.end());

    // Fill the matrix with unique characters from the keyword
    int row = 0, col = 0;
    for (char c : key) {
        matrix[row][col++] = c;
        if (col == MATRIX_SIZE) {
            col = 0;
            row++;
        }
    }

    // Fill the remaining matrix with the alphabet (except 'J')
    for (char c = 'A'; c <= 'Z'; ++c) {
        if (c != 'J' && key.find(c) == string::npos) {
            matrix[row][col++] = c;
            if (col == MATRIX_SIZE) {
                col = 0;
                row++;
            }
        }
    }
}

// Function to find the position of a character in the Playfair matrix
void findPosition(char matrix[MATRIX_SIZE][MATRIX_SIZE], char target, int& row, int& col) {
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            if (matrix[i][j] == target) {
                row = i;
                col = j;
                return; // Found the position, exit the function
            }
        }
    }
    // If the character is not found, set row and col to -1
    row = -1;
    col = -1;
}


// Function to encrypt plaintext using the Playfair cipher
string encrypt(const string& plaintext, char matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    string encryptedText;
    // Implement encryption logic
    // Iterate through pairs of characters in the plaintext
    for (size_t i = 0; i < plaintext.size(); i += 2) {
        char first = plaintext[i];
        char second = (i + 1 < plaintext.size()) ? plaintext[i + 1] : 'X'; // Pad with 'X' if plaintext length is odd
        
        // Find positions of characters in the Playfair matrix
        int row1, col1, row2, col2;
        findPosition(matrix, first, row1, col1);
        findPosition(matrix, second, row2, col2);

        // Apply Playfair cipher rules
        if (row1 == row2) { // Same row
            encryptedText += matrix[row1][(col1 + 1) % MATRIX_SIZE];
            encryptedText += matrix[row2][(col2 + 1) % MATRIX_SIZE];
        }
        else if (col1 == col2) { // Same column
            encryptedText += matrix[(row1 + 1) % MATRIX_SIZE][col1];
            encryptedText += matrix[(row2 + 1) % MATRIX_SIZE][col2];
        }
        else { // Form rectangle and swap
            encryptedText += matrix[row1][col2];
            encryptedText += matrix[row2][col1];
        }
    }
    return encryptedText;
}

// Function to decrypt ciphertext using the Playfair cipher
string decrypt(const string& ciphertext, char matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    string decryptedText;
    // Implement decryption logic
    // Iterate through pairs of characters in the ciphertext
    for (size_t i = 0; i < ciphertext.size(); i += 2) {
        char first = ciphertext[i];
        char second = ciphertext[i + 1];
        // Find positions of characters in the Playfair matrix
        // Find positions of characters in the Playfair matrix
        int row1, col1, row2, col2;
        findPosition(matrix, first, row1, col1);
        findPosition(matrix, second, row2, col2);

        // Apply Playfair cipher rules
        if (row1 == row2) { // Same row
            decryptedText += matrix[row1][(col1 + MATRIX_SIZE - 1) % MATRIX_SIZE];
            decryptedText += matrix[row2][(col2 + MATRIX_SIZE - 1) % MATRIX_SIZE];
        }
        else if (col1 == col2) { // Same column
            decryptedText += matrix[(row1 + MATRIX_SIZE - 1) % MATRIX_SIZE][col1];
            decryptedText += matrix[(row2 + MATRIX_SIZE - 1) % MATRIX_SIZE][col2];
        }
        else { // Form rectangle and swap
            decryptedText += matrix[row1][col2];
            decryptedText += matrix[row2][col1];
        }
    }
    return decryptedText;
}

int main() {
    // Input keyword and plaintext/ciphertext
    string keyword, text;
    cout << "Enter keyword: ";
    cin >> keyword;
    cout << "Enter text: ";
    cin >> text;

    // Generate Playfair matrix
    char matrix[MATRIX_SIZE][MATRIX_SIZE];
    generatePlayfairMatrix(matrix, keyword);

    // Encrypt or decrypt text
    string encryptedText = encrypt(text, matrix);
    string decryptedText = decrypt(encryptedText, matrix);

    // Output results
    cout << "Encrypted text: " << encryptedText << endl;
    cout << "Decrypted text: " << decryptedText << endl;

    return 0;
}





//#include <iostream>
//#include <string>
//#include <vector>
//#include <unordered_map>
//#include <algorithm>
//
//using namespace std;
//
//// Function to generate the Playfair matrix
//vector<vector<char>> generatePlayfairMatrix(const string& keyword) {
//    // Remove duplicates from the keyword
//    string key = "";
//    unordered_map<char, bool> used;
//    for (char c : keyword) {
//        if (!used[c] && isalpha(c)) {
//            key += toupper(c);
//            used[c] = true;
//        }
//    }
//
//    // Fill the matrix with the keyword
//    vector<vector<char>> matrix(5, vector<char>(5));
//    int index = 0;
//    for (char c : key) {
//        matrix[index / 5][index % 5] = c;
//        index++;
//    }
//
//    // Fill the matrix with the remaining letters of the alphabet
//    for (char c = 'A'; c <= 'Z'; ++c) {
//        if (c != 'J' && used[c] == false) {
//            matrix[index / 5][index % 5] = c;
//            index++;
//        }
//    }
//
//    return matrix;
//}
//
//// Function to find the positions of a character in the Playfair matrix
//pair<int, int> findPosition(const vector<vector<char>>& matrix, char ch) {
//    for (size_t i = 0; i < matrix.size(); ++i) {
//        for (size_t j = 0; j < matrix[i].size(); ++j) {
//            if (matrix[i][j] == ch) {
//                return { i, j };
//            }
//        }
//    }
//    return { -1, -1 }; // Character not found
//}
//
//// Function to encrypt plaintext using the Playfair cipher
//string encrypt(const string& plaintext, const vector<vector<char>>& matrix) {
//    string result = "";
//    for (size_t i = 0; i < plaintext.size(); i += 2) {
//        char first = plaintext[i];
//        char second = (i + 1 < plaintext.size()) ? plaintext[i + 1] : 'X';
//
//        // If the two characters are in the same row, replace them with the characters to their right
//        // If the two characters are in the same column, replace them with the characters below them
//        // Otherwise, form a rectangle and take the characters at the opposite corners
//        int row1, col1, row2, col2;
//        tie(row1, col1) = findPosition(matrix, first);
//        tie(row2, col2) = findPosition(matrix, second);
//
//
//        if (row1 == row2) {
//            result += matrix[row1][(col1 + 1) % 5];
//            result += matrix[row2][(col2 + 1) % 5];
//        }
//        else if (col1 == col2) {
//            result += matrix[(row1 + 1) % 5][col1];
//            result += matrix[(row2 + 1) % 5][col2];
//        }
//        else {
//            result += matrix[row1][col2];
//            result += matrix[row2][col1];
//        }
//    }
//    return result;
//}
//
//// Function to decrypt ciphertext using the Playfair cipher
//string decrypt(const string& ciphertext, const vector<vector<char>>& matrix) {
//    string result = "";
//    for (size_t i = 0; i < ciphertext.size(); i += 2) {
//        char first = ciphertext[i];
//        char second = ciphertext[i + 1];
//
//        // If the two characters are in the same row, replace them with the characters to their left
//        // If the two characters are in the same column, replace them with the characters above them
//        // Otherwise, form a rectangle and take the characters at the opposite corners
//        int row1, col1, row2, col2;
//        tie(row1, col1) = findPosition(matrix, first);
//        tie(row2, col2) = findPosition(matrix, second);
//
//
//        if (row1 == row2) {
//            result += matrix[row1][(col1 + 4) % 5];
//            result += matrix[row2][(col2 + 4) % 5];
//        }
//        else if (col1 == col2) {
//            result += matrix[(row1 + 4) % 5][col1];
//            result += matrix[(row2 + 4) % 5][col2];
//        }
//        else {
//            result += matrix[row1][col2];
//            result += matrix[row2][col1];
//        }
//    }
//    return result;
//}
//
//int main(int argc, char* argv[]) {
//    if (argc != 4) {
//        cerr << "Usage: " << argv[0] << " -[e|d] -k<keyword> <text>" << endl;
//        return 1;
//    }
//
//    char option = argv[1][1];
//    string keyword = &argv[2][2];
//    string text = argv[3];
//
//    if (keyword.empty() || text.empty()) {
//        cerr << "Keyword and text must not be empty." << endl;
//        return 1;
//    }
//
//    if (option != 'e' && option != 'd') {
//        cerr << "Invalid option. Use -e to encrypt or -d to decrypt." << endl;
//        return 1;
//    }
//
//    // Generate Playfair matrix using the keyword
//    vector<vector<char>> matrix = generatePlayfairMatrix(keyword);
//
//    string result;
//    if (option == 'e') {
//        result = encrypt(text, matrix);
//        cout << "Encrypted text: " << result << endl;
//    }
//    else {
//        result = decrypt(text, matrix);
//        cout << "Decrypted text: " << result << endl;
//    }
//
//    return 0;
//}
