%{
    #include <stdlib.h>
    #include <stdio.h>
    #define YY_DECL extern "C" int yylex()
    #include "y.tab.h"
    void yyerror(char *);
%}
%option yylineno

SPACE           " "
open_bracket    "("
closed_bracket  ")"
%%

{SPACE}*[RCLVI][a-zA-Z0-9]+{SPACE}+                 { yylval=strdup(yytext); return TYPE; }
                                
((Net|NET)[0-9]+|0){SPACE}+                         { yylval=strdup(yytext); return NODE; }
                                
{SPACE}+(([0-9]+.[0-9]+)|([0-9]+))                  { return NUM; }
                                
[0-9]+(K|NF|NH|MH|MF|KF|KH|PF|PH){SPACE}*           { yylval=strdup(yytext); return UNIT; }
                                
(SINE){SPACE}+                                      { return SINE; }

{SPACE}+(([0-9]+.[0-9]+)|[0-9]+)(Khz)               { return FREQ; }

{SPACE}+(([0-9]+.[0-9]+)|[0-9]+)(S)                 { return DELAY; }
                                                                                                                                                                                                                       
[ \n]                                               { return *yytext; }

{SPACE}*{open_bracket}                              { return OPENBRACKET; }

{SPACE}*{closed_bracket}{SPACE}*                    { return CLOSEBRACKET; }

.                                                   yyerror("invalid character");

%%

int yywrap(void) {
    return 1;
}