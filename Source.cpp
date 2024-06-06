#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <conio.h>

using namespace std; // I used namespace std to avoid writing std:: before cout, cin, endl, etc.

const int ALPHABET_SIZE = 26; // I used a constant for the alphabet size to make the code more readable




class TrieNode // I used a class for the TrieNode to make the code more readable
{
public: // I used public access modifier to make the code more readable

    TrieNode* children[ALPHABET_SIZE]; // I used an array of TrieNode pointers to store the children of a node

    string meaning; // I used a string to store the meaning of a word

    bool isEndOfWord; // I used a boolean to mark the end of a word

    TrieNode() // I used a constructor to initialize the TrieNode
    {

        for (int i = 0; i < ALPHABET_SIZE; ++i) // I used a for loop to initialize the children of a node
        {
            children[i] = nullptr; // I used nullptr to initialize the children of a node
        }

        meaning = ""; // I used an empty string to initialize the meaning of a word

        isEndOfWord = false; // I used false to initialize the end of a word
    }
};





class Trie
{ // I used a class for the Trie to make the code more readable

private: // I used private access modifier to make the code more readable

    TrieNode* root; // I used a TrieNode pointer to store the root node

public:
    Trie()
    { // I used a constructor to initialize the Trie

        root = new TrieNode(); // I used new to initialize the root node
    }

    void insert(const string& word, const string& meaning) // Insert a word into the trie
    {
        TrieNode* current = root; // Start from the root node

        for (int i = 0; i < word.length(); ++i)// Traverse the trie
        {

            char ch = word[i]; // Get the current character

            if (ch == ' ')
                continue;

            int index = ch - 'a'; // Get the index of the character

            if (!current->children[index]) // If the character is not found 
            {
                current->children[index] = new TrieNode(); // Create a new node
            }

            current = current->children[index]; // Move to the next node
        }

        current->meaning = meaning; // Set the meaning of the word

        current->isEndOfWord = true; // Mark the end of the word
    }

    void deletenode(string& word, string& meaning) // Insert a word into the trie
    {
        TrieNode* current = root; // Start from the root node

        for (int i = 0; i < word.length(); ++i)// Traverse the trie
        {

            char ch = word[i]; // Get the current character
            /*if (ch == ' ')
                continue;*/

            int index = ch - 'a'; // Get the index of the character

            if (!current->children[index]) // If the character is not found 
            {
                current->children[index] = NULL;
            }

            current = current->children[index]; // Move to the next node
        }

        current->meaning = " "; // Set the meaning of the word

        current->isEndOfWord = true; // Mark the end of the word
    }


    bool search(const string& word, string& meaning) const
    {
        const TrieNode* node = searchNode(word); // Search for the word in the trie

        if (node && node->isEndOfWord) // If the word is found and it is the end of a word
        {
            meaning = node->meaning; // Get the meaning of the word

            return true; // Word found
        }

        return false; // Word not found
    }

    TrieNode* getRoot() const { // Getter for the root node

        return root; // Return the root node
    }

    TrieNode* searchNode(const string& word) const { // Search for a word in the trie

        TrieNode* current = root; // Start from the root node


        for (int i = 0; i < word.length(); ++i) // Traverse the trie
        {

            char ch = word[i]; // Get the current character

            int index = ch - 'a'; // Get the index of the character

            if (!current->children[index]) // If the character is not found
            {
                return nullptr; // Return null
            }

            current = current->children[index]; // Move to the next node
        }


        return current; // Return the node
    }

};







class Dictionary  // I used a class for the Dictionary to make the code more readable
{

private:

    Trie trie; // I used a Trie to store the words and meanings

public:

    bool isLoaded = false; // I used a boolean to check if the dictionary is loaded

    //Function to load words and meanings from a file into the dictionary

