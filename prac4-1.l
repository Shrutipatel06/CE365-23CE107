%option noyywrap
%{
	#include<stdio.h>
%}

%%
[0-9]+  { printf("%s\n", yytext); }
.       { /* Ignore other characters */ }
%%
int main()
{
	printf("enter string:");
	yylex();
	return 0;
}