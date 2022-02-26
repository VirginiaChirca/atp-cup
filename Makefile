build:
	gcc -o tenis structuri.c liste.c utile.c stiva.c coada.c BST.c prototip.c
clean:
	rm -f *.o
	rm -f tenis