        void LoadDictionary(const string& filename)
    {
        if (isLoaded)
        { // Check if the dictionary is already loaded
            cout << "\n\t    |====================================================================|\n\n";
            cout << endl << "\t      DICTIONARY IS ALREADY LOADED." << endl;
            cout << "\n\t    |====================================================================|\n\n";
            return;
        }
        cout << "\n\t    |====================================================================|\n\n";
        cout << "\n\t      Loading dictionary... Please wait..." << endl;
        cout << "\n\t    |====================================================================|\n\n";
        ifstream file(filename); // Open the file

        try
        {
            if (!file.is_open()) { // Check if the file is open
                throw runtime_error("Error opening file."); // Throw an exception
            }

            string line; // I used a string to store a line from the file 

            while (getline(file, line))
            { // Read the file line by line

                istringstream iss(line); // I used istringstream to read the line

                string word;

                string meaning;

                //Read the word

                    if (getline(iss, word, '\t'))
                    { // I used '\t' as a delimiter to separate the word and the meaning

                       /// Read the rest of the line as the meaning
                            getline(iss >> ws, meaning);

                        ///Convert the word to lowercase before inserting into the trie
                            string lowercaseWord = transformToLowercase(word); // I used transformToLowercase to convert the word to lowercase
                        trie.insert(lowercaseWord, meaning); // Insert the word and the meaning into the trie
                    }
            }

            cout << endl << "\t      DICTIONARY LOADED SUCCESSFULLY." << endl;
            cout << "\n\t    |====================================================================|\n\n";

            isLoaded = true; // Set the flag to true after loading
        }
        catch (const exception& e)

        { // Handle exceptions

            cerr << "Exception: " << e.what() << endl;
        }
        catch (...)// Handle unknown exceptions
        {

            cerr << "An unknown exception occurred." << endl;
        }
    }

    void updateDictionary(const string& filename, string key)
    {
        string update;

        if (!isLoaded)
        { // Check if the dictionary is already loaded
            cout << "Dictionary is not loaded." << endl;
            return;
        }

        TrieNode* current = trie.getRoot(); // Start from the root node
        bool found = 1;

        for (int i = 0; i < key.length(); ++i) // Traverse the trie
        {

            char ch = key[i]; // Get the current character

            int index = ch - 'a'; // Get the index of the character

            if (!current->children[index]) // If the character is not found
            {
                found = 0;
                break;
            }
            current = current->children[index]; // Move to the next node
        }
        if (found == 1 && current->isEndOfWord) // If the word is found and it is the end of a word
        {
            cout << endl << "\t      WORD IS FOUND" << endl << endl;
            cout << "\t    |====================================================================|\n";

            cout << "\t      PLEASE INPUT THE MEANING TO UPDATE : ";
            cin >> update;
            cout << "\n\t    |====================================================================|\n";
            current->meaning = update;

            cout << "\n\t      Updating dictionary... Please wait..." << endl;
            cout << "\n\t    |====================================================================|\n";

            ifstream inputFile(filename);  // Open the file for reading
            ofstream tempFile("temp.txt");  // Create a temporary file for writing

            try {
                if (!inputFile.is_open()) {
                    throw runtime_error("Error opening file for reading: " + filename);
                }

                if (!tempFile.is_open()) {
                    throw runtime_error("Error opening temporary file for writing.");
                }

                string line;

                while (getline(inputFile, line)) {
                    //Assuming the format is "WORD\tMEANING"
                        size_t pos = line.find('\t');
                    if (pos != string::npos) {
                        string word = line.substr(0, pos);
                        string meaning = line.substr(pos + 1);

                        if (word == key) {
                            //Update the meaning for the specific word
                                tempFile << key << "\t\t\t\t\t" << current->meaning << "\n";
                        }
                        else {
                            //Copy unchanged lines to the temporary file
                                tempFile << line << endl;
                        }
                    }
                    else {
                        //Handle invalid format or empty lines as needed
                    }
                }

                //Close the input and temporary files
                    inputFile.close();
                tempFile.close();

                //Replace the original file with the temporary file
                    remove(filename.c_str());        // Remove the original file
                rename("temp.txt", filename.c_str());  // Rename the temporary file

                cout << endl << "\t      WORD SUCCESSFULLY UPDATED" << endl << endl;
                cout << endl << "\t      DICTIONARY SAVED SUCCESSFULLY." << endl;
                cout << "\t    |====================================================================|\n";

                isLoaded = true;
            }
            catch (const exception& e) {
                cerr << "Exception: " << e.what() << endl;
            }
            catch (...) {
                cerr << "An unknown exception occurred." << endl;
            }
        }
        else
        {
            cout << endl << "WORD TO BE UPDATED NOT FOUND" << endl << endl;
        }


    }

