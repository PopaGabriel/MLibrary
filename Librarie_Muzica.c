#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"Structuri.h"
#include"HashMap.h"
#include"Initializare.h"
#include"Serialise.h"
#include"Delete.h"

void Tree_Album(Album album)
{
	while(album) {
		printf("\033[0;31m");
		printf("		%s: %d\n", album->name_album, album->mark_album);
		printf("\033[0m");
		album = album->next;
	}
}

void Tree_Autor(Author author)
{
	while (author) {
		printf("\033[0;32m");
		printf("%s :\n",author->name_author);
		printf("\033[0m");
		Tree_Album(author->album);
		author = author->next;
	}
}

void Show_author_work(Author author) {
	if(!author)
		return;
	printf("\033[0;32m");
	printf("%s :\n",author->name_author);
	printf("\033[0m");
	Tree_Album(author->album);
}

void Change_mark_album_aux(Album album_head, Album aux_album)
{
	while (album_head) {
		if (strcmp(album_head->name_album, aux_album->name_album) == 0) {
			album_head->mark_album = aux_album->mark_album;
			return;
		}
		album_head = album_head->next;
	}
}

void Change_mark_album(Author author_head, Author aux_author)
{
	if (author_head == NULL)
		return;
	if (aux_author == NULL)
		return;
	while (author_head) {
		if (strcmp(author_head->name_author, aux_author->name_author) == 0) {
			Change_mark_album_aux(author_head->album, aux_author->album);
			return;
		}
		author_head = author_head->next;
	}
	printf("Nu a fost gasit autorul");
}

void Change_name_autor(Author author_head, char *name)
{
	while (author_head) {
		if (strcmp(author_head->name_author, name) == 0) {
			printf("Cu ce vrei sa il inlocuiesti ?");
			if(fgets(name, 255, stdin))
				name[strlen(name) - 1] = '\0';
			else
				break;
			free(author_head->name_author);
			author_head->name_author = (char *)malloc((strlen(name) + 1) * sizeof(char));
			strcpy(author_head->name_author, name);
			return;
		}
		author_head = author_head->next;
	}
}
void Cauta_in_interior_peste_mark(char *name_author, Album album_head,int mark) {
	if(album_head == NULL)
		return;
	while (album_head) {
		if(album_head->mark_album >= mark)
			printf("%s: %s: %s:%d\n", name_author, album_head->name_album, album_head->LINK_YOUTUBE, album_head->mark_album);
		album_head = album_head->next;
	}
}

void Cauta_albumuri_peste_mark(Author author_head, int mark)
{
	if(author_head == NULL)
		return;

	while (author_head) {
		Cauta_in_interior_peste_mark(author_head->name_author,
			author_head->album, mark);
		author_head = author_head->next;
	}
}

void Change_LINK_aux(Album album_head, Album aux_album) {
	while (album_head) {
		if (strcmp(album_head->name_album, aux_album->name_album) == 0) {
			free(album_head->LINK_YOUTUBE);
			Aloc_memory_LINK(&(album_head)->LINK_YOUTUBE, aux_album->LINK_YOUTUBE);
			return;
		}
		album_head = album_head->next;
	}
}

void Change_LINK(Author author_head, Author aux_author)
{
	while (author_head) {
		if (strcmp(author_head->name_author, aux_author->name_author) == 0) {
			Change_LINK_aux(author_head->album, aux_author->album);
			Free_Author(aux_author);
			return;
		}
		author_head = author_head->next;
	}
	printf("Autorul nu exista in lista\n");
	Free_Author(aux_author);
}

