#include "utile.h"

//cerinta 2
/*functie pentru verificarea daca un numar este putere a lui 2, 
returneaza 1 in caz afirmativ*/
int power(int n)
{
	while(n!=1) {
		if(n%2!=0)//daca nr nu se divide cu 2 e clar ca nu e putere
		return 0;
		n=n/2;
	}
	return 1;
}

