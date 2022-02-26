#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "structuri.h"
#include "liste.h"
#include "stiva.h"
#include "coada.h"
#include "BST.h"

void sterg_bst(Node_BST *root)
{
  if(root)
  {sterg_bst(root->left);
  sterg_bst(root->right);
  free(root);}
}
int main(int argc, char *argv[])
{
  	FILE *f, *g, *k;
  	int *v;
  	Node *head=NULL;
  	int nr_teams, i, j;
  	//deschid fisierul f ptr citire
  	if((f=fopen(argv[2], "rt"))==NULL) {
      puts("fisierul nu poate fi deschis");
      exit(1);
	}
  	fscanf(f,"%d",&nr_teams);//citesc nr echipelor
  	for(i=0;i<nr_teams;i++)
   	 	addEnd(&head, citire_tar(i, f)); //adaug elemente rand pe rand la finalul listei
  	fclose(f);
  	//deschid fisierul g pentru scriere
  	if((g=fopen(argv[3], "wt"))==NULL) {
      puts("fisierul nu poate fi deschis");
      exit(1);
	}
	//k=fisierul de cerinte, il deschid ptr citire
  	if((k=fopen(argv[1],"rt"))==NULL) {
      puts("fisierul nu poate fi deschis");
      exit(1);
  	} 
  	//creez un vector in care pun valorile care imi spun daca se executa
  	//o anumita cerinta
    v=(int*)malloc(5*sizeof(int));
	for(i=0; i<5; i++)
		fscanf(k,"%d",&v[i]);
	if(v[0])
  		afisare(head,g);
  	fclose(g);
  	if(v[1])
  		modific(&head,&nr_teams,argv[3]);
  	//imi creez stiva de tari
  	Node_stiva *stacktop=NULL;
  	stiva_tari(&stacktop, head);
  	int l=1;//numarul etapei
  	if((g=fopen(argv[3],"at"))==NULL) { //deschid fisierul ptr adaugare
      puts("fisierul nu poate fi deschis");
      exit(1);
	}
	Country *ultime;
	alocare_tari(&ultime, 4);
	if(v[2])
  	afisare_meciuri(&stacktop,&nr_teams,&l,g,&ultime);
  	fclose(g);
  	if((g=fopen(argv[3],"at"))==NULL) { //deschid fisierul ptr adaugare
      puts("fisierul nu poate fi deschis");
      exit(1);
	}
	Node_BST*root=NULL;
  	if(v[3]){
  	root=insert(root,ultime[0].players[0]);//inserez primul element
  	creare_arbore(&root,ultime);
  	fprintf(g,"\n====== CLASAMENT JUCATORI ======\n");
  	afisare_descrescator(root,g);
  	}
  	free(ultime);
  	fclose(g);
	if((g=fopen(argv[3],"at"))==NULL) { //deschid fisierul ptr adaugare
      puts("fisierul nu poate fi deschis");
      exit(1);
	}
	Player dat1,dat2;
	int nr=0;
	dat1=citire_juc(i, k);
	dat2=citire_juc(i, k);
	if(v[4]){
		ultima_cerinta(root,dat1,dat2,g,&nr);
		//daca numarul este diferit de 0 il afisez
		if(nr)
			fprintf(g,"\n%d",nr);
	}
	fclose(g);
  	free(v);
    sterg_bst(root);
    free(stacktop);
    free(dat1.last_name);
    free(dat1.first_name);
    free(dat2.last_name);
    free(dat2.first_name);
  	fclose(k);
   	return 0;
}