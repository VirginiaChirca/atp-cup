#include "structuri.h"
//functie alocare dinamica pentru un vector de tari
void alocare_tari(Country **C, int n)
{
	*C=calloc(n, sizeof(Country));
	if(*C==NULL)
		printf("alocare nereusita");
}

//functie alocare dinamica pentru un vector de jucatori
void alocare_juc(Player **P, int m)
{
	*P=calloc(m, sizeof(Player));
	if(*P==NULL)
		printf("alocare nereusita");
}
//functie de citire (din fisier) a campurilor pentru un singur jucator
Player citire_juc(int i, FILE *f)
{   
	Player p;
	/*am folosit urmatoarele siruri auxiliare ptr ca nu stiam lungimea
	precisa a numelor unui jucator*/
	char buffer1[20], buffer2[20];
	fscanf(f, "%s", buffer1);
	p.last_name=malloc(sizeof(char)*(strlen(buffer1)+1));
	strcpy(p.last_name, buffer1);
	fscanf(f, "%s", buffer2);
	p.first_name=malloc(sizeof(char)*(strlen(buffer2)+1));
	strcpy(p.first_name, buffer2);
    fscanf(f, "%d", &p.score);
    return p;
}
//functie de citire (din fisier) a campurilor unei singure tari
Country citire_tar(int i, FILE *f)
{
	Country c;
	int j;
	fscanf(f, "%d", &c.nr_players);
    char buffer[20];//folosit ptr ca nu stiam lungimea numelui unei tari
	fscanf(f, "%s", buffer);
	c.name=malloc(sizeof(char)*(strlen(buffer) + 1));//aloc memorie pentru numele unei tari
	strcpy(c.name, buffer);
	alocare_juc(&c.players, c.nr_players);//aloc dinamic emorie pentru un vector de jucatori
    for(j=0; j<c.nr_players; j++)
        c.players[j]=citire_juc(j, f); //creez vectorul de jucatori pentru o tara
    return c;
}
//functie pentru returnarea scorului initial al unei tari
float score_initial(Country c)
{
	float medie;
	int suma=0;
	int i;
	for(i=0; i<c.nr_players; i++)
		suma=suma+c.players[i].score; //suma scorurilor jucatorilor unei tari
    medie=(float)suma/c.nr_players;
    return medie;
}

/*functie care gaseste jucatorul cu scorul cel mai mare dintre
jucatorii a 2 tari si returneaza tara jucatorului*/
Country scor_maxim(Country tara1, Country tara2)
{
	//max1,max2 iau initial scorul primului jucator din fiecare tara
	int max1=tara1.players[0].score;
	int max2=tara2.players[0].score;
	int i;
	for(i=1; i<tara1.nr_players; i++)
		if(max1<tara1.players[i].score)
			max1=tara1.players[i].score;
	for(i=1; i<tara2.nr_players; i++)
		if(max2<tara2.players[i].score)
			max2=tara2.players[i].score;
	//verific care dintre scorurile maxime ale celor 2 tari este mai mare
	if(max1>max2)
		return tara1;
	else if(max1<max2) return tara2;
	//daca scorurile maxime sunt egale, returnez prima tara iesita din stiva
	else if(max1==max2) return tara1;
	
}
