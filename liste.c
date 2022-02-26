#include "liste.h"

//fct de adaugare nod la finalul listei
void addEnd(Node **head, Country info_tara)
{  //daca lista este goala,adauga primul nod(informatiile despre prima tara)
	if(*head==NULL) {
		Node *new_node=(Node*)malloc(sizeof(Node));
		new_node->tara=info_tara;
		new_node->next=new_node->prev=new_node;
		*head = new_node;
		return;
	}

	//daca lista nu este goala se cauta ultimul nod
	Node *ultim=(*head)->prev;
	//alocare dinamica pentru noul nod
	Node *new_node=(Node*)malloc(sizeof(Node));
	new_node->tara=info_tara; //pun informatiile despre tara in noul nod
	new_node->next=*head;
	(*head)->prev=new_node;//creez legatura intre noul nod si santinela
	new_node->prev=ultim;
	//ultimul nod va fi nodul nou adaugat
	ultim->next=new_node;
}

/*functie care imi returneaza nodul in care se gaseste tara
cu scorul initial minim*/
Node *minimal(Node **head)
{	
	Node *curent; 
  	curent=*head;//initializez nodul curent cu head
    Node *minim=(Node*)malloc(sizeof(Node));
  	minim->tara=(*head)->tara;
    //initializez min cu scorul initial al primei tari din lista 
    float min = score_initial((*head)->tara);
    // Cat timp n-am parcurs toata lista caut minimul
    while (curent->next!=*head) {
  		if (score_initial(curent->next->tara)<min) {
            min = score_initial(curent->next->tara);
            minim=curent->next;
        } 
        curent=curent->next;//se deplaseaza spre urmatorul nod
    }
  	return minim;
}

//fct de eliminare nod din lista, dat prin adresa
void sterg_nod(Node **head, Node *adr)
{
	if(*head==NULL)//caz lista goala
		return;
	Node *curent=*head,*prev=NULL;
	while(strcmp(curent->tara.name,adr->tara.name)) { //se cauta nodul de sters
		if(curent->next==*head) { //daca se ajunge iar la inceputul listei, nu s-a gasit nodul
			printf("Nu exista acest nod");
			return;
		}
		prev=curent;
		curent=curent->next;
	}
	//daca-i singur in lista
	if(curent->next==*head&&prev==NULL) {
		(*head)=NULL;
		free(curent);//eliberez memorie ptr nod/il sterg
	}

	if(curent==*head) {//daca nodul de sters este primul nod din lista/santinela
		prev=(*head)->prev;
		*head=(*head)->next;
		prev->next=*head;
		(*head)->prev=prev;
		free(curent);
	} else
	if(curent->next==*head) { //daca nodul de sters este ultimul
		prev->next=*head;
		(*head)->prev=prev;
		free(curent);
	} else { //altfel iau un nod temporar care se gaseste dupa nodul cautat
		Node *temp=curent->next;
		prev->next=temp;  //creez legaturi intre nodul temporar si predecesorul nodului de sters
		temp->prev=prev;
		free(curent);
	}
}

//functie de afisare in fisier a numelor tarilor din lista
void afisare(Node *head, FILE *g)
{
	Node *temp=head;
	do {
		fprintf(g, "%s\n", temp->tara.name);
		temp=temp->next;
	}	
	while(temp!=head);
}

/*functie in care sterg tarile cu scorul initial cel mai mic 
pana cand numarul lor este o putere a lui 2 si le afisez pe cele ramase 
in fisier*/
void modific(Node **head, int *nr_teams, char *nume)
{	
	FILE *g;
	if((g=fopen(nume,"wt"))==NULL) {
      puts("fisierul nu poate fi deschis");
      exit(1);
	}
	
	while(power(*nr_teams)==0) {
		Node *sters=minimal(&(*head));
		sterg_nod(&(*head), sters);
	    (*nr_teams)--;
	}
	afisare(*head, g);
	fclose(g);
}
