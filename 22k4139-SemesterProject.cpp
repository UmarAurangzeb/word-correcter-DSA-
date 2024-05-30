#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>
#include <string.h>
#include <cstring>
#include <cstdlib>
#define RESET "\033[1;30;47m"
#define RED "\033[1;31;47m"
using namespace std;
class node
{
public:
    string word;
    node *next;
    node(string word)
    {
        this->word = word;
        next = NULL;
    }
};

class list
{
public:
    node *head;
    list()
    {
        head = NULL;
    }
    void insert(string s)
    {
        node *n = new node(s);
        if (head == NULL)
        {
            head = n;
            return;
        }
        node *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = n;
    }
};
class hashtable
{
public:
    node **table;
    hashtable()
    {
        table = new node *[1000];
        for (int i = 0; i < 1000; i++)
        {
            table[i] = NULL;
        }
    }
    int hashfunc(string temp_word)
    {
        int mod_value = 0;
        for (int i = 0; i < temp_word.length(); i++)
        {
            mod_value += temp_word[i];
        }
        return mod_value % 1000;
    }
    void insert()
    {
        string temp_word;
        ifstream fin;
        fin.open("dictionary.txt");

        while (fin >> temp_word)
        {

            transform(temp_word.begin(), temp_word.end(), temp_word.begin(), [](unsigned char c)
                      { return tolower(c); });
            int index = hashfunc(temp_word);
            node *new_node = new node(temp_word);
            if (table[index] == NULL)
            {
                table[index] = new_node;
            }
            else
            {
                node *temp = table[index];
                while (temp->next != NULL)
                {
                    temp = temp->next;
                }
                temp->next = new_node;
            }
        }
        fin.close();
    }
    void print()
    {
        node *temp;
        for (int i = 0; i < 1000; i++)
        {
            temp = table[i];
            if (table[i] == NULL)
            {
                cout << "NULL" << endl;
                continue;
            }
            while (temp != NULL)
            {

                cout << " " << temp->word;
                temp = temp->next;
            }
            cout << endl;
        }
    }
    bool search(string key)
    {
        int mod_value = 0;
        for (int i = 0; i < key.length(); i++)
        {
            mod_value += key[i];
        }
        int index = mod_value % 1000;
        node *temp = table[index];
        while (temp != NULL)
        {
            if (temp->word == key)
            {

                return true;
            }
            temp = temp->next;
        }
        return false;
    }
};
string takeInput()
{
    string paragraph;
    cout << "Enter a paragraph:" << endl;
    getline(cin, paragraph);
    return paragraph;
    string s1;
}
list pushtolist(string paragraph, list &l1)
{
    int lengthofparagraph = paragraph.length();

    string word;
    for (int i = 0; i < lengthofparagraph; i++)
    {
        if (paragraph[i] == ' ' || i == lengthofparagraph - 1 || paragraph[i] == ',' || paragraph[i] == '.' || paragraph[i] == '?' || paragraph[i] == '!')
        {
            if (i == lengthofparagraph - 1)
            {
                word += paragraph[i];
            }

            transform(word.begin(), word.end(), word.begin(), [](unsigned char c)
                      { return tolower(c); });
            l1.insert(word);
            word = "";
            if (paragraph[i] == ',' || paragraph[i] == '.' || paragraph[i] == '?' || paragraph[i] == '!')
            {
                word += paragraph[i];
                l1.insert(word);
                word = "";
            }

            continue;
        }
        else
        {
            word += paragraph[i];
        }
    }
    return l1;
};

int levenshteinRecursiveae(string &word1, string &word2, int m, int n)
{
    int **dp = new int *[m + 1];

    for (int i = 0; i <= m; ++i)
    {
        dp[i] = new int[n + 1];
        dp[i][0] = i;
    }

    for (int j = 0; j <= n; ++j)
    {
        dp[0][j] = j;
    }

    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (word1[i - 1] == word2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = 1 + std::min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
            }
        }
    }

    int result = dp[m][n];

    for (int i = 0; i <= m; ++i)
    {
        delete[] dp[i];
    }
    delete[] dp;

    return result;
}

