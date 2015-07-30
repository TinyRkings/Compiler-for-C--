%{
	#include "node.h"
	#include "hash.h"  //for semantic analysis
	#include "lex.yy.c"
	int error_line;
	char*content;
	void print_treeinfo(Node *p, int lavel);
	extern void print_error();
	int grammar_error = 0;
	Node *CreateTerminal(char *name, int childnumber, ...);
	Node*root;
%}

%union{
	Node *node;
};

%token <node> INT FLOAT ID IF ELSE WHILE STRUCT TYPE RETURN 
%token <node> SEMI COMMA ASSIGNOP RELOP PLUS MINUS STAR DIV 
%token <node> AND OR DOT NOT LP RP LB RB LC RC
%type <node> Program ExtDefList ExtDef ExtDecList
%type <node> Specifier StructSpecifier OptTag Tag
%type <node> VarDec FunDec VarList ParamDec
%type <node> CompSt StmtList Stmt 
%type <node> DefList Def DecList Dec
%type <node> Exp Args
%nonassoc LOWER_THAN_RP
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%right ASSIGNOP
%left AND OR
%left RELOP 
%left PLUS MINUS 
%left STAR DIV  
%right NOT
%nonassoc UMINUS
%left LP RP LB RB DOT
%nonassoc LOWER_THAN_COMMA
%nonassoc COMMA
%nonassoc LOWEST

%%

/* High-Level Definitions */
Program			:	ExtDefList				
{$$ = CreateTerminal("Program",1,$1);
//print_treeinfo($$, 0);
root=$$;
}
				;
ExtDefList		:	ExtDef ExtDefList				{$$ = CreateTerminal("ExtDefList",2,$1,$2);}
				|	/*empty*/						{$$ = CreateTerminal("ExtDefList",0);}
				;
ExtDef			:	Specifier ExtDecList SEMI		{$$ = CreateTerminal("ExtDef",3,$1,$2,$3);}
				|	Specifier SEMI					{$$ = CreateTerminal("ExtDef",2,$1,$2);}
				|	Specifier FunDec CompSt			{$$ = CreateTerminal("ExtDef",3,$1,$2,$3);}
				|	Specifier FunDec SEMI 			{$$ = CreateTerminal("ExtDef",3,$1,$2,$3);}
				|	error SEMI
					{content="Missing the type or variation error";print_error();}//solve no specifier problem
				|	Specifier ExtDecList error{content="Missing the Semicolon";print_error();}
				;
ExtDecList		:	VarDec	%prec LOWER_THAN_COMMA	{$$ = CreateTerminal("ExtDecList",1,$1);}
				|	VarDec COMMA ExtDecList			{$$ = CreateTerminal("ExtDecList",3,$1,$2,$3);}
				;
/* Specifier */
Specifier		:	TYPE							{$$ = CreateTerminal("Specifier",1,$1);}
				|	StructSpecifier					{$$ = CreateTerminal("Specifier",1,$1);}
				;
StructSpecifier	:	STRUCT OptTag LC DefList RC		{$$ = CreateTerminal("StructSpecifier",5,$1,$2,$3,$4,$5);}
				|	STRUCT Tag						{$$ = CreateTerminal("StructSpecifier",2,$1,$2);}
				;
OptTag			:	ID								{$$ = CreateTerminal("OptTag",1,$1);}
				|	/*empty*/						{$$ = CreateTerminal("OptTag",0);}
				;
Tag				:	ID								{$$ = CreateTerminal("Tag",1,$1);}
				;

/* Declarators */
VarDec			:	ID								{$$ = CreateTerminal("VarDec",1,$1);}
				|	VarDec LB INT RB				{$$ = CreateTerminal("VarDec",4,$1,$2,$3,$4);}
				;
FunDec			:	ID LP VarList RP				{$$ = CreateTerminal("FunDec",4,$1,$2,$3,$4);}
				|	ID LP RP						{$$ = CreateTerminal("FunDec",3,$1,$2,$3);}
				|error LP RP{content="the name of Fun comes up errors";print_error();}
				|error LP VarList RP{content="the name of Fun comes up errors";print_error();}
				;
VarList			:	ParamDec COMMA VarList			{$$ = CreateTerminal("VarList",3,$1,$2,$3);}
				|	ParamDec						{$$ = CreateTerminal("VarList",1,$1);}
				|error{content="the Parm of Fun comes up errors";print_error();}	
				;
ParamDec		:	Specifier VarDec				{$$ = CreateTerminal("ParamDec",2,$1,$2);}
				;
/* Statements */
CompSt			:	LC DefList StmtList RC			{$$ = CreateTerminal("CompSt",4,$1,$2,$3,$4);}
				|error RC{content="Missing LC";print_error();}//lost LC	
				;
StmtList		:	Stmt StmtList					{$$ = CreateTerminal("StmtList",2,$1,$2);}
				|	/*empty*/						{$$ = CreateTerminal("StmtList",0);}
				;
Stmt			:	Exp SEMI						{$$ = CreateTerminal("Stmt",2,$1,$2);}
				|	CompSt							{$$ = CreateTerminal("Stmt",1,$1);}
				|	RETURN Exp SEMI					{$$ = CreateTerminal("Stmt",3,$1,$2,$3);}
				|	IF LP Exp RP Stmt %prec LOWER_THAN_ELSE	{$$ = CreateTerminal("Stmt",5,$1,$2,$3,$4,$5);}
				|	IF LP Exp RP Stmt ELSE Stmt		{$$ = CreateTerminal("Stmt",7,$1,$2,$3,$4,$5,$6,$7);}
				|	WHILE LP Exp RP Stmt			{$$ = CreateTerminal("Stmt",5,$1,$2,$3,$4,$5);}
				|error Stmt ELSE Stmt 
					{content="if-else statement comes up errors";print_error();}//if,else error
				|error Stmt %prec LOWER_THAN_ELSE
					{content="if or while statement comes up errors";print_error();}//while error,if error
				|error SEMI 
				{content="statement comes up errors";print_error();}//exp,return error
				;
