#include"Structuri.h"

#ifndef FREE_FILE
#define FREE_FILE


void Free_Album(Album album)
{
	Album aux;
	aux = NULL;

	while(album != NULL) {
		aux = album;
		album = album->next;
		free(aux->LINK_YOUTUBE);
		free(aux->nume_album);
		free(aux);
	}
}

void Free_Autor(Autor autor)
{
	Autor aux;
	aux = NULL;

	while(autor != NULL) {
		aux = autor;
		autor = autor->next;
		Free_Album(aux->album);
		free(aux->nume_autor);
		free(aux);
	}
}

#endif
