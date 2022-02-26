#ifndef Structuri_H
#define Structuri_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//structura ptr jucator
typedef struct { 
   char *last_name;
   char *first_name;
   int score;
} Player;

//structura pentru tara
typedef struct {
   char *name;
   int nr_players;
   int global_score;
   Player *players;
} Country;
//functie alocare dinamica pentru un vector de tari
void alocare_tari(Country **C, int n);
//functie alocare dinamica pentru un vector de jucatori
void alocare_juc(Player **P, int m);
//functie de citire (din fisier) a campurilor pentru un singur jucator
Player citire_juc(int i, FILE *f);
//functie de citire (din fisier) a campurilor unei singure tari
Country citire_tar(int i, FILE *f);
//functie pentru returnarea scorului initial al unei tari
float score_initial(Country c);
/*functie care gaseste jucatorul cu scorul cel mai mare dintre
jucatorii a 2 tari si returneaza tara jucatorului*/
Country scor_maxim(Country tara1, Country tara2);
#endif //Structuri_H