void WordCorrector(list &l1, hashtable &ob, string **arr, list &l2)
{

    int j = 0;
    ob.insert();
    node *temp = l1.head;

    while (temp != NULL)
    {
        int ctr = 0;
        int flag = 0;
        int k = 0;
        if (ob.search(temp->word) == true)
        {
            temp = temp->next;
        }
        else
        {
            l2.insert(temp->word);
            node *temp2;
            for (int i = 0; i < 1000; i++)
            {
                temp2 = ob.table[i];
                if (temp2 == NULL)
                {
                    continue;
                }
                else
                {
                    while (temp2 != NULL)
                    {
                        int distance = levenshteinRecursiveae(temp->word, temp2->word, temp->word.length(), temp2->word.length());
                        if (distance == 1 && flag == 0)
                        {
                            arr[j][k] = temp2->word;
                            ++k;
                            ctr++;
                        }
                        if (distance == 2 && flag == 1)
                        {

                            arr[j][k] = temp2->word;
                            ++k;
                            ctr++;
                        }
                        if (distance == 3 && flag == 2)
                        {

                            arr[j][k] = temp2->word;
                            ++k;
                            ctr++;
                        }
                        if (distance == 4 && flag == 3)
                        {
                            arr[j][k] = temp2->word;
                            ++k;
                            ctr++;
                        }
                        if (distance == 5 && flag == 4)
                        {

                            arr[j][k] = temp2->word;
                            ++k;
                            ctr++;
                        }
                        if (distance == 6 && flag == 5)
                        {

                            arr[j][k] = temp2->word;
                            ++k;
                            ctr++;
                        }
                        if (distance == 7 && flag == 6)
                        {

                            arr[j][k] = temp2->word;
                            ++k;
                            ctr++;
                        }
                        if (distance == 8 && flag == 7)
                        {

                            arr[j][k] = temp2->word;
                            ++k;
                            ctr++;
                        }

                        if ((i + 1) == 1000 && arr[j][0] == "")
                        {
                            flag++;
                            i = 0;
                            break;
                        }
                        if (ctr == 10)
                        {
                            break;
                        }

                        temp2 = temp2->next;
                    }
                }
                if (ctr == 10)
                {
                    break;
                }
            }
            j++;

            temp = temp->next;
        }
    }
}
void wordreplacer(list &l1, list &l2, string **arr)
{
    cout << endl;
    string s;

    int i = 0;
    int a;
    node *temp = l1.head;
    node *temp2 = l2.head;
    while (temp2 != NULL)
    {
        if (arr[i][0] == "")
        {
            cout << "no replacement found for word " << temp2->word << endl
                 << endl;
            i++;
            temp2 = temp2->next;
            continue;
        }
        int ctr = 0;
        cout << "Replace the word: " << temp2->word << " with " << endl
             << " ";

        for (int j = 0; j < 100; j++)
        {
            if (arr[i][j] == "")
            {
                break;
            }
            cout << ctr << ")" << arr[i][j] << " ";

            ctr++;
        }
        cout << ctr << ")"
             << "Keep the same word"
             << " " << endl;
        cin >> a;
        while (a > ctr)
        {
            cin >> a;
            if (a > ctr)
            {
                cout << "incorrect input,please enter again" << endl;
            }
        }
        s = arr[i][a];
        if (a == ctr)
        {
            i++;
            temp2 = temp2->next;
            continue;
        }

        while (temp != NULL)
        {
            if (temp2->word == temp->word)
            {
                temp->word = s;
                break;
            }
            temp = temp->next;
        }
        i++;
        temp2 = temp2->next;
    }
}
void printparagraph(list &l1, list &l2)
{
    system("color 70");

    cout << endl
         << endl;
    node *temp = l1.head;
    node *temp2 = l2.head;
    while (temp != NULL)
    {
        if (temp2 == NULL)
        {
            cout << temp->word << " ";
            temp = temp->next;
            continue;
        }
        else if (l2.head != NULL && temp->word == temp2->word)
        {
            if (temp->word == "." || temp->word == "?" || temp->word == "!" || temp->word == ",")
            {
                cout << temp->word;
                temp2 = temp2->next;
            }
            else
            {
                cout << RED << temp->word << " " << RESET;
                temp2 = temp2->next;
            }
        }
        else
        {
            cout << temp->word << " ";
        }
        temp = temp->next;
    }
    cout << endl;
}
void print(list &l1)
{
    cout << endl;
    node *temp = l1.head;
    cout << "===============================================UPDATED PARAGRAPH===================================================\n"
         << endl;
    while (temp != NULL)
    {
        cout << temp->word << " ";
        temp = temp->next;
    }
}

int main(int argc, char const *argv[])
{
    system("color 70");
    hashtable ob;
    string **arr = new string *[100];
    for (int i = 0; i < 100; i++)
    {
        arr[i] = new string[100];
    }
    string paragraph;
    paragraph = takeInput();
    list l1;
    list l2;
    l1 = pushtolist(paragraph, l1);

    system("cls");
    system("color 70");
    cout << "Your Paragraph: " << endl;
    WordCorrector(l1, ob, arr, l2);
    printparagraph(l1, l2);
    wordreplacer(l1, l2, arr);
    print(l1);

    return 0;
}
