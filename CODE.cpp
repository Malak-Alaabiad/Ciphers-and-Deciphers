
// Purpose: This Program Can encrypt or decrypt any message you want using two different ciphers.
// The first is ( Route Cipher ). In this cipher, a secret integer key is used to create a matrix whose number of columns is equal to the key
// and then the message is written in as many rows as needed in this matrix. Then the encrypted message is collected by going in a spiral path starting from the top right corner.
// The Second is ( Morse Cipher ). In this cipher, you can translate a message to Morse code and the opposite.
// Assume that each letter is separated by one space from the next and that each word is separated by three spaces from the next.
// Authors: Malak Mohamed Saad Fahmy Al-Aabiad
// Emails: malakkalaabiadd@gmail.com


#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include <cmath>
#include <unordered_map>
#include <bits/stdc++.h>

using namespace std;

// Function for display welcome message to the user
void start()
{
    cout << "\n** Welcome To Cipher Program **";
    cout << "\n-------------------------------" << endl;
}

// Function for Affine Cipher Encryption
void Affine_Cipher_Encryption(){
    // cipher text initially empty
    string cipher = "";
    string message;
    int a, b;
    string text;
    cout << endl << "Enter the value of 'a': ";
    cin >> a;
    cout << "\nEnter the value of 'b': ";
    cin >> b;
    cout << "\nPlease, Enter the message you want to encrypt: ";
    cin.ignore();
    getline(cin, message);

    for (char ch : message) {
        if (isalpha(ch)) {
            int x = toupper(ch) - 'A';
            // applying encryption formula and added 'A' to bring it in range of ascii alphabet [ 65-90 | A-Z ]
            int encrypted = (a * x + b) % 26;
            cipher += char(encrypted + 'A');
        }
        // else simply append space character
        else {
            cipher += ch;
        }
    }
    // Output the encrypted message
    cout << "\nEncrypted message: " << cipher << endl;
}

// Function for Affine Cipher Decryption
void Affine_Cipher_Decryption() {
    string result = "";
    string message;
    int a , b, c ;
    cout << endl << "Enter the value of 'a': ";
    cin >> a;
    cout << "\nEnter the value of 'b': ";
    cin >> b;
    cout << "\nEnter the value of 'c': ";
    cin.ignore();
    cin >> c;
    cout << "\nPlease, Enter the cipher text: ";
    cin.ignore();
    getline(cin, message);

    for (char ch : message) {
        if (isalpha(ch)) {
            int y = toupper(ch) - 'A';
            int decrypted = c * (y - b);
            while (decrypted < 0) {
                decrypted += 26;
            } // applying encryption formula and added 'A' to bring it in range of ascii alphabet [ 65-90 | A-Z ]
            decrypted %= 26;
            result += char(decrypted + 'A');
        } // else simply append space character
        else {
            result += ch;
        }
    }
    // Output the encrypted message
    cout << "\nDecrypted message: " << result << endl;
}

// Function for Route Cipher Encryption
void Route_Cipher_encryption(){
    // Declare the key
    int key;
    cout<<"\nPlease, Enter the key (ex:3): ";
    cin >> key;
    // Take the message which the user wants to encrypt as input
    string message;
    cin.ignore();
    cout<<"\nEnter the message that you want to encrypt: ";
    getline(cin, message);

    string no_space_message = "";

    // Remove spaces and convert to uppercase
    for (int i = 0; i < message.size(); i++)
        if (isalpha(message[i])) no_space_message += toupper(message[i]);

    // Calculate number of rows required
    int rows = ceil(static_cast<double>(no_space_message.size()) / float(key));
    char arr[rows][key];
    // Create character array to store message
    int count = 0, length = no_space_message.size();
    // Fill array with message characters
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < key; j++)
        {
            if (count < length)
            {
                arr[i][j] = no_space_message[count];
                count++;
            }
            else arr[i][j] = 'X'; // Fill remaining spaces with 'X'
        }

    // Encrypt the message using Route Cipher algorithm
    string encryptedMessage = "";
    int i = 0, j = key - 1;
    int left = 0, right = key - 1, up = 0, down = rows - 1;
    count = 0;
    int d = 1;

    while (count < (rows * key))
    {
        encryptedMessage += arr[i][j];   // Append character to encrypted message
        count++;                         // Update indices based on direction
        if (i == up && j < right && d == 4) {j++; if (j == right) {up++; d = 1;}}
        else if (i == down && j > left && d == 2) {j--; if (j == left) {down--; d = 3;}}
        else if (j == right && i < down && d == 1) {i++; if (i == down) {right--; d = 2;}}
        else if (j == left && i > up && d == 3) {i--; if (i == up) {left++; d = 4;}}
    }
    // Output encrypted message
    cout << "\nEncrypted message: " << encryptedMessage << '\n';
}

// Function for Route Cipher Decryption
void Route_Cipher_Decryption(){
    // Declare the key
    int key;
    cout << "\nPlease, Enter the key (ex:3): ";
    cin >> key;
    cin.ignore();
    // Take the message which the user wants to encrypt as input
    string message;
    cout <<"\nEnter the message that you want to decrypt: ";
    getline(cin, message);
    // Remove spaces and convert to uppercase
    string no_space_message = "";

    for (int i = 0; i < message.size(); i++)
        if (isalpha(message[i])) no_space_message += toupper(message[i]);

    // Calculate number of rows required
    int rows = ceil(no_space_message.size() / float(key));
    char matrix[rows][key];
    char arr[rows][key];   // Create character array to store message
    int count = 0, length = no_space_message.size();
    int up = 0 , left = 0, down = rows - 1, right = key - 1;

    // Decrypt the message using Route Cipher algorithm
    while(true) {
        if(up>down)
            break;
        for (int i = up; i <= down; i++) {
            arr[i][right] = no_space_message[count];
            count++;
        }
        right--;

        if (left>right) {
            break;
        }
        for (int i = right; i >= left; i--) {
            arr[down][i] = no_space_message[count];
            count++;
        }
        down--;

        if(up>down) {
            break;
        }
        for (int i = down; i >= up; i--) {
            arr[i][left] = no_space_message[count];
            count++;
        }
        left++;


        if(left > right)
            break;
        for (int i = left; i <= right; i++){
            arr[up][i] = no_space_message[count];
            count++;
        }
        up++;
    }
    // Output the decrypted message
    cout << "\nDecrypted message: ";
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < key; j++)
        {
            if (arr[i][j] == 'X')
                continue;
            cout <<arr[i][j];
        }
    }
    cout <<endl;
}

