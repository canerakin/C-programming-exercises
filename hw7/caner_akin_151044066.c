#include <stdio.h>
#include <string.h>
#include <stdlib.h>
	/*EACH FILE MOST OPENED UP TO TWO TİMES*/
#define INP 10 	/*define the max input char*/

typedef struct   /*define the struct for INPUT*/ 
{
	char word[INP];		/*there save the input name*/	
	int value;	      /*there save the input answer*/
}Number;

typedef struct    /*define the struct for AND,OR and others*/
{
	char type;      /*there save the type*/
	char name[INP];		/*there save the new answers name*/
	int answer;			/*there save the new answers*/
	int place_root1;	/*there save where in the struct*/
	int reply_root1;	/*there find answer root*/
	int place_root2;	/*there save where in the struct*/	
	int reply_root2;	/*there find answer root*/    
}Gate;

void SIZE_INP(int *size);   	/*this function find the input long*/
void SIZE(int *size_down ,int *size_right);		/*this function find the input long*/	
int AND_GATE(int number1 ,int number2);			/*for operation*/
int OR_GATE(int number1 ,int number2);			/*for operation*/
int NOT_GATE(int number1);						/*for operation*/	
int FLIPFLOP_GATE(int number1 ,int number2);	/*for operation*/
int find_value(Number * number ,Gate * gate ,int size_right ,int j ,char array[INP] ,int * place);		/*for find the root*/	
void find_end(Number * number ,Gate * gate ,int size_down ,int size_right , int *flip_last);	/*for do operation with tree*/