    void deleteWorddic(string filename, string& key)
    {
        char cho;
        while (true)
        {
            cout << "\n\t    |====================================================================|\n";
            cout << "\n\t\tWORD:  " << key << endl << endl;
            cout << "\t\tARE YOU SURE YOU WISH TO DELETE THIS WORD ?  (Y:YES       N:NO)   ";
            cho = _getch();
            if (!(cho == 'Y' || cho == 'y' || cho == 'N' || cho == 'n'))
            {
                system("cls");
                cout << "\n\t\tInvalid Input... Please ReEnter...\n\n";
                continue;
            }
            else if (cho == 'Y' || cho == 'y')
            {
                break;
            }
            else if (cho == 'N' || cho == 'n')
            {
                return;
            }

        }
        TrieNode* current = trie.getRoot(); // Start from the root node
        bool found = 1;
        string del;

        for (int i = 0; i < key.length(); ++i) // Traverse the trie
        {

            char ch = key[i]; // Get the current character

            int index = ch - 'a'; // Get the index of the character

            if (!current->children[index]) // If the character is not found
            {
                found = 0;
                break;
            }
            current = current->children[index]; // Move to the next node
        }

        if (found == 1 && current->isEndOfWord) // If the word is found and it is the end of a word
        {

            del = "";
            cout << "\n\t    |====================================================================|\n";
            current->meaning = del;
            current->isEndOfWord = 0;

            cout << "\n\t      Deleting word from dictionary... Please wait..." << endl;
            cout << "\n\t    |====================================================================|\n";

            ifstream inputFile(filename);  // Open the file for reading
            ofstream tempFile("temp.txt");  // Create a temporary file for writing

            try {
                if (!inputFile.is_open())
                {
                    throw runtime_error("Error opening file for reading: " + filename);
                }

                if (!tempFile.is_open())
                {
                    throw runtime_error("Error opening temporary file for writing.");
                }

                string line;

                while (getline(inputFile, line))
                {
                   // Assuming the format is "WORD\tMEANING"
                        size_t pos = line.find('\t');
                    if (pos != string::npos)
                    {
                        string word = line.substr(0, pos);
                        string meaning = line.substr(pos + 1);

                        if (word == key) {
                            //Update the meaning for the specific word
                                tempFile << "\n";
                        }
                        else {
                            //Copy unchanged lines to the temporary file
                                tempFile << line << endl;
                        }
                    }
                    else {
                        //Handle invalid format or empty lines as needed
                    }
                }

                //Close the input and temporary files
                    inputFile.close();
                tempFile.close();

                //Replace the original file with the temporary file
                    remove(filename.c_str());        // Remove the original file
                rename("temp.txt", filename.c_str());  // Rename the temporary file

                cout << endl << "\t      WORD DELETED SUCCESSFULLY...." << endl << endl;
                cout << endl << "\t      CHANGES IN FILE ARE SAVED.\n" << endl;
                cout << "\t    |====================================================================|\n";

                isLoaded = true;
            }
            catch (const exception& e)
            {
                cerr << "Exception: " << e.what() << endl;
            }
            catch (...)
            {
                cerr << "An unknown exception occurred." << endl;
            }
        }
        else
        {
            cout << endl << "WORD TO BE Deleted NOT FOUND" << endl << endl;
        }

    }


