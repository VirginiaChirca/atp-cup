#include "headertema1.h"
#include<stdlib.h>
#include<stdio.h>

int main()
{
  FILE *f;
  Country *C;
	if((f=fopen("date.in","rt"))==NULL)
	{
      puts("fisierul nu poate fi deschis");
      exit(1);
	}
	int nr_teams,i;
   	fscanf(f,"%d",&nr_teams);
   	alocare_tari(&C,nr_teams)
   	for(i=0;i<nr_teams,i++)
   	 C[i]=citiretar(i,f);
   	fclose(f);
   	free(C);



}