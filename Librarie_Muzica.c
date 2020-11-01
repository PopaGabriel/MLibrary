#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include"Structuri.h"
#include"Initializare.h"
#include"Serialise.h"
#include"HashMap.h"
#include"Delete.h"

void Tree_Album(Album album)
{
	while(album) {
		printf("\033[0;31m");
		printf("		%s: %d\n", album->nume_album, album->nota_album);
		printf("\033[0m");
		album = album->next;
	}
}

void Tree_Autor(Autor autor)
{
	while (autor) {
		printf("\033[0;32m");
		printf("%s :\n",autor->nume_autor);
		printf("\033[0m");
		Tree_Album(autor->album);
		autor = autor->next;
	}
}

void Show_author_work(Autor autor) {
	if(!autor)
		return;
	printf("\033[0;32m");
	printf("%s :\n",autor->nume_autor);
	printf("\033[0m");
	Tree_Album(autor->album);
}

void Schimba_nota_album_aux(Album album_head, Album aux_album)
{
	while (album_head) {
		if (strcmp(album_head->nume_album, aux_album->nume_album) == 0) {
			album_head->nota_album = aux_album->nota_album;
			return;
		}
		album_head = album_head->next;
	}
}

void Schimba_nota_album(Autor autor_head, Autor aux_autor)
{
	if (autor_head == NULL)
		return;
	if (aux_autor == NULL)
		return;
	while (autor_head) {
		if (strcmp(autor_head->nume_autor, aux_autor->nume_autor) == 0) {
			Schimba_nota_album_aux(autor_head->album, aux_autor->album);
			return;
		}
		autor_head = autor_head->next;
	}
	printf("Nu a fost gasit autorul");
}

void Schimba_nume_autor(Autor autor_head, char *nume)
{
	while (autor_head) {
		if (strcmp(autor_head->nume_autor, nume) == 0) {
			printf("Cu ce vrei sa il inlocuiesti ?");
			if(fgets(nume, 255, stdin))
				nume[strlen(nume) - 1] = '\0';
			else
				break;
			free(autor_head->nume_autor);
			autor_head->nume_autor = (char *)malloc((strlen(nume) + 1) * sizeof(char));
			strcpy(autor_head->nume_autor, nume);
			return;
		}
		autor_head = autor_head->next;
	}
}
void Cauta_in_interior_peste_nota(char *nume_autor, Album album_head,int nota) {
	if(album_head == NULL)
		return;
	while (album_head) {
		if(album_head->nota_album >= nota)
			printf("%s: %s: %s:%d\n", nume_autor, album_head->nume_album, album_head->LINK_YOUTUBE, album_head->nota_album);
		album_head = album_head->next;
	}
}

void Cauta_albumuri_peste_nota(Autor autor_head, int nota)
{
	if(autor_head == NULL)
		return;

	while (autor_head) {
		Cauta_in_interior_peste_nota(autor_head->nume_autor,
			autor_head->album, nota);
		autor_head = autor_head->next;
	}
}

void Schimba_LINK_aux(Album album_head, Album aux_album) {
	while (album_head) {
		if (strcmp(album_head->nume_album, aux_album->nume_album) == 0) {
			free(album_head->LINK_YOUTUBE);
			Aloc_memory_LINK(&(album_head)->LINK_YOUTUBE, aux_album->LINK_YOUTUBE);
			return;
		}
		album_head = album_head->next;
	}
}

void Schimba_LINK(Autor autor_head, Autor aux_autor)
{
	while (autor_head) {
		if (strcmp(autor_head->nume_autor, aux_autor->nume_autor) == 0) {
			Schimba_LINK_aux(autor_head->album, aux_autor->album);
			Free_Autor(aux_autor);
			return;
		}
		autor_head = autor_head->next;
	}
	printf("Autorul nu exista in lista\n");
	Free_Autor(aux_autor);
}

