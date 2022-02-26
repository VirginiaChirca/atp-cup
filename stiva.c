#include "stiva.h"

//functie adaugare element in stiva
void push(Node_stiva **top, Country info_tara)   
//varful trebuie intors modificat din functie
{
	Node_stiva* newNode=(Node_stiva*)malloc(sizeof(Node_stiva));
	newNode->tara=info_tara;
	newNode->next=(*top);
	*top=newNode;
}


//verificare stiva goala
int isEmpty(Node_stiva *top)
{
	return top==NULL;
}


//functie in care parcurg lista si introduc tarile in stiva
void stiva_tari(Node_stiva **top, Node *head)
{	
	Node *temp=head;
	do {
		push(&(*top), temp->tara);
		temp=temp->next;
	}	
	while(temp!=head);
	free(temp);
}
//functie care sterge un nod din stiva si imi intoarce tara aflata acolo
Country pop(Node_stiva **top) 
// se returneaza informatia stocata in varf si se sterge acest nod
{ 
	Node_stiva *temp=*top;   //stochez adresa varful in temp
	Country aux=temp->tara;  //stochez valoarea din varf in aux
	*top=(*top)->next;       //sterg elementul din varf
	free(temp);
	return aux;
} 
//functie afisare nume tari din stiva
void afisare_stiva(Node_stiva **top)
{	
	while (!isEmpty(*top))
		printf("%s\n", pop(&(*top)).name);
}
//functie pentru modificare scorului global al unei tari si adaugare 
//tara castigatoare
void stiva_castigator(Node_stiva **Winner,int scor_local1,int scor_local2,Country *tara1, Country *tara2)
{
	//fac comparatiile necesare si adaug tara castigatoare in stiva
	if(scor_local1>scor_local2) {
		(*tara1).global_score=(*tara1).global_score+scor_local1;
		push(&(*Winner),*tara1);
	} else
	if(scor_local1<scor_local2) {
		(*tara2).global_score=(*tara2).global_score+scor_local2;
		push(&(*Winner),*tara2);
	} else
	if(scor_local1==scor_local2) {
		//in acest caz ma folosesc de fct scor_maxim ca sa mi returneze 
		//numele tarii in care se afla juc cu scorul cel mai mare
		if(strcmp(scor_maxim(*tara1,*tara2).name,(*tara1).name)==0) {
			(*tara1).global_score=(*tara1).global_score+scor_local1;
			push(&(*Winner),*tara1);
		} else
		if(strcmp(scor_maxim(*tara1,*tara2).name,(*tara2).name)==0) {
			(*tara2).global_score=(*tara2).global_score+scor_local2;
			push(&(*Winner),*tara2);
		}
	}
}

//fct ptr afisarea tarilor castigatoare din stiva Winner
//vectorul de tari *ultime l-am introdus pentru retinerea ultimelor 4 
//tari ramase in turneu, pentru cerinta 4
void tari_castigatoare(Node_stiva **top, Node_stiva **Winner, FILE *g, int nr_teams, Country **ultime)
{
	int p=0;
	while (!isEmpty(*Winner)) {
		Country castigatoare=pop(&(*Winner));
		/*daca au ramas 4 echipe, le voi introduce in vectorul de tari
		cu scorul din acea etapa*/
		if(nr_teams==4) { 
			(*ultime)[p]=castigatoare;
			p++;
		} else 
		/*daca numarul echipelor este mai mic deact 4 trebuie sa 
		modific scorul tarilor care au iesit invingatoare
		din confruntarile ce-au urmat*/
		if(nr_teams<4)
			for(int i=0;i<4;i++)
				//verific daca tara din vector este aceeasi cu tara din stiva
				if(strcmp((*ultime)[i].name,castigatoare.name)==0)
					(*ultime)[i]=castigatoare;
		push(&(*top),castigatoare);//introduc tara in stiva initiala
		fprintf(g,"%s --- %d\n", castigatoare.name, castigatoare.global_score);
	}
	free(*Winner);//eliberez memorie
}

