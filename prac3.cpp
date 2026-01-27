#include <iostream>
#include <cctype>
#include <set>
#include <vector>
using namespace std;

set<string> keywords = {
    "int","float","char","double","long","short","void",
    "return","if","else","while","for","do","break","continue",
    "struct","scanf","printf"
};

set<char> operators = {'+','-','*','/','=','<','>','%'};
set<char> punctuations = {';',',','(',')','{','}','[',']'};

set<string> symbolTable;
vector<string> lexicalErrors;

bool isKeyword(string s) {
    return keywords.count(s);
}

int main() {
    cout << "Paste C code (type END to finish):\n";

    string line;
    bool inMultiComment = false;
    int lineNo = 0;

    cout << "\nTOKENS\n";

    while (true) {
        getline(cin, line);
        if (line == "END") break;

        lineNo++;
        int i = 0;

        while (i < line.length()) {

            if (!inMultiComment && i+1 < line.length() &&
                line[i]=='/' && line[i+1]=='*') {
                inMultiComment = true;
                i += 2;
                continue;
            }

            if (inMultiComment) {
                if (i+1 < line.length() &&
                    line[i]=='*' && line[i+1]=='/') {
                    inMultiComment = false;
                    i += 2;
                } else i++;
                continue;
            }

            if (i+1 < line.length() &&
                line[i]=='/' && line[i+1]=='/')
                break;

            if (isspace(line[i])) {
                i++;
                continue;
            }

            if (isalpha(line[i]) || line[i]=='_') {
                string word;
                while (i < line.length() &&
                      (isalnum(line[i]) || line[i]=='_'))
                    word += line[i++];

                if (isKeyword(word))
                    cout << "Keyword: " << word << endl;
                else {
                    cout << "Identifier: " << word << endl;
                    symbolTable.insert(word);
                }
            }

            else if (isdigit(line[i])) {
                string num;
                while (i < line.length() && isalnum(line[i]))
                    num += line[i++];

                if (isalpha(num.back()))
                    lexicalErrors.push_back(
                        "Line " + to_string(lineNo) +
                        " : " + num + " invalid lexeme");
                else
                    cout << "Constant: " << num << endl;
            }

            else if (line[i]=='\'') {
                string ch;
                ch += line[i++];
                if (i < line.length()) ch += line[i++];
                if (i < line.length() && line[i]=='\'') ch += line[i++];
                cout << "Constant: " << ch << endl;
            }

            else if (line[i]=='"') {
                string str;
                str += line[i++];
                while (i < line.length() && line[i]!='"')
                    str += line[i++];
                str += '"';
                i++;
                cout << "Constant: " << str << endl;
            }

            else if (operators.count(line[i])) {
                cout << "Operator: " << line[i++] << endl;
            }

            else if (punctuations.count(line[i])) {
                cout << "Punctuation: " << line[i++] << endl;
            }

            else i++;
        }
    }

    cout << "\nLEXICAL ERRORS\n";
    for (auto &e : lexicalErrors)
        cout << e << endl;

    cout << "\nSYMBOL TABLE ENTRIES\n";
    int id = 1;
    for (auto &s : symbolTable)
        cout << id++ << ") " << s << endl;

    return 0;
}