// Function for Atbash Cipher Encryption
void Atbash_Cipher_Encryption(){
    string message;
    cout<<"\nEnter the message that you want to encrypt: ";
    getline(cin, message);
    string encrypted_message = "";

    for (char& c : message) {
        if (isalpha(c)) {
            char shiftedChar = 'Z' - (toupper(c) - 'A');
            encrypted_message += shiftedChar;
        }
        else {
            encrypted_message += c;
        }
    }
    cout << "\nEncrypted message: "<< encrypted_message << endl;
}

// Function for Atbash Cipher Decryption
void Atbash_Cipher_Decryption(){
    string encrypted_message;
    cout<<"\nEnter the message that you want to decrypt: ";
    getline (cin, encrypted_message);
    string decrypted_message = "";

    for (char& c : encrypted_message) {
        if (isalpha(c)) {
            char shiftedChar = 'Z' - (toupper(c) - 'A');
            decrypted_message += shiftedChar;
        } else {
            decrypted_message += c;
        }
    }
    cout << "\nDecrypted text: " << decrypted_message << endl;
}

// Function for Vignere Cipher Encryption
void Vigenere_Cipher_Encryption(){
    const int max_message_length = 80;
    const int max_keyword_length = 8;
    char message[max_message_length + 1];
    char keyword[max_keyword_length + 1];
    cout << "\nPlease, enter the message that you want to encrypt (up to 80 characters): ";
    cin.getline(message, max_message_length + 1);
    cout << "\nPlease, enter the keyword (up to 8 characters): ";
    cin.getline(keyword, max_keyword_length + 1);
    // Encrypt the message
    int message_length = strlen(message);
    int keyword_length = strlen(keyword);

    for (int i = 0; i < message_length; ++i) {
        message[i] = toupper(message[i]);
        if (!isalpha(message[i])) {
            continue;
        }
        int message_code = message[i] - 'A';
        int keyword_code = keyword[i % keyword_length] - 'A';
        int encrypted_code = (message_code + keyword_code) % 26;
        message[i] = encrypted_code + 'A';
    }
    cout << "\nEncrypted message: " << message << endl;
}

// Function to decrrypt a single character
char decrypt_char(char encrypted_char, char keyword_char){
    encrypted_char = toupper(encrypted_char);
    keyword_char = toupper(keyword_char);
    if(!isalpha(encrypted_char)){
        return encrypted_char;
    }
    int encrypted_code = encrypted_char - 'A';
    int keyword_code = keyword_char - 'A';
    int decrypted_code = (encrypted_code - keyword_code + 26) % 26;
    return decrypted_code + 'A';
}

// Function for Vigenere Cipher Decryption
void Vigenere_Cipher_Decryption(){
    const int max_message_length = 80;
    const int max_keyword_length = 8;
    char message[max_message_length + 1];
    char keyword[max_keyword_length + 1];
    cout << "\nPlease, enter the encrypted message that you want to decrypt (up to 80 characters): ";
    cin.getline(message, max_message_length + 1);
    cout << "\nPlease, enter the keyword (up to 8 characters): ";
    cin.getline(keyword, max_keyword_length + 1);
    int messageLength = strlen(message);
    int keywordLength = strlen(keyword);
    int keyword_index = 0;
    for (int i = 0; i < messageLength; ++i) {
        message[i] = decrypt_char(message[i], keyword[keyword_index]);
        keyword_index = (keyword_index + 1) % keywordLength;
    }
    cout << "\nDecrypted message: " << message << endl;
}

map<char, string> lookup = {
        {'A', "aaaaa"}, {'B', "aaaab"}, {'C', "aaaba"}, {'D', "aaabb"}, {'E', "aabaa"},
        {'F', "aabab"}, {'G', "aabba"}, {'H', "aabbb"}, {'I', "abaaa"}, {'J', "abaab"},
        {'K', "ababa"}, {'L', "ababb"}, {'M', "abbaa"}, {'N', "abbab"}, {'O', "abbba"},
        {'P', "abbbb"}, {'Q', "baaaa"}, {'R', "baaab"}, {'S', "baaba"}, {'T', "baabb"},
        {'U', "babaa"}, {'V', "babab"}, {'W', "babba"}, {'X', "babbb"}, {'Y', "bbaaa"}, {'Z', "bbaab"}, {' ', ""}
};

// Function for Baconian Cipher Encryption
void Baconian_Cipher_Encryption(){
    string message;
    cout<<"\nEnter the message that you want to encrypt: ";
    getline(cin, message);
    string cipher = "";
    for (char letter : message) {
        // Checks for space
        if (letter != ' ') {
            cipher += lookup[toupper(letter)] + " ";
        } else {
            // Adds space
            cipher += " ";
        }
    }
    cout << "\nEncrypted message: " << cipher << endl;
}

// Function for Baconian Cipher Decryption
void Baconian_Cipher_Decryption(){
    string message;
    cout<<"\nEnter the message that you want to decrypt: ";
    getline (cin, message);
    string decipher = "";
    for (size_t i = 0; i < message.length(); i += 5) {
        // Extracting a set of ciphertext from the message
        string substr = message.substr(i, 5);
        // Checking for space as the first character of the substring
        if (substr[i] != ' ') {
            decipher += static_cast<char>(toupper((find_if(lookup.begin(), lookup.end(),
                                                           [&substr](const pair<char, string> &p) {
                                                               return p.second == substr;
                                                           }))->first));
            i++;
        }
        else {
            // Adds space
            decipher += " ";
            // Index next to the space
            i++;
        }
    }
    cout << "\nDecrypted message: " << decipher << endl;
}

