#include <stdio.h>
#define MAX 512

void search_island(int gate[MAX][MAX] ,int i ,int j , int island_number); 		/*this function find same island with recursive*/
int main()
{
	int gate[MAX][MAX];  	/*define the array*/
	FILE *file_inp;			/*open files*/
	FILE *file_out;			
	file_inp = fopen("input.txt","r");			/*define for read*/
	file_out = fopen("output.txt","w");			/*define for write*/
	int Line , island_number = -1 ;	
	int i ,j ,size;

	fscanf(file_inp,"%d",&Line);		/*there take the water line*/
	for (i = 0; i < MAX; ++i)
	{
		for (j = 0; j < MAX; ++j)
		{
			fscanf(file_inp,"%d",&size);		/*there take in input*/
			if (size > Line)		/*control for island*/
			{
				gate[i][j] = 1;
			}
			else		/*for water*/
			{
				gate[i][j] = 0;
			}					
		}
	}
	for (i = 0; i < MAX; ++i)
	{
		for (j = 0; j < MAX; ++j)
		{
			if (gate[i][j] == 1 )		/*if here a new island */
			{
				search_island(gate ,i ,j ,island_number);		/*call function for find island*/
				island_number -= 1;			/*for next island*/
			}
		}
	}
	fprintf(file_out,"%d",( (island_number+1) * -1 ));			/*there print island number in output*/
	island_number = -1;	
	for (i = 0; i < MAX; ++i)
	{
		for (j = 0; j < MAX; ++j)
		{
			if (gate[i][j] == island_number)		/*if there a new island*/
			{
				fprintf(file_out,"%c%d %d",'\n' ,i ,j );
				island_number -= 1;	
			}
		}
	}
	fclose(file_inp);	/*close the files*/
	fclose(file_out);
	return 0;	
} 
void search_island(int gate[MAX][MAX] ,int i ,int j , int island_number)		/*this function find same island with recursive*/
{
	gate[i][j] = island_number;    	 /*make assignment*/
	if (gate[i-1][j] == 1 && i > 0)   	  /*control for down*/
	{
		search_island(gate ,i-1 ,j ,island_number);			/*call again*/
	} 
	if (gate[i+1][j] == 1 && (i+1) < MAX)   	/*control for up*/
	{
		search_island(gate ,i+1 ,j ,island_number);			/*call again*/
	} 
	if (gate[i][j-1] == 1 && j > 0)			/*control for left*/
	{
		search_island(gate ,i ,j-1 ,island_number);			/*call again*/
	} 
	if (gate[i][j+1] == 1 && (j+1) < MAX)		/*control for right*/
	{
		search_island(gate ,i ,j+1 ,island_number);			/*call again*/
	}		
}