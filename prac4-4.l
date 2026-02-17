%option noyywrap

%{
#include <stdio.h>
#include <string.h>

int hasLower = 0;
int hasUpper = 0;
int hasDigit = 0;
int hasSymbol = 0;
int length = 0;
%}

%%

[a-z]      { hasLower = 1; length++; }
[A-Z]      { hasUpper = 1; length++; }
[0-9]      { hasDigit = 1; length++; }
[\*\;\#\$\@] { hasSymbol = 1; length++; }

\n {
        if(length >= 9 && length <= 15 &&
           hasLower && hasUpper &&
           hasDigit && hasSymbol)
            printf("Valid password\n");
        else
            printf("Invalid password\n");

        /* Reset for next input */
        hasLower = hasUpper = hasDigit = hasSymbol = 0;
        length = 0;
    }

.          { length++; }   /* Count any other character */

%%

int main()
{
    printf("Enter password: ");
    yylex();
    return 0;
}
