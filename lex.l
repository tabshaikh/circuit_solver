%{
    #include <stdlib.h>
    #include <stdio.h>
    #define YY_DECL extern "C" int yylex()
    #include "y.tab.h"
    void yyerror(char *);
%}
%option yylineno
%option caseless

SPACE           " "
open_bracket    "("
closed_bracket  ")"
%%

{SPACE}*[RCLVI][a-zA-Z0-9]+                { yylval.str=strdup(yytext); return TYPE; }
                                
([0-9]+(\.[0-9]+)?){SPACE}+         { yylval.str=strdup(yytext); return NUM; }


{SPACE}+(NET[0-9]+|0)                               { yylval.str=strdup(yytext); return NODE; }
                                
                                
{SPACE}+[0-9]+(K|NF|NH|MH|MF|KF|KH|PF|PH){SPACE}*           { yylval.str=strdup(yytext); return UNIT; }
                                
{SPACE}+(SINE)                                      { return SINE; }

(([0-9]+\.[0-9]+)|[0-9]+)(Khz){SPACE}+               { yylval.str=strdup(yytext); return FREQ; }

(([0-9]+\.[0-9]+)|[0-9]+)(S){SPACE}+                 { yylval.str=strdup(yytext); return DELAY; }

                                                                                                                                                                                                                       
[\n]                                               { return *yytext; }

{SPACE}+{open_bracket}{SPACE}*                                      { return OPENBRACKET; }

{closed_bracket}{SPACE}*                    { return CLOSEBRACKET; }

.                                                   yyerror("invalid character");

%%

int yywrap(void) {
    return 1;
}