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
		free(aux->name_album);
		free(aux);
	}
}

void Free_Author (Author author)
{
	Author aux;
	aux = NULL;

	while (author) {
		aux = author;
		author = author->next;
		Free_Album(aux->album);
		free(aux->name_author);
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

	if (strcmp((*album_head)->name_album, album->name_album) == 0) {
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
		if (strcmp(next->name_album, album->name_album) == 0) {
			prev->next = next->next;
			next->next = NULL;
			Free_Album(next);
			return;
		}
		prev = prev->next;
		next = next->next;
	}

	if (strcmp(prev->name_album, album->name_album) == 0)
		Free_Album(prev);
}

void Delete_album_from_author (Author *author_head, Author author)
{
	if (!(*author_head))
		return;

	if (!author)
		return;

	Author next, prev;
	prev = *author_head;
	next = (*author_head)->next;

	if (strcmp((*author_head)->name_author, author->name_author) == 0) {
		if ((*author_head)->next == NULL) {
			Sterge_albumul(&(*author_head)->album, author->album);
			if ((*author_head)->album == NULL) {
				Free_Author(prev);
				return;
			}
		} else {
			Sterge_albumul(&(*author_head)->album, author->album);
			if ((*author_head)->album == NULL) {
				*author_head = next;
				prev->next = NULL;
				Free_Author(prev);
				return;
			}
		}
		Free_Author(author);
	}

	while (next) {
		if (strcmp(next->name_author, author->name_author) == 0) {
			Sterge_albumul(&(next)->album, author->album);
			if (next->album == NULL) {
				prev->next = next->next;
				next->next = NULL;
				Free_Author(next);
			}
			Free_Author(author);
			return;
		}
		prev = next;
		next = next->next;
	}

	if(strcmp(prev->name_author, author->name_author) == 0) {
		Sterge_albumul(&(prev)->album, author->album);
		if (prev->album == NULL)
			Free_Author(prev);
		Free_Author(author);
	}
	Free_Author(author);
	printf("The album was not found, or it didn't exist in the list");
}

void Delete_author(Author *author_head, char *nume, HashMap hashmap)
{
	if ((*author_head) == NULL)
		return;

	unsigned long long number = String_to_Sum(nume);

	Author next, prev;
	next = (*author_head)->next;
	prev = *author_head;

	if (strcmp((*author_head)->name_author, nume) == 0) {
		if ((*author_head)->next == NULL) {

			if ((*author_head)->prev_HashMap) {
				(*author_head)->prev_HashMap = (*author_head)->next_HashMap;
			} else {
				hashmap->v[number] = (*author_head)->next_HashMap;
			}

			Free_Author((*author_head));
			return;
		} else {
			*author_head = next;
			prev->next = NULL;

			if (prev->prev_HashMap) {
				prev->prev_HashMap = prev->next_HashMap;
			} else {
				hashmap->v[number] = prev->next_HashMap;
			}

			Free_Author(prev);
			return;
		}
	}

	while (next) {
		if (strcmp(next->name_author, nume) == 0) {
			prev->next = next->next;
			next->next = NULL;

			if (next->prev_HashMap) {
				next->prev_HashMap = next->next_HashMap;
			} else {
				hashmap->v[number] = next->next_HashMap;
			}

			Free_Author(next);
			return;
		}
		prev = next;
		next = next->next;
	}
	if (strcmp(prev->name_author, nume) == 0) {
		if (prev->prev_HashMap) {
				prev->prev_HashMap = prev->next_HashMap;
			} else {
				hashmap->v[number] = prev->next_HashMap;
			}
		Free_Author(prev);
	}
}
#endif
