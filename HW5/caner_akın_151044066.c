#include <stdio.h>
#define MAX 250

void recursive_read_file(char array[MAX] ,int i ,int flag ,int count ,FILE *file_read);		/*this function read the file with recursive*/
void recursive_print_hyphen(int flag ,FILE *file_write); 		/*this function print hyphen with recursive*/
int recursive_control_space(char array[MAX] ,int i,int *j);		/*this function control with recursive*/
void recursive_print_character(char array[MAX] ,int i ,int count ,int flag ,FILE *file_write);	/*this function print file with recursive*/
int main()
{
	FILE * file1;	/*define for input.txt*/
	FILE * file2;	/*define for output.txt*/
	file1 = fopen("input.txt","r");	/*file1 to be called*/
	file2 = fopen("output.txt","w");	/*file2 to be called*/

	char array[MAX];		/*define the char array*/
	int i = 0 ,count = 0 ,flag = 0;

	recursive_read_file(array,i ,flag ,count ,file1);   /*call function for the read file1*/
	recursive_print_character(array ,i ,count ,flag ,file2);	/*call function for the write file2*/

	fclose(file2);	/*file2 closed*/
	fclose(file1);	/*file1 closed*/
	return 0;
}
void recursive_read_file(char array[MAX] ,int i ,int flag ,int count ,FILE *file_read )		/*this function read the file with recursive*/
{
	char character;
	count += 1;
	if (count <= MAX)   /*if file finish recursive read is finish*/
	{
		fscanf(file_read,"%c",&character);
		if (flag == 0 && character == ' ')    /*for space in start*/
		{
			recursive_read_file(array ,i ,flag ,count ,file_read);
		}
		else if (character == ' ' && array[i-1] == ')')    /*for space in finish*/
		{
			array[i] ='\0';
		}
		else
		{
			flag = 1;
			array[i] = character;    /*save the character*/
			i += 1;
			recursive_read_file(array ,i ,flag ,count ,file_read);      /*for read next character*/
		}
	}
}
void recursive_print_hyphen(int flag ,FILE *file_write) 		/*this function print hyphen with recursive*/
{
	if (flag > 0)		/*if recursive read all hyphen after finish*/
	{
		fprintf(file_write,"%c",'-');      /*print hyphen*/
		flag -= 1;
		recursive_print_hyphen(flag ,file_write);		/*recursive beeing contunie*/
	}
}
int recursive_control_space(char array[MAX] ,int i,int *j)	/*this function control with recursive*/
{
	if (array[i] == ' ')
	{
		return recursive_control_space(array ,i+1 ,j);     /*call again*/
	}
	else if (array[i] == '(')
	{
		*j = i;
		return 1;
	}
	else    /*if a normal node*/
	{
		return 0;
	}
}
void recursive_print_character(char array[MAX] ,int i ,int count ,int flag ,FILE *file_write)	/*this function print file with recursive*/
{
	int control , j;
	if (array[i] != '\0')     /*if recursive write finish*/
	{
		if (array[i] == '(')     /*if character == '('    ++count for print hyphen*/
		{
			count += 1;
		}
		else if (array[i] == ')')		/*if character == '('    --count for print hyphen*/
		{
			count -= 1;
		}
		else if (array[i] != ',')		/*if array[i] == character  print */
		{
			if (array[i-1] == '(' || array[i-1] == ',')
			{
				if (flag == 1 )
				{
				fprintf(file_write,"%c",'\n');		/*write file for a new line*/
				}
				recursive_print_hyphen(count ,file_write);		/*call function for write hyphen*/
			}
			fprintf(file_write,"%c",array[i]);		/*print character in file*/
			flag = 1;		/*control for \n*/
		}
		else if (array[i] == ',')
		{
			if (array[i+1] != '(')
			{
				control = recursive_control_space(array ,i+1 ,&j);    /*for control space*/
				if (control == 1)
				{
					i = j - 1; 
				}
			}		
		}
		i += 1;		/*next character*/
		recursive_print_character(array ,i ,count ,flag ,file_write);		/*pass the next character*/
	}
}