#ifndef bst_H
#define bst_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "structuri.h"
//cerinta 4
//implementare arbore
typedef struct Node_BST Node_BST;
struct Node_BST 
{ 
	Player juc;// datele efective memorate
	struct Node_BST  *left,*right; // legatura catre subarborii din stanga si dreapta
};
//adagare element in BST
Node_BST* newNode_arbore(Player juc_nou);
//fct inserare element nod BST
Node_BST* insert(Node_BST* node, Player juc_nou);
//functie de creare a arborelui cu jucatori
void creare_arbore(Node_BST **root, Country*ultime);
//fct de afisare in ordine descrescatoare a jucatorilor in fct de scor
void afisare_descrescator(Node_BST *root,FILE *g);
//cerinta 5
//fct de cautare in arbore 
Node_BST* search(Node_BST* root, Player cautat);
//fct in care aflu numarul jucatorilor cu scorul in cei 2 juc cititi 
//din fisier
void numarare(Node_BST *root, Player dat1, Player dat2, int *nr, FILE *g);
int ultima_cerinta(Node_BST*root, Player dat1, Player dat2, FILE *g,int*nr);
#endif //bst_H