%option noyywrap
%{
#include<stdio.h>

int chars = 0;
int words = 0;
int lines = 0;
int inword = 0;
%}

%%
[ \t]        { chars += yyleng; }
"\n"          { chars++; lines++; }      
.     { chars++;
      if(inword == 0) {
               words++;
               inword = 1;
               }
             }
%%

int main()
{
    FILE *fp;
    fp = fopen("input.txt","r");

    if(fp == NULL)
    {
        printf("File not found\n");
        return 0;
    }

    yyin = fp;
    yylex();

    printf("Characters : %d\n", chars);
    printf("Words : %d\n", words);
    printf("Lines : %d\n", lines++);

    fclose(fp);
    return 0;
}