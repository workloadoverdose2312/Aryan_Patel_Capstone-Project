#include <iostream>
#include <vector>
#include <fstream>

#define RESET "\033[0m"
#define RED "\033[31m"

using namespace std;

class node
{
public:
    node *children[26];
    bool end_of_word;

    node()
    {
        for (int i = 0; i < 26; i++)
        {
            children[i] = nullptr;
        }
        end_of_word = false;
    }
};

class Trie
{
public:
    node *root;

    Trie()
    {
        root = new node();
    }

    void insert_word(string words)
    {
        node *current = root;
        for (int i = 0; i < words.length(); i++)
        {
            if (words[i] == '.' || words[i] == ',' || words[i] == '!')
            {
                continue;
            }
            else if (words[i] >= 97 && words[i] <= 122)
            {
                int index = words[i] - 'a';
                if (current->children[index] == nullptr)
                {
                    current->children[index] = new node();
                }
                if (i == words.length() - 1)
                {
                    current->children[index]->end_of_word = true;
                }
                current = current->children[index];
            }
            else if (words[i] >= 65 && words[i] <= 90)
            {
                words[i] = words[i] + 32;
                int index = words[i] - 'a';
                if (current->children[index] == nullptr)
                {
                    current->children[index] = new node();
                }
                if (i == words.length() - 1)
                {
                    current->children[index]->end_of_word = true;
                }
                current = current->children[index];
            }
        }
    }

    bool search(string key)
    {
        node *current = root;
        for (int i = 0; i < key.length(); i++)
        {

            int index = key[i] - 'a';
            if (current->children[index] == nullptr)
            {
                return false;
            }
            if (i == key.length() - 1 && current->children[index]->end_of_word == false)
            {
                return false;
            }
            current = current->children[index];
        }
        return true;
    }

    vector<string> suggestCorrections(const string &wrongString)
    {
        node *current = root;
        vector<string> suggestions;
        string prefix = "";

        for (int i = 0; i < wrongString.length(); i++)
        {
            int index = wrongString[i] - 'a';

            if (current->children[index] == nullptr)
            {
                exploreSuggestions(current, prefix, suggestions);
                break;
            }

            prefix += wrongString[i];
            current = current->children[index];
        }
        return suggestions;
    }

    string exploreSuggestions(node *node, string prefix, vector<string> &suggestions)
    {
        if (node->end_of_word)
        {
            suggestions.push_back(prefix);
        }

        for (int i = 0; i < 26; ++i)
        {
            if (node->children[i] != nullptr)
            {
                char nextChar = 'a' + i;
                exploreSuggestions(node->children[i], prefix + nextChar, suggestions);
            }
        }

        return "";
    }
};

vector<string> load_dictionary(const string &filename)
{
    vector<string> dictionary;
    ifstream file(filename);
    string word;
    if (file.is_open())
    {
        while (file >> word)
        {
            dictionary.push_back(word);
        }
        file.close();
        return dictionary;
    }
    else
    {
        cout << "Unable to open the file" << endl;
        return dictionary;
    }
}

vector<string> check_string(const string &filename)
{
    vector<string> check;
    ifstream file(filename);
    string word;
    if (file.is_open())
    {
        while (file >> word)
        {
            check.push_back(word);
        }
        file.close();
    }
    else
    {
        cout << "Unable to open the file " << endl;
    }
    return check;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<string> dictionary = load_dictionary("dictionary_111.txt");
    Trie trie;
    for (int i = 0; i < dictionary.size(); i++)
    {
        trie.insert_word(dictionary[i]);
    }
    cout << dictionary.size() << endl;

    ifstream file("input.txt");
    string coloured_file;
    vector<string> wrong_file;
    vector<string> wrong_word;
    vector<string> corrected_word;
    if (file.is_open())
    {
        string word;

        while (file >> word)
        {

            char lastChar = word.back();
            string trimmedWord = word;
            if (lastChar == '.' || lastChar == ',' || lastChar == ';' || lastChar == '/' || lastChar == '&' || lastChar == '^' || lastChar == '!')
            {
                trimmedWord = word.substr(0, word.length() - 1);
            }

            if (trie.search(trimmedWord))
            {
                coloured_file += word + " ";
                wrong_file.push_back(trimmedWord);
            }
            else
            {
                wrong_word.push_back(trimmedWord);
                corrected_word.push_back(trimmedWord);
                coloured_file += RED + trimmedWord + RESET;
                if (lastChar == '.' || lastChar == ',')
                {
                    coloured_file += lastChar;
                }
                coloured_file += " ";
            }
        }
        file.close();
    }
    else
    {
        cout << "Error opening the file" << endl;
    }
    cout << "The errors are pointed output by red colour" << endl;
    cout << coloured_file << endl;

    for (int i = 0; i < corrected_word.size(); i++)
    {
        cout << "Wrong Word is " << corrected_word[i] << endl;

        vector<string> suggestions = trie.suggestCorrections(corrected_word[i]);
        cout << "Suggestions: " << endl;
        cout << "The size of suggestions is " << suggestions.size() << endl;
        for (int j = 0; j < suggestions.size(); j++)
        {
            cout << "Suggestion Index " << j << ": " << suggestions[j] << endl;
        }
        // cout << "Choose an option:\n1. Use a suggestion\n2. Ignore\n3. Enter custom correction\n";
        int choice;

        cin >> choice;

        if (choice == 1)
        {

            int suggestionIndex;
            cin >> suggestionIndex;
            if (suggestionIndex >= 0 && suggestionIndex < suggestions.size())
            {
                corrected_word[i] = suggestions[suggestionIndex];
            }
            else
            {
                corrected_word[i] = corrected_word[i];
                cout << "Invalid suggestion index. Ignoring suggestion." << endl;
            }
        }
        else if (choice == 2)
        {
            corrected_word[i] = corrected_word[i];
        }
        else if (choice == 3)
        {
            cin.ignore();
            string custom;

            getline(cin, custom);
            corrected_word[i] = custom;
        }
    }

    for (int x = 0; x < wrong_file.size(); x++)
    {
        for (int i = 0; i < corrected_word.size(); i++)
        {
            if (wrong_word[i] == wrong_file[x])
            {
                wrong_file[x] = corrected_word[i];
                break;
            }
        }
    }

    cout << "The corrected paragraph is " << endl;

    for (int i = 0; i < wrong_file.size(); i++)
    {
        cout << wrong_file[i];

        cout << " ";
    }

    cout << endl;

    return 0;
}
