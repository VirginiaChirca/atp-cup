#ifndef Node_H
#define Node_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifndef Country
#define Country

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifndef Player
#define Player

//Structura Player cu datele stocate in structura Country

//Structura pentru jucator:
typedef struct { 
   char *last_name;
   char *first_name;
   int score;
} Player;
 
#endif

//Structura Country cu datele stocate in nod

//Structura pentru tara:
typedef struct {
   char *name;
   int nr_players;
   int global_score;
   Player *players;
} Country;

#endif

//Element din lista dublu inlantuita 

typedef struct Elem{
	Country tara;
	struct Elem *next,*prev;
}Node;

void alocare_tari(Country **C,int n);
void alocare_juc(Player **P,int m);
Player citirejuc(int i);
Country citiretar(int i);

#endif