%option noyywrap
%{
    #include<stdio.h>
%}

%%
charusat    { printf("university"); }
\n          { return 0; }
.           { printf("%s", yytext); }
%%

int main()
{
    printf("enter string:");
    yylex();
    return 0;
}
