#include <iostream>
#include <string>
using namespace std;

string str;
int i = 0;

bool S(){
    if( i < str.length() && str[i] == 'a'){
        i++;
        return true;
    }

    if( i < str.length() && str[i] == '('){
        i++;
        if(!S()){
            return false;
        }
        while( i < str.length() && str[i] == ','){
            i++;
            if(!S()){
                return false;
            }
        }
        if(i < str.length() && str[i] == ')'){
            i++;
            return true;
        }
        return false;
    }
    return false;
}

int main(){
    cout << "Enter your string";
    getline(cin,str);

    string temp = "";
    for (char c : str){
        if (c != ' '){
            temp += c;
        }
    }

    str = temp;

    if(S() && i == str.length()){
        cout << "Valid String!!";
    }
    else{
        cout << "Invalid String!!";
    }

    return 0;

}