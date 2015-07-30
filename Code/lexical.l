%{
	#include <stdio.h>
	#include <string.h>
	#include "syntax.tab.h"
	int morphology=0;//stand for the error type A
	void yyerror(char *msg);
	Node *CreateIntLeaf(int value, int lineno);
	Node *CreateFloatLeaf(float value, int lineno);
	Node *CreateIDLeaf(char *id, int lineno);
	Node *CreateOther(char *name, char *text, int lineno);
%}

%option yylineno
/*	regular definitions	*/
ws			[ \t\n\r]
digit_less 	[1-9]
digit 		[0-9]
letter_ 	[A-Za-z_]
SEMI		";"
COMMA		","
ASSIGNOP	"="
RELOP		">"|"<"|">="|"<="|"=="|"!="
PLUS		"+"
MINUS		"-"
STAR		"*"
DIV			"/"
AND			"&&"
OR			"||"
DOT			"."
NOT			"!"
TYPE		"int"|"float"
LP			"("
RP			")"
LB			"["
RB			"]"
LC			"{"
RC			"}"
STRUCT		"struct"
RETURN		"return"
IF			"if"
ELSE		"else"
WHILE		"while"
INT 		{digit}|({digit_less}({digit}){1,10})
FLOAT		[0-9]+\.[0-9]+
ID 			{letter_}({letter_}|{digit}){0,31}
%%
{ws}		{}
"//"   		{ 
				char c = input();
				while (c != '\n' && c != EOF) c = input();
			}
"/*" {int left=1;
	char first=input();
	char second;
	if(first!=EOF)
		second=input();
	else 
		second=EOF;
	while(left!=0&&second!=EOF)
	{
		if(first=='*'&&second=='/')
		{	left=0;
		}
		else
		{	left++;
			first=second;
			second=input();
		}
	}
	if(left!=0)
		printf("Error type A at Line %d : Missing the sign */\n",yylineno);
	}
{IF}		{yylval.node = CreateOther("IF", yytext, yylineno);return(IF);}
{ELSE}		{yylval.node = CreateOther("ELSE", yytext, yylineno);return(ELSE);}
{WHILE}		{yylval.node = CreateOther("WHILE", yytext, yylineno);return(WHILE);}
{STRUCT}	{yylval.node = CreateOther("STRUCT", yytext, yylineno);return(STRUCT);}
{RETURN}	{yylval.node = CreateOther("RETURN", yytext, yylineno);return(RETURN);}
{TYPE}		{yylval.node = CreateOther("TYPE", yytext, yylineno);return(TYPE);}
{INT}		{yylval.node = CreateIntLeaf(atoi(yytext), yylineno);return(INT);}
{FLOAT}		{yylval.node = CreateFloatLeaf(atof(yytext), yylineno);return(FLOAT);}
{ID}		{yylval.node = CreateIDLeaf(yytext, yylineno);return(ID);}
{SEMI}		{yylval.node = CreateOther("SEMI", yytext, yylineno);return(SEMI);}
{COMMA}		{yylval.node = CreateOther("COMMA", yytext, yylineno);return(COMMA);}
{ASSIGNOP}	{yylval.node = CreateOther("ASSIGNOP", yytext, yylineno);return(ASSIGNOP);}
{RELOP}		{yylval.node = CreateOther("RELOP", yytext, yylineno);return(RELOP);}
{PLUS}		{yylval.node = CreateOther("PLUS", yytext, yylineno);return(PLUS);}
{MINUS}		{yylval.node = CreateOther("MINUS", yytext, yylineno);return(MINUS);}
{STAR}		{yylval.node = CreateOther("STAR", yytext, yylineno);return(STAR);}
{DIV}		{yylval.node = CreateOther("DIV", yytext, yylineno);return(DIV);}
{AND}		{yylval.node = CreateOther("AND", yytext, yylineno);return(AND);}
{OR}		{yylval.node = CreateOther("OR", yytext, yylineno);return(OR);}
{DOT}		{yylval.node = CreateOther("DOT", yytext, yylineno);return(DOT);}
{NOT}		{yylval.node = CreateOther("NOT", yytext, yylineno);return(NOT);}
{LP}		{yylval.node = CreateOther("LP", yytext, yylineno);return(LP);}
{RP}		{yylval.node = CreateOther("RP", yytext, yylineno);return(RP);}
{LB}		{yylval.node = CreateOther("LB", yytext, yylineno);return(LB);}
{RB}		{yylval.node = CreateOther("RB", yytext, yylineno);return(RB);}
{LC}		{yylval.node = CreateOther("LC", yytext, yylineno);return(LC);}
{RC}		{yylval.node = CreateOther("RC", yytext, yylineno);return(RC);}
. 			{morphology=1;printf("Error type A at Line %d : Mysterious characters %s\n",yylineno,yytext);}
%%
//create other node
Node *CreateOther(char *name, char *text, int lineno){
	Node *p=malloc(sizeof(Node));
	p->name = name;
	p->node_type = OtherTerminal;
	p->lineno = lineno;
	p->other_terminal = strdup(text);
	return p;
}
//create the int node
Node *CreateIntLeaf(int value, int lineno){
	Node *p=malloc(sizeof(Node));
	p->name = "INT";
	p->node_type = IntType;
	p->lineno = lineno;
	p->int_value = value;
	return p;
}
//create the float node
Node *CreateFloatLeaf(float value, int lineno){
	Node *p=malloc(sizeof(Node));
	p->name = "FLOAT";
	p->node_type = FloatType;
	p->lineno = lineno;
	p->float_value = value;
	return p;
}
//create the id node
Node *CreateIDLeaf(char *id, int lineno){
	Node *p= malloc(sizeof(Node));
	p->name = "ID";
	p->node_type = IDType;
	p->lineno = lineno;
	p->id_value = strdup(id);
	return p;
}