#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 10

char productions[][20] = {
    "S=ABC",
    "S=D",
    "A=a",
    "A=#",
    "B=b",
    "B=#",
    "C=(S)",
    "C=c",
    "D=AC"
};

int n = 9;

char first[10][10];
char follow[10][10];
int first_count[10];
int follow_count[10];

int isNonTerminal(char c){
    return (c >= 'A' && c <= 'Z');
}

void addToSet(char set[10][10], int count[], int index, char value){
    for(int i=0;i<count[index];i++){
        if(set[index][i] == value)
            return;
    }
    set[index][count[index]++] = value;
}

void findFirst(char c, int index){
    for(int i=0;i<n;i++){
        if(productions[i][0] == c){
            if(!isNonTerminal(productions[i][2])){
                addToSet(first, first_count, index, productions[i][2]);
            }
            else{
                findFirst(productions[i][2], productions[i][2]-'A');
                for(int j=0;j<first_count[productions[i][2]-'A'];j++){
                    addToSet(first, first_count, index,
                             first[productions[i][2]-'A'][j]);
                }
            }
        }
    }
}

void findFollow(char c, int index){
    if(c == 'S')
        addToSet(follow, follow_count, index, '$');

    for(int i=0;i<n;i++){
        for(int j=2; j<strlen(productions[i]); j++){
            if(productions[i][j] == c){
                if(productions[i][j+1] != '\0'){
                    char next = productions[i][j+1];

                    if(!isNonTerminal(next)){
                        addToSet(follow, follow_count, index, next);
                    }
                    else{
                        for(int k=0;k<first_count[next-'A'];k++){
                            if(first[next-'A'][k] != '#')
                                addToSet(follow, follow_count, index,
                                         first[next-'A'][k]);
                        }
                    }
                }
                else{
                    if(productions[i][0] != c){
                        findFollow(productions[i][0],
                                   productions[i][0]-'A');
                        for(int k=0;k<follow_count[productions[i][0]-'A'];k++){
                            addToSet(follow, follow_count, index,
                                     follow[productions[i][0]-'A'][k]);
                        }
                    }
                }
            }
        }
    }
}

int main(){

    char nonTerminals[] = {'S','A','B','C','D'};
    int nt_count = 5;

    for(int i=0;i<nt_count;i++)
        findFirst(nonTerminals[i], nonTerminals[i]-'A');

    for(int i=0;i<nt_count;i++)
        findFollow(nonTerminals[i], nonTerminals[i]-'A');

    printf("FIRST Sets:\n");
    for(int i=0;i<nt_count;i++){
        printf("First(%c) = { ", nonTerminals[i]);
        for(int j=0;j<first_count[nonTerminals[i]-'A'];j++)
            printf("%c ", first[nonTerminals[i]-'A'][j]);
        printf("}\n");
    }

    printf("\nFOLLOW Sets:\n");
    for(int i=0;i<nt_count;i++){
        printf("Follow(%c) = { ", nonTerminals[i]);
        for(int j=0;j<follow_count[nonTerminals[i]-'A'];j++)
            printf("%c ", follow[nonTerminals[i]-'A'][j]);
        printf("}\n");
    }

    return 0;
}