    void exploreSuggestions(TrieNode* node, const string& partialTerm, string suggestions[], int& count) {
        if (node->isEndOfWord && count < 10) {
            suggestions[count++] = "Word: " + partialTerm + "\t\t\t| Meaning: " + node->meaning;
        }

        for (int i = 0; i < 26; ++i) {
            if (node->children[i]) {
                char ch = static_cast<char>('a' + i);
                exploreSuggestions(node->children[i], partialTerm + ch, suggestions, count);
            }
        }
    }

    void suggestRelatedTerms(const Trie& termTrie, string& partialTerm) {
        TrieNode* current = termTrie.getRoot();
        for (char character : partialTerm) {
            int index = character - 'a';
            if (!current->children[index]) {
                cout << "WORD NOT FOUND" << endl;
                return;
            }
            current = current->children[index];
        }

        string termSuggestions[10];
        int count = 0;

        exploreSuggestions(current, partialTerm, termSuggestions, count);

        cout << endl << "\t\tSUGGESTIONS : " << endl << endl;
        for (int i = 0; i < 10; ++i)
        {
            cout << "\t\t " << termSuggestions[i] << endl;
        }
    }

    //Function to show all the loaded words from the dictionary
        void ShowAllWords()
    {
        cout << "Showing all words in alphabetical order..." << endl;

        //Display words using Trie traversal

            displayTrieWords(trie); // I used displayTrieWords to display the words in alphabetical order
    }

    //Function to add a word to the dictionary(case-insensitive)

        void AddWord(const string& word, const string& meaning)

    {
        //Convert the word to lowercase before adding

            string lowercaseWord = transformToLowercase(word);

        //Check if the word already exists

            string existingMeaning;

        if (trie.search(lowercaseWord, existingMeaning))
        {
            cout << "\n\t\tWord already exists: " << lowercaseWord << "\t\t\t| Meaning: " << existingMeaning << endl;
        }
        else
        {
            trie.insert(lowercaseWord, meaning);

            cout << "Word added successfully." << endl;

            //Append the new word and meaning to the "dictionary.txt" file

                ofstream dictionaryFile("dictionary.txt", ios::app);

            if (dictionaryFile.is_open())
            {
                dictionaryFile << lowercaseWord << "\t" << meaning << "\n";

                dictionaryFile.close();

                cout << "Word added to the dictionary file." << endl;
            }
            else
            {
                cerr << "Error opening dictionary file for appending." << endl;
            }
        }
    }



    //Function to search for a word in the dictionary(case-insensitive)

        void SearchWord(string& word)
    {
       // Convert the search term to lowercase

            string lowercaseWord = transformToLowercase(word);

        //Search for the word in the trie

            string meaning;

        if (trie.search(lowercaseWord, meaning))
        {
            char cho;
            while (1)
            {
                cout << "\n\t\tWord: " << lowercaseWord << "\t\t\t| Meaning: " << meaning << endl;
                cout << "\n\t\tU: Update Word\n\t\tD: Delete Word\n\t\tS: Suggested Words\n\t\tEsc: Exit\n\t\t";
                cho = _getch();
                if (!(cho == 'U' || cho == 'u' || cho == 'D' || cho == 'd' || cho == 'S' || cho == 's' || cho == 27))
                {
                    system("cls");
                    cout << "\n\t\tInvalid Input... Please ReEnter...\n\n";
                    continue;
                }
                break;
            }

            if (cho == 'D' || cho == 'd')  //Delete word
            {
                while (true)
                {
                    cout << "\n\t\tDelete Word?\t( Y:Yes     N:NO ). ";

                    cho = _getch();

                    if (cho == 'Y' || cho == 'y')
                    {

                        break;
                    }

                    else if (cho == 'N' || cho == 'n')
                    {
                        break;
                    }

                    else
                    {
                        cout << "\n\t\tInvalid Input...Try Again...";
                    }
                }
            }

            else if (cho == 'U' || cho == 'u')  //Update Words
            {
                while (true)
                {
                    cout << "\n\t\tUpdate Word?\t( Y:Yes     N:NO ). ";

                    cho = _getch();

                    if (cho == 'Y' || cho == 'y')
                    {

                        break;
                    }

                    else if (cho == 'N' || cho == 'n')
                    {
                        break;
                    }

                    else
                    {
                        cout << "\n\t\tInvalid Input...Try Again...";
                    }
                }
            }
            else if (cho == 'S' || cho == 's') //Suggestions Words
            {
                string check = "";
                check += word[0];
                suggestRelatedTerms(trie, check);
            }

        }


        else
        {
            cout << "\n\t\tWord not found" << endl;
        }
    }

private:
    //Display words using Trie traversal


