#include "hash.h"
#include "ir.h"
#include "semantic.h"
#include <fcntl.h>
#define temp_size 100
char *reg_var[temp_size];//store temp name
int offset_reg[temp_size];//the offset of every reg
int used_reg_num = 0;//the use number of reg_var
int top_offset;
char *reg_arg[20];//parameters of the function
int arg_num = 0;//the number of parameters
int return_used = 0;//return used
char* return_var;//return name
int print_reg(char *name,FILE *fp)
{
	int i;
	if(return_used == 1 && strcmp(return_var, name) == 0)//the return statement
	{
		top_offset=top_offset+4;
		fprintf(fp,"\taddi $sp, $sp, -4\n");
		return -1;//stand for return
	}
	for(i = 0; i < arg_num; i ++)//whether it is the parameter
	{
		if(strcmp(reg_arg[i], name) == 0)
		{
			break;
		}
	}
	if(i < arg_num)//it is parameter
	{
		return (12+i*4);
	}
	for(i = 0; i < used_reg_num; i ++)//whether it is already existed
	{
		if(strcmp(reg_var[i], name) == 0)
		{
			break;
		}
	}
	if(i == used_reg_num)//never existed
	{
		reg_var[i] = strdup(name);
		used_reg_num ++;
		top_offset=top_offset+4;
		fprintf(fp,"\taddi $sp, $sp, -4\n");
		offset_reg[i]=top_offset;
		return top_offset;
	}
	else
	{
		return offset_reg[i];
	}
	/*if(i < 10)
		fprintf(fp,"$t%d", i);
	else
		fprintf(fp,"$s%d", i-10);
		*/
}
char* get_var_name(Operand op)
{
	if(op->kind == VARIABLE)
		return op->var_name;
	else if(op->kind==ADDRESS||op->kind==POINT)
	{
		if(op->addr->kind==VARIABLE)
			return op->addr->var_name;
		else if(op->addr->kind==TEMP)
		{
			char str[20];
			sprintf(str,"t%d",op->addr->temp_id);
			char *s = strdup(str);
			return s;
		}
	}
	else
	{
		char str[20];
		sprintf(str,"t%d",op->temp_id);
		char *s = strdup(str);
		return s;
	}	
}
void create_mips_code(InterCodes codes,char*output_name)
{
	FILE *fp = fopen(output_name, "w+");
	fprintf(fp,".data\n");
	fprintf(fp,"_prompt: .asciiz \"Enter an integer:\"\n");
	fprintf(fp,"_ret: .asciiz \"\\n\"\n");
	fprintf(fp,".globl main\n");
	fprintf(fp,".text\n");
	fprintf(fp,"read:\n");
	fprintf(fp,"\tli $v0, 4\n");
	fprintf(fp,"\tla $a0, _prompt\n");
	fprintf(fp,"\tsyscall\n");
	fprintf(fp,"\tli $v0, 5\n");
	fprintf(fp,"\tsyscall\n");
	fprintf(fp,"\tjr $ra\n");
	fprintf(fp,"\n");
	fprintf(fp,"write:\n");
	fprintf(fp,"\tli $v0, 1\n\tsyscall\n\tli $v0, 4\n\tla $a0, _ret\n\tsyscall\n");
	fprintf(fp,"\tmove $v0, $0\n");
	fprintf(fp,"\tjr $ra\n");
	fprintf(fp,"\n");
	int temp_reg, i, j,q;
	InterCodes firstArg;
	while(codes!=NULL)
	{
		switch(codes->code.kind)
		{
			case ADD:
			{	if(codes->code.binop.op1->kind==CONSTANT && codes->code.binop.op2->kind==CONSTANT)
				{
					fprintf(fp,"\tli $t0, %d\n",codes->code.binop.op1->value);
					fprintf(fp,"\taddi $t1, $t0, %d\n",codes->code.binop.op2->value);
					if(codes->code.binop.result->kind==POINT)
					{
						int move_size=print_reg(get_var_name(codes->code.binop.result),fp);
						fprintf(fp,"\tlw $t2, -%d($fp)\n",move_size);
						fprintf(fp,"\tadd $t2, $t2, $fp\n");
						fprintf(fp,"\tsw $t1, ($t2)\n");
					}
					else
					{
						int move_size3=print_reg(get_var_name(codes->code.binop.result),fp);//result
						fprintf(fp,"\tsw $t1, -%d($fp)\n",move_size3);	
					}
				}
				else if(codes->code.binop.op1->kind == CONSTANT || codes->code.binop.op2->kind == CONSTANT)
				{
					if(codes->code.binop.op1->kind == CONSTANT)
					{
						fprintf(fp,"\tli $t0, %d\n",codes->code.binop.op1->value);
						if(codes->code.binop.op2->kind==ADDRESS)
						{
						char*or_name2=get_var_name(codes->code.binop.op2);
						char*new_name2=malloc(2+strlen(or_name2)+1);
						new_name2[0]='#';
						new_name2[1]='0'+0;
						new_name2[2]='\0';
						strcat(new_name2,or_name2);
						int move_size2=print_reg(new_name2,fp);
						fprintf(fp,"\tli $t1, %d\n",move_size2);
						}
						else if(codes->code.binop.op2->kind==POINT)
						{
						int move_size=print_reg(get_var_name(codes->code.binop.op2),fp);
						fprintf(fp,"\tlw $t1, -%d($fp)\n",move_size);
						fprintf(fp,"\tadd $t1, $t1, $fp\n");
						fprintf(fp,"\tlw $t1, ($t1)\n");
						}
						else
						{
						int move_size2=print_reg(get_var_name(codes->code.binop.op2),fp);
						fprintf(fp,"\tlw $t1, -%d($fp)\n",move_size2);
						}
						fprintf(fp,"\tadd $t2, $t0, $t1\n");
						if(codes->code.binop.result->kind==POINT)
						{
							int move_size=print_reg(get_var_name(codes->code.binop.result),fp);
							fprintf(fp,"\tlw $t3, -%d($fp)\n",move_size);
							fprintf(fp,"\tadd $t3, $t3, $fp\n");
							fprintf(fp,"\tsw $t2, ($t3)\n");
						}
						else
						{
							int move_size3=print_reg(get_var_name(codes->code.binop.result),fp);//result
							fprintf(fp,"\tsw $t2, -%d($fp)\n",move_size3);	
						}
					}
					else
					{
						if(codes->code.binop.op1->kind==ADDRESS)
						{
						char*or_name=get_var_name(codes->code.binop.op1);
						char*new_name=malloc(2+strlen(or_name)+1);
						new_name[0]='#';
						new_name[1]='0'+0;
						new_name[2]='\0';
						strcat(new_name,or_name);
						int move_size=print_reg(new_name,fp);
						fprintf(fp,"\tli $t0, %d\n",move_size);
						}
						else if(codes->code.binop.op1->kind==POINT)
						{
						int move_size=print_reg(get_var_name(codes->code.binop.op1),fp);
						fprintf(fp,"\tlw $t0, -%d($fp)\n",move_size);
						fprintf(fp,"\tadd $t0, $t0, $fp\n");
						fprintf(fp,"\tlw $t0, ($t0)\n");
						}
						else
						{
						int move_size=print_reg(get_var_name(codes->code.binop.op1),fp);
						fprintf(fp,"\tlw $t0, -%d($fp)\n",move_size);	
						}
						fprintf(fp,"\tli $t1, %d\n",codes->code.binop.op2->value);
						fprintf(fp,"\tadd $t2, $t0, $t1\n");
						if(codes->code.binop.result->kind==POINT)
						{
							int move_size=print_reg(get_var_name(codes->code.binop.result),fp);
							fprintf(fp,"\tlw $t3, -%d($fp)\n",move_size);
							fprintf(fp,"\tadd $t3, $t3, $fp\n");
							fprintf(fp,"\tsw $t2, ($t3)\n");
						}
						else
						{
							int move_size3=print_reg(get_var_name(codes->code.binop.result),fp);//result
							fprintf(fp,"\tsw $t2, -%d($fp)\n",move_size3);	
						}
					}
				}
				else
				{
					if(codes->code.binop.op1->kind==ADDRESS)
					{
						char*or_name=get_var_name(codes->code.binop.op1);
						char*new_name=malloc(2+strlen(or_name)+1);
						new_name[0]='#';
						new_name[1]='0'+0;
						new_name[2]='\0';
						strcat(new_name,or_name);
						int move_size=print_reg(new_name,fp);
						fprintf(fp,"\tli $t0, %d\n",move_size);
					}
					else if(codes->code.binop.op1->kind==POINT)
					{
						int move_size=print_reg(get_var_name(codes->code.binop.op1),fp);
						fprintf(fp,"\tlw $t0, -%d($fp)\n",move_size);
						fprintf(fp,"\tadd $t0, $t0, $fp\n");
						fprintf(fp,"\tlw $t0, ($t0)\n");
					}
					else
					{
						int move_size=print_reg(get_var_name(codes->code.binop.op1),fp);
						fprintf(fp,"\tlw $t0, -%d($fp)\n",move_size);
					}
					if(codes->code.binop.op2->kind==ADDRESS)
					{
						char*or_name2=get_var_name(codes->code.binop.op2);
						char*new_name2=malloc(2+strlen(or_name2)+1);
						new_name2[0]='#';
						new_name2[1]='0'+0;
						new_name2[2]='\0';
						strcat(new_name2,or_name2);
						int move_size2=print_reg(new_name2,fp);
						fprintf(fp,"\tli $t1, %d\n",move_size2);
					}
					else if(codes->code.binop.op2->kind==POINT)
					{
						int move_size=print_reg(get_var_name(codes->code.binop.op2),fp);
						fprintf(fp,"\tlw $t1, -%d($fp)\n",move_size);
						fprintf(fp,"\tadd $t1, $t1, $fp\n");
						fprintf(fp,"\tlw $t1, ($t1)\n");
					}
					else
					{
						int move_size2=print_reg(get_var_name(codes->code.binop.op2),fp);
						fprintf(fp,"\tlw $t1, -%d($fp)\n",move_size2);
					}
					fprintf(fp,"\tadd $t2, $t0, $t1\n");
					if(codes->code.binop.result->kind==POINT)
					{
						int move_size=print_reg(get_var_name(codes->code.binop.result),fp);
						fprintf(fp,"\tlw $t3, -%d($fp)\n",move_size);
						fprintf(fp,"\tadd $t3, $t3, $fp\n");
						fprintf(fp,"\tsw $t2, ($t3)\n");
					}
					else
					{
						int move_size3=print_reg(get_var_name(codes->code.binop.result),fp);//result
						fprintf(fp,"\tsw $t2, -%d($fp)\n",move_size3);	
					}
				}
			}
				break;
			case SUB:
			{	if(codes->code.binop.op1->kind == CONSTANT && codes->code.binop.op2->kind == CONSTANT)
				{
					fprintf(fp,"\tli $t0, %d\n",codes->code.binop.op1->value);
					fprintf(fp,"\taddi $t1, $t0, -%d\n",codes->code.binop.op2->value);
					if(codes->code.binop.result->kind==POINT)
					{
						int move_size=print_reg(get_var_name(codes->code.binop.result),fp);
						fprintf(fp,"\tlw $t2, -%d($fp)\n",move_size);
						fprintf(fp,"\tadd $t2, $t2, $fp\n");
						fprintf(fp,"\tsw $t1, ($t2)\n");
					}
					else
					{
						int move_size3=print_reg(get_var_name(codes->code.binop.result),fp);//result
						fprintf(fp,"\tsw $t1, -%d($fp)\n",move_size3);	
					}
				}
				else if(codes->code.binop.op1->kind == CONSTANT || codes->code.binop.op2->kind == CONSTANT)
				{
					if(codes->code.binop.op1->kind == CONSTANT)
					{
						fprintf(fp,"\tli $t0, %d\n",codes->code.binop.op1->value);
						if(codes->code.binop.op2->kind==ADDRESS)
						{
						char*or_name2=get_var_name(codes->code.binop.op2);
						char*new_name2=malloc(2+strlen(or_name2)+1);
						new_name2[0]='#';
						new_name2[1]='0'+0;
						new_name2[2]='\0';
						strcat(new_name2,or_name2);
						int move_size2=print_reg(new_name2,fp);
						fprintf(fp,"\tli $t1, %d\n",move_size2);
						}
						else if(codes->code.binop.op2->kind==POINT)
						{
						int move_size=print_reg(get_var_name(codes->code.binop.op2),fp);
						fprintf(fp,"\tlw $t1, -%d($fp)\n",move_size);
						fprintf(fp,"\tadd $t1, $t1, $fp\n");
						fprintf(fp,"\tlw $t1, ($t1)\n");
						}
						else
						{
						int move_size2=print_reg(get_var_name(codes->code.binop.op2),fp);
						fprintf(fp,"\tlw $t1, -%d($fp)\n",move_size2);
						}
						fprintf(fp,"\tsub $t2, $t0, $t1\n");
						if(codes->code.binop.result->kind==POINT)
						{
							int move_size=print_reg(get_var_name(codes->code.binop.result),fp);
							fprintf(fp,"\tlw $t3, -%d($fp)\n",move_size);
							fprintf(fp,"\tadd $t3, $t3, $fp\n");
							fprintf(fp,"\tsw $t2, ($t3)\n");
						}
						else
						{
							int move_size3=print_reg(get_var_name(codes->code.binop.result),fp);//result
							fprintf(fp,"\tsw $t2, -%d($fp)\n",move_size3);	
						}
					}
					else
					{
						if(codes->code.binop.op1->kind==ADDRESS)
						{
						char*or_name=get_var_name(codes->code.binop.op1);
						char*new_name=malloc(2+strlen(or_name)+1);
						new_name[0]='#';
						new_name[1]='0'+0;
						new_name[2]='\0';
						strcat(new_name,or_name);
						int move_size=print_reg(new_name,fp);
						fprintf(fp,"\tli $t0, %d\n",move_size);
						}
						else if(codes->code.binop.op1->kind==POINT)
						{
						int move_size=print_reg(get_var_name(codes->code.binop.op1),fp);
						fprintf(fp,"\tlw $t0, -%d($fp)\n",move_size);
						fprintf(fp,"\tadd $t0, $t0, $fp\n");
						fprintf(fp,"\tlw $t0, ($t0)\n");
						}
						else
						{
						int move_size=print_reg(get_var_name(codes->code.binop.op1),fp);
						fprintf(fp,"\tlw $t0, -%d($fp)\n",move_size);	
						}
						fprintf(fp,"\tli $t1, %d\n",codes->code.binop.op2->value);
						fprintf(fp,"\tsub $t2, $t0, $t1\n");
						if(codes->code.binop.result->kind==POINT)
						{
							int move_size=print_reg(get_var_name(codes->code.binop.result),fp);
							fprintf(fp,"\tlw $t3, -%d($fp)\n",move_size);
							fprintf(fp,"\tadd $t3, $t3, $fp\n");
							fprintf(fp,"\tsw $t2, ($t3)\n");
						}
						else
						{
							int move_size3=print_reg(get_var_name(codes->code.binop.result),fp);//result
							fprintf(fp,"\tsw $t2, -%d($fp)\n",move_size3);	
						}
					}
				}
				else
				{
					if(codes->code.binop.op1->kind==ADDRESS)
					{
						char*or_name=get_var_name(codes->code.binop.op1);
						char*new_name=malloc(2+strlen(or_name)+1);
						new_name[0]='#';
						new_name[1]='0'+0;
						new_name[2]='\0';
						strcat(new_name,or_name);
						int move_size=print_reg(new_name,fp);
						fprintf(fp,"\tli $t0, %d\n",move_size);
					}
					else if(codes->code.binop.op1->kind==POINT)
					{
						int move_size=print_reg(get_var_name(codes->code.binop.op1),fp);
						fprintf(fp,"\tlw $t0, -%d($fp)\n",move_size);
						fprintf(fp,"\tadd $t0, $t0, $fp\n");
						fprintf(fp,"\tlw $t0, ($t0)\n");
					}
					else
					{
						int move_size=print_reg(get_var_name(codes->code.binop.op1),fp);
						fprintf(fp,"\tlw $t0, -%d($fp)\n",move_size);
					}
					if(codes->code.binop.op2->kind==ADDRESS)
					{
						char*or_name2=get_var_name(codes->code.binop.op2);
						char*new_name2=malloc(2+strlen(or_name2)+1);
						new_name2[0]='#';
						new_name2[1]='0'+0;
						new_name2[2]='\0';
						strcat(new_name2,or_name2);
						int move_size2=print_reg(new_name2,fp);
						fprintf(fp,"\tli $t1, %d\n",move_size2);
					}
					else if(codes->code.binop.op2->kind==POINT)
					{
						int move_size=print_reg(get_var_name(codes->code.binop.op2),fp);
						fprintf(fp,"\tlw $t1, -%d($fp)\n",move_size);
						fprintf(fp,"\tadd $t1, $t1, $fp\n");
						fprintf(fp,"\tlw $t1, ($t1)\n");
					}
					else
					{
						int move_size2=print_reg(get_var_name(codes->code.binop.op2),fp);
						fprintf(fp,"\tlw $t1, -%d($fp)\n",move_size2);
					}
					fprintf(fp,"\tsub $t2, $t0, $t1\n");
					if(codes->code.binop.result->kind==POINT)
					{
						int move_size=print_reg(get_var_name(codes->code.binop.result),fp);
						fprintf(fp,"\tlw $t3, -%d($fp)\n",move_size);
						fprintf(fp,"\tadd $t3, $t3, $fp\n");
						fprintf(fp,"\tsw $t2, ($t3)\n");
					}
					else
					{
						int move_size3=print_reg(get_var_name(codes->code.binop.result),fp);//result
						fprintf(fp,"\tsw $t2, -%d($fp)\n",move_size3);	
					}
				}
			}
				break; 
			case MUL:
			{	//attention,already optimize the situation of two constant
				if(codes->code.binop.op1->kind == CONSTANT || codes->code.binop.op2->kind == CONSTANT)
				{
					if(codes->code.binop.op1->kind == CONSTANT)
					{					
						fprintf(fp,"\tli $t0, %d\n",codes->code.binop.op1->value);
						if(codes->code.binop.op2->kind==ADDRESS)
						{
						char*or_name2=get_var_name(codes->code.binop.op2);
						char*new_name2=malloc(2+strlen(or_name2)+1);
						new_name2[0]='#';
						new_name2[1]='0'+0;
						new_name2[2]='\0';
						strcat(new_name2,or_name2);
						int move_size2=print_reg(new_name2,fp);
						fprintf(fp,"\tli $t1, %d\n",move_size2);
						}
						else if(codes->code.binop.op2->kind==POINT)
						{
						int move_size=print_reg(get_var_name(codes->code.binop.op2),fp);
						fprintf(fp,"\tlw $t1, -%d($fp)\n",move_size);
						fprintf(fp,"\tadd $t1, $t1, $fp\n");
						fprintf(fp,"\tlw $t1, ($t1)\n");
						}
						else
						{
						int move_size2=print_reg(get_var_name(codes->code.binop.op2),fp);
						fprintf(fp,"\tlw $t1, -%d($fp)\n",move_size2);
						}
						fprintf(fp,"\tmul $t2, $t0, $t1\n");
						if(codes->code.binop.result->kind==POINT)
						{
							int move_size=print_reg(get_var_name(codes->code.binop.result),fp);
							fprintf(fp,"\tlw $t3, -%d($fp)\n",move_size);
							fprintf(fp,"\tadd $t3, $t3, $fp\n");
							fprintf(fp,"\tsw $t2, ($t3)\n");
						}
						else
						{
							int move_size3=print_reg(get_var_name(codes->code.binop.result),fp);//result
							fprintf(fp,"\tsw $t2, -%d($fp)\n",move_size3);	
						}
					}
					else
					{	
						if(codes->code.binop.op1->kind==ADDRESS)
						{
						char*or_name=get_var_name(codes->code.binop.op1);
						char*new_name=malloc(2+strlen(or_name)+1);
						new_name[0]='#';
						new_name[1]='0'+0;
						new_name[2]='\0';
						strcat(new_name,or_name);
						int move_size=print_reg(new_name,fp);
						fprintf(fp,"\tli $t0, %d\n",move_size);
						}
						else if(codes->code.binop.op1->kind==POINT)
						{
						int move_size=print_reg(get_var_name(codes->code.binop.op1),fp);
						fprintf(fp,"\tlw $t0, -%d($fp)\n",move_size);
						fprintf(fp,"\tadd $t0, $t0, $fp\n");
						fprintf(fp,"\tlw $t0, ($t0)\n");
						}
						else
						{
						int move_size=print_reg(get_var_name(codes->code.binop.op1),fp);
						fprintf(fp,"\tlw $t0, -%d($fp)\n",move_size);	
						}
						fprintf(fp,"\tli $t1, %d\n",codes->code.binop.op2->value);
						fprintf(fp,"\tmul $t2, $t0, $t1\n");
						if(codes->code.binop.result->kind==POINT)
						{
							int move_size=print_reg(get_var_name(codes->code.binop.result),fp);
							fprintf(fp,"\tlw $t3, -%d($fp)\n",move_size);
							fprintf(fp,"\tadd $t3, $t3, $fp\n");
							fprintf(fp,"\tsw $t2, ($t3)\n");
						}
						else
						{
							int move_size3=print_reg(get_var_name(codes->code.binop.result),fp);//result
							fprintf(fp,"\tsw $t2, -%d($fp)\n",move_size3);	
						}
					}
				}
				else
				{
					if(codes->code.binop.op1->kind==ADDRESS)
					{
						char*or_name=get_var_name(codes->code.binop.op1);
						char*new_name=malloc(2+strlen(or_name)+1);
						new_name[0]='#';
						new_name[1]='0'+0;
						new_name[2]='\0';
						strcat(new_name,or_name);
						int move_size=print_reg(new_name,fp);
						fprintf(fp,"\tli $t0, %d\n",move_size);
					}
					else if(codes->code.binop.op1->kind==POINT)
					{
						int move_size=print_reg(get_var_name(codes->code.binop.op1),fp);
						fprintf(fp,"\tlw $t0, -%d($fp)\n",move_size);
						fprintf(fp,"\tadd $t0, $t0, $fp\n");
						fprintf(fp,"\tlw $t0, ($t0)\n");
					}
					else
					{
						int move_size=print_reg(get_var_name(codes->code.binop.op1),fp);
						fprintf(fp,"\tlw $t0, -%d($fp)\n",move_size);
					}
					if(codes->code.binop.op2->kind==ADDRESS)
					{
						char*or_name2=get_var_name(codes->code.binop.op2);
						char*new_name2=malloc(2+strlen(or_name2)+1);
						new_name2[0]='#';
						new_name2[1]='0'+0;
						new_name2[2]='\0';
						strcat(new_name2,or_name2);
						int move_size2=print_reg(new_name2,fp);
						fprintf(fp,"\tli $t1, %d\n",move_size2);
					}
					else if(codes->code.binop.op2->kind==POINT)
					{
						int move_size=print_reg(get_var_name(codes->code.binop.op2),fp);
						fprintf(fp,"\tlw $t1, -%d($fp)\n",move_size);
						fprintf(fp,"\tadd $t1, $t1, $fp\n");
						fprintf(fp,"\tlw $t1, ($t1)\n");
					}
					else
					{
						int move_size2=print_reg(get_var_name(codes->code.binop.op2),fp);
						fprintf(fp,"\tlw $t1, -%d($fp)\n",move_size2);
					}
					fprintf(fp,"\tmul $t2, $t0, $t1\n");
					if(codes->code.binop.result->kind==POINT)
					{
						int move_size=print_reg(get_var_name(codes->code.binop.result),fp);
						fprintf(fp,"\tlw $t3, -%d($fp)\n",move_size);
						fprintf(fp,"\tadd $t3, $t3, $fp\n");
						fprintf(fp,"\tsw $t2, ($t3)\n");
					}
					else
					{
						int move_size3=print_reg(get_var_name(codes->code.binop.result),fp);//result
						fprintf(fp,"\tsw $t2, -%d($fp)\n",move_size3);	
					}
				}
			}
				break; 
			case DIVIDE:
			{	//attention,already optimize the situation of two constants 
				if(codes->code.binop.op1->kind == CONSTANT || codes->code.binop.op2->kind == CONSTANT)
				{
					if(codes->code.binop.op1->kind == CONSTANT)
					{					
						fprintf(fp,"\tli $t0, %d\n",codes->code.binop.op1->value);
						if(codes->code.binop.op2->kind==ADDRESS)
						{
						char*or_name2=get_var_name(codes->code.binop.op2);
						char*new_name2=malloc(2+strlen(or_name2)+1);
						new_name2[0]='#';
						new_name2[1]='0'+0;
						new_name2[2]='\0';
						strcat(new_name2,or_name2);
						int move_size2=print_reg(new_name2,fp);
						fprintf(fp,"\tli $t1, %d\n",move_size2);
						}
						else if(codes->code.binop.op2->kind==POINT)
						{
						int move_size=print_reg(get_var_name(codes->code.binop.op2),fp);
						fprintf(fp,"\tlw $t1, -%d($fp)\n",move_size);
						fprintf(fp,"\tadd $t1, $t1, $fp\n");
						fprintf(fp,"\tlw $t1, ($t1)\n");
						}
						else
						{
						int move_size2=print_reg(get_var_name(codes->code.binop.op2),fp);
						fprintf(fp,"\tlw $t1, -%d($fp)\n",move_size2);
						}
						fprintf(fp,"\tdiv $t0, $t1\n");
						fprintf(fp,"\tmflo $t2\n");
						if(codes->code.binop.result->kind==POINT)
						{
							int move_size=print_reg(get_var_name(codes->code.binop.result),fp);
							fprintf(fp,"\tlw $t3, -%d($fp)\n",move_size);
							fprintf(fp,"\tadd $t3, $t3, $fp\n");
							fprintf(fp,"\tsw $t2, ($t3)\n");
						}
						else
						{
							int move_size3=print_reg(get_var_name(codes->code.binop.result),fp);//result
							fprintf(fp,"\tsw $t2, -%d($fp)\n",move_size3);	
						}
					}
					else
					{	
						if(codes->code.binop.op1->kind==ADDRESS)
						{
						char*or_name=get_var_name(codes->code.binop.op1);
						char*new_name=malloc(2+strlen(or_name)+1);
						new_name[0]='#';
						new_name[1]='0'+0;
						new_name[2]='\0';
						strcat(new_name,or_name);
						int move_size=print_reg(new_name,fp);
						fprintf(fp,"\tli $t0, %d\n",move_size);
						}
						else if(codes->code.binop.op1->kind==POINT)
						{
						int move_size=print_reg(get_var_name(codes->code.binop.op1),fp);
						fprintf(fp,"\tlw $t0, -%d($fp)\n",move_size);
						fprintf(fp,"\tadd $t0, $t0, $fp\n");
						fprintf(fp,"\tlw $t0, ($t0)\n");
						}
						else
						{
						int move_size=print_reg(get_var_name(codes->code.binop.op1),fp);
						fprintf(fp,"\tlw $t0, -%d($fp)\n",move_size);	
						}
						fprintf(fp,"\tli $t1, %d\n",codes->code.binop.op2->value);
						fprintf(fp,"\tdiv $t0, $t1\n");
						fprintf(fp,"\tmflo $t2\n");
						if(codes->code.binop.result->kind==POINT)
						{
							int move_size=print_reg(get_var_name(codes->code.binop.result),fp);
							fprintf(fp,"\tlw $t3, -%d($fp)\n",move_size);
							fprintf(fp,"\tadd $t3, $t3, $fp\n");
							fprintf(fp,"\tsw $t2, ($t3)\n");
						}
						else
						{
							int move_size3=print_reg(get_var_name(codes->code.binop.result),fp);//result
							fprintf(fp,"\tsw $t2, -%d($fp)\n",move_size3);	
						}
					}
				}
				else
				{
					if(codes->code.binop.op1->kind==ADDRESS)
					{
						char*or_name=get_var_name(codes->code.binop.op1);
						char*new_name=malloc(2+strlen(or_name)+1);
						new_name[0]='#';
						new_name[1]='0'+0;
						new_name[2]='\0';
						strcat(new_name,or_name);
						int move_size=print_reg(new_name,fp);
						fprintf(fp,"\tli $t0, %d\n",move_size);
					}
					else if(codes->code.binop.op1->kind==POINT)
					{
						int move_size=print_reg(get_var_name(codes->code.binop.op1),fp);
						fprintf(fp,"\tlw $t0, -%d($fp)\n",move_size);
						fprintf(fp,"\tadd $t0, $t0, $fp\n");
						fprintf(fp,"\tlw $t0, ($t0)\n");
					}
					else
					{
						int move_size=print_reg(get_var_name(codes->code.binop.op1),fp);
						fprintf(fp,"\tlw $t0, -%d($fp)\n",move_size);
					}
					if(codes->code.binop.op2->kind==ADDRESS)
					{
						char*or_name2=get_var_name(codes->code.binop.op2);
						char*new_name2=malloc(2+strlen(or_name2)+1);
						new_name2[0]='#';
						new_name2[1]='0'+0;
						new_name2[2]='\0';
						strcat(new_name2,or_name2);
						int move_size2=print_reg(new_name2,fp);
						fprintf(fp,"\tli $t1, %d\n",move_size2);
					}
					else if(codes->code.binop.op2->kind==POINT)
					{
						int move_size=print_reg(get_var_name(codes->code.binop.op2),fp);
						fprintf(fp,"\tlw $t1, -%d($fp)\n",move_size);
						fprintf(fp,"\tadd $t1, $t1, $fp\n");
						fprintf(fp,"\tlw $t1, ($t1)\n");
					}
					else
					{
						int move_size2=print_reg(get_var_name(codes->code.binop.op2),fp);
						fprintf(fp,"\tlw $t1, -%d($fp)\n",move_size2);
					}
					fprintf(fp,"\tdiv $t0, $t1\n");
					fprintf(fp,"\tmflo $t2\n");
					if(codes->code.binop.result->kind==POINT)
					{
						int move_size=print_reg(get_var_name(codes->code.binop.result),fp);
						fprintf(fp,"\tlw $t3, -%d($fp)\n",move_size);
						fprintf(fp,"\tadd $t3, $t3, $fp\n");
						fprintf(fp,"\tsw $t2, ($t3)\n");
					}
					else
					{
						int move_size3=print_reg(get_var_name(codes->code.binop.result),fp);//result
						fprintf(fp,"\tsw $t2, -%d($fp)\n",move_size3);	
					}
				}
			}
				break;
			case ASSIGN:
			{	if(codes->code.assign.left != NULL)
				{
					Operand left = codes->code.assign.left;
					Operand right = codes->code.assign.right;
					if(right->kind == CONSTANT)
					{
						fprintf(fp,"\tli $t0, %d\n",right->value);
					}
					else if(right->kind==ADDRESS)
					{
						char*or_name=get_var_name(right);
						char*new_name=malloc(2+strlen(or_name)+1);
						new_name[0]='#';
						new_name[1]='0'+0;
						new_name[2]='\0';
						strcat(new_name,or_name);
						int move_size=print_reg(new_name,fp);
						fprintf(fp,"\tli $t0, %d\n",move_size);
					}
					else if(right->kind==POINT)
					{
						int move_size=print_reg(get_var_name(right),fp);
						fprintf(fp,"\tlw $t0, -%d($fp)\n",move_size);
						fprintf(fp,"\tadd $t0, $t0, $fp\n");
						fprintf(fp,"\tlw $t0, ($t0)\n");
					}
					else
					{
						int move_size=print_reg(get_var_name(right),fp);
						if(move_size==-1)//return
							fprintf(fp,"\tmove $t0, $v0\n");
						else
							fprintf(fp,"\tlw $t0, -%d($fp)\n",move_size);
					}
					/*if(left->kind==ADDRESS)
					{
						char*or_name2=get_var_name(left);
						char*new_name2=malloc(2+strlen(or_name2)+1);
						new_name2[0]='#';
						new_name2[1]='0'+0;
						new_name2[2]='\0';
						strcat(new_name2,or_name2);
						int move_size2=print_reg(new_name2,fp);
						fprintf(fp,"\tli $t1, %d\n",move_size2);
					}
					*/
					if(left->kind==POINT)
					{
						int move_size=print_reg(get_var_name(left),fp);
						fprintf(fp,"\tlw $t1, -%d($fp)\n",move_size);
						fprintf(fp,"\tadd $t1, $t1, $fp\n");
						fprintf(fp,"\tsw $t0, ($t1)\n");
					}
					else
					{
						int move_size2=print_reg(get_var_name(left),fp);
						fprintf(fp,"\tsw $t0, -%d($fp)\n",move_size2);
					}
				}
			}
				break;
			case LABEL:
			{	
				fprintf(fp,"label%d :\n", codes->code.id);
			}
				break;
			case GOTO:
			{	
				fprintf(fp,"\tj label%d\n", codes->code.id);
			}
				break;
			case IFGOTO:
			{	temp_reg = 0;
				if(codes->code.ifgoto.op1->kind == CONSTANT)
				{
					fprintf(fp,"\tli $t0, %d\n",codes->code.ifgoto.op1->value);
				}
				else if(codes->code.ifgoto.op1->kind == POINT)
				{
					int move_size=print_reg(get_var_name(codes->code.ifgoto.op1),fp);
					fprintf(fp,"\tlw $t5, -%d($fp)\n",move_size);
					fprintf(fp,"\tadd $t5, $t5, $fp\n");
					fprintf(fp,"\tlw $t0, ($t5)\n");
				}
				else
				{	
					int move_size=print_reg(get_var_name(codes->code.ifgoto.op1),fp);
					fprintf(fp,"\tlw $t0, -%d($fp)\n",move_size);

				}
				if(codes->code.ifgoto.op2->kind == CONSTANT)
				{
					fprintf(fp,"\tli $t1, %d\n",codes->code.ifgoto.op2->value);
				}
				else if(codes->code.ifgoto.op2->kind == POINT)
				{
					int move_size=print_reg(get_var_name(codes->code.ifgoto.op2),fp);
					fprintf(fp,"\tlw $t4, -%d($fp)\n",move_size);
					fprintf(fp,"\tadd $t4, $t4, $fp\n");
					fprintf(fp,"\tlw $t1, ($t4)\n");
				}
				else
				{
					int move_size2=print_reg(get_var_name(codes->code.ifgoto.op2),fp);
					fprintf(fp,"\tlw $t1, -%d($fp)\n",move_size2);
				}
				if(strcmp(codes->code.ifgoto.relop, "==") == 0)
					fprintf(fp,	"\tbeq ");
				else if(strcmp(codes->code.ifgoto.relop, "!=") == 0)
					fprintf(fp,"\tbne ");
				else if(strcmp(codes->code.ifgoto.relop, ">") == 0)
					fprintf(fp,"\tbgt ");
				else if(strcmp(codes->code.ifgoto.relop, "<") == 0)
					fprintf(fp,"\tblt ");
				else if(strcmp(codes->code.ifgoto.relop, ">=") == 0)
					fprintf(fp,"\tbge ");
				else if(strcmp(codes->code.ifgoto.relop, "<=") == 0)
					fprintf(fp,"\tble ");
				fprintf(fp,"$t0, $t1, label%d\n",codes->code.ifgoto.label->code.id);
			}
				break;
			case READ:
			{	fprintf(fp,"\taddi $sp, $sp, -4\n");
				fprintf(fp,"\tsw $ra, 0($sp)\n");
				fprintf(fp,"\taddi $sp, $sp, -4\n");
				fprintf(fp,"\tsw $fp, 0($sp)\n");
				fprintf(fp,"\tjal read\n");
				fprintf(fp,"\tlw $fp, 0($sp)\n");
				fprintf(fp,"\taddi $sp, $sp, 4\n");
				fprintf(fp,"\tlw $ra, 0($sp)\n");
				fprintf(fp,"\taddi $sp, $sp, 4\n");
				if(codes->code.assign.right->kind==POINT)
				{
					int move_size=print_reg(get_var_name(codes->code.assign.right),fp);
					fprintf(fp,"\tlw $t1, -%d($fp)\n",move_size);
					fprintf(fp,"\tadd $t1, $t1, $fp\n");
					fprintf(fp,"\tsw $v0, ($t1)\n");
				}
				else
				{
					int move_size=print_reg(get_var_name(codes->code.assign.right),fp);
					fprintf(fp,"\tsw $v0, -%d($fp)\n",move_size);
				}
				return_used = 1;
				return_var = strdup(get_var_name(codes->code.assign.right));
			}
				break;
			case WRITE:
			{	if(codes->code.assign.right->kind==CONSTANT)
					fprintf(fp,"\tli $a0, %d\n", codes->code.assign.right->value);
				else if(codes->code.assign.right->kind==POINT)
				{
					int move_size=print_reg(get_var_name(codes->code.assign.right),fp);
					fprintf(fp,"\tlw $t1, -%d($fp)\n",move_size);
					fprintf(fp,"\tadd $t1, $t1, $fp\n");
					fprintf(fp,"\tlw $a0, ($t1)\n");
				}
				else
				{
					int move_size=print_reg(get_var_name(codes->code.assign.right),fp);
					fprintf(fp,"\tlw $a0, -%d($fp)\n",move_size);
				}
				fprintf(fp,"\taddi $sp, $sp, -4\n");
				fprintf(fp,"\tsw $ra, 0($sp)\n");

				fprintf(fp,"\taddi $sp, $sp, -4\n");
				fprintf(fp,"\tsw $fp, 0($sp)\n");

				fprintf(fp,"\tjal write\n");

				fprintf(fp,"\tlw $fp, 0($sp)\n");
				fprintf(fp,"\taddi $sp, $sp, 4\n");

				fprintf(fp,"\tlw $ra, 0($sp)\n");
				fprintf(fp,"\taddi $sp, $sp, 4\n");
			}
				break;
			case CALL:
			{	fprintf(fp,"\tjal %s\n", codes->code.call.funName);
				return_used = 1;
				return_var = strdup(get_var_name(codes->code.call.result));
				if(codes->code.call.result->kind==POINT)
				{
					int move_size=print_reg(get_var_name(codes->code.call.result),fp);
					fprintf(fp,"\tlw $t4, -%d($fp)\n",move_size);
					fprintf(fp,"\tadd $t4, $t4, $fp\n");
					fprintf(fp,"\tlw $v0, ($t4)\n");
				}
				fprintf(fp,"\tlw $ra, 0($sp)\n");
				fprintf(fp,"\taddi $sp, $sp, 4\n");
			}
				break;
			case RET:
			{	if(codes->code.assign.right->kind == CONSTANT)
				{
					fprintf(fp,"\tmove $sp, $fp\n");
					fprintf(fp,"\tli $v0, %d\n\tjr $ra\n", codes->code.assign.right->value);
				}
				else if(codes->code.assign.right->kind == POINT)
				{
					fprintf(fp,"\tmove $sp, $fp\n");
					int move_size=print_reg(get_var_name(codes->code.assign.right),fp);
					fprintf(fp,"\tlw $t0, -%d($fp)\n",move_size);
					fprintf(fp,"\tadd $t0, $t0, $fp\n");
					fprintf(fp,"\tlw $v0, ($t0)\n");
					fprintf(fp,"\tjr $ra\n");
				}
				else
				{
					fprintf(fp,"\tmove $sp, $fp\n");
					int move_size=print_reg(get_var_name(codes->code.assign.right),fp);
					fprintf(fp,"\tlw $v0, -%d($fp)\n",move_size);
					fprintf(fp,"\tjr $ra\n");	
				}
			}
				break;
			case FUNDEC:
			{	fprintf(fp, "\n");
				fprintf(fp,"%s:\n", codes->code.fun_name);
				fprintf(fp,"\tsw $ra, -4($sp)\n");//save address of return
				fprintf(fp,"\tsw $sp, -8($sp)\n");//$fp
				fprintf(fp,"\taddi $sp, $sp, -8\n");//$fp
				fprintf(fp,"\tlw $fp, 0($sp)\n");//save to $fp
				top_offset=8;
				arg_num = 0;
				q=0;
				for(;q<20;q++)
					reg_arg[q]=NULL;//argument clear
				used_reg_num=0;
				q=0;
				for(;q<temp_size;q++)
					reg_var[q]=NULL;//register clear
			}
				break;
			case PARAM:
			{	reg_arg[arg_num] = strdup(get_var_name(codes->code.assign.right));
				if(arg_num<4)
				{
					fprintf(fp,"\taddi $sp, $sp, -4\n");
					fprintf(fp,"\tsw $a%d, 0($sp)\n",arg_num);
				}
				else
				{
					fprintf(fp,"\taddi $sp, $sp, -4\n");
					fprintf(fp,"\tlw $t0, %d($fp)\n",(arg_num-4)*4);
					fprintf(fp,"\tsw $t0, 0($sp)\n");
				}
				top_offset=top_offset+4;
				arg_num ++;
			}
				break;
			case ARG:
			{	if(codes->next->code.kind == WRITE)//special dealing
					break;
				fprintf(fp,"\taddi $sp, $fp, -1000\n");
				q=0;
				for(;q<10;q++)
					fprintf(fp,"\tsw $t%d, %d($sp)\n",q,q*4);//save all register
				int w=0;
				for(;w<8;w++)
				{
					fprintf(fp,"\tsw $s%d, %d($sp)\n",w,q*4);//save all register
					q++;
				}
				firstArg = codes;
				i = 1;
				while(firstArg->next->code.kind == ARG)//cal the number of arg
				{
					firstArg = firstArg->next;
					i ++;
				}
				if(i>4)
					fprintf(fp,"\taddi $sp, $sp, -%d\n",(i-4)*4);
				for(j = 0; j < i; j ++)
				{
					if(j>3)
					{
						if(firstArg->code.assign.right->kind==CONSTANT)
						{
							fprintf(fp,"\tli $t0, %d\n",firstArg->code.assign.right->value);

						}
						else if(firstArg->code.assign.right->kind==POINT)
						{
							int move_size=print_reg(get_var_name(firstArg->code.assign.right),fp);
							fprintf(fp,"\tlw $t1, -%d($fp)\n",move_size);
							fprintf(fp,"\tadd $t1, $t1, $fp\n");
							fprintf(fp,"\tlw $t0, ($t1)\n");
						}
						else
						{
							int move_size=print_reg(get_var_name(firstArg->code.assign.right),fp);
							fprintf(fp,"\tlw $t0, -%d($fp)\n",move_size);
						}
						fprintf(fp,"\tsw $t0, %d($sp)\n",(j-4)*4);//save extra arg
					}
					else if(firstArg->code.assign.right->kind==CONSTANT)
					{
						fprintf(fp,"\tli $a%d, %d\n",j,firstArg->code.assign.right->value);
					}
					else if(firstArg->code.assign.right->kind==POINT)
					{
						int move_size=print_reg(get_var_name(firstArg->code.assign.right),fp);
						fprintf(fp,"\tlw $t1, -%d($fp)\n",move_size);
						fprintf(fp,"\tadd $t1, $t1, $fp\n");
						fprintf(fp,"\tlw $a%d, ($t1)\n",j);
					}
					else
					{
						int move_size=print_reg(get_var_name(firstArg->code.assign.right),fp);
						fprintf(fp,"\tlw $a%d, -%d($fp)\n",j,move_size);
					}
					firstArg = firstArg->prev;
				}
				while(codes->code.kind == ARG)
				{
					codes->prev->next = NULL;
					codes = codes->next;						
				}
				fprintf(fp,"\tjal %s\n", codes->code.call.funName);
				//return_used = 1;
				//return_var = strdup(get_var_name(codes->code.call.result));

				//revise t0~t9,s0~s7,a0~a3,ra,fp,sp
				//first ,revise t0~t9,s0~s7
				if(i>4)
					fprintf(fp,"\taddi $sp, $sp, %d\n",(i-4)*4);
				q=0;
				for(;q<10;q++)
					fprintf(fp,"\tlw $t%d, %d($sp)\n",q,q*4);//save all register
				w=0;
				for(;w<8;w++)
				{
					fprintf(fp,"\tlw $s%d, %d($sp)\n",w,q*4);//save all register
					q++;
				}
				//revise $fp
				fprintf(fp,"\taddi $sp, $sp, 1000\n");
				fprintf(fp,"\tlw $fp, -8($sp)\n");
				//revise $sp
				fprintf(fp,"\taddi $sp, $fp, -%d\n",top_offset);
				//revise $ra
				fprintf(fp,"\tlw $ra, -4($fp)\n");
				//revise a0~a3
				if(arg_num > 0)
				{
					int loop_number=0;
					for(;loop_number<arg_num;loop_number++)
					{
						fprintf(fp,"\tlw $a%d, -%d($fp)\n",loop_number,12+loop_number*4);

					}
				}
				if(codes->code.call.result->kind==POINT)
				{
					int move_size=print_reg(get_var_name(codes->code.call.result),fp);
					fprintf(fp,"\tlw $t4, -%d($fp)\n",move_size);
					fprintf(fp,"\tadd $t4, $t4, $fp\n");
					fprintf(fp,"\tsw $v0, ($t4)\n");
				}
				else
				{
					int move_size4=print_reg(get_var_name(codes->code.call.result),fp);
					fprintf(fp,"\tmove $t0, $v0\n");
					fprintf(fp,"\tsw $t0, -%d($fp)\n",move_size4);
				}
			}
				break;
			//---------------------need to revise
			case DEC:
			{	char*shuzu_name=get_var_name(codes->code.assign.left);
				int shuzu_size=(codes->code.assign.right->value)/4;
				int ww=0;
				for(;ww<shuzu_size;ww++)
				{
					char*new_name=malloc(2+strlen(shuzu_name)+1);
					new_name[0]='#';
					new_name[1]='0'+ww;
					new_name[2]='\0';
					strcat(new_name,shuzu_name);
					print_reg(new_name,fp);
				}
			}
				break;
			default://NOTHING
				break;
		}
		codes->prev->next = NULL;
		codes = codes->next;
	}
}