// Function for Simple Substitution Cipher Encryption
void Simple_Substitution_Cipher_Encryption(){
    string Text, keyword;
    cout<<"\nPlease, enter the message that you want to encrypt:  ";
    getline(cin,Text);
    cout<<"\nPlease, enter the keyword (ex: zebra):  ";
    getline(cin,keyword);
    transform(Text.begin(), Text.end(), Text.begin(), ::tolower);
    transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);
    int freq[26] = {};
    for (int i = 0; i < keyword.size(); i++)
        freq[keyword[i] - 'a'] = 1;

    for (int i = 0; i <= 26; i++)
        if (!freq[i])
            keyword += char(i + 'a');

    cout << "\nEncrypted message: ";

    for (int i = 0; i < Text.size(); i++){
        if(Text[i] != ' ') {
            cout << keyword[Text[i] - 'a'];
        }
        else {
            cout << Text[i];
        }
    }
}

// Function for Simple Substitution Cipher Decryption
void Simple_Substitution_Cipher_Decryption(){
    string Text, key;
    cout<<"\nPlease, enter the encrypted message that you want to decrypt:  ";
    getline(cin, Text);
    cout<<"\nPlease, enter the keyword (ex: zebra): ";
    cin >> key;
    transform(Text.begin(), Text.end(), Text.begin(), ::tolower);
    transform(key.begin(), key.end(), key.begin(), ::tolower);
    bool freq[26] = {};

    for (int i = 0; i < key.size(); i++)
        freq[key[i] - 'a'] = 1;

    for (int i = 0; i < 26; i++)
    {
        if (!freq[i])
            key += char(i + 'a');
    }
    cout << "\nDecrypted message: ";
    for (char c : Text)
    {
        if (c != ' ')
        {
            size_t found = key.find(c);
            if (found != string::npos)
            {
                cout << char('A' + found);
            }
        }
        else
            cout << " ";
    }
}

// Function for Polybius Square Cipher Encryption
const int Size = 5;
void Polybius_Square_Encryption(){
    int key[Size];
    char alphabet[Size][Size];
    cout<<"\nPlease, enter the key, which is five integers separated by a space: ";
    for (int i = 0; i < Size; i++)
    {
        cin >> key[i];
    }
    char c;
    for (int i = 0; i < Size * Size; i++)
    {
        if (char(i + 'A') >= 'J')
            c = char(i + 'B');
        else
            c = char(i + 'A');
        alphabet[i / Size][i % Size] = c;
    }
    string s;
    cin.ignore();
    cout<<"\nPlease, enter the message that you want to encrypt:  ";
    getline(cin, s);
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    replace(s.begin(), s.end(), 'J', 'I');
    cout << "\nEncrypted message: ";
    for (int i = 0; i < s.size(); i++)
    {
        for (int j = 0; j < Size * Size; j++)
        {
            if (alphabet[j / Size][j % Size] == s[i])
            {
                cout << key[j / Size] << key[j % Size];
            }
        }
        if (isspace(s[i]))
            cout << " ";
    }
}

// Function for Polybius Square Cipher Decryption
void Polybius_Square_Decryption(){
    int key[Size];
    char alphabet[Size][Size];
    cout<<"\nPlease, enter the key, which is five integers separated by a space: ";
    for (int i = 0; i < Size; i++)
    {
        cin >> key[i];
    }
    char c;
    for (int i = 0; i < Size * Size; i++)
    {
        if (char(i + 'A') >= 'J')
            c = char(i + 'B');
        else
            c = char(i + 'A');
        alphabet[i / Size][i % Size] = c;
    }
    cin.ignore();
    cout<<"\nPlease, enter the message that you want to decrypt:  ";
    string s;
    getline(cin, s);
    string decrypted_message = "";
    for ( int i = 0; i < s.size(); i+=2 )
    {
        if(s[i] == ' '){
            decrypted_message += ' ';
            i--;
            continue;
        }
        int row = -1, col = -1;
        for (int j = 0; j < Size; j++){
            if (key[j] == (s[i] - '0')) {
                row = j;
                break;
            }

        }
        for ( int j = 0; j < Size; j++ ) {
            if (key[j] == (s[i + 1] - '0')) {
                col = j;
                break;
            }
        }
        decrypted_message += alphabet[row][col];
    }
    cout << "\nDecrypted message: " << decrypted_message << endl;
}

