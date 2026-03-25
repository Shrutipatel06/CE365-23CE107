#include <iostream>
#include <stack>
using namespace std;

int temp = 1;

string newTemp() {
    return "t" + to_string(temp++);
}

int prec(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    return 0;
}

void solve(string s) {
    stack<string> val;
    stack<char> op;

    cout << "Op\tOp1\tOp2\tRes\n";

    for (int i = 0; i < s.size(); i++) {
        if (s[i] == ' ') continue;

        if (isdigit(s[i])) {
            string num = "";
            while (i < s.size() && isdigit(s[i])) num += s[i++];
            i--;
            val.push(num);
        }
        else if (s[i] == '(') op.push('(');
        else if (s[i] == ')') {
            while (op.top() != '(') {
                string b = val.top(); val.pop();
                string a = val.top(); val.pop();
                string t = newTemp();
                cout << op.top() << "\t" << a << "\t" << b << "\t" << t << endl;
                val.push(t);
                op.pop();
            }
            op.pop();
        }
        else {
            while (!op.empty() && prec(op.top()) >= prec(s[i])) {
                string b = val.top(); val.pop();
                string a = val.top(); val.pop();
                string t = newTemp();
                cout << op.top() << "\t" << a << "\t" << b << "\t" << t << endl;
                val.push(t);
                op.pop();
            }
            op.push(s[i]);
        }
    }

    while (!op.empty()) {
        string b = val.top(); val.pop();
        string a = val.top(); val.pop();
        string t = newTemp();
        cout << op.top() << "\t" << a << "\t" << b << "\t" << t << endl;
        val.push(t);
        op.pop();
    }
}

int main() {
    string s;
    getline(cin, s);
    solve(s);
}
