#include"HashMap.h"
#ifndef Initializare_File
#define Initializare_File

Author Create_Structure_Author (char *name_author)
{
	Author author = malloc(sizeof(struct Author));
	author->name_author = malloc((strlen(name_author) + 1)* sizeof(char));
	strcpy(author->name_author, name_author);
	author->album = NULL;
	author->next = NULL;
	author->next_HashMap = NULL;
	author->prev_HashMap = NULL;

	return author;
}

Album Create_Structure_Album(char *name_album)
{
	Album album = malloc(sizeof(struct Album));
	album->name_album = malloc((strlen(name_album) + 1) * sizeof(char));
	strcpy(album->name_album, name_album);
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

	if (strcmp((*album_head)->name_album, album->name_album) > 0) {
		album->next = (*album_head);
		*album_head = album;
		return;
	}

	while (prev->next != NULL) {

		if (strcmp(next->name_album, album->name_album) > 0 ) {
			album->next = next;
			prev->next = album;
			return;
		}
		prev = prev->next;
		next = next->next;
	}
	prev->next = album;
}

void Adauga_autor(Author *author_head, Author author)
{

	if(author == NULL)
		return;

	if (*author_head == NULL) {
		*author_head = author;
		return;
	}

	Author prev, next;
	prev = *author_head;
	next = (*author_head)->next;

	if (strcmp((*author_head)->name_author, author->name_author) > 0) {
		author->next = (*author_head);
		*author_head = author;
		return;
	}

	if (strcmp((*author_head)->name_author, author->name_author) == 0) {
			Adauga_album(&prev->album, author->album);
			free(author->name_author);
			free(author);
			return;
	}

	while (next != NULL) {

		if (strcmp(prev->name_author, author->name_author) == 0 ) {
			Adauga_album(&prev->album, author->album);
			free(author->name_author);
			free(author);
			return;
		} else if (strcmp(next->name_author, author->name_author) > 0) {
			author->next = next;
			prev->next = author;
			return;
		}
		prev = next;
		next = next->next;
	}

	if (strcmp(prev->name_author, author->name_author) == 0) {
			Adauga_album(&prev->album, author->album);
			free(author->name_author);
			free(author);
			return;
	}

	prev->next = author;
}

void Aloc_memory_LINK(char **Link, char *Link_aux)
{
	*Link = (char *)malloc((strlen(Link_aux) + 1) * sizeof(char));
	strcpy(*Link, Link_aux);
}

Author Initialise(FILE *in, HashMap hashmap)
{

	char buff[255];
	char *pointer;
	Author author, author_head;

	author = NULL;
	author_head = NULL;

	Album album;
	album = NULL;

	while(fgets(buff, 255, in)) {
  		pointer = strtok (buff,"@");
 		author = Create_Structure_Author(pointer);

 		pointer = strtok (NULL, "@");
 		album = Create_Structure_Album(pointer);

 		pointer = strtok (NULL, "@");
 		Aloc_memory_LINK(&(album->LINK_YOUTUBE), pointer);

 		pointer = strtok (NULL, "@");
 		album->mark_album = atoi(pointer);
 		author->album = album;

 		push_HashMap(hashmap, author);
 		Adauga_autor(&author_head, author);

 	}
 	return author_head;
}

#endif
