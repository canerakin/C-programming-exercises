#include <stdio.h>
#define class1 10
#define class2 10

int main()
{
	float status,first_point,second_point;	/*status = kontrol unit ; first_point = x coordinate ; second_point*/
	float class1_avarage1 = 0,class1_avarage2 = 0; 
	float class2_avarage1 = 0,class2_avarage2 = 0; 	/*veriables to collect coordinates*/
	int count = 0;
	float average_point,separating_line; 	/*slopes*/
	float area_of_class; 	/*location*/
	float constant;
	status = 1.1;

	while(status != 0 && count < class1 + class2)
	{
		if (count < class1) 	/*program takes there until class1*/
		{
			printf("line %d > ",count);
			status = scanf("%f%f",&first_point,&second_point);
			class1_avarage1 += first_point; 
			class1_avarage2 += second_point; 	/*every coordinate is plus*/
			count += 1;	
		}
		else	/*if class1 is enought after take class2*/
		{
			printf("line %d > ",count);
			status = scanf("%f%f",&first_point,&second_point);
			class2_avarage1 += first_point; 
			class2_avarage2 += second_point;  /*every coordinate is plus*/			
			count += 1;		
		}
	}

	class1_avarage1 /= class1; 	/*averages are taken*/
	class1_avarage2 /= class1; 
	class2_avarage1 /= class2; 
	class2_avarage2 /= class2; 

			/*finding the tilt coordinate => y = m*x + b(constant)*/

	if (class2_avarage1 - class1_avarage1 == 0)
	{
		average_point = (class2_avarage2 - class1_avarage2) / (0.0001) ;	/*if x beeing 0 program take 0.0001*/
	}
	else
	{
		average_point = (class2_avarage2 - class1_avarage2) / (class2_avarage1 - class1_avarage1) ;
	}

	separating_line = -1 / average_point; 	/*find the separating_line slope*/
	constant = ((class2_avarage2 + class1_avarage2) / 2) - (separating_line *((class1_avarage1 + class2_avarage1)/2)) ;	 /*find the constant*/

	while(status != 0 )	/*if user's input be not number after program quit*/
	{
		printf("line %d > ",count);
		status = scanf("%f%f",&first_point,&second_point);
		count += 1;
		area_of_class = separating_line * first_point - second_point + constant;	/*find to coordinate*/

		if (status != 0)
		{
			if (area_of_class <= 0)
			{
				printf("line %d > class2\n",count);
			}
			else
			{
				printf("line %d > class1\n",count);
			}
		}

		count += 1;
	}	

	return 0;
}