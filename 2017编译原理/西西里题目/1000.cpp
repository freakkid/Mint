#include <iostream>
#include <cstring>
#include <cstdio>
#include <cctype>
using namespace std;

struct { int number; string str[10]; } keywords={3,"int","main","return"} ;
struct { int number; string str[10]; } operators ={5,"+","*","=","+=","*="};
struct { int number; string str[10]; } boundaries ={6,"(",")","{","}",",",";"} ;
struct { int number; string str[100];} identifieres={0};
struct { int number; string str[100];} Unsigned_integer={0};

#define MAXSIZE 2000
#define KEYWORDS 1
#define OPERATORS 2
#define BOUNDARIES 3
#define IDENTIFIERES 4
#define UNSIGNED_INTEGER 5

// ------- judge if word exists or not --------
int is_exist_in_keywords(string word) {
    for (int i = 0; i < keywords.number; i++) {
        if (keywords.str[i] == word)
            return i;
    }
    
    return -1;
}

int is_exist_in_operators(string word) {
    for (int i = 0; i < operators.number; i++) {
        if (operators.str[i] == word)
            return i;
    }
    return -1;
}

int is_exist_in_boundaries(string word) {
    for (int i = 0; i < boundaries.number; i++) {
        if (boundaries.str[i] == word) {
            return i;
        }
    }
    return -1;
}

int is_exist_in_identifieres(string word) {
    for (int i = 0; i < identifieres.number; i++) {
        if (identifieres.str[i] == word) {
            return i;
        }
    }
    return -1;
}

int is_exist_in_Unsigned_integer(string word) {
    for (int i = 0; i < Unsigned_integer.number; i++) {
        if (Unsigned_integer.str[i] == word)
            return i;
    }
    return -1;
}
// ---------------------------------------------------

// ------ print identifieres and Unsigned_integer -----
void print_identifieres_content() {
    cout << "identifieres:";
    for (int i = 0; i < identifieres.number; i++) {
        cout << identifieres.str[i];
        if (i != identifieres.number - 1)
            cout << " ";
    }
    cout << endl;
}

void print_Unsigned_integer_content() {
    cout << "Unsigned_integer:";
    for (int i = 0; i < Unsigned_integer.number; i++) {
        cout << Unsigned_integer.str[i];
        if (i != Unsigned_integer.number - 1)
            cout << " ";
    }
    cout << endl;
}
// --------------------------------------------------

// add item in identifieres and Unsigned_integer
void add_identifieres(string word) {
    identifieres.str[identifieres.number++] = word;
}

void add_Unsigned_integer(string word) {
    Unsigned_integer.str[Unsigned_integer.number++] = word;
}
// ---------------------------------------------------

// print class and index
void print_class_index_nums(int class_num, int index_num) {
    cout << "<" << class_num << "," << index_num << ">";
}
// --------------------------------------------------

// ------------------ split a continus word ------------------
void split_word(string word) {
    int pos = -1;
    int type = 0; // A D
    int i = 0;
    if (word.size() - i > 3 && is_exist_in_keywords(word.substr(0, 4)) != -1) {
        print_class_index_nums(KEYWORDS, is_exist_in_keywords(word.substr(0, 4)));
        i = 4;
    }
    for ( ; i < word.size(); i++) {
        if (isalpha(word[i])) {
            if (pos == -1) {
                pos = i;
                type = 'A';
            }
        }
        else if (isdigit(word[i])) {
            if (pos == -1) {
                pos = i;
                type = 'D';
            }
        }
        else {
            if (pos != -1) {
                string tmp = word.substr(pos, i - pos);
                if (type == 'A') {
                    if (is_exist_in_identifieres(tmp) != -1) {
                        print_class_index_nums(IDENTIFIERES, is_exist_in_identifieres(tmp));
                    }
                    else {
                        add_identifieres(tmp);
                        print_class_index_nums(IDENTIFIERES, is_exist_in_identifieres(tmp));
                    }
                }
                else {
                    if (is_exist_in_Unsigned_integer(tmp) != -1) {
                        print_class_index_nums(UNSIGNED_INTEGER, is_exist_in_Unsigned_integer(tmp));
                    }
                    else {
                        add_Unsigned_integer(tmp);
                        print_class_index_nums(UNSIGNED_INTEGER, is_exist_in_Unsigned_integer(tmp));
                    }
                }
                pos = -1;
                type = 0;
            }
            if (is_exist_in_boundaries(word.substr(i, 1)) != -1) {
                print_class_index_nums(BOUNDARIES, is_exist_in_boundaries(word.substr(i, 1)));
            }
            else if (is_exist_in_operators(word.substr(i, 1)) != -1) {
                if (i + 1 < word.size() && is_exist_in_operators(word.substr(i, 2)) != -1) {
                    print_class_index_nums(OPERATORS, is_exist_in_operators(word.substr(i, 2)));
                    ++i;
                }
                else {
                    print_class_index_nums(OPERATORS, is_exist_in_operators(word.substr(i, 1)));
                }
            }
        }
    }
}
// ----------------------------------------------------------

// ------------------deal with a word-------------------------
void deal_with_a_word(string word) {
    if (is_exist_in_keywords(word) != -1) {
        print_class_index_nums(KEYWORDS, is_exist_in_keywords(word));
    }
    else if (is_exist_in_operators(word) != -1) {
        print_class_index_nums(OPERATORS, is_exist_in_operators(word));
    }
    else if (is_exist_in_boundaries(word) != -1) {
        print_class_index_nums(BOUNDARIES, is_exist_in_boundaries(word));
    }
    else if (is_exist_in_identifieres(word) != -1) {
        print_class_index_nums(IDENTIFIERES, is_exist_in_identifieres(word));
    }
    else if (is_exist_in_Unsigned_integer(word) != -1) {
        print_class_index_nums(UNSIGNED_INTEGER, is_exist_in_Unsigned_integer(word));
    }
    else {
        split_word(word);
    }
}
// ---------------------------------------------------------

// ----------- split an input string into many words ---------
void deal_with_input_string(string input_string) {        
    int word_first = -1;    // position of the first char of word
    for (int i = 0; i < input_string.size(); i++) {
        if (input_string[i] == ' ' || input_string[i] == '\n' || input_string[i] == '\r' || input_string[i] == '#') {
            if (word_first == -1)
                continue;
            else {
                deal_with_a_word(input_string.substr(word_first, i - word_first));
                word_first = -1;
            }
        }
        else {
            if (word_first == -1)
                word_first = i;
        }
    }
}
// ---------------------------------------------------------

int main() {
    char input_string[MAXSIZE] = {0};
    int num = -1;
    while ((input_string[++num] = getchar()) != '#');
    string input_str(input_string);
    deal_with_input_string(input_str);
    cout << endl;
    print_identifieres_content();
    print_Unsigned_integer_content();
    return 0;
}