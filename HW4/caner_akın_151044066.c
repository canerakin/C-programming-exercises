#include <stdio.h>
#include <math.h>

#define VALUE_SIZE 100   /*for max number*/
#define POLINOM_SIZE 1000    /*for max character*/

double find_number(char *p);	/*this function read a array and return the number*/
void find_write(double value, char polinom[], FILE *file);		/*this function find all f(x) and write the file*/

int main()
{
	FILE *file1;
	FILE *file2;
	FILE *file3;	
	file1 = fopen("values.txt","r"); 	/*for only read open*/
	file2 = fopen("polynomial.txt","r");	/*for only read open*/
	file3 = fopen("evaluations.txt","w");	/*for only write open*/

	double values_file[VALUE_SIZE];
	char polinom_file[POLINOM_SIZE] , chrktr;
	int i = 0;

	while(!feof(file1)){	/*there contunie to end of file1*/
		fscanf(file1,"%lf ",&values_file[i]); 	/*save in array*/
		i += 1;
	}
	values_file[i] = '\0';
	fclose(file1);		/*close the files*/
	i = 0;

	while(fscanf(file2,"%c",&chrktr) != EOF){ /*there contunie to end of file2*/
		if (chrktr != ' ' && chrktr != '\n') /*dont save the space in array*/
		{
			polinom_file[i] = chrktr;
			i += 1;
		}		
	}
	polinom_file[i] = '\0';
	fclose(file2);		/*close the files*/
	i = 0;
	while(values_file[i] != '\0') 	/*there contunie to end of array*/
	{
		find_write(values_file[i],polinom_file,file3);    /*call function for find number*/
		i += 1;		
	}

	fclose(file3); 	 /*close the files*/
	return 0;
}

double find_number(char *p)		/*this function read a array and return the number*/
{
	double number;
	sscanf(p,"%lf",&number);
	return number;
}

void find_write(double value, char polinom[], FILE *file)		/*this function find all f(x) and write the file*/
{
	int i = 0;
	double result = 0 , base , multiple ; 	/* result = write file , base = for find_pow , multiple = for coefficient*/
	double rt_pow;
	while(polinom[i] != '\0')	 /*continue whit */
	{
		base = 0;
		rt_pow = 0;
		multiple = 0;
		multiple = find_number(&polinom[i]);   /*call function for find coefficient */
		if (polinom[i] == 'x') 	/*if file start with x*/
		{			
			if (polinom[i+1] == '^')	/*find base*/
			{
				i += 2;
				base = find_number(&polinom[i]);	/*call function for find base*/
				while(polinom[i] != '+' && polinom[i] != '-' && polinom[i] != '\0')		/*contunie  up to don't seeing a number*/
				{
					i += 1;
				}
			}
			else	/*for don't have a base*/
			{
				base = 1;
				i += 1;
			}			
			rt_pow = pow(value,base);
			result += rt_pow;	 
		}
		else if (polinom[i] == '+' && polinom[i+1] == 'x') 	/*if operation start with + and contunie with x*/
		{
			i += 1;
			if (polinom[i+1] == '^')	/*find base*/
			{
				i += 2;
				base = find_number(&polinom[i]);	/*call function for find base*/
				while(polinom[i] != '+' && polinom[i] != '-' && polinom[i] != '\0')		/*contunie  up to don't seeing a number*/
				{
					i += 1;
				}
			}
			else	/*for don't have a base*/
			{
				base = 1;
				i += 1;
			}			
			rt_pow = pow(value,base);
			result += rt_pow;
		}
		else if (polinom[i] == '-' && polinom[i+1] == 'x')		/*if operation start with - and contunie with x*/
		{
			i += 1;
			if (polinom[i+1] == '^')/*find base*/
			{
				i += 2;
				base = find_number(&polinom[i]);
				while(polinom[i] != '+' && polinom[i] != '-' && polinom[i] != '\0')	/*contunie  up to don't seeing a number*/
				{
					i += 1;
				}
			}
			else	/*for don't have a base*/
			{
				base = 1;
				i += 1;
			}			
			rt_pow = pow(value,base);
			result -= rt_pow;
		}
		else  	/*if operation start with  + or - number and if only number in there*/
		{
			if (polinom[i] == '+' || polinom[i] == '-') 	/*if number have a operation*/
			{
				i += 1;
			}
			while(polinom[i] != 'x' && polinom[i] != '+' && polinom[i] != '-' && polinom[i] != '\0') /*contunie  up to don't seeing a number*/
			{
				i += 1;
			} 
			if (polinom[i] == 'x')  /*if number not only*/
			{
				if (polinom[i+1] == '^')/*find base*/
				{
					i += 2;
					base = find_number(&polinom[i]);
					while(polinom[i] != '+' && polinom[i] != '-' && polinom[i] != '\0')	/*contunie  up to don't seeing a number*/
					{
						i += 1;
					}
				}
				else    /*for don't have a base*/
				{
					base = 1;
					i += 1;
				}
			}
			else	/*if only number */
			{
				base = 0;
			}
			rt_pow = pow(value,base);
			rt_pow = rt_pow * multiple;
			result += rt_pow;
		}
	}/*end of while*/
	fprintf(file,"%.2lf %c",result,'\n');	
}/*end of function*/