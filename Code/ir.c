#include "hash.h"
#include "ir.h"
#include "semantic.h"
#include <fcntl.h>

#define MAXSIZE 2000
extern char*strdup(char*s);
int labelNum = 0;//create the label,cal the location of label
int tempNum = 0;//create the temp id,cal the location of temp
int id_varNum = 0;//the location of idTable
int paramNum = 0;//the location of paramTable
int IR_number = 0;//the location of addressTable
char* paramTable[MAXSIZE];
char* addressTable[MAXSIZE];
Operand idTable[MAXSIZE];
int test_id=0;
int test_id2=0;
int test_id3=0;

void test()
{
	if(test_id==1)
		printf("hello!\n");
}
void test2()
{
	if(test_id2==1)
		printf("error!\n");
}
int getArraySpace(Type type){
	test();
	if(type->kind == array){
		return type->array.size * getArraySpace(type->array.elem);
	}
	else{
		int space = 0;
		if(type->kind==structure)
		{
			printf("Cannot translate: Code contains variables or parameters of structure type\n");
			exit(0);
		}
		else if(type->kind==basic&&type->basic==0)
			space=4;
		else
			space=4;
		return space;
	}
}
Operand lookup(char *name){
	int i;
	for(i = 0; i < id_varNum; i ++){
		if(strcmp(idTable[i]->var_name, name) == 0)
			break;
	}
	if(i == id_varNum){
		Operand op = malloc(sizeof(struct Operand_));
		op->kind = VARIABLE;
		op->var_name = name;
		idTable[i] = op;
		id_varNum ++;
	}
	return idTable[i];
}
//create the code of label statement
InterCodes new_label(){
	InterCodes label = malloc(sizeof(struct InterCodes_));
	label->prev = label->next = label;
	label->code.kind = LABEL;
	label->code.id = labelNum;
	labelNum++;
	return label;
}
void test3()
{
	if(test_id3==1)
		printf("error!\n");
}
//create the code of goto statement according by the label number
InterCodes new_goto(int i){
	InterCodes newCode = malloc(sizeof(struct InterCodes_));
	newCode->prev = newCode->next = newCode;
	newCode->code.kind = GOTO;
	newCode->code.id = i;
	return newCode;
}
//create the operand of temporary variable
Operand new_temp(){
	Operand temp = malloc(sizeof(struct Operand_));
	temp->kind = TEMP;
	temp->temp_id = tempNum;
	tempNum++;
	return temp;
}
//create the operand of size of the array
Operand new_create_space(int value){
	Operand op = malloc(sizeof(struct Operand_));
	op->kind = SPACE;
	op->value = value;
	return op;
}
//discern if it is the array in the parameter
int isParam(char *name){
	int i;
	for(i = 0; i < paramNum; i ++){
		if(strcmp(paramTable[i], name) == 0)
			return 1;
	}
	return 0;
}
//discern if it is the array
int isAddress(char *name){
	int i;
	for(i = 0; i < IR_number; i ++){
		if(strcmp(addressTable[i], name) == 0)
			return 1;
	}
	return 0;
}
//do optimize for the exp
Operand optimizeExp(Node *exp){
	if(exp->cnode.arity == 1){
		if(strcmp(exp->cnode.children[0]->name, "ID") == 0)
			return lookup(exp->cnode.children[0]->id_value);
		else if(strcmp(exp->cnode.children[0]->name, "INT") == 0){
			Operand op = malloc(sizeof(struct Operand_));
			op->kind = CONSTANT;
			op->value = exp->cnode.children[0]->int_value;
			return op;
		}
		else{
			Operand op = malloc(sizeof(struct Operand_));
			op->kind = FCONSTANT;
			op->fvalue = exp->cnode.children[0]->float_value;
			return op;
		}
	}
	else
		return new_temp();
}
InterCodes connectCodes(int total, ...){
	test();
	va_list ap;
	va_start(ap,total);
	InterCodes ic1 = va_arg(ap, InterCodes); 
	total--;
	while(total > 0) {
		InterCodes ic2 = va_arg(ap, InterCodes); 
		total--;
		if(ic2 == NULL) continue;
		if(ic1 == NULL) {
			ic1 = ic2;
			continue;
		}
		InterCodes tmp;
		tmp = ic2->prev;
		ic2->prev->next = ic1;
		ic1->prev->next = ic2;
		ic2->prev = ic1->prev;
		ic1->prev = tmp;
	}
	va_end(ap);
	return ic1;
}
InterCodes translate_Cond(Node *p, InterCodes label_true, InterCodes label_false){
	test2();
	//Exp : Exp AND Exp
	if(p->cnode.arity==3&&strcmp(p->cnode.children[1]->name, "AND")==0)
	{
		InterCodes label1 = new_label();
		InterCodes c1=translate_Cond(p->cnode.children[0],label1, label_false);
		InterCodes c2=translate_Cond(p->cnode.children[2],label_true, label_false);
		return connectCodes(3, c1, label1, c2);
	}
	//Exp : Exp OR Exp
	else if(p->cnode.arity>=2&&strcmp(p->cnode.children[1]->name, "OR")==0)
	{
		InterCodes label1 = new_label();
		InterCodes c1 = translate_Cond(p->cnode.children[0], label_true, label1);
		InterCodes c2 = translate_Cond(p->cnode.children[2], label_true, label_false);
		return connectCodes(3, c1, label1, c2);
	}
	//Exp : Exp RELOP Exp
	else if(p->cnode.arity>=2&&strcmp(p->cnode.children[1]->name,"RELOP")==0)
	{
		Operand temp1 = optimizeExp(p->cnode.children[0]);
		Operand temp2 = optimizeExp(p->cnode.children[2]);
		test3();
		Operand t1, t2; 
		InterCodes c1, c2;
		if(temp1->kind==TEMP){
			c1 = translate_Exp(p->cnode.children[0], temp1);
			if(strcmp(p->cnode.children[0]->cnode.children[1]->name,"LB")==0)
			{
				t1=malloc(sizeof(struct Operand_));	
				t1->kind = POINT;
				t1->addr = temp1;
			}
			else 
				t1=temp1;
		}
		else{

			c1 = NULL;
			t1 = temp1;	
		}
		if(temp2->kind == TEMP){
			c2 = translate_Exp(p->cnode.children[2], temp2);
			if(strcmp(p->cnode.children[2]->cnode.children[1]->name,"LB") ==0)
			{
				t2 = malloc(sizeof(struct Operand_));	
				t2->kind = POINT;
				t2->addr = temp2;
			}
			else 
				t2 = temp2;
		}
		else{
			c2 = NULL;
			t2 = temp2;	
		}
		InterCodes c3 = malloc(sizeof(struct InterCodes_));
		c3->prev = c3->next = c3;
		c3->code.kind = IFGOTO;
		c3->code.ifgoto.label = label_true;
		c3->code.ifgoto.op1 = t1;
		c3->code.ifgoto.op2 = t2;
		c3->code.ifgoto.relop = strdup(p->cnode.children[1]->other_terminal);
		return connectCodes(4, c1, c2, c3, new_goto(label_false->code.id));
	}
	//Exp : NOT Exp
	else if(strcmp(p->cnode.children[0]->name, "NOT")==0){
		return translate_Cond(p->cnode.children[1], label_false, label_true);
	}
	else
	{
		Operand temp = optimizeExp(p);
		InterCodes c1;
		Operand t1;
		if(temp->kind == TEMP)
		{
			c1 = translate_Exp(p, temp); 
			if(strcmp(p->cnode.children[1]->name, "LB") == 0)
			{
				t1 = malloc(sizeof(struct Operand_));	
				t1->kind = POINT;
				t1->addr = temp;
			}
			else 
				t1 = temp;
		}
		else{
			c1 = NULL;
			t1 = temp;
		}
		InterCodes c2 = malloc(sizeof(struct InterCodes_));
		Operand t2 = malloc(sizeof(struct Operand_));
		t2->kind = CONSTANT;
		t2->value = 0;
		c2->prev = c2->next = c2;
		c2->code.kind = IFGOTO;
		c2->code.ifgoto.label = label_true;
		c2->code.ifgoto.op1 = t1;
		c2->code.ifgoto.op2 = t2;
		c2->code.ifgoto.relop = strdup("!=");
		return connectCodes(3, c1, c2, new_goto(label_false->code.id));
	}
	test();
}
InterCodes translate_Exp(Node *p, Operand place){
	//Exp : INT
	if(strcmp(p->cnode.children[0]->name, "INT") == 0){
		if(place==NULL)
			return NULL;
		InterCodes codes = malloc(sizeof(struct InterCodes_));
		codes->prev = codes->next = codes;
		codes->code.kind = ASSIGN;
		codes->code.assign.left = place;
		Operand rightOp = malloc(sizeof(struct Operand_));
		rightOp->kind = CONSTANT;
		rightOp->value = p->cnode.children[0]->int_value;
		codes->code.assign.right = rightOp;
		return codes;
	}
	//Exp : FLOAT
	else if(strcmp(p->cnode.children[0]->name, "FLOAT") == 0){
		if(place==NULL)
			return NULL;
		test2();
		InterCodes codes = malloc(sizeof(struct InterCodes_));
		codes->prev = codes->next = codes;
		codes->code.kind = ASSIGN;
		codes->code.assign.left = place;
		Operand rightOp = malloc(sizeof(struct Operand_));
		rightOp->kind = FCONSTANT;
		rightOp->fvalue = p->cnode.children[0]->float_value;
		codes->code.assign.right = rightOp;
		test3();
		return codes;
	}
	//Exp : ID
	else if(p->cnode.arity==1&&strcmp(p->cnode.children[0]->name, "ID")==0)
	{
		if(place==NULL)
			return NULL;
		InterCodes codes = malloc(sizeof(struct InterCodes_));
		codes->prev = codes->next = codes;
		codes->code.kind = ASSIGN;
		test();
		codes->code.assign.left = place;
		codes->code.assign.right = lookup(p->cnode.children[0]->id_value);
		return codes;
	}
	//Exp : Exp DOT ID
	else if(strcmp(p->cnode.children[1]->name, "DOT") == 0){
		printf("Cannot translate: Code contains variables or parameters of structure type\n");
		exit(0);
	}
	//Exp : Exp LB Exp RB
	else if(strcmp(p->cnode.children[1]->name, "LB") == 0)
	{
		if(place==NULL)
			return NULL;
		Operand temp = optimizeExp(p->cnode.children[0]);
		Operand t1;
		Operand op1 = optimizeExp(p->cnode.children[2]);
		InterCodes c0, c1;
		if(op1->kind == TEMP){
			c0 = translate_Exp(p->cnode.children[2], op1);
		}
		else{
			c0 = NULL;
		}
		Operand op2 = malloc(sizeof(struct Operand_));
		op2->kind = CONSTANT;
		op2->value = getArraySpace(arrayExp(p));
		Operand t2;
		InterCodes c2;
		if(op1->kind==CONSTANT)
		{
			int total_size=op1->value*op2->value;
			op2->value=total_size;
			t2=op2;
			c2=NULL;
		}
		else
		{
			t2= new_temp();
			//c2 stand for the MUL opeartion
			c2 = malloc(sizeof(struct InterCodes_));
			c2->next = c2->prev = c2;
			c2->code.kind = MUL;
			c2->code.binop.result = t2;
			c2->code.binop.op1 = op1;		
			c2->code.binop.op2 = op2;
		}
		InterCodes c3 = malloc(sizeof(struct InterCodes_));
		c3->next = c3->prev = c3;
		c3->code.kind = ADD;
		//may be parameter of the function as array
		if(temp->kind==TEMP||isParam(p->cnode.children[0]->cnode.children[0]->id_value) == 0)
		{
			if(temp->kind==TEMP){
				c1 = translate_Exp(p->cnode.children[0], temp);
				t1 = temp;
			}
			else{
				c1 = NULL;
				t1 = malloc(sizeof(struct Operand_));
				t1->kind = ADDRESS;
				t1->addr = temp;			
			}
		/*	if(t2->kind==CONSTANT&&t2->value==0)
			{
				place=t1;
				c3=NULL;
				return connectCodes(4, c0, c1, c2, c3);
			}
			else*/
			c3->code.binop.result = place;
			c3->code.binop.op1 = t1;
			c3->code.binop.op2 = t2;
			return connectCodes(4, c0, c1, c2, c3);
		}
		else{
			Operand t3;
			if(t2->kind==CONSTANT&&t2->value==0)
			{
				t1=temp;
				t3=temp;
				c3=NULL;
			}
			else
			{
				t1 = temp;
				t3 = new_temp();
				c3->code.binop.result = t3;
				c3->code.binop.op1 = t1;
				c3->code.binop.op2 = t2;
			}
			c1 = malloc(sizeof(struct InterCodes_));
			c1->prev = c1->next = c1;
			c1->code.kind = ASSIGN;
			c1->code.assign.left = place;
			Operand t0 = malloc(sizeof(struct Operand_));
			t0->kind = POINT;
			t0->addr = t3;
			c1->code.assign.right = t0;
			return connectCodes(4, c0, c2, c3, c1);		
		}
	}			
	//Exp : ID LP RP
	else if(strcmp(p->cnode.children[0]->name,"ID")==0&&p->cnode.arity==3)
	{
		if(place==NULL)
			place=new_temp();
		InterCodes codes = malloc(sizeof(struct InterCodes_));
		codes->prev = codes->next = codes;
		if(strcmp(p->cnode.children[0]->id_value, "read")==0){
			codes->code.kind = READ;
			codes->code.assign.right=place;
		}
		else{
			codes->code.kind = CALL;
			codes->code.call.result = place;
			codes->code.call.funName = p->cnode.children[0]->id_value;
		}
		return codes;  	
	}
	//Exp : ID LP Args RP
	else if(strcmp(p->cnode.children[0]->name,"ID")==0&&p->cnode.arity==4)
	{
		if(place==NULL)
			place=new_temp();
		InterCodes codes = malloc(sizeof(struct InterCodes_));
		codes->prev = codes->next = codes;
		Arguments arg_list = NULL;
		test();
		InterCodes codes1 = translate_Args(p->cnode.children[2], &arg_list);
		if(strcmp(p->cnode.children[0]->id_value, "write") == 0){
			codes->code.kind = WRITE;
			codes->code.assign.right = arg_list->op;
			return connectCodes(2, codes1, codes);
		}
		else
		{
		codes = NULL;
		while(arg_list != NULL){
			InterCodes codes2 = malloc(sizeof(struct InterCodes_));
			codes2->prev = codes2->next = codes2;
			codes2->code.kind = ARG;
			codes2->code.assign.right = arg_list->op;
			codes = connectCodes(2, codes, codes2);
			arg_list = arg_list->next;
		}
		InterCodes codes2 = malloc(sizeof(struct InterCodes_));
		codes2->prev = codes2->next = codes2;
		codes2->code.kind = CALL;
		codes2->code.call.funName = p->cnode.children[0]->id_value;
		codes2->code.call.result = place;
		return connectCodes(3, codes1, codes, codes2);
		}  
	}
	//Exp : Exp1 ASSIGNOP Exp2
	else if(strcmp(p->cnode.children[1]->name, "ASSIGNOP") == 0)
	{	
		Node *Exp1 = p->cnode.children[0];
		Node *Exp2 = p->cnode.children[2];
		Operand temp1 = optimizeExp(Exp1);
		Operand temp2 = optimizeExp(Exp2);
		Operand t1, t2;
		InterCodes codes, codes1;
		//left situation:single variable,ele of array, or ele of struct
		if(temp1->kind==TEMP){
			codes = translate_Exp(Exp1, temp1);	
			t1 = malloc(sizeof(struct Operand_));	
			t1->kind = POINT;
			t1->addr = temp1;
		}
		else{
			codes = NULL;
			t1 = temp1;
		}
		if(temp2->kind == TEMP)
		{
			codes1 = translate_Exp(Exp2, temp2);
			if(strcmp(Exp2->cnode.children[1]->name, "LB")==0)
			{
				t2 = malloc(sizeof(struct Operand_));	
				t2->kind = POINT;
				t2->addr = temp2;
			}
			else 
				t2 = temp2;
		}
		else
		{
			t2 = temp2;
			codes1 = NULL;
		}
		InterCodes codes2 = malloc(sizeof(struct InterCodes_));
		InterCodes codes3 = malloc(sizeof(struct InterCodes_));
		codes2->prev = codes2->next = codes2;
		codes3->prev = codes3->next = codes3;
		codes2->code.kind = ASSIGN;
		codes2->code.assign.left = t1;
		codes2->code.assign.right = t2;
		codes3->code.kind = ASSIGN;
		codes3->code.assign.left = place;
		codes3->code.assign.right = codes2->code.assign.left;
		return connectCodes(4, codes1, codes, codes2, codes3);	
	}
	//Exp : Exp PLUS Exp
	//Exp : Exp MINUS Exp
	//Exp : Exp STAR Exp
	//Exp : Exp DIV Exp	
	else if(strcmp(p->cnode.children[1]->name,"PLUS")==0||strcmp(p->cnode.children[1]->name,"STAR")==0||strcmp(p->cnode.children[1]->name,"MINUS")==0||strcmp(p->cnode.children[1]->name,"DIV")==0)
	{
		if(place==NULL)
			return NULL;
		test2();
		InterCodes codes1, codes2;//code1:exp1   code2:exp2
		Operand t1, t2;
		Operand temp1 = optimizeExp(p->cnode.children[0]);
		Operand temp2 = optimizeExp(p->cnode.children[2]);
		if(temp1->kind==TEMP)
		{
			codes1 = translate_Exp(p->cnode.children[0], temp1);
			if(p->cnode.children[0]->cnode.arity==4&&strcmp(p->cnode.children[0]->cnode.children[1]->name, "LB")==0)
			{
				t1 = malloc(sizeof(struct Operand_));	
				t1->kind = POINT;
				t1->addr = temp1;
			}
			else 
				t1 = temp1;
		}
		else
		{
			codes1 = NULL;
			t1 = temp1;	
		}
		if(temp2->kind==TEMP)
		{
			codes2 = translate_Exp(p->cnode.children[2], temp2);
			if(p->cnode.children[2]->cnode.arity == 4&&strcmp(p->cnode.children[2]->cnode.children[1]->name, "LB") ==0)
			{
				t2 = malloc(sizeof(struct Operand_));	
				t2->kind = POINT;
				t2->addr = temp2;
			}
			else 
				t2 = temp2;
		}
		else{
			codes2 = NULL;
			t2 = temp2;	
		}
		InterCodes codes3 = malloc(sizeof(struct InterCodes_));
		codes3->prev = codes3->next = codes3;
		if(t1->kind==CONSTANT&&t2->kind==CONSTANT)
		{
			codes3->code.kind=ASSIGN;
			codes3->code.assign.left = place;
			if(strcmp(p->cnode.children[1]->name, "PLUS") == 0)
			{
				t1->value=t1->value+t2->value;
				codes3->code.assign.right =t1;
			}
			else if(strcmp(p->cnode.children[1]->name, "MINUS") == 0)
			{
				t1->value=t1->value-t2->value;
				codes3->code.assign.right =t1;
			}
			else if(strcmp(p->cnode.children[1]->name, "STAR") == 0)
			{
				t1->value=t1->value*t2->value;
				codes3->code.assign.right =t1;
			}
			else
			{	
				t1->value=(t1->value)/(t2->value);
				codes3->code.assign.right =t1;
			}
			return connectCodes(3, codes1, codes2, codes3);
		}
		else
		{
			codes3->code.binop.op1 = t1;
			codes3->code.binop.op2 = t2;
			test2();
			codes3->code.binop.result = place;
			if(strcmp(p->cnode.children[1]->name, "PLUS") == 0)
				codes3->code.kind = ADD;
			else if(strcmp(p->cnode.children[1]->name, "MINUS") == 0)
				codes3->code.kind = SUB;
			else if(strcmp(p->cnode.children[1]->name, "STAR") == 0)
				codes3->code.kind = MUL;
			else
				codes3->code.kind = DIVIDE;
			return connectCodes(3, codes1, codes2, codes3);
		}
	}
	//Exp : LP Exp RP
	else if(strcmp(p->cnode.children[0]->name, "LP") == 0){
		return translate_Exp(p->cnode.children[1], place);
	}
	//Exp : MINUS Exp
	else if(strcmp(p->cnode.children[0]->name, "MINUS") == 0)
	{
		Operand t1 = optimizeExp(p->cnode.children[1]);
		Operand t_point;
		InterCodes code1;
		if(t1->kind == TEMP)
		{	
			code1 = translate_Exp(p->cnode.children[1], t1);
			if(p->cnode.children[1]->cnode.arity==4&&strcmp(p->cnode.children[1]->cnode.children[1]->name, "LB")==0)
			{
				t_point = malloc(sizeof(struct Operand_));	
				t_point->kind = POINT;
				t_point->addr = t1;
			}
			else 
				t_point = t1;
		}
		else
		{	
			code1 = NULL;
			t_point = t1;
		}
		InterCodes code2 = malloc(sizeof(struct InterCodes_));
		code2->prev = code2->next = code2;
		code2->code.kind = SUB;
		code2->code.binop.result = place;
		Operand newop = malloc(sizeof(struct Operand_));
		newop->kind = CONSTANT;
		newop->value = 0;
		code2->code.binop.op1 = newop;
		code2->code.binop.op2 = t_point;
		return connectCodes(2, code1, code2);		
	}
	//Exp : Exp AND Exp
	//Exp : Exp OR Exp
	//Exp : Exp RELOP Exp
	//Exp : NOT Exp
	else
	{
		InterCodes label1 = new_label();
		InterCodes label2 = new_label();
		InterCodes c1 = malloc(sizeof(struct InterCodes_));
		c1->prev = c1->next = c1;
		c1->code.kind = ASSIGN;
		c1->code.assign.left = place;
		Operand op_false = malloc(sizeof(struct Operand_));
		op_false->kind = CONSTANT;
		op_false->value = 0;
		c1->code.assign.right = op_false;
		InterCodes c2 = translate_Cond(p, label1, label2);
		InterCodes c3 = malloc(sizeof(struct InterCodes_));
		c3->prev = c3->next = c3;
		c3->code.kind = ASSIGN;
		c3->code.assign.left = place;
		Operand right2 = malloc(sizeof(struct Operand_));
		right2->kind = CONSTANT;
		right2->value = 1;
		c3->code.assign.right = right2;	
		return connectCodes(5, c1, c2, label1, c3, label2);
	}
}
InterCodes translate_Stmt(Node *p){
	//Stmt : CompSt
	if(p->cnode.arity==1){
		return translate_CompSt(p->cnode.children[0]);
	}
	//Stmt : Exp SEMI
	else if(p->cnode.arity==2){
		return translate_Exp(p->cnode.children[0], NULL);
	}
	//Stmt : RETURN Exp SEMI
	else if(p->cnode.arity==3){
		Operand t1 = optimizeExp(p->cnode.children[1]);
		InterCodes c1;
		Operand t_point;
		if(t1->kind==TEMP)
		{
			c1 = translate_Exp(p->cnode.children[1], t1);
			if(p->cnode.children[1]->cnode.arity==4&&strcmp(p->cnode.children[1]->cnode.children[1]->name, "LB")==0)
			{
				t_point = malloc(sizeof(struct Operand_));	
				t_point->kind = POINT;
				t_point->addr = t1;
			}
			else 
				t_point = t1;
		}
		else
		{
			c1 = NULL;
			t_point = t1;
		}
		InterCodes c2 = malloc(sizeof(struct InterCodes_));
		c2->prev = c2->next = c2;
		c2->code.kind = RET;
		c2->code.assign.right = t_point;
		test();
		return connectCodes(2, c1, c2);
	}
	//Stmt : IF LP Exp RP Stmt
	else if(strcmp(p->cnode.children[0]->name,"IF")==0&&p->cnode.arity==5)
	{
		InterCodes label1 = new_label();
		InterCodes label2 = new_label();
		InterCodes c1 = translate_Cond(p->cnode.children[2], label1, label2);
		InterCodes c2 = translate_Stmt(p->cnode.children[4]);	
		return connectCodes(4, c1, label1, c2, label2);	
	}
	//Stmt : IF LP Exp RP Stmt ELSE Stmt
	else if(p->cnode.arity==7){
		InterCodes label1 = new_label();
		InterCodes label2 = new_label();
		InterCodes label3, newGoto;
		//the next is return statement,we can reduce the label3 and newGoto
		if(strcmp(p->cnode.children[4]->cnode.children[0]->name,"RETURN")==0)
		{
			label3 = NULL;
			newGoto = NULL;
		}
		else
		{
			label3 = new_label();
			newGoto = new_goto(label3->code.id);
		}
		InterCodes c1 = translate_Cond(p->cnode.children[2], label1, label2);
		InterCodes c2 = translate_Stmt(p->cnode.children[4]);
		InterCodes c3 = translate_Stmt(p->cnode.children[6]);	
		return connectCodes(7, c1, label1, c2, newGoto, label2, c3, label3);
	}
	//Stmt : WHILE LP Exp RP Stmt
	else
	{
		InterCodes label1 = new_label();
		InterCodes label2 = new_label();
		InterCodes label3 = new_label();
		InterCodes c1 = translate_Cond(p->cnode.children[2], label2, label3);
		InterCodes c2 = translate_Stmt(p->cnode.children[4]);		
		return connectCodes(6, label1, c1, label2, c2, new_goto(label1->code.id), label3);
	}
}
InterCodes translate_StmtList(Node *p){
	//StmtList : Stmt StmtList
	if(p->cnode.arity==2){
		InterCodes c1=translate_Stmt(p->cnode.children[0]);
		InterCodes c2=translate_StmtList(p->cnode.children[1]);
		return connectCodes(2, c1, c2);
	}
	//StmtList : NULL
	return NULL;
}
InterCodes translate_CompSt(Node *p){
	//CompSt : LC DefList StmtList RC
	InterCodes c1 = translate_DefList(p->cnode.children[1]);
	InterCodes c2 = translate_StmtList(p->cnode.children[2]);
	return connectCodes(2, c1, c2);	
}
InterCodes translate_Args(Node *p, Arguments* arg_list){
	Operand temp = optimizeExp(p->cnode.children[0]);
	InterCodes c1;
	Operand t1;
	if(temp->kind == TEMP){
		c1 = translate_Exp(p->cnode.children[0], temp);
		if(strcmp(p->cnode.children[0]->cnode.children[1]->name, "LB")==0)
		{
			t1 = malloc(sizeof(struct Operand_));	
			t1->kind = POINT;
			t1->addr = temp;
		}
		else if(strcmp(p->cnode.children[0]->cnode.children[1]->name,"DOT") ==0)
		{
			printf("Cannot translate: Code contains variables or parameters of structure type\n");
			exit(0);
		}
		else 
			t1 = temp;
	}
	else{
		c1 = NULL;
		if(strcmp(p->cnode.children[0]->cnode.children[0]->name,"ID") != 0)
			t1 = temp;
		else if(isAddress(p->cnode.children[0]->cnode.children[0]->id_value) ==1)		{
			t1 = malloc(sizeof(struct Operand_));
			t1->kind = ADDRESS;
			t1->addr = temp;
		}
		else
			t1 = temp;
	}
	Arguments arg = malloc(sizeof(struct Arguments_));
	arg->op = t1;
	arg->next = *arg_list;
	*arg_list = arg;
	//Args : Exp
	if(p->cnode.arity == 1)
		return c1;
	//Args : Exp COMMA Args
	return connectCodes(2, c1, translate_Args(p->cnode.children[2], arg_list));
}
InterCodes translate_ExtDefList(Node*p)
{
	//ExtDefList : ExtDef ExtDefList
	if(p->cnode.arity==2){
		InterCodes c1 = translate_ExtDef(p->cnode.children[0]);
		InterCodes c2 = translate_ExtDefList(p->cnode.children[1]);
		return connectCodes(2, c1, c2);	
	}
	//ExtDefList : NULL
		return NULL;
}
InterCodes translate_VarDec(Node *specifier, Node *p, int param){
	test2();
	//VarDec : VarDec LB INT RB
	if(p->cnode.arity == 4){
		InterCodes c1 = malloc(sizeof(struct InterCodes_));
		c1->prev = c1->next = c1;
		char id[20];
		//get the size of the array,if struct,printf "error"
		int spacesize = getArraySpace(arrayType(p, id, specifier));	
		addressTable[IR_number] = strdup(id);
		IR_number ++;
		if(param==0){
			c1->code.kind = DEC;
			c1->code.assign.left = lookup(strdup(id));
			c1->code.assign.right = new_create_space(spacesize);
		}
		else{
			c1->code.kind = PARAM;
			c1->code.assign.right = lookup(strdup(id));
			paramTable[paramNum] = strdup(id);
			paramNum ++;
		}
		insertTable(varTable, VarDec(p, specifier), 0);
		return c1;
	}
	//VarDec : ID
	if(strcmp(specifier->name, "TYPE") == 0){
		insertTable(varTable, VarDec(p, specifier), 0);
		if(param == 1){
			InterCodes c1 = malloc(sizeof(struct InterCodes_));
			c1->prev = c1->next = c1;
			c1->code.kind = PARAM;
			c1->code.assign.right = lookup(p->cnode.children[0]->id_value);
			return c1;
		}
		return NULL;
	}
	//maybe struct {}a;  or struct A a;
	else if(strcmp(specifier->name, "StructSpecifier") == 0){
		printf("Cannot translate: Code contains variables or parameters of structure type\n");
		exit(0);
	}
	return NULL;
}
//first :specifier,second:ExtDecList
InterCodes translate_ExtDecList(Node *specifier, Node *p){
	//ExtDecList :VarDec
	if(p->cnode.arity == 1){
		return translate_VarDec(specifier->cnode.children[0], p->cnode.children[0], 0);
	}
	//ExtDecList : VarDec COMMA ExtDecList 
	else{
		InterCodes c1 = translate_VarDec(specifier->cnode.children[0], p->cnode.children[0], 0);
		InterCodes c2 = translate_ExtDecList(specifier, p->cnode.children[2]);	
		return connectCodes(2, c1, c2);	
	}
}
InterCodes translate_ExtDef(Node *p){
	//ExtDef : Specifier SEMI
	if(strcmp(p->cnode.children[1]->name,"SEMI") == 0){
		return NULL;	
	}
	//ExtDef : Specifier ExtDecList SEMI
	else if(strcmp(p->cnode.children[1]->name,"ExtDecList") == 0){
		return translate_ExtDecList(p->cnode.children[0], p->cnode.children[1]);
	}
	//ExtDef : Specifier FunDec CompSt
	else{
		InterCodes c1 = translate_FunDec(p->cnode.children[1]);
		InterCodes c2 = translate_CompSt(p->cnode.children[2]);
		return connectCodes(2, c1, c2);	
	}
}
InterCodes translate_DecList(Node *specifier_next, Node *p){
	//DecList : Dec
	if(p->cnode.arity == 1){
		return translate_Dec(specifier_next, p->cnode.children[0]);
	}
	//DecList : Dec COMMA DecList 
	else{
		InterCodes c1 = translate_Dec(specifier_next, p->cnode.children[0]);
		InterCodes c2 = translate_DecList(specifier_next, p->cnode.children[2]);	
		return connectCodes(2, c1, c2);	
	}
}
InterCodes translate_DefList(Node *p){
	if(p->cnode.arity == 2){
	//DefList : Def DefList
	//Def : Specifier DecList SEMI
		InterCodes c1 = translate_DecList(p->cnode.children[0]->cnode.children[0]->cnode.children[0], p->cnode.children[0]->cnode.children[1]);
		InterCodes c2 = translate_DefList(p->cnode.children[1]);
		return connectCodes(2, c1, c2);
	}
	//DefList : NULL
	return NULL;
}
InterCodes translate_Dec(Node *specifier_next, Node *p){
	//Dec : VarDec
	if(p->cnode.arity==1){
		return translate_VarDec(specifier_next, p->cnode.children[0], 0);
	}
	//Dec : VarDec ASSIGNOP Exp
	else
	{
		//optimize the exp if the next is int ,float ,or id
		Operand temp1 = optimizeExp(p->cnode.children[2]);
		InterCodes c0, c1;
		//attention!
		//because VarDec cannot be array,so c0 is NULL
		c0 = translate_VarDec(specifier_next, p->cnode.children[0], 0);
		Operand t1;//right Operand
		if(temp1->kind == TEMP){
			c1 = translate_Exp(p->cnode.children[2], temp1);
			if(strcmp(p->cnode.children[2]->cnode.children[1]->name, "LB") == 0 || strcmp(p->cnode.children[2]->cnode.children[1]->name, "DOT") == 0){
				t1 = malloc(sizeof(struct Operand_));	
				t1->kind = POINT;
				t1->addr = temp1;
			}
			else 
				t1 = temp1;
		}
		else{
			c1 = NULL;
			t1 = temp1;
		}
		InterCodes c2 = malloc(sizeof(struct InterCodes_));
		c2->prev = c2->next = c2;
		c2->code.kind = ASSIGN;
		c2->code.assign.left = lookup(p->cnode.children[0]->cnode.children[0]->id_value);
		c2->code.assign.right = t1;
		return connectCodes(3, c0, c1, c2);
	}
}
InterCodes translate_VarList(Node *p){
	//VarList : ParamDec COMMA VarList
	//ParamDec : Specifier VarDec
	if(p->cnode.arity == 3){
		InterCodes c1 = translate_VarDec(p->cnode.children[0]->cnode.children[0]->cnode.children[0], p->cnode.children[0]->cnode.children[1], 1);
		InterCodes c2 = translate_VarList(p->cnode.children[2]);
		return connectCodes(2, c1, c2);
	}
	//VarList : ParamDec
	//ParamDec : Specifier VarDec
	return translate_VarDec(p->cnode.children[0]->cnode.children[0]->cnode.children[0], p->cnode.children[0]->cnode.children[1], 1);
}