int main()
{	
	Gate * gate;
	Number * number;
	FILE *file_cir;
	FILE *file_inp;
	FILE *file_out;
	file_cir = fopen("circuit.txt","r");	
	file_inp = fopen("input.txt","r");	
	file_out = fopen("output.txt","w");
	char inp[INP] ,crktr;
	int i ,j , temp , flip_last = 0 ,place ;
	int size_down = 0, size_right = 0 , size = 0;

	SIZE_INP(&size);	/*there find the size*/
	SIZE(&size_down ,&size_right);	/*there find the size*/
	
	number = malloc(size_right * sizeof(Number));		/*take a memory with malloc*/	
	gate = malloc((size_down) * sizeof(Gate));			

	i = 0;
	j = -1;
	while(fscanf(file_cir,"%s",inp) != EOF)
	{	
		if(inp[0] == 'I')		/*there operation is saved structure*/
		{
			for (i = 0; i < size_right; ++i)
				{
					fscanf(file_cir,"%s",inp);
					strcpy(number[i].word ,inp) ;
				}			
		}
		else if(strcmp("OR",inp) == 0)		/*there operation is saved structure*/
		{
			gate[j].type = 'O';
			fscanf(file_cir,"%s",inp);
			strcpy(gate[j].name ,inp);
			fscanf(file_cir,"%s",inp);	
			gate[j].reply_root1 = find_value(number ,gate ,size_right ,j ,inp ,&place);	/*there find for root1*/
			gate[j].place_root1 = place;			
			fscanf(file_cir,"%s",inp);
			gate[j].reply_root2 = find_value(number ,gate ,size_right ,j ,inp ,&place);	/*there find for root2*/
			gate[j].place_root2 = place;			
		}
		else if(strcmp("AND",inp) == 0)		/*there operation is saved structure*/
		{
			gate[j].type = 'A';	
			fscanf(file_cir,"%s",inp);	
			strcpy(gate[j].name ,inp);
			fscanf(file_cir,"%s",inp);
			gate[j].reply_root1 = find_value(number ,gate ,size_right ,j ,inp ,&place);	/*there find for root1*/
			gate[j].place_root1 = place;			
			fscanf(file_cir,"%s",inp);
			gate[j].reply_root2 = find_value(number ,gate ,size_right ,j ,inp ,&place);	/*there find for root2*/
			gate[j].place_root2 = place;				
		}
		else if(strcmp("NOT",inp) == 0)		/*there operation is saved structure*/
		{
			gate[j].type = 'N';	
			fscanf(file_cir,"%s",inp);
			strcpy(gate[j].name ,inp);
			fscanf(file_cir,"%s",inp);		
			gate[j].reply_root1 = find_value(number ,gate ,size_right ,j ,inp ,&place);	/*there find for root1*/
			gate[j].place_root1 = place;
		}
		else if(strcmp("FLIPFLOP",inp) == 0)		/*there operation is saved structure*/
		{
			gate[j].type = 'F';
			fscanf(file_cir,"%s",inp);			
			strcpy(gate[j].name ,inp);
			fscanf(file_cir,"%s",inp);
			gate[j].reply_root1 = find_value(number ,gate ,size_right ,j ,inp ,&place);	/*there find for root1*/
			gate[j].place_root1 = place;			
		}
		j += 1;
	}

	for (i = 0; i < size; ++i)
	{
		for (j = 0; j < size_right; ++j) 	/*there save a new input*/
		{
			fscanf(file_inp,"%d%c",&temp,&crktr);	/*there take the number*/
			number[j].value = temp;		/*saved in structure*/
		}
		if (i > 0)
		{
			fprintf(file_out,"%c",'\n' ); 	/*for output */
		}
		find_end(number ,gate ,size_down ,size_right,&flip_last);	/*find answer*/
		fprintf(file_out,"%d",gate[size_down-1].answer ); 	/*save in output*/
	}
	free(gate);		/*there free structure*/
	free(number); 

	fclose(file_cir);	/*there close the file*/
	fclose(file_inp);
	fclose(file_out);
	return 0;	
}
void SIZE_INP(int *size)		/*this function find the input long*/
{
	FILE *file;
	file = fopen("input.txt","r");
	char crktr;

	while(fscanf(file,"%c",&crktr) != EOF)
	{	
		if (crktr == '\n')
		{
			*size += 1;		
		}
	}	
	fclose(file);
}
void SIZE(int *size_down ,int *size_right)		/*this function find the input long*/	
{
	FILE *file;
	file = fopen("circuit.txt","r");
	char inp[INP] , crktr;
	while(fscanf(file,"%s",inp) != EOF)
	{	
		if(inp[0] == 'I')
		{		
			while( (crktr =(fgetc(file))) != '\n'){	
				if(crktr == ' '){
					*size_right += 1;;      /*there find size for INPUT and save*/
				}
			}
		}
		else if(strcmp("OR",inp) == 0)
		{
			*size_down += 1;		/*there find operation long and save*/
		}
		else if(strcmp("AND",inp) == 0)
		{
			*size_down += 1;		/*there find operation long and save*/
		}
		else if(strcmp("NOT",inp) == 0)
		{
			*size_down += 1;		/*there find operation long and save*/
		}
		else if(strcmp("FLIPFLOP",inp) == 0)
		{
			*size_down += 1;		/*there find operation long and save*/
		}
	}
	fclose(file);
}
int AND_GATE(int number1 ,int number2)		/*for operation*/
{
	if (number1 == 1 && number2 == 1)
	{
		return 1;
	}
	return 0;
}
int OR_GATE(int number1 ,int number2)		/*for operation*/
{
	if (number1 == 0 && number2 == 0)
	{
		return 0;
	}
	return 1;
}
int NOT_GATE(int number1)		/*for operation*/
{
	if (number1 == 1)
	{
		return 0;
	}
	return 1;
}
int FLIPFLOP_GATE(int number1 ,int number2)		/*for operation*/
{
	if (number1 == number2)
	{
		return 0;
	}
	return 1;
}
int find_value(Number * number ,Gate * gate ,int size_right ,int j ,char array[INP] , int * place)		/*for find the root*/
{
	int  i;
		for (i = 0; i < size_right; ++i)
		{
			*place = 1;
			if(strcmp(array ,number[i].word) == 0) 	/*if equal*/
			{
				return i;
			}
		}
		for (i = 0; i < j; ++i)
		{
			*place = 2;
			if(strcmp(array ,gate[i].name) == 0)		/*if equal*/
			{
				return i;
			}			
		}	
}
void find_end(Number * number ,Gate * gate ,int size_down ,int size_right , int * flip_last)		/*for do operation with tree*/	
{
	int j = 0 , count;
	int number1 ,number2;
	for (j = 0; j < size_down; ++j)		/*there continue up to end of structure*/	
	{
		if (gate[j].type == 'A')       /*if AND operation*/
		{
			if (gate[j].place_root1 == 1)     /*choise type the struct*/
			{
				count = gate[j].reply_root1;
				number1 = number[count].value;
			}
			else
			{
				count = gate[j].reply_root1;
				number1 = gate[count].answer;
			}	
			if (gate[j].place_root2 == 1)		/*choise type the struct*/
			{
				count = gate[j].reply_root2;
				number2 = number[count].value;
			}
			else
			{
				count = gate[j].reply_root2;
				number2 = gate[count].answer;
			}
			gate[j].answer = AND_GATE(number1 ,number2);	/*save the answer*/				
		}
		else if (gate[j].type == 'O')	/*if OR operation*/
		{
			if (gate[j].place_root1 == 1)		/*choise type the struct*/
			{
				count = gate[j].reply_root1;
				number1 = number[count].value;
			}
			else
			{
				count = gate[j].reply_root1;
				number1 = gate[count].answer;
			}	
			if (gate[j].place_root2 == 1)		/*choise type the struct*/
			{
				count = gate[j].reply_root2;
				number2 = number[count].value;
			}
			else
			{
				count = gate[j].reply_root2;
				number2 = gate[count].answer;
			}
			gate[j].answer = OR_GATE(number1 ,number2);		/*save the answer*/			
		}
		else if (gate[j].type == 'N')	/*if NOT operation*/
		{
			if (gate[j].place_root1 == 1)		/*choise type the struct*/
			{
				count = gate[j].reply_root1;
				number1 = number[count].value;
			}
			else
			{
				count = gate[j].reply_root1;
				number1 = gate[count].answer;
			}
			gate[j].answer = NOT_GATE(number1);		/*save the answer*/	
		}
		else if (gate[j].type == 'F')	/*if FLIPFLOP operation*/
		{
			if (gate[j].place_root1 == 1)		/*choise type the struct*/
			{
				count = gate[j].reply_root1;
				number1 = number[count].value;
			}
			else
			{
				count = gate[j].reply_root1;
				number1 = gate[count].answer;
			}
			gate[j].answer = FLIPFLOP_GATE(number1 ,*flip_last);	/*save the answer*/		
			*flip_last = gate[j].answer;        /*for next operation*/
		}						
	}
}