// Define a map to store the Morse code equivalents of letters
map<char, string> morse_code_map = {
        {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."}, {'E', "."},
        {'F', "..-."}, {'G', "--."}, {'H', "...."}, {'I', ".."}, {'J', ".---"},
        {'K', "-.-"}, {'L', ".-.."}, {'M', "--"}, {'N', "-."}, {'O', "---"},
        {'P', ".--."}, {'Q', "--.-"}, {'R', ".-."}, {'S', "..."}, {'T', "-"},
        {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"}, {'Y', "-.--"},
        {'Z', "--.."}, {' ', "   "}
};

// Function to convert text to Morse code
string text_to_morse(string text) {
    string morse = "";
    for (char ch : text) {
        // Convert uppercase letters to Morse code
        if (isalpha(ch)) {
            morse += morse_code_map[toupper(ch)] + " ";  // Add space between letters
        } else if (ch == ' ') {
            morse += " ";  // Add space between words
        }
    }
    return morse;
}

// Function to convert Morse code to text
string morse_to_text(string morse) {
    int count = 0;
    string text = "";
    string result = "";
    string word = "";
    for (char c : morse){
        if (isspace(c)){
            count += 1;
            for (auto index = morse_code_map.begin(); index != morse_code_map.end(); ++index) {
                if (index->second == text) {
                    result += index->first;
                    text = "";
                    break;
                }
            }
        } else {
            count = 0;
            text += c;
        }
        if (count == 3){
            result += " ";
            count = 0;
        }

    }

    for (auto index = morse_code_map.begin(); index != morse_code_map.end(); ++index) {
        if (index->second == text) {
            result += index->first;
            text = "";
            break;
        }
    }
    return result;
}

// The same function is used to encrypt and decrypt
void Xor_encrypt() {
    string message;
    cout<<"\nPlease, enter the message that you want to encrypt:  ";
    getline(cin, message);
    char Key;
    cout<<"\nPlease, enter the key: ";
    cin >> Key;
    cin.ignore();
    int len = message.length();
    for (int i = 0; i < len; i++)
    {
        message[i] = message[i] ^ Key;
        cout << "\nEncrypted message: " << message[i];
    }
}

void Xor_decrypt() {
    string message;
    cout<<"\nPlease, enter the message that you want to encrypt:  ";
    getline(cin, message);
    char Key;
    cout<<"\nPlease, enter the key: ";
    cin >> Key;
    cin.ignore();
    int len = message.length();
    for (int i = 0; i < len; i++)
    {
        message[i] = message[i] ^ Key;
        cout << "\nDecrypted message: " << message[i];
    }
}

// function to encrypt a message
void railfence_cipher_Encryption() {
    string text;
    cout<<"\nPlease, enter the message that you want to encrypt:  ";
    getline(cin, text);
    int key;
    cout<<"\nPlease, enter the key: ";
    cin >> key;
    char rail[key][(text.length())];

    for (int i=0; i < key; i++)
        for (int j = 0; j < text.length(); j++)
            rail[i][j] = '\n';
    bool dir_down = false;
    int row = 0, col = 0;

    for (int i=0; i < text.length(); i++)
    {
        if (row == 0 || row == key-1)
            dir_down = !dir_down;

        rail[row][col++] = text[i];

        dir_down?row++ : row--;
    }

    string result;
    for (int i=0; i < key; i++)
        for (int j=0; j < text.length(); j++)
            if (rail[i][j]!='\n')
                result.push_back(rail[i][j]);

    cout << "\nEncrypted message: "<< result;
}

void railfence_cipher_Decryption() {
    string cipher;
    cout<<"\nPlease, enter the message that you want to decrypt:  ";
    getline(cin, cipher);
    int key;
    cout<<"\nPlease, enter the key: ";
    cin >> key;
    char rail[key][cipher.length()];

    for (int i=0; i < key; i++)
        for (int j=0; j < cipher.length(); j++)
            rail[i][j] = '\n';

    bool dir_down;

    int row = 0, col = 0;

    for (int i=0; i < cipher.length(); i++)
    {
        if (row == 0)
            dir_down = true;
        if (row == key-1)
            dir_down = false;

        rail[row][col++] = '*';

        dir_down?row++ : row--;
    }

    int index = 0;
    for (int i=0; i<key; i++)
        for (int j=0; j<cipher.length(); j++)
            if (rail[i][j] == '*' && index<cipher.length())
                rail[i][j] = cipher[index++];

    string result;

    row = 0, col = 0;
    for (int i=0; i< cipher.length(); i++)
    {
        if (row == 0)
            dir_down = true;
        if (row == key-1)
            dir_down = false;
        if (rail[row][col] != '*')
            result.push_back(rail[row][col++]);

        dir_down?row++: row--;
    }
    cout << "\nDecrypted message: "<< result;
}

// The main function for the program
int main()
{
    // Display welcome message
    start();
    bool continueProgram = true;
    while (continueProgram) {
        string choice1;
        cout << "Please, Choose the cipher that you want\n1 ) Affine Cipher                   2 ) Route Cipher \n3 ) Atbash Cipher                   4 ) Vignere Cipher \n5 ) Baconian Cipher                 6 ) Simple Substitution Cipher \n7 ) Polybius Square Cipher          8 ) Morse Cipher \n9 ) XOR Cipher                      10) Rail-fence Cipher \nEnter your choice: ";
        getline(cin, choice1);  // Take user choice
        // Affine Cipher
        if (choice1 == "1") {
            while (true) {
                string choice2;
                // Display welcome message and the Explanation of the program to the user
                cout << "\n** Welcome To Affine Cipher Program **";
                cout << "\n--------------------------------------";
                cout << "\nIn Affine Cipher each letter in an alphabet is mapped to its numeric equivalent x"
                        "encrypted using a simple mathematical function, and converted back to a letter. "
                        "Letter A is given number 0 and letter Z is given number 25. " << endl;
                cout << "\nPlease, Choose what do you want to do.\n1) Encrypt a message using Affine Cipher  \n2) Decrypt a message using Affine Cipher \nEnter your choice from (1/2): ";
                getline(cin, choice2);     // Take user choice
                if (choice2 == "1") {            // Encrypt message
                    // Calling encryption function
                    Affine_Cipher_Encryption();
                } else if (choice2 == "2") {     // Decrypt message
                    // Calling decryption function
                    Affine_Cipher_Decryption();
                } else {
                    cout << endl << "Invalid choice. Please, try again.";    // Error message for invalid choice
                    continue;
                }
                break;
            }
        }
        // Route Cipher
        else if (choice1 == "2") {
            while (true) {
                string choice3;
                // Display welcome message and the Explanation of the program to the user
                cout << "\n** Welcome To Route Cipher Program **";
                cout << "\n--------------------------------------";
                cout << "\nIn this cipher, a secret integer key is used to create a matrix whose number of columns is equal to the key and then"
                        "the message is written in as many rows as needed in this matrix. Then the encrypted message is"
                        " collected by going in a spiral path starting from the top right corner. " << endl;
                cout << "\nPlease, Choose what do you want to do.\n1) Encrypt a message using Route Cipher  \n2) Decrypt a message using Route Cipher \nEnter your choice from (1/2): ";
                getline(cin, choice3);                                 // Take user choice
                if (choice3 == "1") {                                        // Encrypt message
                    Route_Cipher_encryption();
                } else if (choice3 == "2") {                                 // Decrypt message
                    Route_Cipher_Decryption();
                } else {
                    cout << endl << "Invalid choice. Please, try again.";    // Error message for invalid choice
                    continue;
                }
                break;
            }
        }
        // Atbash Cipher
        else if (choice1 == "3") {
            while (true) {
                string choice4;
                // Display welcome message and the Explanation of the program to the user
                cout << "\n** Welcome To Atbash Cipher Program **";
                cout << "\n--------------------------------------";
                cout << "\nThe Atbash cipher is a very common, simple cipher. Basically, when encoded, an \"A\" becomes a \n"
                        "\"Z\", \"B\" turns into \"Y\", etc." << endl;
                cout << "\nPlease, Choose what do you want to do.\n1) Encrypt a message using Atbash Cipher  \n2) Decrypt a message using Atbash Cipher \nEnter your choice from (1/2): ";
                getline(cin, choice4);                                 // Take user choice
                if (choice4 == "1") {                                        // Encrypt message
                    Atbash_Cipher_Encryption();
                } else if (choice4 == "2") {                                 // Decrypt message
                    Atbash_Cipher_Decryption();
                } else {
                    cout << endl << "Invalid choice. Please, try again.";    // Error message for invalid choice
                    continue;
                }
                break;
            }
        }
        // Vignere Cipher
        else if (choice1 == "4") {
            while (true) {
                string choice4;
                // Display welcome message and the Explanation of the program to the user
                cout << "\n** Welcome To Vignere Cipher Program **";
                cout << "\n--------------------------------------";
                cout << "\nIn this method, a keyword is repeatedly added character by character to each alphabetic letter in the original message."
                        "The addition is carried out using the ASCII codes for each of the characters,"
                        "modulo 26 (the number of letters in the alphabet), and the result is added to the code for the letter in the ASCII code sequence." << endl;
                cout << "\nPlease, Choose what do you want to do.\n1) Encrypt a message using Vignere Cipher  \n2) Decrypt a message using Vignere Cipher \nEnter your choice from (1/2): ";
                getline(cin, choice4);
                if (choice4 == "1") { // Take user choice
                    // Encrypt message
                    Vigenere_Cipher_Encryption();
                } else if (choice4 == "2") {                                 // Decrypt message
                    Vigenere_Cipher_Decryption();
                } else {
                    cout << endl << "Invalid choice. Please, try again.";    // Error message for invalid choice
                    continue;
                }
                break;
            }
        }
        // Baconian Cipher
        else if (choice1 == "5") {
            while (true) {
                string choice4;
                // Display welcome message and the Explanation of the program to the user
                cout << "\n** Welcome To Baconian Cipher Program **";
                cout << "\n--------------------------------------";
                cout << "\nTo encode a message, each letter of the plaintext is replaced by a group of five of the letters. This replacement is a binary encoding." << endl;
                cout << "\nPlease, Choose what do you want to do.\n1) Encrypt a message using Baconian Cipher  \n2) Decrypt a message using Baconian Cipher \nEnter your choice from (1/2): ";
                getline(cin, choice4);                                 // Take user choice
                if (choice4 == "1") {                                        // Encrypt message
                    Baconian_Cipher_Encryption();
                } else if (choice4 == "2") {                                 // Decrypt message
                    Baconian_Cipher_Decryption();
                } else {
                    cout << endl << "Invalid choice. Please, try again.";    // Error message for invalid choice
                    continue;
                }
                break;
            }
        }
         // Simple Substitution Cipher
        else if (choice1 == "6") {
            while (true) {
                string choice4;
                // Display welcome message and the Explanation of the program to the user
                cout << "\n** Welcome To Simple Substitution Cipher Program **";
                cout << "\n--------------------------------------";
                cout << "\nIn this cipher, a replacement alphabet is used to replace each letter by another one." << endl;
                cout << "\nPlease, Choose what do you want to do.\n1) Encrypt a message using Simple Substitution Cipher  \n2) Decrypt a message using Simple Substitution Cipher \nEnter your choice from (1/2): ";
                getline(cin, choice4);                                 // Take user choice
                if (choice4 == "1") {                                        // Encrypt message
                    Simple_Substitution_Cipher_Encryption();
                } else if (choice4 == "2") {                                 // Decrypt message
                    Simple_Substitution_Cipher_Decryption();
                } else {
                    cout << endl << "Invalid choice. Please, try again.";    // Error message for invalid choice
                    continue;
                }
                break;
            }
        }
        // Polybius Square Cipher
        else if (choice1 == "7") {
            while (true) {
                string choice4;
                // Display welcome message and the Explanation of the program to the user
                cout << "\n** Welcome To Polybius Square Cipher Program **";
                cout << "\n--------------------------------------";
                cout << "\nUsing numbers. Each letter is replaced with two numbers according to the following table (row, column)." << endl;
                cout << "\nPlease, Choose what do you want to do.\n1) Encrypt a message using Polybius Square Cipher  \n2) Decrypt a message using Polybius Square Cipher \nEnter your choice from (1/2): ";
                getline(cin, choice4);                                 // Take user choice
                if (choice4 == "1") {                                        // Encrypt message
                    Polybius_Square_Encryption();
                } else if (choice4 == "2") {                                 // Decrypt message
                    Polybius_Square_Decryption();
                } else {
                    cout << endl << "Invalid choice. Please, try again.";    // Error message for invalid choice
                    continue;
                }
                break;
            }
        }
        // Morse Cipher
        else if (choice1 == "8") {
            while (true) {
                string choice9;
                cout << "\n** Welcome To Morse Message Encryption **";
                cout << "\n-----------------------------------------";
                cout << "\nMorse Message Encoder is a program to translate a message to Morse code and the opposite. "
                        "\nAssume that each letter is separated by one space from the next and that each word is separated by three spaces from the next." << endl;
                cout << endl <<"Please, Choose what do you want to do.\n1) Encrypt a message using Morse Cipher  \n2) decrypt a message using Route Cipher \nEnter your choice from (1/2): ";
                getline(cin, choice9);  // Take user choice
                if (choice9 == "1") { // Encrypt message
                    string message;
                    cout << "\nPlease, Enter the message you want to encrypt: ";
                    getline(cin, message);  // Take user input
                    string morse_code = text_to_morse(message);   // Convert to Morse code
                    cout << "\nMorse text: " << morse_code << endl;    // Output Morse code
                } else if (choice9 == "2") {  // Decrypt message
                    string morse_code2;
                    cout << "\nPlease, Enter the Morse code to translate it: ";
                    getline(cin, morse_code2);                  // Take user input
                    string text = morse_to_text(morse_code2);  // Convert Morse code to text
                    cout << "\nDecrypted message: " << text << endl;   // Output decrypted message
                } else {
                    cout << endl << "Invalid choice. Please, try again.";  // Error message for invalid choice
                    continue;
                }
                break;
            }

        }
        else if (choice1 == "9") {
            while (true) {
                string choice4;
                // Display welcome message and the Explanation of the program to the user
                cout << "\n** Welcome To XOR Cipher Program **";
                cout << "\n-----------------------------------";
                cout << "\nIn this cipher, a secret key consisting of one letter (or more) is given from the sender to the reciver."
                        "Key can be any number of letters. Then each letter of the message goes through XOR operation with"
                        "one of the secret letters in order. The output is printed in text and hexadecimal."
                        "The original message can be recovered from the encrypted message by the same algorithm, XOR with the secret letter." << endl;
                cout << "\nPlease, Choose what do you want to do.\n1) Encrypt a message using XOR Cipher  \n2) Decrypt a message using XOR Cipher \nEnter your choice from (1/2): ";
                getline(cin, choice4);                                 // Take user choice
                if (choice4 == "1") {                                        // Encrypt message
                    Xor_encrypt();
                } else if (choice4 == "2") {                                 // Decrypt message
                    Xor_decrypt();
                } else {
                    cout << endl << "Invalid choice. Please, try again.";    // Error message for invalid choice
                    continue;
                }
                break;
            }
        }
        else if (choice1 == "10") {
            while (true) {
                string choice4;
                // Display welcome message and the Explanation of the program to the user
                cout << "\n** Welcome To Railfence Cipher Program **";
                cout << "\n--------------------------------------";
                cout << "\nThe railfence cipher is a very simple, easy to crack cipher. "
                        "It is a transposition cipher that follows a simple rule for mixing up the characters in the plaintext to form the ciphertext. "
                        "The railfence cipher offers essentially no communication security, "
                        "and it will be shown that it can be easily broken even by hand." << endl;
                cout << "\nPlease, Choose what do you want to do.\n1) Encrypt a message using Atbash Cipher  \n2) Decrypt a message using Atbash Cipher \nEnter your choice from (1/2): ";
                getline(cin, choice4);                                 // Take user choice
                if (choice4 == "1") {                                        // Encrypt message
                    railfence_cipher_Encryption();
                } else if (choice4 == "2") {                                 // Decrypt message
                    railfence_cipher_Decryption();
                } else {
                    cout << endl << "Invalid choice. Please, try again.";    // Error message for invalid choice
                    continue;
                }
                break;
            }
        }
        else {
            cout << endl << "Invalid choice. Please, try again.";
            continue;
        }
        string choice12;
        while (true){
            cout << endl << "\nDo you want to encrypt or decrypt another message? (Yes/No): ";
            cin >> choice12;    // Take user choice
            for (char &c : choice12){
                c = tolower(c);
            }
            if (choice12 == "yes") {
                cin.ignore();
                return main();
            }
            else if (choice12 == "no") {
                // Exit the program
                cout << "\nExiting the program..." << endl;
                exit(0);
            }
            else {
                cout << endl << "Invalid choice. Please try again." << endl;  // Error message for invalid choice
                cin.ignore();
                continue;
            }
        }
    }
    return 0;
}

/* The algorithm for all ciphers and deciphers:

 *START*
1. Display a welcome message.
2. Ask the user to choose an option:
   - Option 1: Affine Cipher Encryption
   - Option 2: Affine Cipher Decryption
   - Option 3: Route Cipher Encryption
   - Option 4: Route Cipher Decryption
   - Option 5: Encrypt with Atbash Cipher
   - Option 6: Decrypt with Atbash Cipher
   - Option 7: Encrypt with Vigenere Cipher
   - Option 8: Decrypt with Vigenere Cipher
   - Option 9: Encrypt with Baconian Cipher
   - Option 10: Decrypt with Baconian Cipher
   - Option 11: Encrypt with Simple Substitution Cipher
   - Option 12: Decrypt with Simple Substitution Cipher
   - Option 13: Encrypt with Polybius Square Cipher
   - Option 14: Decrypt with Polybius Square Cipher
   - Option 15: Convert text to Morse code
   - Option 16: Encrypt/Decrypt with XOR Cipher
   - Option 17: Encrypt with Rail Fence Cipher
   - Option 18: Decrypt with Rail Fence Cipher
3. If the user selects Option 1:
   - Call the Affine Cipher Encryption function.
4. If the user selects Option 2:
   - Call the Affine Cipher Decryption function.
5. If the user selects Option 3:
   - Call the Route Cipher Encryption function.
6. If the user selects Option 4:
   - Call the Route Cipher Decryption function.
7. If the user chooses Option 5:
   - Call the Atbash Cipher Encryption function.
8. If the user chooses Option 6:
   - Call the Atbash Cipher Decryption function.
9. If the user chooses Option 7:
   - Call the Vigenere Cipher Encryption function.
10. If the user chooses Option 8:
   - Call the Vigenere Cipher Decryption function.
11. If the user chooses Option 9:
   - Call the Baconian Cipher Encryption function.
12. If the user chooses Option 10:
   - Call the Baconian Cipher Decryption function.
13. If the user chooses Option 11:
   - Call the Simple Substitution Cipher Encryption function.
14. If the user chooses Option 12:
   - Call the Simple Substitution Cipher Decryption function.
15. If the user chooses Option 13:
   - Call the Polybius Square Cipher Encryption function.
16. If the user chooses Option 1:
   - Call the Polybius Square Cipher Decryption function.
17. If the user chooses Option 2:
   - Ask the user for the text to convert to Morse code.
   - Convert the text to Morse code using the Morse code map.
   - Display the Morse code.
18. If the user chooses Option 3:
   - Ask the user for the message to encrypt/decrypt and the XOR key.
   - Call the encryptDecrypt function with the input string.
19. If the user chooses Option 4:
   - Ask the user for the message to encrypt and the rail fence key.
   - Call the railfence_cipher_Encryption function.
20. If the user chooses Option 5:
   - Ask the user for the message to decrypt and the rail fence key.
   - Call the railfence_cipher_Decryption function.
21. If the user chooses an invalid option:
   - Display an error message.
22. *END*

*FUNCTION Affine Cipher Encryption*
1. Ask the user for the values of 'a' and 'b'.
2. Ask the user to enter the message to encrypt.
3. Initialize an empty string to store the encrypted message.
4. For each character in the message:
   - If the character is alphabetical:
     - Convert it to uppercase.
     - Calculate the encrypted value using the formula (a * x + b) % 26.
     - Append the encrypted character to the encrypted message.
   - If the character is not alphabetical, append it as it is.
5. Display the encrypted message.
6. *END*

*FUNCTION Affine Cipher Decryption*
1. Ask the user for the values of 'a', 'b', and 'c'.
2. Ask the user to enter the cipher text.
3. Initialize an empty string to store the decrypted message.
4. For each character in the cipher text:
   - If the character is alphabetical:
     - Convert it to uppercase.
     - Calculate the decrypted value using the formula c * (y - b).
     - Handle negative values by adding 26 repeatedly.
     - Append the decrypted character to the decrypted message.
   - If the character is not alphabetical, append it as it is.
5. Display the decrypted message.
6. *END*

*FUNCTION Route Cipher Encryption*
1. Ask the user for the key.
2. Ask the user to enter the message to encrypt.
3. Remove spaces and convert the message to uppercase.
4. Calculate the number of rows required based on the length of the message and the key.
5. Create a 2D array to store the message.
6. Fill the array with the message characters, padding with 'X' if necessary.
7. Encrypt the message using the Route Cipher algorithm.
8. Display the encrypted message.
9. *END*

*FUNCTION Route Cipher Decryption*
1. Ask the user for the key.
2. Ask the user to enter the message to decrypt.
3. Remove spaces and convert the message to uppercase.
4. Calculate the number of rows required based on the length of the message and the key.
5. Create a 2D array to store the message.
6. Decrypt the message using the Route Cipher algorithm.
7. Display the decrypted message.
8. *END*

*FUNCTION Atbash Cipher Encryption*
1. Ask the user for the message to encrypt.
2. Initialize an empty string to store the encrypted message.
3. For each character in the message:
   - If it is alphabetic, calculate its Atbash Cipher equivalent and append it to the encrypted message.
   - If it is not alphabetic, append it as it is.
4. Display the encrypted message.
5. *END*

*FUNCTION Atbash Cipher Decryption*
1. Ask the user for the encrypted message.
2. Initialize an empty string to store the decrypted message.
3. For each character in the encrypted message:
   - If it is alphabetic, calculate its Atbash Cipher equivalent and append it to the decrypted message.
   - If it is not alphabetic, append it as it is.
4. Display the decrypted message.
5. *END*

*FUNCTION Vigenere Cipher Encryption*
1. Ask the user for the message to encrypt and the keyword.
2. Initialize an empty string to store the encrypted message.
3. Convert the message and keyword to uppercase.
4. Encrypt each character of the message using the Vigenere Cipher algorithm and append it to the encrypted message.
5. Display the encrypted message.
6. *END*

*FUNCTION Vigenere Cipher Decryption*
1. Ask the user for the encrypted message and the keyword.
2. Initialize an empty string to store the decrypted message.
3. Convert the message and keyword to uppercase.
4. Decrypt each character of the message using the Vigenere Cipher algorithm and append it to the decrypted message.
5. Display the decrypted message.
6. *END*

*FUNCTION Baconian Cipher Encryption*
1. Ask the user for the message to encrypt.
2. Initialize an empty string to store the encrypted message.
3. For each character in the message:
   - If it's not a space, find its Baconian Cipher equivalent and append it to the encrypted message.
   - If it's a space, append a space to the encrypted message.
4. Display the encrypted message.
5. *END*

*FUNCTION Baconian Cipher Decryption*
1. Ask the user for the encrypted message.
2. Initialize an empty string to store the decrypted message.
3. Split the encrypted message into sets of 5 characters.
4. For each set:
   - If it doesn't start with a space, find its Baconian Cipher equivalent and append it to the decrypted message.
   - If it starts with a space, append a space to the decrypted message and skip the next set.
5. Display the decrypted message.
6. *END*

*FUNCTION Simple Substitution Cipher Encryption*
1. Ask the user for the message to encrypt and the keyword.
2. Initialize an empty string to store the encrypted message.
3. Prepare the keyword by removing duplicates and adding the remaining characters of the alphabet.
4. For each character in the message:
   - If it's not a space, find its substitution in the keyword and append it to the encrypted message.
   - If it's a space, append a space to the encrypted message.
5. Display the encrypted message.
6. *END*

*FUNCTION Simple Substitution Cipher Decryption*
1. Ask the user for the encrypted message and the keyword.
2. Initialize an empty string to store the decrypted message.
3. Prepare the keyword by removing duplicates and adding the remaining characters of the alphabet.
4. For each character in the encrypted message:
   - If it's not a space, find its corresponding letter in the alphabet using the keyword and append it to the decrypted message.
   - If it's a space, append a space to the decrypted message.
5. Display the decrypted message.
6. *END*

*FUNCTION Polybius Square Cipher Encryption*
1. Ask the user for the key and the message to encrypt.
2. Create a 5x5 alphabet square using the key.
3. Replace 'J' with 'I' in the message and convert it to uppercase.
4. For each character in the message:
   - Find its coordinates in the alphabet square and append them to the encrypted message.
   - If it's a space, append a space to the encrypted message.
5. Display the encrypted message.
6. *END*

*FUNCTION Polybius Square Cipher Decryption*
1. Ask the user for the key and the message to decrypt.
2. Create a 5x5 alphabet square using the key.
3. Replace 'J' with 'I' in the message and convert it to uppercase.
4. For each character in the message:
   - Find its coordinates in the alphabet square and append them to the decrypted message.
   - If it's a space, append a space to the decrypted message.
5. Display the decrypted message.
6. *END*

*FUNCTION Convert text to Morse code*
1. Ask the user for the text to convert to Morse code.
2. Convert each character of the text to its Morse code equivalent using the Morse code map.
3. Add a space between each Morse code letter and three spaces between each word.
4. Display the Morse code.
5. *END*

*FUNCTION Encrypt/Decrypt with XOR Cipher*
1. Ask the user for the message to encrypt/decrypt and the XOR key.
2. Perform bitwise XOR operation between each character of the message and the XOR key.
3. Display the encrypted/decrypted message.
4. *END*

*FUNCTION Encrypt with Rail Fence Cipher*
1. Ask the user for the message to encrypt and the rail fence key.
2. Create a rail fence matrix and fill it with the message characters in a zigzag pattern.
3. Concatenate the characters row by row to form the encrypted message.
4. Display the encrypted message.
5. *END*

*FUNCTION Decrypt with Rail Fence Cipher*
1. Ask the user for the message to decrypt and the rail fence key.
2. Create a rail fence matrix and mark the positions of the encrypted characters.
3. Traverse the matrix to extract the characters in the original order.
4. Display the decrypted message.
5. *END*

*START*
1. Display a welcome message.
2. Set a variable continueProgram to true.
3. While continueProgram is true, do the following:
   - Display a menu with cipher options.
   - Ask the user to choose a cipher option.
   - If the user chooses:
     - Option 1 (Affine Cipher):
       - Display a welcome message and explanation of the Affine Cipher.
       - Ask the user to choose between encryption and decryption.
       - If the user chooses encryption, call the Affine Cipher Encryption function.
       - If the user chooses decryption, call the Affine Cipher Decryption function.
     - Option 2 (Route Cipher):
       - Display a welcome message and explanation of the Route Cipher.
       - Ask the user to choose between encryption and decryption.
       - If the user chooses encryption, call the Route Cipher Encryption function.
       - If the user chooses decryption, call the Route Cipher Decryption function.
     - Option 3 (Atbash Cipher):
       - Display a welcome message and explanation of the Atbash Cipher.
       - Ask the user to choose between encryption and decryption.
       - If the user chooses encryption, call the Atbash Cipher Encryption function.
       - If the user chooses decryption, call the Atbash Cipher Decryption function.
     - Option 4 (Vigenere Cipher):
       - Display a welcome message and explanation of the Vigenere Cipher.
       - Ask the user to choose between encryption and decryption.
       - If the user chooses encryption, call the Vigenere Cipher Encryption function.
       - If the user chooses decryption, call the Vigenere Cipher Decryption function.
     - Option 5 (Baconian Cipher):
       - Display a welcome message and explanation of the Baconian Cipher.
       - Ask the user to choose between encryption and decryption.
       - If the user chooses encryption, call the Baconian Cipher Encryption function.
       - If the user chooses decryption, call the Baconian Cipher Decryption function.
     - Option 6 (Simple Substitution Cipher):
       - Display a welcome message and explanation of the Simple Substitution Cipher.
       - Ask the user to choose between encryption and decryption.
       - If the user chooses encryption, call the Simple Substitution Cipher Encryption function.
       - If the user chooses decryption, call the Simple Substitution Cipher Decryption function.
     - Option 7 (Polybius Square Cipher):
       - Display a welcome message and explanation of the Polybius Square Cipher.
       - Ask the user to choose between encryption and decryption.
       - If the user chooses encryption, call the Polybius Square Cipher Encryption function.
       - If the user chooses decryption, call the Polybius Square Cipher Decryption function.
     - Option 8 (Morse Cipher):
       - Display a welcome message and explanation of the Morse Cipher.
       - Ask the user to choose between encryption and decryption.
       - If the user chooses encryption, convert the message to Morse code.
       - If the user chooses decryption, convert the Morse code to text.
     - Option 9 (XOR Cipher):
       - Display a welcome message and explanation of the XOR Cipher.
       - Ask the user to choose between encryption and decryption.
       - If the user chooses encryption, call the XOR Cipher Encryption function.
       - If the user chooses decryption, call the XOR Cipher Decryption function.
     - Option 10 (Rail-fence Cipher):
       - Display a welcome message and explanation of the Rail-fence Cipher.
       - Ask the user to choose between encryption and decryption.
       - If the user chooses encryption, call the Rail-fence Cipher Encryption function.
       - If the user chooses decryption, call the Rail-fence Cipher Decryption function.
     - If the user chooses an invalid option, display an error message.
   - Ask the user if they want to encrypt or decrypt another message.
   - If the user chooses "Yes," return to the beginning of the loop.
   - If the user chooses "No," display a goodbye message and exit the program.
   - If the user inputs an invalid choice, ask again.
4. *END*

 */
