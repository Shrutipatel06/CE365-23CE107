#include <iostream>
#include <map>
#include <set>
using namespace std;

int main() {

    int nSymbols;
    cout << "Number of input symbols : ";
    cin >> nSymbols;

    char symbols[nSymbols];
    cout << "Input symbols : ";
    for (int i = 0; i < nSymbols; i++)
        cin >> symbols[i];

    int nStates;
    cout << "Enter number of states : ";
    cin >> nStates;

    int startState;
    cout << "Initial state : ";
    cin >> startState;

    int nAccept;
    cout << "Number of accepting states : ";
    cin >> nAccept;

    set<int> acceptStates;
    cout << "Accepting states : ";
    for (int i = 0; i < nAccept; i++) {
        int x;
        cin >> x;
        acceptStates.insert(x);
    }

    map<pair<int,char>, int> transition;

    cout << "Transition table :\n";
    for (int i = 1; i <= nStates; i++) {
        for (int j = 0; j < nSymbols; j++) {
            int next;
            cout << i << " to " << symbols[j] << " -> ";
            cin >> next;
            transition[{i, symbols[j]}] = next;
        }
    }

    string input;
    cout << "Input string : ";
    cin >> input;

    int currentState = startState;

    for (char ch : input) {

        if (transition.find({currentState, ch}) == transition.end()) {
            cout << "\nInvalid String\n";
            return 0;
        }

        currentState = transition[{currentState, ch}];
    }

    if (acceptStates.count(currentState))
        cout << "\nValid String\n";
    else
        cout << "\nInvalid String\n";

    return 0;
}
