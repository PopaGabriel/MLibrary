#include"HashMap.h"
#ifndef Initializare_File
#define Initializare_File

Autor Creeaza_Structura_Autor (char *nume_autor)
{
	Autor autor = malloc(sizeof(struct Autor));
	autor->nume_autor = malloc((strlen(nume_autor) + 1)* sizeof(char));
	strcpy(autor->nume_autor, nume_autor);
	autor->album = NULL;
	autor->next = NULL;
	autor->next_HashMap = NULL;
	autor->prev_HashMap = NULL;

	return autor;
}

Album Creeaza_Structura_Album(char *nume_album)
{
	Album album = malloc(sizeof(struct Album));
	album->nume_album = malloc((strlen(nume_album) + 1) * sizeof(char));
	strcpy(album->nume_album, nume_album);
	album->LINK_YOUTUBE = NULL;
	album->next = NULL;
	return album;
}

void Adauga_album(Album *album_head, Album album)
{
	if (album == NULL)
		return;
	if (*album_head == NULL) {
		*album_head = album;
		return;
	}

	Album prev, next;
	prev = *album_head;
	next = (*album_head)->next;

	if (strcmp((*album_head)->nume_album, album->nume_album) > 0) {
		album->next = (*album_head);
		*album_head = album;
		return;
	}

	while (prev->next != NULL) {

		if (strcmp(next->nume_album, album->nume_album) > 0 ) {
			album->next = next;
			prev->next = album;
			return;
		}
		prev = prev->next;
		next = next->next;
	}
	prev->next = album;
}

void Adauga_autor(Autor *autor_head, Autor autor)
{

	if(autor == NULL)
		return;

	if (*autor_head == NULL) {
		*autor_head = autor;
		return;
	}

	Autor prev, next;
	prev = *autor_head;
	next = (*autor_head)->next;

	if (strcmp((*autor_head)->nume_autor, autor->nume_autor) > 0) {
		autor->next = (*autor_head);
		*autor_head = autor;
		return;
	}

	if (strcmp((*autor_head)->nume_autor, autor->nume_autor) == 0) {
			Adauga_album(&prev->album, autor->album);
			free(autor->nume_autor);
			free(autor);
			return;
	}

	while (next != NULL) {

		if (strcmp(prev->nume_autor, autor->nume_autor) == 0 ) {
			Adauga_album(&prev->album, autor->album);
			free(autor->nume_autor);
			free(autor);
			return;
		} else if (strcmp(next->nume_autor, autor->nume_autor) > 0) {
			autor->next = next;
			prev->next = autor;
			return;
		}
		prev = next;
		next = next->next;
	}

	if (strcmp(prev->nume_autor, autor->nume_autor) == 0) {
			Adauga_album(&prev->album, autor->album);
			free(autor->nume_autor);
			free(autor);
			return;
	}

	prev->next = autor;
}

void Aloc_memory_LINK(char **Link, char *Link_aux)
{
	*Link = (char *)malloc((strlen(Link_aux) + 1) * sizeof(char));
	strcpy(*Link, Link_aux);
}

Autor Initialise(FILE *in, HashMap hashmap)
{

	char buff[255];
	char *pointer;
	Autor autor, autor_head;

	autor = NULL;
	autor_head = NULL;

	Album album;
	album = NULL;

	while(fgets(buff, 255, in)) {
  		pointer = strtok (buff,"@");
 		autor = Creeaza_Structura_Autor(pointer);

 		pointer = strtok (NULL, "@");
 		album = Creeaza_Structura_Album(pointer);

 		pointer = strtok (NULL, "@");
 		Aloc_memory_LINK(&(album->LINK_YOUTUBE), pointer);

 		pointer = strtok (NULL, "@");
 		album->nota_album = atoi(pointer);
 		autor->album = album;

 		push_HashMap(hashmap, autor);
 		Adauga_autor(&autor_head, autor);

 	}
 	return autor_head;
}

#endif
