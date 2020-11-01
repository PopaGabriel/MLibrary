#include"Structuri.h"

#ifndef Delete_FILE
#define Delete_FILE

void Free_Album (Album album)
{
	Album aux;
	aux = NULL;

	while (album != NULL) {
		aux = album;
		album = album->next;
		free(aux->LINK_YOUTUBE);
		free(aux->nume_album);
		free(aux);
	}
}

void Free_Autor (Autor autor)
{
	Autor aux;
	aux = NULL;

	while (autor) {
		aux = autor;
		autor = autor->next;
		Free_Album(aux->album);
		free(aux->nume_autor);
		free(aux);
	}
}
void Sterge_albumul (Album *album_head, Album album)
{
	if (!(*album_head))
		return;

	if (!album)
		return;

	Album next, prev;
	next = (*album_head)->next;
	prev = *album_head;

	if (strcmp((*album_head)->nume_album, album->nume_album) == 0) {
		if ((*album_head)->next == NULL) {
			*album_head = NULL;
			Free_Album(prev);
			return;
		} else {
			*album_head = next;
			prev->next = NULL;
			Free_Album(prev);
			return;
		}
	}

	while (next) {
		if (strcmp(next->nume_album, album->nume_album) == 0) {
			prev->next = next->next;
			next->next = NULL;
			Free_Album(next);
			return;
		}
		prev = prev->next;
		next = next->next;
	}

	if (strcmp(prev->nume_album, album->nume_album) == 0)
		Free_Album(prev);
}

void Sterge_album_din_autor (Autor *autor_head, Autor autor)
{
	if (!(*autor_head))
		return;

	if (!autor)
		return;

	Autor next, prev;
	prev = *autor_head;
	next = (*autor_head)->next;

	if (strcmp((*autor_head)->nume_autor, autor->nume_autor) == 0) {
		if ((*autor_head)->next == NULL) {
			Sterge_albumul(&(*autor_head)->album, autor->album);
			if ((*autor_head)->album == NULL) {
				Free_Autor(prev);
				return;
			}
		} else {
			Sterge_albumul(&(*autor_head)->album, autor->album);
			if ((*autor_head)->album == NULL) {
				*autor_head = next;
				prev->next = NULL;
				Free_Autor(prev);
				return;
			}
		}
		Free_Autor(autor);
	}

	while (next) {
		if (strcmp(next->nume_autor, autor->nume_autor) == 0) {
			Sterge_albumul(&(next)->album, autor->album);
			if (next->album == NULL) {
				prev->next = next->next;
				next->next = NULL;
				Free_Autor(next);
			}
			Free_Autor(autor);
			return;
		}
		prev = next;
		next = next->next;
	}

	if(strcmp(prev->nume_autor, autor->nume_autor) == 0) {
		Sterge_albumul(&(prev)->album, autor->album);
		if (prev->album == NULL)
			Free_Autor(prev);
		Free_Autor(autor);
	}
	Free_Autor(autor);
	printf("The album was not found, or it didn't exist in the list");
}

void Sterge_autor(Autor *autor_head, char *nume, HashMap hashmap)
{
	if ((*autor_head) == NULL)
		return;

	unsigned long long number = String_to_Sum(nume);

	Autor next, prev;
	next = (*autor_head)->next;
	prev = *autor_head;

	if (strcmp((*autor_head)->nume_autor, nume) == 0) {
		if ((*autor_head)->next == NULL) {

			if ((*autor_head)->prev_HashMap) {
				(*autor_head)->prev_HashMap = (*autor_head)->next_HashMap;
			} else {
				hashmap->v[number] = (*autor_head)->next_HashMap;
			}

			Free_Autor((*autor_head));
			return;
		} else {
			*autor_head = next;
			prev->next = NULL;

			if (prev->prev_HashMap) {
				prev->prev_HashMap = prev->next_HashMap;
			} else {
				hashmap->v[number] = prev->next_HashMap;
			}

			Free_Autor(prev);
			return;
		}
	}

	while (next) {
		if (strcmp(next->nume_autor, nume) == 0) {
			prev->next = next->next;
			next->next = NULL;

			if (next->prev_HashMap) {
				next->prev_HashMap = next->next_HashMap;
			} else {
				hashmap->v[number] = next->next_HashMap;
			}

			Free_Autor(next);
			return;
		}
		prev = next;
		next = next->next;
	}
	if (strcmp(prev->nume_autor, nume) == 0) {
		if (prev->prev_HashMap) {
				prev->prev_HashMap = prev->next_HashMap;
			} else {
				hashmap->v[number] = prev->next_HashMap;
			}
		Free_Autor(prev);
	}
}
#endif
