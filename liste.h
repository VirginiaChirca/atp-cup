#ifndef Liste_H
#define Liste_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "structuri.h"
#include "utile.h"
//structura unui nod pentru o lista circulara dublu inlantuita
typedef struct Elem {
	Country tara;
	struct Elem *next,*prev;
} Node;
//fct de adaugare nod la finalul listei
void addEnd(Node **head, Country info_tara);
/*functie care imi returneaza nodul in care se gaseste tara
cu scorul initial minim*/
Node *minimal(Node **head);
//fct de eliminare nod din lista, dat prin adresa
void sterg_nod(Node **head, Node *adr);
//functie de afisare in fisier a numelor tarilor din lista
void afisare(Node *head, FILE *g);
/*functie in care sterg tarile cu scorul initial cel mai mic 
pana cand numarul lor este o putere a lui 2 si le afisez pe cele ramase 
in fisier*/
void modific(Node **head, int *nr_teams, char *nume);




#endif //Liste_H