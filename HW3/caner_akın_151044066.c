#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define MAX_LEN 250 
#define MAX_ROW 100
#define WORD_LENGTH 10

void read_input2(char array[][MAX_LEN],FILE *file);/*this function read the input2.txt*/
int vertical(char array[MAX_ROW][MAX_LEN], char word[WORD_LENGTH], int word_size,int i,int j);/*this function vertical search the word in kordinant */
int horizontal(char array[MAX_ROW][MAX_LEN], char word[WORD_LENGTH], int word_size,int i,int j);/*this function horizontal search the word in kordinant */
void look_Map(char array[MAX_ROW][MAX_LEN],char word[WORD_LENGTH], int size,FILE *file);/*this function find the word*/

int main(){

	FILE *file1;
	FILE *file2;
	FILE *file3;	
	file1 = fopen("input1.txt","r"); 	/*for only read open*/
	file2 = fopen("input2.txt","r");	/*for only read open*/
	file3 = fopen("output.txt","w");	/*for only write open*/

	int size;
	char word_array[WORD_LENGTH];	
	char array[MAX_ROW][MAX_LEN];

	read_input2(array,file2);	/*there call the function for take map*/
	while(fscanf(file1,"%s",word_array) != EOF)	/*there contunie to end of file*/
	{	
		size = strlen(word_array);/*find the word length*/
		look_Map(array,word_array,size,file3); /*call the function for find the word in map*/
	}
	fclose(file3); 	 /*close the files*/
	fclose(file2);
	fclose(file1);
	return(0);
}
void read_input2(char array[][MAX_LEN],FILE *file)	/*this function read the input2.txt*/
{
	int i = 0;	
	while(!feof(file)){	/*there contunie to end of file*/
		fscanf(file,"%s",array[i]); /*save in array*/
		i += 1;
	}
	array[i][0] = '\0';
}
/*this function vertical search the word in kordinant */
int vertical(char array[MAX_ROW][MAX_LEN], char word[WORD_LENGTH], int word_size,int i,int j){

	int x;
	char control[word_size];	
	int size = 0;
	/*for search vertical program plus the x*/
	for(x = i; x<i+word_size; ++x){
		control[size] = array[x][j]; /*there copy the new array*/ 
		++size;
	}
	control[size] = 0;/*this assignment for do not destroy the word */
	if(strcmp(control,word)==0){ /*if same the map*/
		return 1;	}
	else{
		return 0;	}
}
/*this function horizontal search the word in kordinant */
int horizontal(char array[MAX_ROW][MAX_LEN], char word[WORD_LENGTH], int word_size,int i,int j){

	int y;
	char control[word_size];	
	int size = 0;
	
	/*for search horizontal program plus the y*/
	for(y = j; y<j+word_size; ++y){
		control[size] = array[i][y]; /*there copy the new array*/ 
		size++;
	}
	control[size] = 0;			/*this assignment for do not destroy the word */
	if(strcmp(control,word)==0){ /*if same the map*/
		return 1;	}
	else{
		return 0;	}
}
/*this function find the word*/
void look_Map(char array[MAX_ROW][MAX_LEN],char word[WORD_LENGTH], int size,FILE *file){	

	int i = 0;
	int j = 0;
	
	for(j = 0; j<MAX_LEN; ++j){
		if(array[i][j] == 0){
			++i;
			j=-1;
		}
		else{
			if(array[i][j] == word[0]){		/*if same letter look there*/	
				if((horizontal(array,word,size,i,j)) == 1){ /*If the word we are looking for is horizontal*/
					++i;	
					++j;
					fprintf(file,"%s (%d,%d) Horizontal%c",word, i, j,'\n'); /*write the file*/
					break;
				}
				else if(vertical(array,word,size,i,j) == 1){ /*If the word we are looking for is vertical*/
					++i;	
					++j;
					fprintf(file,"%s (%d,%d) Vertical%c",word, i, j,'\n'); /*write the file*/
					break;
				}
			}
		}
	}
}
