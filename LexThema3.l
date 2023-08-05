/*** Definition Section has includes, one bool variable
which can be accessed inside yylex() 
and main(), the definition of the function findRepeatedTop***/
%{
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
bool acceptableRule = true;
int findRepeatedTop(char* s);
%}

/*** Rule Section has 10 rules, 1-8 rule 
matches with geometric shapes, 9th rule
matches with any character except newline and 
10th rule does not take input after the enter

acceptableRule = false if the user input does not 
conform with geometric shape and correct number of tops 

yytext is the text in the buffer***/
%%
point([ ])[A-Z]{1} { findRepeatedTop(yytext);}
line([ ])[A-Z]{2} { findRepeatedTop(yytext);}
triangle([ ])[A-Z]{3} { findRepeatedTop(yytext);}
square([ ])[A-Z]{4} { findRepeatedTop(yytext);}
pentagon([ ])[A-Z]{5} { findRepeatedTop(yytext);}
hexagon([ ])[A-Z]{6} { findRepeatedTop(yytext);}
heptagon([ ])[A-Z]{7} { findRepeatedTop(yytext);}
octagon([ ])[A-Z]{8} { findRepeatedTop(yytext);}

.     {acceptableRule = false;}
\n    {return 0;}

%%

// yywrap() - wraps the above rule section
int yywrap(){}

int findRepeatedTop(char* s)
{
//The algorithm would not work if lower cap letters were also acceptable tops, as it searches the entire input string
    int p = -1, i, j;
    for (i = 0; i < strlen(s); i++) {
        for (j = i + 1; j < strlen(s); j++) {
            if (s[i] == s[j]) {
                p = i;
                break;
            }
        }
        if (p != -1)
            break;
    }
    //if p == -1, repeated letter not found
     if (p != -1)   
        printf("Repeated letter found. ");
}

int main(){

	printf("\nEnter shape with it's tops, for example: «triangle ABC», and I will tell you if it is acceptable or not: ");

	/* yylex() - this is the main flex function which runs the Rule Section*/
	yylex();
	
	if (!acceptableRule)
		printf("The shape you entered does not exist, or does not conform with the tops given \n");
	else
		printf("The shape with the tops you entered are acceptable.\n");

	return 0;

}