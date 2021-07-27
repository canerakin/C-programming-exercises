#include <stdio.h>

#define LINE_INP 101      /*define for long input*/
#define MAX_NAME 50			/*define for short name*/

void fix(char array[]);			/*this function delete \n in end of array*/ 
double find_number(char *p);		/*this function read a array and return the number*/
double input_value(char array[]);		/*this function be recursive and find every value*/

int main()
{
	char array[MAX_NAME];   /*for first input*/
	double answer;

	printf("Name the object:\n");
	fgets(array,MAX_NAME,stdin);	/*take name*/
	fix(array);			/*call function for delete \n in end of array*/
	printf("Define %s?:\n",array);		
	
	answer = input_value(array);      /*call function*/
	printf("Total cost of %s is %.1lf\n",array ,answer );
	return 0;
}

void fix(char array[])		/*this function delete \n in end of array*/
{
	int i = 0;
	while(array[i] != '\n' && array[i] != '\0')		/*if end of array be \n , function be fix*/
	{
		i += 1;
	}
	array[i] = '\0';
}

double find_number(char *p)		/*this function read a array and return the number*/
{
	double number;
	sscanf(p,"%lf",&number);		/*take the double number*/
	return number;
}

double input_value(char array[])		/*this function be recursive and find every value*/
{
	int i = 0 , j;
	double count = 0 , number = 0 , coefficient;
	char input_array[LINE_INP];      /*for a input array*/
	char name[MAX_NAME];		/*for a piece name*/


	fgets(input_array,LINE_INP,stdin);		/*take input*/
	fix(input_array);		/*call function for delete \n in end of array*/

	while(input_array[i] == ' ')      /*if input start with space , indicator jump*/
	{
		i += 1;
	}

	while(input_array[i] != '\0')		/*there contunie up to end of array*/
	{
		j = 0;
		coefficient = find_number(&input_array[i]);		/*this function read a array and return the number*/ 
		while(input_array[i] != ' ')     /*up to space*/
		{
			if (input_array[i] == '\0')     /*control for finish*/
			{
				return coefficient;
			}
			i += 1;			
		}
		while(input_array[i] == ' ')	/*up to character*/
		{
			i += 1;
		}
		if (input_array[i] == '\0')		/*control for finish*/
		{
			return coefficient;
		}
		while(input_array[i] != ' ' && input_array[i] != '\0')	 /*copy name in array up to space or end*/
		{
			name[j] = input_array[i];
			j += 1;
			i += 1;
		}
		name[j] = '\0';	
		while(input_array[i] == ' ')		/*up to number*/
		{
			i += 1;
		}
		printf("Define %s in %s?:\n",name ,array);    /*print the user ask*/
		number = input_value(name);    /*call again function with recursive*/
		number = number * coefficient;    
		count = count + number;		/*calculate value*/
	}

	return count;    /*return value*/
}