InterCodes translate_FunDec(Node *p){
	InterCodes c1 = malloc(sizeof(struct InterCodes_));
	c1->prev = c1->next = c1;
	c1->code.kind = FUNDEC;
	c1->code.fun_name = strdup(p->cnode.children[0]->id_value);
	//FunDec : ID LP VarList RP
	if(p->cnode.arity == 4){
		InterCodes c2 = translate_VarList(p->cnode.children[2]);
		return connectCodes(2, c1, c2);
	}
	//FunDec : ID LP RP
	else
		return c1;
}
InterCodes ir_generate(Node *p)
{
	if(strcmp(p->name,"ExtDefList") == 0)
	{
		return translate_ExtDefList(p);
	}
	else if(strcmp(p->name,"CompSt") == 0)
	{
		return translate_CompSt(p);
	}
	else if(strcmp(p->name,"Exp") == 0)
	{
		return translate_Exp(p, NULL);
	}
	else if(strcmp(p->name,"Stmt") == 0)
	{
		return translate_Stmt(p);
	}
	else if(strcmp(p->name,"DefList") == 0)
	{
		return translate_DefList(p);
	}
	else
	{
		int i = 0;
		InterCodes codes = NULL;
		if(p->node_type == Nonterminal){
			for(; i < p->cnode.arity; i++){
				codes = connectCodes(2, codes, ir_generate(p->cnode.children[i]));
			}
		}
		return codes;	
	}
}
void print_op(Operand op, FILE *fp){
	switch(op->kind){
		case VARIABLE:
			fprintf(fp, "%s", op->var_name);
			break;
		case CONSTANT:
			fprintf(fp, "#%d", op->value);
			break;
		case FCONSTANT:
			fprintf(fp, "#%f", op->fvalue);
			break;
		case ADDRESS:
			fprintf(fp, "&");
			print_op(op->addr, fp);
			break;
		case TEMP:
			fprintf(fp, "t%d", op->temp_id);
			break;
		case SPACE:
			fprintf(fp, " %d", op->value);
			break;
		case POINT:
			fprintf(fp, "*");
			print_op(op->addr, fp);
			break;
		case STRUCTURE:
			fprintf(fp, "%s", op->var_name);
			break;
	}
}
char* getopposize_relop(char*source_relop)
{
	if(strcmp(source_relop,">")==0)
		return "<=";
	else if(strcmp(source_relop,">=")==0)
		return "<";
	else if(strcmp(source_relop,"<")==0)
		return ">=";
	else if(strcmp(source_relop,"<=")==0)
		return ">";
	else if(strcmp(source_relop,"==")==0)
		return "!=";
	else if(strcmp(source_relop,"!=")==0)
		return "==";
}
void delete_one_code(InterCodes code) {
	code->next->prev = code->prev;
	code->prev->next = code->next;
}
//replace largelabel with smalllabel
void replacelabel(InterCodes codes,int smalllabel,int largelabel)
{
	InterCodes head=codes;
	codes=codes->next;
	while(codes!=head)
	{
		switch(codes->code.kind)
		{
			case GOTO:
				if(codes->code.id==largelabel)
				{
					codes->code.id=smalllabel;
				}
				break;
			case IFGOTO:
				if(codes->code.ifgoto.label->code.id==largelabel)
				{
					codes->code.ifgoto.label->code.id=smalllabel;
				}
				break;
		}
		codes=codes->next;
	}
}
void optimizetwolabels(InterCodes codes)
{
	InterCodes head=codes;
	codes=codes->next;
	while(codes!=head)
	{
		switch(codes->code.kind)
		{
			case LABEL:
				if(codes->next!=head&&codes->next->code.kind==LABEL)
				{
					int small=codes->code.id;
					int large=codes->next->code.id;
					if(codes->code.id>codes->next->code.id)
					{
						small=codes->next->code.id;
						large=codes->code.id;
						replacelabel(head,small,large);
						//delete_one_code(codes);
						InterCodes temp=codes->next;
						codes->next->prev = codes->prev;
						codes->prev->next = codes->next;
					}
					else
					{
						replacelabel(head,small,large);
						//printf("%dhhhh%d\n",codes->code.id,codes->next->code.id);
						//codes=codes->next;
						//delete_one_code(codes);
						codes->next->next->prev = codes;
						codes->next = codes->next->next;
					}
				}
				break;
		}
		codes=codes->next;
	}

}
void optimizeifgoto(InterCodes codes)
{
	InterCodes head=codes;
	codes=codes->next;
	while(codes!=head)
	{
		switch(codes->code.kind)
		{
			case IFGOTO:
				if(codes->next!=head&&codes->next->code.kind==GOTO&&codes->next->next!=head&&codes->next->next->code.kind==LABEL)
				{
					if(codes->code.ifgoto.label->code.id==codes->next->next->code.id)
					{
						char*opposize_re=getopposize_relop(codes->code.ifgoto.relop);
						free(codes->code.ifgoto.relop);
						codes->code.ifgoto.relop=NULL;
						codes->code.ifgoto.relop=strdup(opposize_re);
						int origin_id=codes->code.ifgoto.label->code.id;
						codes->code.ifgoto.label->code.id=codes->next->code.id;
						delete_one_code(codes->next);
						delete_one_code(codes->next);
						InterCodes label_temp=malloc(sizeof(struct InterCodes_));
						label_temp->prev = label_temp->next = label_temp;
						label_temp->code.kind = LABEL;
						label_temp->code.id = origin_id;
						label_temp->prev=codes;
						label_temp->next=codes->next;
						codes->next=label_temp;
					}
				}
				break;
		}
		codes=codes->next;
	}
}
void print_code(InterCodes codes,char*output_name)
{
	FILE *fp = fopen(output_name, "w+");
	while(codes != NULL){
		switch(codes->code.kind){
			case ASSIGN:
				if(codes->code.assign.left != NULL){
				print_op(codes->code.assign.left, fp);
				fprintf(fp, " := ");
				print_op(codes->code.assign.right, fp);
				fprintf(fp, "\n");
				}
				break;
			case ADD: 
				print_op(codes->code.binop.result, fp);
				fprintf(fp, " := ");
				print_op(codes->code.binop.op1, fp);
				fprintf(fp, " + ");
				print_op(codes->code.binop.op2, fp);
				fprintf(fp, "\n");
				break;
			case SUB:
				print_op(codes->code.binop.result, fp);
				fprintf(fp, " := ");
				print_op(codes->code.binop.op1, fp);
				fprintf(fp, " - ");
				print_op(codes->code.binop.op2, fp);
				fprintf(fp, "\n");
				break; 
			case MUL:
				print_op(codes->code.binop.result, fp);
				fprintf(fp, " := ");
				print_op(codes->code.binop.op1, fp);
				fprintf(fp, " * ");
				print_op(codes->code.binop.op2, fp);
				fprintf(fp, "\n");
				break; 
			case DIVIDE:
				print_op(codes->code.binop.result, fp);
				fprintf(fp, " := ");
				print_op(codes->code.binop.op1, fp);
				fprintf(fp, " / ");
				print_op(codes->code.binop.op2, fp);
				fprintf(fp, "\n");
				break;
			case LABEL:
				fprintf(fp, "LABEL label%d :\n", codes->code.id);
				break;
			case GOTO:
				fprintf(fp, "GOTO label%d\n", codes->code.id);
				break;
			case IFGOTO:
				fprintf(fp, "IF ");
				print_op(codes->code.ifgoto.op1, fp);
				fprintf(fp, " %s ", codes->code.ifgoto.relop);
				print_op(codes->code.ifgoto.op2, fp);
				fprintf(fp, " GOTO label%d\n", codes->code.ifgoto.label->code.id);
				break;
			case FUNDEC:
				fprintf(fp, "FUNCTION %s :\n", codes->code.fun_name);
				break;
			case CALL:
				print_op(codes->code.call.result, fp);
				fprintf(fp, " := CALL %s\n", codes->code.call.funName);
				break;
			case RET:
				fprintf(fp, "RETURN ");
				print_op(codes->code.assign.right, fp);
				fprintf(fp, "\n");
				break;
			case READ:
				fprintf(fp, "READ ");
				print_op(codes->code.assign.right, fp);
				fprintf(fp, "\n");
				break;
			case WRITE:
				fprintf(fp, "WRITE ");
				print_op(codes->code.assign.right, fp);
				fprintf(fp, "\n");
				break;
			case ARG:
				fprintf(fp, "ARG ");
				print_op(codes->code.assign.right, fp);
				fprintf(fp, "\n");
				break;
			case PARAM:
				fprintf(fp, "PARAM ");
				print_op(codes->code.assign.right, fp);
				fprintf(fp, "\n");
				break;
			case DEC:
				fprintf(fp, "DEC ");
				print_op(codes->code.assign.left, fp);
				print_op(codes->code.assign.right, fp);
				fprintf(fp, "\n");
				break;
			default:
				break;
		}
		codes->prev->next = NULL;
		codes = codes->next;
	}
}