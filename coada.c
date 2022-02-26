#include "coada.h"
//functie creare coada
Queue* createQueue()
{
	Queue *q;
	q=(Queue*)malloc(sizeof(Queue));
	if(q==NULL) return NULL;
	q->front=q->rear=NULL;
	return q;
}

//functie adaugare element coada
void enQueue(Queue*q, Meci new_game)
{
	Node_coada* newNode=(Node_coada*)malloc(sizeof(Node_coada));
	newNode->game.p1=new_game.p1;
	newNode->game.p2=new_game.p2;
	newNode->next=NULL;//nodurile noi se adauga la finalul cozii
	if (q->rear==NULL) q->rear=newNode;  //daca nu aveam niciun nod in coada 
	else
	{
		(q->rear)->next=newNode;
		(q->rear)=newNode;
	}
	if (q->front==NULL) 
		q->front=q->rear; // daca e singurul element din coada
} 

//verificare coada goala
int isEmpty_coada(Queue*q)
{
	return (q->front==NULL);
}

//functie scoatere element coada, intoarce acel element
Meci deQueue(Queue*q) 
{  
	Node_coada *aux; 
	Meci d;
	aux=q->front; 
	d=aux->game;
	q->front=(q->front)->next;
	free(aux);
	return d;  
}

//functie in care imi creez coada de meciuri pentru 2 tari
void creare_coada_meciuri(Queue**q, int *scor_local1, int *scor_local2, Country *tara1, Country *tara2)
{
	//cu cele 2 for-uri aleg jucatorii ptr confruntare
	for(int i=0; i<(*tara1).nr_players; i++) {
		Meci new_game;
		for(int j=0;j<(*tara2).nr_players;j++) {	
			new_game.p1=(*tara1).players[i];
			new_game.p2=(*tara2).players[j];
			enQueue(*q, new_game);//adaug meci
			//fac comparatiile necesare si modific scorurile
			if((*tara1).players[i].score>(*tara2).players[j].score) {
				(*tara1).players[i].score=(*tara1).players[i].score+5;
				(*scor_local1)=(*scor_local1)+3;
			} else
			if((*tara1).players[i].score<(*tara2).players[j].score) {
				(*tara2).players[j].score=(*tara2).players[j].score+5;
				(*scor_local2)=(*scor_local2)+3;
			} else
			if((*tara1).players[i].score==(*tara2).players[j].score) {
				(*tara1).players[i].score=(*tara1).players[i].score+2;
				(*tara2).players[j].score=(*tara2).players[j].score+2;
				(*scor_local1)=(*scor_local1)+1;
				(*scor_local2)=(*scor_local2)+1;
			}
		}
	}
}

//fct de afisare a meciurilor
void afisare_meciuri(Node_stiva **top, int *nr_teams, int *k, FILE *g,Country **ultime)
{	
	fprintf(g,"\n");
	fprintf(g,"====== ETAPA %d ======\n\n",*k);//k retine numarul etapei
	(*k)++;//se incrementeaza la fiecare apel,il initializez in main cu 1
	Country tara1, tara2;
	Node_stiva *Winner=NULL;
	//cat timp  mai am tari in stiva initiala
	while (!isEmpty(*top)) {
		Queue* q=createQueue();
		//extrag tarile cu pop
		tara1=pop(&(*top));
		int scor_local1=0;
		tara2=pop(&(*top));
		int scor_local2=0;
		/*doar la primul apel al functiei scorurile globale ale tarilor
		sunt egale cu 0*/
		if((*k)==2) { 
			tara1.global_score=0;
			tara2.global_score=0;
		}
		fprintf(g,"%s %d ----- %s %d\n", tara1.name, tara1.global_score, tara2.name, tara2.global_score);
		creare_coada_meciuri(&q,&scor_local1,&scor_local2,&tara1,&tara2);
		//extrag meci cu meci din coada si-l afisez
		while (!isEmpty_coada(q)) {
			Meci game=deQueue(q);
			fprintf(g,"%s %s %d vs %s %s %d\n", game.p1.last_name, game.p1.first_name, game.p1.score, game.p2.last_name, game.p2.first_name, game.p2.score);
		}
		free(q);
		fprintf(g,"\n");
		//apelez fct ptr modificarea scorurilor
		stiva_castigator(&Winner,scor_local1,scor_local2,&tara1, &tara2);
	}	
	fprintf(g,"=== WINNER ===\n");
	//dupa fiecare etapa numarul echipelor se injumatateste
	*nr_teams=*nr_teams/2; 
	tari_castigatoare(&(*top),&Winner,g,*nr_teams,&(*ultime));
	/*cat timp stiva initiala nu a devenit goala si retine mai mult 
	de o tara apelez fct sa repete operatiile*/
	while((!isEmpty(*top))&&(*nr_teams!=1))
	afisare_meciuri(&(*top), &(*nr_teams),&(*k), g,&(*ultime));
}