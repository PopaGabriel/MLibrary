#include"Structuri.h"

#ifndef HEADER_FILE
#define HEADER_FILE


void Free_Album(Album album)
{
	Album aux;
	while(album) {
		//aux = album;
		album = album->next;
		printf("De ce am intrat aici????");
		//free(aux->nume_album);
		//free(aux);
	}
}

void Free_Autor(Autor autor) {
	Autor aux;
	while(autor != NULL) {
		aux = autor;
		autor = autor->next;
		//Free_Album(autor->album);
		free(aux->nume_autor);
		free(aux);
	}
}

#endif
