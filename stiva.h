#ifndef Stiva_H
#define Stiva_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "structuri.h"
#include "liste.h"

//implementare stiva
typedef struct Elem_stiva Node_stiva;  
struct Elem_stiva { 
	Country tara; 
	struct Elem_stiva* next; };

//functie adaugare element in stiva
void push(Node_stiva **top, Country info_tara);
//verificare stiva goala
int isEmpty(Node_stiva *top);
//functie in care parcurg lista si introduc tarile in stiva
void stiva_tari(Node_stiva **top, Node *head);
//functie care sterge un nod din stiva si imi intoarce tara aflata acolo
Country pop(Node_stiva **top);
//functie afisare nume tari din stiva
void afisare_stiva(Node_stiva **top);
//functie pentru modificare scorului global al unei tari si adaugare 
//tara castigatoare
void stiva_castigator(Node_stiva **Winner,int scor_local1,int scor_local2,Country *tara1, Country *tara2);
//fct ptr afisarea tarilor castigatoare din stiva Winner
//vectorul de tari *ultime l-am introdus pentru retinerea ultimelor 4 
//tari ramase in turneu, pentru cerinta 4
void tari_castigatoare(Node_stiva **top, Node_stiva **Winner, FILE *g, int nr_teams, Country **ultime);
#endif //Stiva_H