int main(int argc, char **argv)
{
	HashMap hashmap = NULL;
	char command[100], name[255];
	int mark;
	Author author = NULL, aux_author = NULL;
	Album aux_album = NULL;
	FILE *in, *out;

	in = fopen(argv[1],"r");
	out = fopen(argv[2],"w");
	hashmap = Alocate_HashMap(1024);
	author = Initialise(in, hashmap);

	while (fgets(command, 100, stdin)) {
		command[strlen(command)-1] = '\0';
		hashmap = check_memory_HashMap(hashmap);

		if (strcmp(command,"Show all") == 0) {
			Tree_Autor(author);
		} else if (strcmp(command,"Exit") == 0) {
			Serialise(author, out, hashmap);
			Free_Author(author);
			break;
		} else if (strcmp(command,"Add Band") == 0) {

			printf("What is the name of the band/singer\n");

			if(fgets(name, 255, stdin))
				name[strlen(name) - 1] = '\0';
			else
				continue;
			aux_author = Create_Structure_Author(name);

			printf("What's the name of the album?\n");
			if(fgets(name, 255, stdin))
				name[strlen(name) - 1] = '\0';
			else
				continue;
			aux_album = Create_Structure_Album(name);

			printf("What is its link?");
			if(fgets(name, 255, stdin)){
				name[strlen(name) - 1] = '\0';
				Aloc_memory_LINK(&(aux_album)->LINK_YOUTUBE, name);
			}
			else
				continue;

			printf("How much did you enjoy the album on a scale from one to ten ?\n");
			if(scanf("%d", &mark));
			else
				continue;

			aux_album->mark_album = mark;
			aux_author->album = aux_album;

			Adauga_autor(&author, aux_author);

		} else if (strcmp(command, "Delete Album") == 0) {

			printf("What is the name of the band/singer?\n");

			if(fgets(name, 255, stdin))
			name[strlen(name) - 1] = '\0';
			else
				continue;

			aux_author = Create_Structure_Author(name);

			printf("What is the name of the album?\n");
			if(fgets(name, 255, stdin))
				name[strlen(name) - 1] = '\0';
			else {
				Free_Author(aux_author);
				continue;
			}

			aux_album = Create_Structure_Album(name);
			aux_author->album = aux_album;
			aux_author->album->mark_album = 0;

			Delete_album_from_author(&author, aux_author);

		} else if (strcmp(command, "Delete Author") == 0) {
			printf("What author do you want to delete?");
			if(fgets(name, 255, stdin))
				name[strlen(name) - 1] = '\0';
			else
				continue;

			Delete_author(&author, name, hashmap);
		} else if (strcmp(command, "Change mark album") == 0) {

			printf("Who made this album?");
			if(fgets(name, 255, stdin))
				name[strlen(name) - 1] = '\0';
			else
				continue;

			aux_author = Create_Structure_Author(name);

			printf("What is the name of the album?\n");
			if(fgets(name, 255, stdin))
				name[strlen(name) - 1] = '\0';
			else {
				Free_Author(aux_author);
				continue;
			}

			aux_album = Create_Structure_Album(name);

			printf("How much did you enjoy the album on a scale from one to ten ?\n");
			if(scanf("%d", &mark))
				aux_album->mark_album = mark;
			else {
				Free_Author(aux_author);
				continue;
			}

			aux_author->album = aux_album;

			Change_mark_album(author, aux_author);
			Free_Author(aux_author);
		} else if (strcmp(command, "Change name author") == 0) {

			printf("What is the authors name?\n");
			if(fgets(name, 255, stdin))
				name[strlen(name) - 1] = '\0';
			else
				continue;

			Change_name_autor(author, name);
		} else if (strcmp(command, "Show albums over") == 0) {

			printf("Over what mark do you want to see the album?");
			if (scanf("%d",&mark)) {
				Cauta_albumuri_peste_mark(author, mark);
			} else {
				continue;
			}
		} else if (strcmp(command, "Change link album") == 0) {

			printf("What is the name of the author?\n");
			if(fgets(name, 255, stdin))
				name[strlen(name) - 1] = '\0';
			else
				continue;
			aux_author = Create_Structure_Author(name);

			printf("What is the name of the album??\n");
			if(fgets(name, 255, stdin))
				name[strlen(name) - 1] = '\0';
			else {
				Free_Author(aux_author);
				continue;
			}
			aux_album = Create_Structure_Album(name);

			printf("What is the new link?\n");
			if(fgets(name, 255, stdin)) {
				name[strlen(name) - 1] = '\0';
				Aloc_memory_LINK(&(aux_album)->LINK_YOUTUBE, name);
			}
			else {
				Free_Author(aux_author);
				continue;
			}
			aux_author->album = aux_album;
			Change_LINK(author, aux_author);

		} else if(strcmp(command, "Look up author") == 0) {
			printf("What is the name of the author?\n");
			if(fgets(name, 255, stdin)) {
				name[strlen(name) - 1] = '\0';
				Author aux = Look_up_Author(hashmap, name);
				if(aux) {
					Show_author_work(aux);
				}else
					printf("The author could not be found\n");
			}
		}
	}
	printf("\nHave a nice day\n");
	fclose(in);
	fclose(out);
}
