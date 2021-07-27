#include <stdio.h>
#define p1 0.5
#define p2 20

float find_a(float chunk[][1000] ,int i);	/*find the average of chuck(a)*/
float find_b(float chunk[][1000] ,int i ,float next_number);	/*find the average of chuck and after number(b)*/

int main()
{
	FILE * file1;	/*define for input.txt*/
	FILE * file2;	/*define for output.txt*/
	float chunk[100][1000];	/*includes any posibility */
	float averages[100];/*chuck averages*/
	float  n;	/*n = file number*/
	float a , b; 	/*a = now average , b = next average*/
	int i = 0 , j = 0 , k = 0 , m = 0 ,count;	/*i = chuck size , other standart count*/
	float big_average;

	file1 = fopen("input.txt","r");	/*file1 to be called*/
	file2 = fopen("output.txt","w");	/*file2 to be called*/

	while(!feof(file1))	/*dosyadaki taranmamış eleman kalmayana kadar devam eder*/
	{
		fscanf(file1,"%f ",&n);	/*dosyadan harf olarak teker teker alınır*/
		if (i == 0 && j == 0) 	/*that is for first number*/
		{
			chunk[i][j] = n;
			chunk[i][j+1] = '\0';
			j += 1;
		}
		else
		{
			a = find_a(chunk,i);	/*find a*/
			b = find_b(chunk,i,n);	/*find b*/
			if (!(b < (a*(1-p1)) || b > (a*(1+p1)) || a > (n*p2) || a < (n/p2)))	/*that's given formal*/
			{
				chunk[i][j] = n;	
				j += 1;
				chunk[i][j] = '\0';				
			}
			else	/*if number not add to chuck after program in there and create chuck for number*/
			{
				chunk[i][j] = '\0';
				averages[i] = find_a(chunk,i);	/*last chuck's averages*/
				i += 1;
				chunk[i][0] = n;
				j = 1;
				chunk[i][j] = '\0';
			}
		}
	}
	averages[i] = find_a(chunk,i);

	big_average = find_a(chunk,0);	/*first average taken*/	
	for (m = 1; m <= i; ++m)
	{
		if (big_average < find_a(chunk,m))
		{
			big_average = find_a(chunk,m);	/*find the big average*/
		}
	}
	big_average += 1;	/*now big_averages bigger than other averages*/

	for (m = 0; m <= i; ++m)
	{
		j = 0;
		for (k = 1; k <= i; ++k)
		{
			if (averages[j] > averages[k])
			{
				j = k;	 /*find the smallest average*/
			}
		}
		count = 0;
		while(chunk[j][count] != '\0') 	/*smallest average is written to the file*/
		{
			fprintf(file2,"%.4f ",chunk[j][count]);
			count += 1;
		}
		fprintf(file2,"%c",'\n');	
		averages[j] = big_average; 	/*for the next cycle smallest number assigned to big_number*/
	}

	fclose(file2);	/*file2 closed*/
	fclose(file1);	/*file1 closed*/
	return 0;
}

float find_a(float chunk[][1000] ,int i)	/*find the average of chuck(a)*/
{
	int j = 0;
	float count = 0;
	while(chunk[i][j] != '\0')
	{
		count += chunk[i][j]; 	/*every number is plus there*/
		j += 1;
	}
	count /= j;    /*after find the average*/
	return count;
}

float find_b(float chunk[][1000] ,int i ,float next_number)	/*find the average of chuck and after number(b)*/
{
	int j = 0;
	float count = 0;
	while(chunk[i][j] != '\0')
	{
		count += chunk[i][j];	/*every number is add there*/
		j += 1;
	}
	count += next_number;	/*after add the next number*/
	count /= (j + 1);	/*after find the average*/
	return count;	
}