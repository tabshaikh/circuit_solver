%{
    #include <stdio.h>
    #include <string.h>
    #include <ctype.h>
    #include <fstream>
    #include <iostream>
    #include <string.h>
    #include <vector>
    #include <algorithm>
    #include "y.tab.h"
    #include "component.h"
    using namespace std;
    // #define YYSTYPE char *
    void yyerror(char *);
    char* trim(char* input);
    extern "C" int yylex();
    extern "C" FILE *yyin;
    vector <component> components;
    vector <int> uniq;
    int error=0;
%}
%union{
    char * str;
}
%token <str> TYPE NAME NODE UNIT NUM FREQ DELAY
%token  SINE OPENBRACKET CLOSEBRACKET

%%
program:    program statement '\n' 
            | program statement
            | program '\n'
            | program ' '
            |
            ;
statement:  comp
            | source
            ;
comp:       TYPE NODE NODE UNIT     
            {
                char *type = trim($1);
                char *unit = trim($4);
                int unitLength = strlen(unit);
                if(type[0]=='R' && unit[unitLength-1]!='K')
                {
                    yyerror("Register Units are Wrong");
                }
                else if(type[0]=='C' && (unit[unitLength-2]!='N'||unit[unitLength-2]!='M'||unit[unitLength-2]!='K'||unit[unitLength-2]!='P')&& unit[unitLength-1]!='F')
                {
                    yyerror("Capacitor Units are Wrong");
                }
                else if(type[0]=='L' && (unit[unitLength-2]!='N'||unit[unitLength-2]!='M'||unit[unitLength-2]!='K'||unit[unitLength-2]!='P')&& unit[unitLength-1]!='H')
                {
                    yyerror("Inductor Units are Wrong");
                }
                else
                {
                    char *start,*end,*mag,*unit;
                    char *node1 = trim($2);
                    if(node1[0]=='0')
                    {   start=new char[1];
                        start="-1";
                    }
                    else
                    {
                        int len = strlen(node1);
                        start=new char[len-3];
                        int i=3;
                        while(i != len)
                        {
                            start[i-3]=node1[i];
                            i++;
                        }
                        start[i-3]=NULL;
                    }

                    char *node2 = trim($3);
                    if(node2[0]=='0')
                    {   end=new char[1];
                        end="-1";
                    }
                    else
                    {
                        int len = strlen(node2);
                        end=new char[len-3];
                        int i=3;
                        while(i != len)
                        {
                            end[i-3]=node2[i];
                            i++;
                        }
                        end[i-3]=NULL;
                    }

                    char *units = trim($4);
                    {
                        int len = strlen(units);
                        mag=new char[len];
                        unit=new char[len];
                        int imag=0,iunit=0,i=0;
                        while(i!=len)
                        {
                            if(isdigit(units[i]))
                            {
                                mag[imag]=units[i];
                                imag++;
                            }
                            else
                            {
                                unit[imag]=units[i];
                                iunit++;
                            }
                            i++;
                        }
                        mag[imag]=NULL;
                        unit[iunit]=NULL;
                    }
                    component temp;
                    temp.type = type[0];
                    temp.name = string((type+1));
                    temp.start = atoi(start)<atoi(end)? atoi(start):atoi(end);
                    temp.end = atoi(start)>atoi(end)? atoi(start):atoi(end);
                    temp.magnitude = atoi(mag);
                    temp.unit = string(unit);
                    components.push_back(temp);               

                }
            }
            ;
source:     TYPE NODE NODE SINE OPENBRACKET NUM NUM FREQ DELAY NUM CLOSEBRACKET
            {
                char *type = trim($1);
                if(type[0]!='V' && type[0]!='I')
                {
                    yyerror("No such source availble");
                }
                else
                {
                    char *start,*end;
                    char *node1 = trim($2);
                    if(node1[0]=='0')
                    {   start=new char[1];
                        start="-1";
                    }
                    else
                    {
                        int len = strlen(node1);
                        start=new char[len-3];
                        int i=3;
                        while(i != len)
                        {
                            start[i-3]=node1[i];
                            i++;
                        }
                        start[i-3]=NULL;
                    }

                    char *node2 = trim($3);
                    if(node2[0]=='0')
                    {   end=new char[1];
                        end="-1";
                    }
                    else
                    {
                        int len = strlen(node2);
                        end=new char[len-3];
                        int i=3;
                        while(i != len)
                        {
                            end[i-3]=node2[i];
                            i++;
                        }
                        end[i-3]=NULL;
                    }
                    component temp;
                    temp.type=type[0];
                    temp.name = string((type+1));
                    temp.start = atoi(start)<atoi(end)? atoi(start):atoi(end);
                    temp.end = atoi(start)>atoi(end)? atoi(start):atoi(end);
                    temp.dcoffset = atof($6);
                    temp.amplitude = atof($7);
                    char *frequency1 = trim($8);
                    char *frequency2;
                    {
                        int len = strlen(frequency1);
                        frequency2 = new char[len];
                        int i1=0, i2=0;
                        while( i1 != len )
                        {
                            if(isdigit(frequency1[i1])||frequency1[i1]=='.')
                            {
                                frequency2[i2]=frequency1[i1];
                                i2++;
                            }
                            i1++;
                        }
                        frequency2[i2]=NULL;
                    }
                    temp.f = atof(frequency2);
                    char *delay1 = trim($9);
                    char *delay2;
                    {
                        int len = strlen(delay1);
                        delay2 = new char[len];
                        int i1=0, i2=0;
                        while( i1 != len )
                        {
                            if(isdigit(delay1[i1])||delay1[i1]=='.')
                            {
                                delay2[i2]=delay1[i1];
                                i2++;
                            }
                            i1++;
                        }
                        delay2[i2]=NULL;
                    }
                    temp.delay = atof(delay2);
                    temp.dampingfactor=atof($10);
                    components.push_back(temp);
                }
            }
            ;
%%
char* trim(char* input)
{
    char* output = input;
    int i = 0, j = 0;
        
    while (input[i] != NULL)
    {
        if (input[i] != ' ')
        {
            output[j] = input[i];
            j++;
            i++;
        }
        else
        {
            i++;
        }
    }
    output[j]=NULL;
    return output;	
}
void yyerror(char *s) {
    error=-1;
    extern int yylineno;
    fprintf(stderr, "Line Number%d:-%s\n",yylineno, s);
}
int find(int s)
{
    for(int i=0;i<uniq.size();i++){
        if(uniq[i] == s){
            return i;
        }
    }
    return -1;
}
void node()
{
    for(int i=0; i<components.size(); i++)
    {
        if(find(components[i].start)==-1)
        {
            uniq.push_back(components[i].start);
        }
        if(find(components[i].end)==-1)
        {
            uniq.push_back(components[i].end);
        }
    }
    sort (uniq.begin(), uniq.begin()+4);
}

void printvector()
{
    for(int i=0;i<components.size();i++)
    {
        cout<<components[i].start<<"  "<<components[i].end<<endl;
    }
}

int parser(void) {
   FILE *pt = fopen("top.cir", "r" );
    if(!pt)
    {
        cout << "No such file exists" << endl;
        return -1;
    }
    yyin = pt;
    do
    {
        yyparse();
    }while (!feof(yyin));
    node();
    return error;
}
