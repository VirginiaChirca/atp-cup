#ifndef Coada_H
#define Coada_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "structuri.h"
#include "stiva.h"
//o strcutura care imi retine 2 jucatori
struct Meci {
	Player p1,p2;
};
typedef struct Meci Meci;

//implementare elemente si coada
struct Elem_coada { 
	Meci game; // datele a 2 jucatori  
	struct Elem_coada* next; // legatura catre nodul urmator
}; 
typedef struct Elem_coada Node_coada; 

struct Q {
	Node_coada *front, *rear;
};
typedef struct Q Queue;
//functie creare coada
Queue* createQueue();
//functie adaugare element coada
void enQueue(Queue*q, Meci new_game);
//verificare coada goala
int isEmpty_coada(Queue*q);
//functie scoatere element coada, intoarce acel element
Meci deQueue(Queue*q);
//functie in care imi creez coada de meciuri pentru 2 tari
void creare_coada_meciuri(Queue**q, int *scor_local1, int *scor_local2, Country *tara1, Country *tara2);
//fct de afisare a meciurilor
void afisare_meciuri(Node_stiva **top, int *nr_teams, int *k, FILE *g,Country **ultime);
#endif //Coada_H