/* Local Definitions */
DefList			:	Def DefList						{$$ = CreateTerminal("DefList",2,$1,$2);}
				|	/*empty*/						{$$ = CreateTerminal("DefList",0);}
				;
Def				:	Specifier DecList SEMI			{$$ = CreateTerminal("Def",3,$1,$2,$3);}
				;
DecList			:	Dec								{$$ = CreateTerminal("DecList",1,$1);}
				|	Dec COMMA DecList				{$$ = CreateTerminal("DecList",3,$1,$2,$3);}
				|error COMMA DecList  				{content="Missing dot2(,)";print_error();}//lost first Dec
				|error DecList 						{content="Missing dot3(,)";print_error();}//lost COMMA
				|error  							{content="Missing id";print_error();}//lost Dec 
				;
Dec				:	VarDec							{$$ = CreateTerminal("Dec",1,$1);}
				|	VarDec ASSIGNOP Exp				{$$ = CreateTerminal("Dec",3,$1,$2,$3);}
				;
/* Expressions */
Exp				:	Exp ASSIGNOP Exp				{$$ = CreateTerminal("Exp",3,$1,$2,$3);}
				|	Exp AND Exp						{$$ = CreateTerminal("Exp",3,$1,$2,$3);}
				|	Exp OR Exp						{$$ = CreateTerminal("Exp",3,$1,$2,$3);}
				|	Exp RELOP Exp					{$$ = CreateTerminal("Exp",3,$1,$2,$3);}
				|	Exp PLUS Exp					{$$ = CreateTerminal("Exp",3,$1,$2,$3);}
				|	Exp MINUS Exp					{$$ = CreateTerminal("Exp",3,$1,$2,$3);}
				|	Exp STAR Exp					{$$ = CreateTerminal("Exp",3,$1,$2,$3);}
				|	Exp DIV Exp						{$$ = CreateTerminal("Exp",3,$1,$2,$3);}
				|	LP Exp RP						{$$ = CreateTerminal("Exp",3,$1,$2,$3);}
				|	MINUS Exp  %prec UMINUS 		{$$ = CreateTerminal("Exp",2,$1,$2);}
				|	NOT Exp							{$$ = CreateTerminal("Exp",2,$1,$2);}
				|	ID LP Args RP					{$$ = CreateTerminal("Exp",4,$1,$2,$3,$4);}
				|	ID LP RP						{$$ = CreateTerminal("Exp",3,$1,$2,$3);}
				|	Exp LB Exp RB					{$$ = CreateTerminal("Exp",4,$1,$2,$3,$4);}
				|	Exp DOT ID						{$$ = CreateTerminal("Exp",3,$1,$2,$3);}
				|	ID								{$$ = CreateTerminal("Exp",1,$1);}
				|	INT								{$$ = CreateTerminal("Exp",1,$1);}
				|	FLOAT							{$$ = CreateTerminal("Exp",1,$1);}
				;
Args			:	Exp COMMA Args					{$$ = CreateTerminal("Args",3,$1,$2,$3);}
				|	Exp								{$$ = CreateTerminal("Args",1,$1);}
				;
%%
void print_error(){
	fprintf(stderr,"Error type B at Line %d : %s\n",error_line,content);
}
void yyerror(char *msg){
	grammar_error = 1;
	error_line=yylineno;
	//printf("Error type B at line %d : %s \n", yylineno, msg);
}
void print_treeinfo(Node *p, int nLayer){
	if(p->node_type == Nonterminal && p->cnode.arity == 0)
		return;
	int i;
	for(i = 0; i < nLayer; i ++)
		printf("  ");
	if(p->node_type == IntType)
		printf("INT: %d\n", p->int_value);
	else if(p->node_type == FloatType)
		printf("FLOAT: %f\n", p->float_value);
	else if(p->node_type == IDType)
		printf("ID: %s\n", p->id_value);
	else if(p->node_type == OtherTerminal){
		if(p->name == "TYPE")
			printf("TYPE: %s\n", p->other_terminal);
		else
			printf("%s\n", p->name);
	}
	else{
		nLayer ++;
		printf("%s (%d)\n", p->name, p->lineno);
		for(i = 0; i < p->cnode.arity; i ++)
			print_treeinfo(p->cnode.children[i], nLayer);
	}		
}
Node *CreateTerminal(char *name, int arity, ...){
	va_list children;
	Node *p;
	int i;
	if ((p = malloc(sizeof(Node))) == NULL)
		yyerror("Memory not enough");
	if ((p->cnode.children = malloc(arity * (sizeof(Node) + sizeof(int)))) == NULL)
		yyerror("Memory not enough");
	p->node_type = Nonterminal;
	p->name = name;
	p->lineno = 0;
	p->cnode.arity = arity;
	va_start(children, arity);
	for(i = 0; i < arity; i ++){
		p->cnode.children[i] = va_arg(children, Node*);
	}
	if(arity != 0)
		p->lineno = p->cnode.children[0]->lineno;
	va_end(children);
	return p;	
}