int main(int argc, char **argv)
{
	HashMap hashmap = NULL;
	char comanda[100], nume[255];
	int nota;
	Autor autor = NULL, aux_autor = NULL;
	Album aux_album = NULL;
	FILE *in, *out;

	in = fopen(argv[1],"r");
	out = fopen(argv[2],"w");
	hashmap = Alocate_HashMap(1024, 0);
	autor = Initialise(in, hashmap);

	while (fgets(comanda, 100, stdin)) {
		comanda[strlen(comanda)-1] = '\0';

		if (strcmp(comanda,"Show all") == 0) {
			Tree_Autor(autor);
		} else if (strcmp(comanda,"Exit") == 0) {
			Serialise(autor, out, hashmap);
			Free_Autor(autor);
			break;
		} else if (strcmp(comanda,"Adauga album") == 0) {

			printf("Ce nume are autorul/trupa?\n");

			if(fgets(nume, 255, stdin))
				nume[strlen(nume) - 1] = '\0';
			else {
				Serialise(autor, out, hashmap);
				break;
			}
			aux_autor = Creeaza_Structura_Autor(nume);

			printf("Ce nume are albumul?\n");
			if(fgets(nume, 255, stdin))
				nume[strlen(nume) - 1] = '\0';
			else {
				Serialise(autor, out, hashmap);
				break;
			}
			aux_album = Creeaza_Structura_Album(nume);

			printf("Ce link are?");
			if(fgets(nume, 255, stdin)){
				nume[strlen(nume) - 1] = '\0';
				Aloc_memory_LINK(&(aux_album)->LINK_YOUTUBE, nume);
			}
			else {
				Serialise(autor, out, hashmap);
				break;
			}

			printf("Ce nota ii dai ?\n");
			if(scanf("%d", &nota));
			else {
				Serialise(autor, out, hashmap);
				break;
			}

			aux_album->nota_album = nota;
			aux_autor->album = aux_album;

			Adauga_autor(&autor, aux_autor);

		} else if (strcmp(comanda, "Sterge album") == 0) {

			printf("Ce nume are autorul/trupa?\n");

			if(fgets(nume, 255, stdin))
			nume[strlen(nume) - 1] = '\0';
			else {
				Serialise(autor, out, hashmap);
				break;
			}

			aux_autor = Creeaza_Structura_Autor(nume);

			printf("Ce nume are albumul?\n");
			if(fgets(nume, 255, stdin))
				nume[strlen(nume) - 1] = '\0';
			else {
				Serialise(autor, out, hashmap);
				break;
			}

			aux_album = Creeaza_Structura_Album(nume);
			aux_autor->album = aux_album;
			aux_autor->album->nota_album = 0;

			Sterge_album_din_autor(&autor, aux_autor);

		} else if (strcmp(comanda, "Sterge autor") == 0) {
			printf("Ce autor vrei sa stergi?");
			if(fgets(nume, 255, stdin))
				nume[strlen(nume) - 1] = '\0';
			else {
				Serialise(autor, out, hashmap);
				break;
			}

			Sterge_autor(&autor, nume, hashmap);
		} else if (strcmp(comanda, "Schimba nota album") == 0) {

			printf("Ce autor a facut albumul?");
			if(fgets(nume, 255, stdin))
				nume[strlen(nume) - 1] = '\0';
			else {
				Serialise(autor, out, hashmap);
				break;
			}

			aux_autor = Creeaza_Structura_Autor(nume);

			printf("Ce nume are albumul?\n");
			if(fgets(nume, 255, stdin))
				nume[strlen(nume) - 1] = '\0';
			else {
				Serialise(autor, out, hashmap);
				break;
			}

			aux_album = Creeaza_Structura_Album(nume);

			printf("Ce nota ii dai de data asta ?\n");
			if(scanf("%d", &nota))
				aux_album->nota_album = nota;
			else {
				Serialise(autor, out, hashmap);
				break;
			}

			aux_autor->album = aux_album;

			Schimba_nota_album(autor, aux_autor);
			Free_Autor(aux_autor);
		} else if (strcmp(comanda, "Schimba nume autor") == 0) {

			printf("Numele carui autor vrei sa il schimbi?\n");
			if(fgets(nume, 255, stdin))
				nume[strlen(nume) - 1] = '\0';
			else {
				Serialise(autor, out, hashmap);
				break;
			}

			Schimba_nume_autor(autor, nume);
		} else if (strcmp(comanda, "Arata albumuri peste") == 0) {

			printf("Peste ce nota vrei");
			if (scanf("%d",&nota)) {
				Cauta_albumuri_peste_nota(autor, nota);
			} else {
				Serialise(autor, out, hashmap);
				break;
			}
		} else if (strcmp(comanda, "Schimba link album") == 0) {

			printf("Cum se numeste autorul care a facut albumul?\n");
			if(fgets(nume, 255, stdin))
				nume[strlen(nume) - 1] = '\0';
			else {
				Serialise(autor, out, hashmap);
				break;
			}
			aux_autor = Creeaza_Structura_Autor(nume);

			printf("LINKUL carui album vrei sa il schimbi?\n");
			if(fgets(nume, 255, stdin))
				nume[strlen(nume) - 1] = '\0';
			else {
				Serialise(autor, out, hashmap);
				break;
			}
			aux_album = Creeaza_Structura_Album(nume);

			printf("Care este noul LINK ?\n");
			if(fgets(nume, 255, stdin)) {
				nume[strlen(nume) - 1] = '\0';
				Aloc_memory_LINK(&(aux_album)->LINK_YOUTUBE, nume);
			}
			else {
				Serialise(autor, out, hashmap);
				break;
			}
			aux_autor->album = aux_album;
			Schimba_LINK(autor, aux_autor);

		} else if(strcmp(comanda, "Look up author") == 0) {
			if(fgets(nume, 255, stdin)) {
				nume[strlen(nume) - 1] = '\0';
				Autor aux = Look_up_Author(hashmap, nume);
				if(aux) {
					Show_author_work(aux);
				}else
					printf("The author could not be found\n");
			}
		}
	}

	fclose(in);
	fclose(out);
}