        void displayTrieWords(const Trie& trie, const TrieNode* node = nullptr, string currentWord = "") const
    { // I used a default argument to make the code more readable

        if (!node) // If the node is null, start from the root node
        {
            node = trie.getRoot(); // Get the root node
        }

        if (node->isEndOfWord) // If the node is the end of a word
        {
            cout << "\n\t\tWord: " << currentWord << "\t\t\t| Meaning: " << node->meaning << endl; // Display the word and the meaning
        }

        for (int i = 0; i < ALPHABET_SIZE; ++i) // Traverse the trie
        {
            if (node->children[i]) // If the child is not null
            {
                char ch = 'a' + i; // Get the character

                displayTrieWords(trie, node->children[i], currentWord + ch); // Recursively display the words

            }
        }
    }
    //Function to transform a string to lowercase

        string transformToLowercase(const string& str) const
    {
        string result = str; // I used a string to store the result

        for (int i = 0; i < str.length(); ++i) { // Traverse the string

            result[i] = tolower(str[i]); // Convert the character to lowercase
        }

        return result; // Return the result
    }
};

int main()
{
    Dictionary myDictionary;
    char choice, go = '0';
    string word, meaning, update;

    do {
        system("Color F0");
        cout << "\t\t **********************************\n";
        cout << "\t\t **********************************\n";
        cout << "\t\t **   Welcome to the Dictionary  **\n";
        cout << "\t\t **********************************\n";
        cout << "\t\t **********************************\n";
        cout << "\n" << endl;

        cout << "\t      |=====================================|\n";
        cout << "\t\tPRESS 1 TO LOAD DICTIONARY\n";
        cout << "\t      |=====================================|\n";
        cout << "\t\tPRESS 2 TO DISPLAY ALL WORDS\n";
        cout << "\t      |=====================================|\n";
        cout << "\t\tPRESS 3 TO ADD WORD\n";
        cout << "\t      |=====================================|\n";
        cout << "\t\tPRESS 4 TO DELETE A WORD\n";
        cout << "\t      |=====================================|\n";
        cout << "\t\tPRESS 5 TO SEARCH A WORD\n";
        cout << "\t      |=====================================|\n";
        cout << "\t\tPRESS 6 TO UPDATE A WORD\n";
        cout << "\t      |=====================================|\n";

        cout << "\n\t\tPRESS Esc TO END PROGRAM\n\n";

        cout << "\t      |=====================================|\n";
        cout << "\t\tPRESS 0 TO SEE CREDITS OF DICTIONARY\n";
        cout << "\t      |=====================================|\n";

        cout << "\n\t\tPRESS 1,2,3,4,5,6 OR Esc TO PERFORM FUNCTIONS\n";

        choice = _getch();

        switch (choice)
        {
        case '1':
            system("cls");
            system("Color B5");

            myDictionary.LoadDictionary("dictionary.txt");
            system("pause");
            break;

        case '2':
            system("cls");
            system("Color 04");

            if (!myDictionary.isLoaded)
            {
                cout << "DICTIONARY NOT LOADED. PLEASE LOAD THE DICTIONARY FIRST." << endl;
                break;
            }
            myDictionary.ShowAllWords();
            system("pause");
            break;

        case '3':
            system("cls");
            system("Color 4F");

            if (!myDictionary.isLoaded)
            {
                cout << "DICTIONARY NOT LOADED. PLEASE LOAD THE DICTIONARY FIRST." << endl;
                break;
            }
            cout << "\n\t\tADD A WORD\n";
            cout << "\t\t----------------\n";
            cout << "\t\tPLEASE ENTER THE WORD: ";
            cin >> word;
            cout << "\t\tPLEASE ENTER THE MEANING: ";
            getline(cin >> ws, meaning); // Read the meaning including whitespaces
            myDictionary.AddWord(word, meaning);
            system("pause");
            break;

        case '4':
            system("cls");
            system("Color 97");
            if (!myDictionary.isLoaded) {
                cout << "DICTIONARY NOT LOADED. PLEASE LOAD THE DICTIONARY FIRST." << endl;
                break;
            }
            cout << "\n\t    |====================================================================|\n";
            cout << "\n\t\tDELETE A WORD\n";
            cout << "\t\t----------------\n";
            cout << "\t\tENTER THE WORD TO DELETE: ";
            cin >> word;
            myDictionary.deleteWorddic("dictionary.txt", word);
            system("pause");
            break;

        case '5':
            system("cls");
            system("Color 8E");

            if (!myDictionary.isLoaded) {
                cout << "DICTIONARY NOT LOADED. PLEASE LOAD THE DICTIONARY FIRST." << endl;
                break;
            }
            cout << "\n\t\tSEARCH A WORD\n";
            cout << "\t\t----------------\n";
            cout << "\t\tENTER THE WORD TO SEARCH: ";
            cin >> word;
            myDictionary.SearchWord(word);
            system("pause");
            break;

        case '6':
            while (go != 27)
            {
                system("cls");
                system("Color 04");
                cout << "\t    |====================================================================|\n";
                cout << endl << "\t     PLEASE INPUT THE WORD THAT NEED TO BE UPDATED : ";
                cin >> update;
                cout << "\n\t    |====================================================================|\n\n";
                myDictionary.updateDictionary("dictionary.txt", update);
                cout << endl << "\t     PLEASE PRESS Esc IF YOU DON'T WANT TO UPDATE MORE WORDS, OTHERWISE PRESS ANY KEY ";
                go = _getch();
            }
            system("pause");
            break;

        case '0':
            system("cls");
            system("Color F4");
            cout << "\t      |=====================================|\n";
            cout << "\n\t\tTHANK YOU FOR USING THE DICTIONARY ;)" << endl;
            cout << "\n\t\tCredits:\n\t\t\tUSMAN AWAN (22F-3378)\n\t\t\tMUTASIM BILLAH (22F-8772)\n\t\t\tMUHAMMAD HOUD (22F-3376)\n\n";
            cout << "\t      |=====================================|\n";
            cout << endl << endl;
            system("pause");
            break;

        default:
            cout << "INVALID CHOICE." << endl;
            break;
        }

        cout << endl;

        system("cls");

    } while (choice != 27);
    system("Color F4");
    cout << "\t      |=====================================|\n";
    cout << "\n\t\tTHANK YOU FOR USING THE DICTIONARY ;)" << endl;
    cout << "\n\t\tCredits:\n\t\t\tUSMAN AWAN (22F-3378)\n\t\t\tMUTASIM BILLAH (22F-8772)\n\t\t\tMUHAMMAD HOUD (22F-3376)\n\n";
    cout << "\t      |=====================================|\n";
    cout << endl << endl;
    return 0;
}

//Functions with O(1) Time Complexity :
//Trie Constructor : O(1)
//Trie GetRoot : O(1)
//TrieNode Constructor : O(1)
//Functions with O(n) Time Complexity :
//Trie Insert : O(word_length)
//Trie Search : O(word_length)
//Trie SearchNode : O(word_length)
//Dictionary AddWord : O(word_length)
//transformToLowercase : O(str_length)
//Main Loop(Per Iteration) : O(1)
//Functions with O(m* n) Time Complexity :
//Dictionary LoadDictionary : O(number_of_words* average_word_length)
//Dictionary ShowAllWords : O(total_number_of_characters_in_trie)
//displayTrieWords : O(total_number_of_characters_in_trie)
//updateDictionary: O(k + n)
//exploreSuggestions: O(b^d)
//suggestRelatedTerms: O(k + b^d)
