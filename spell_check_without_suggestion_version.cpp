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
            children[i] = NULL;
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

            if (words[i] >= 97 && words[i] <= 122)
            {
                int index = words[i] - 'a';
                if (current->children[index] == NULL)
                {
                    current->children[index] = new node();
                }
                if (i == words.length() - 1)
                {
                    current->children[index]->end_of_word = true;
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
                if (current->children[index] == NULL)
                {
                    current->children[index] = new node();
                }
                if (i == words.length() - 1)
                {
                    current->children[index]->end_of_word = true;
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
            if (current->children[index] == NULL)
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
            if (trie.search(word))
            {
                coloured_file += word + " ";
                wrong_file.push_back(word);
            }
            else
            {
                wrong_word.push_back(word);
                corrected_word.push_back(word);
                coloured_file += RED + word + RESET + " ";
                wrong_file.push_back(word);
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
        cout << "Do you want to ignore it or change it customly(1 for ignore and 2 for custom) " << endl;
        int x;
        cin >> x;
        cin.ignore();
        if (x == 1)
        {
            corrected_word[i] = corrected_word[i];
        }
        else
        {
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
        cout << wrong_file[i] << " ";
    }

    return 0;
}