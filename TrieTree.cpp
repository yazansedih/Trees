
#include <iostream>
#include <cstring>
#include <cctype> 
#include <vector> 

using namespace std;

const int SIZE = 26;
char** results;
int k = 0;


struct TrieNode {
    TrieNode* children[SIZE*2];
    bool isEndOfWord;

    TrieNode() {
        for (int i = 0; i < SIZE*2; i++) {
            children[i] = nullptr;
        }
        isEndOfWord = false;
    }
};

class Trie {
private:
    TrieNode* root;

    void insertUtil(TrieNode* node, const char* key) {
        bool isFirstChar = true; 
        for (int i = 0; key[i] != '\0'; i++) {
            char currentChar = isFirstChar ? toupper(key[i]) : tolower(key[i]);
            int index = isFirstChar ? (currentChar - 'A') : (currentChar - 'a');
            if (!node->children[index]) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
            isFirstChar = false; 
        }
        node->isEndOfWord = true;
    }

    bool searchUtil(TrieNode* node, const char* key) {
        bool isFirstChar = true;     
        for (int i = 0; key[i] != '\0'; i++) {
            int index = isFirstChar ? (key[i] - 'A') : (key[i] - 'a');
            if (!node->children[index]) {
                return false;
            }
            node = node->children[index];
            isFirstChar = false;
        }
        return (node != nullptr && node->isEndOfWord);
    }

    void deleteUtil(TrieNode* node, const char* key) {
        if (!node) {
            return;
        }

        bool isFirstChar = true;  
        TrieNode* current = node;
        for (int i = 0; key[i] != '\0'; i++) {
            int index = isFirstChar ? (key[i] - 'A') : (key[i] - 'a');
            if (!current->children[index]) {
                return; // String not found, nothing to delete
            }
            current = current->children[index];
            isFirstChar = false;
        }
        current->isEndOfWord = false;
    }

    void longestUtil(TrieNode* node, char* current, char** longest) {
        if (node->isEndOfWord) {
            if (strlen(current) > strlen(*longest)) {
                delete[] *longest;
                *longest = new char[strlen(current) + 1];
                strcpy(*longest, current);
            }
        }

        for (int i = 0; i < SIZE; i++) {
            if (node->children[i]) {
                char newCurrent[2] = {static_cast<char>(i + 'A'), '\0'};
                char newStr[50];
                strcpy(newStr, current);
                strcat(newStr, newCurrent);
                longestUtil(node->children[i], newStr, longest);
            }
        }
    }

    void printSortedUtil(TrieNode* node, char* prefix, bool isFirstChar) {

        if (node->isEndOfWord) {
            // cout << prefix << endl;
            results[k] = new char[strlen(prefix) + 1];
            strcpy(results[k],prefix);
            k++;
        }

        for (int i = 0; i < SIZE; i++) {
            if (node->children[i]) {
                char newPrefix[2] = {static_cast<char>(i + 'a'), '\0'}; // only smalle because i make concatenate with prefix
                char newStr[50];
                strcpy(newStr, prefix);
                strcat(newStr, newPrefix);
                printSortedUtil(node->children[i], newStr, false); // Reset the flag here
            }
        }
    }

    


public:
    Trie() {
        root = new TrieNode();
    }

    void insert(const char* key) {
        insertUtil(root, key);
    }

    bool search(const char* key) {
        return searchUtil(root, key);
    }

    void remove(const char* key) {
        deleteUtil(root, key);
    }

    void printLongest() {
        char* longest = new char[52];
        longest[0] = '\0';
        longestUtil(root, "", &longest);

        if (strlen(longest) > 0) 
            longest[0] = toupper(longest[0]);

        for (int i = 1; longest[i] != '\0'; i++) 
            longest[i] = tolower(longest[i]);

        // cout << longest << endl;
        results[k] = new char[strlen(longest) + 1];
        strcpy(results[k],longest);
        k++;
        delete[] longest;
    }

    void StartsWith(const char* prefix) {
        bool isFirstChar = true;
        TrieNode* node = root;
        for (int i = 0; prefix[i] != '\0'; i++) {
            int index = isFirstChar ? (prefix[i] - 'A') : (prefix[i] - 'a');
            if (!node->children[index]) {
                return; // Prefix not found
            }
            node = node->children[index];
            isFirstChar = false;
        }
        printSortedUtil(node, const_cast<char*>(prefix), true); // Pass the flag as an argument
    }

};

int main() {
    Trie trie;
    int N;
    cin >> N;

    results = new char*[N];
    for (int i = 0; i < N; i++) {
        char str[100];
        char command[10];
        cin >> command;

        if (strcmp(command, "insert") == 0) {
            cin >> str;
            trie.insert(str);
        } else if (strcmp(command, "delete") == 0) {
            cin >> str;
            trie.remove(str);
        } else if (strcmp(command, "search") == 0) {
            cin >> str;
            results[k] = new char[4]; // Assuming "YES" or "NO" will be stored
            strcpy(results[k], trie.search(str) ? "YES" : "NO");
            k++;
        } else if (strcmp(command, "startwith") == 0) {
            cin >> str;
            trie.StartsWith(str);
        } else if (strcmp(command, "longest") == 0) {
            trie.printLongest();
        } else {
            cout << "Invalid command" << endl;
        }
    }

    for (int i = 0; i < N; i++) {
        if (results[i] != nullptr) {
            cout << results[i] << endl;
            delete[] results[i]; 
        }
    }
    delete[] results;

    return 0;
}

// 12
// insert Mall
// insert Me
// insert Mat
// insert Cat
// insert Rat
// insert Mandy
// delete Mandy
// startwith Ma
// search Cat
// search Me
// search Mandy
// longest
// Sample Output 0

// Mall
// Mat
// YES
// YES
// NO
// Mall