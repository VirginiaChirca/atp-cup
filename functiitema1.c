#include "headertema1.h"
#include<stdio.h>
#include<stdlib.h>

//alocare dinamica pentru un vector de tari
void alocare_tari(Country **C,int n)
{
	*C=calloc(n,sizeof(Country));
	if(*C==NULL)
		printf("alocare nereusita");

}

void alocare_juc(Player **P,int m)
{
	*P=calloc(m,sizeof(Player));
	if(*P==NULL)
		printf("alocare nereusita");

}
//functie de citire pentru un singur jucator
Player citirejuc(int i)
{   
	Player p;
	char buffer1[20],buffer2[20];
	fscanf(f,"%s",buffer1);
	p.last_name=malloc(sizeof(char)*(strlen(buffer1)+1));
	strcpy(p.last_nume,buffer1);
	fscanf(f,"%s",buffer2);
	p.first_name=malloc(sizeof(char)*(strlen(buffer2)+1));
	strcpy(p.first_name,buffer2);
    fscanf(f,"%d",&score);
    return p;
}

//functie de citire a campurilor unei singure tari
Country citiretar(int i,FILE *f)
{
	Country c;
	int i;
	fscanf(f,"%d",&nr_players);
    char buffer[20];
	fscanf(f,"%s",buffer);
	c.name=malloc(sizeof(char)*(strlen(buffer)+1));
	strcpy(c.name,buffer);
	fscanf(f,"%d",&global_score);
	Player *P;
	alocare_juc(&P,nr_players);
    for(i=0;i<nr_players;i++)
        P[i]=citirejuc(i);
    free(P);
    return c;
    
}

