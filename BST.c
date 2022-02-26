#include "BST.h"
//adagare element in BST
Node_BST* newNode_arbore(Player juc_nou)
{  
	Node_BST* node = (Node_BST*)malloc(sizeof(Node_BST));
	node->juc= juc_nou;
	node->left = node->right = NULL;
	return node;
}

//fct inserare element nod BST
Node_BST* insert(Node_BST* node, Player juc_nou)
{// daca(sub)arborelee gol–se creaza un nod
 //si se returneaza adresa
  	if (node == NULL) return newNode_arbore(juc_nou);
 //altfel se coboara la stanga sau dreapta in arbore 
 	if (juc_nou.score < node->juc.score)  
 		node->left  = insert(node->left, juc_nou);
 	else 
 	if (juc_nou.score > node->juc.score) 
 		node->right = insert(node->right, juc_nou); 
 	else 
 	//daca jucatorul pe care vreau sa-l introduc are acelasi scor cu
 	//unul deja in arbore fac comparatia lexicografica a numelor
 	if(juc_nou.score==node->juc.score) {
 		if(strcmp(juc_nou.last_name,node->juc.last_name)<0)
 			node->juc=juc_nou;
 		else 
 		if(strcmp(juc_nou.last_name,node->juc.last_name)==0)
 			if(strcmp(juc_nou.first_name,node->juc.first_name)<0)
 				node->juc=juc_nou;
	}  
 //pointerul node se intoarce nemodificat pe acest return 
 	return node;
}

//functie de creare a arborelui cu jucatori
void creare_arbore(Node_BST **root, Country*ultime)
{		
	//parcurg vectorul cu ulrimele 4 trai din turneu
	for(int i=0;i<4;i++)
		//iau jucatorii fiecarei tari si-i introduc in arbore
		for(int j=0;j<ultime[i].nr_players;j++)
			insert(*root,ultime[i].players[j]);
}


//fct de afisare in ordine descrescatoare a jucatorilor in fct de scor
void afisare_descrescator(Node_BST *root,FILE *g)
{
	if (root) { 
		afisare_descrescator(root->right,g);
		fprintf(g,"%s %s %d \n",root->juc.last_name,root->juc.first_name,root->juc.score);
		afisare_descrescator(root->left,g);
	}
}

//cerinta 5
//fct de cautare in arbore 
Node_BST* search(Node_BST* root, Player cautat) 
{
	//daca radacina e null sau s-a gasit elementul
	if (root == NULL || (((strcmp(root->juc.last_name,cautat.last_name))==0)&& (strcmp(root->juc.first_name,cautat.first_name)==0)))
		return root;
	//daca valoarea stocata in radacina e mai mica decat scorul juc
	if (root->juc.score< cautat.score)  
		return search(root->right, cautat);
	// daca valoarea stocata in radacina e mai mare decat scorul juc
	return search(root->left, cautat);
} 
//daca nu se gaseste nod cu aceasta scor se returneaza NULL
//fct in care aflu numarul jucatorilor cu scorul in cei 2 juc cititi 
//din fisier
void numarare(Node_BST *root, Player dat1, Player dat2, int *nr, FILE *g)
{	
	
	if(root==NULL) return;
	//daca valoarea radacinii este mai mare decat scorul juc dat1
	if((dat1.score)<=(root->juc.score)) 
		numarare(root->left,dat1,dat2,&(*nr),g);//ma duc in subarborele stang
	//daca valoarea radacinii este intre scorurile celor 2 jucatori dati
	if(dat1.score<root->juc.score&&dat2.score>root->juc.score)
		(*nr)++;//incrementez nr
	//daca valoarea radacinii este mai mica decat scorul jucatorului dat2
	if((dat2.score)>=(root->juc.score))//daca valoarea radacinii este mai mica decat 
		numarare(root->right,dat1,dat2,&(*nr),g);//ma duc in subarborele drept
}

int ultima_cerinta(Node_BST*root, Player dat1, Player dat2, FILE *g,int*nr)
{	
	//verific intai daca jucatorii se afla in arbore
	if(search(root,dat1)==NULL)
		fprintf(g,"\n%s %s nu poate fi identificat!\n",dat1.last_name,dat1.first_name);
	else
	if(search(root,dat2)==NULL)
		fprintf(g,"\n%s %s nu poate fi identificat!\n",dat2.last_name,dat2.first_name);
	else
	//verific care dintre juc cititi are scorul mai mare
	if(dat1.score<dat2.score) 
			numarare(root,dat1,dat2,&(*nr),g);
	else
	if(dat1.score>dat2.score)
			numarare(root,dat2,dat1,&(*nr),g);
		
}