#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"Structuri.h"
#include"Free.h"
#include"Initializare.h"
#include"Serializare.h"

void Tree_Album(Album album)
{
	while(album != NULL ) {
		printf("\033[0;31m");
		printf("		%s: %d\n", album->nume_album, album->nota_album);
		printf("\033[0m");
		album = album->next;
	}
}

void Tree_Autor(Autor autor)
{
	while (autor != NULL) {
		printf("\033[0;32m");
		printf("%s :\n",autor->nume_autor);
		printf("\033[0m");
		Tree_Album(autor->album);
		autor = autor->next;
	}
}

void Sterge_albumul(Album *album_head, Album album)
{
	if (*album_head == NULL)
		return;
	if (album == NULL)
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

void Sterge_album_din_autor(Autor *autor_head, Autor autor)
{
	if (*autor_head == NULL)
		return;
	if (autor == NULL)
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
			//Daca autorul nu mai are albumuri
			//Va fi scos din lista
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
	//Daca nu a fost gasit
	//Eliberam memoria si anuntam user-ul
	Free_Autor(autor);
	printf("Albumul nu a fost gasit, sau nu a existat in lista");
}

void Sterge_autor(Autor *autor_head, char *nume)
{
	if ((*autor_head) == NULL)
		return;

	Autor next, prev;
	next = (*autor_head)->next;
	prev = *autor_head;

	if (strcmp((*autor_head)->nume_autor, nume) == 0) {
		if ((*autor_head)->next == NULL) {
			Free_Autor((*autor_head));
			return;
		} else {
			*autor_head = next;
			prev->next = NULL;
			Free_Autor(prev);
			return;
		}
	}

	while (next) {
		if (strcmp(next->nume_autor, nume) == 0) {
			prev->next = next->next;
			next->next = NULL;
			Free_Autor(next);
			return;
		}
		prev = next;
		next = next->next;
	}
	if (strcmp(prev->nume_autor, nume) == 0)
		Free_Autor(prev);
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
			Aloca_memorie_LINK(&(album_head)->LINK_YOUTUBE, aux_album->LINK_YOUTUBE);
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
	char comanda[100], nume[255];
	int nota;
	Autor autor = NULL, aux_autor = NULL;
	Album aux_album = NULL;
	FILE *in, *out;

	in = fopen(argv[1],"r");
	out = fopen(argv[2],"w");
	autor = Citeste_fisier(in);

	while (fgets(comanda, 100, stdin)) {
		comanda[strlen(comanda)-1] = '\0';

		if (strcmp(comanda,"Show all") == 0) {
			Tree_Autor(autor);
		} else if (strcmp(comanda,"Exit") == 0) {
			Serializeaza(autor, out);
			Free_Autor(autor);
			break;
		} else if (strcmp(comanda,"Adauga album") == 0) {

			printf("Ce nume are autorul/trupa?\n");

			if(fgets(nume, 255, stdin))
				nume[strlen(nume) - 1] = '\0';
			else {
				Serializeaza(autor, out);
				break;
			}
			aux_autor = Creeaza_Structura_Autor(nume);

			printf("Ce nume are albumul?\n");
			if(fgets(nume, 255, stdin))
				nume[strlen(nume) - 1] = '\0';
			else {
				Serializeaza(autor, out);
				break;
			}
			aux_album = Creeaza_Structura_Album(nume);

			printf("Ce link are?");
			if(fgets(nume, 255, stdin)){
				nume[strlen(nume) - 1] = '\0';
				Aloca_memorie_LINK(&(aux_album)->LINK_YOUTUBE, nume);
			}
			else {
				Serializeaza(autor, out);
				break;
			}

			printf("Ce nota ii dai ?\n");
			if(scanf("%d", &nota)){}
			else {
				Serializeaza(autor, out);
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
				Serializeaza(autor, out);
				break;
			}

			aux_autor = Creeaza_Structura_Autor(nume);

			printf("Ce nume are albumul?\n");
			if(fgets(nume, 255, stdin))
				nume[strlen(nume) - 1] = '\0';
			else {
				Serializeaza(autor, out);
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
				Serializeaza(autor, out);
				break;
			}

			Sterge_autor(&autor, nume);
		} else if (strcmp(comanda, "Schimba nota album") == 0) {

			printf("Ce autor a facut albumul?");
			if(fgets(nume, 255, stdin))
				nume[strlen(nume) - 1] = '\0';
			else {
				Serializeaza(autor, out);
				break;
			}

			aux_autor = Creeaza_Structura_Autor(nume);

			printf("Ce nume are albumul?\n");
			if(fgets(nume, 255, stdin))
				nume[strlen(nume) - 1] = '\0';
			else {
				Serializeaza(autor, out);
				break;
			}

			aux_album = Creeaza_Structura_Album(nume);

			printf("Ce nota ii dai de data asta ?\n");
			if(scanf("%d", &nota))
				aux_album->nota_album = nota;
			else {
				Serializeaza(autor, out);
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
				Serializeaza(autor, out);
				break;
			}

			Schimba_nume_autor(autor, nume);
		} else if (strcmp(comanda, "Arata albumuri peste") == 0) {

			printf("Peste ce nota vrei");
			if (scanf("%d",&nota)) {
				Cauta_albumuri_peste_nota(autor, nota);
			} else {
				Serializeaza(autor, out);
				break;
			}
		} else if (strcmp(comanda, "Schimba link album") == 0) {

			printf("Cum se numeste autorul care a facut albumul?\n");
			if(fgets(nume, 255, stdin))
				nume[strlen(nume) - 1] = '\0';
			else {
				Serializeaza(autor, out);
				break;
			}
			aux_autor = Creeaza_Structura_Autor(nume);

			printf("LINKUL carui album vrei sa il schimbi?\n");
			if(fgets(nume, 255, stdin))
				nume[strlen(nume) - 1] = '\0';
			else {
				Serializeaza(autor, out);
				break;
			}
			aux_album = Creeaza_Structura_Album(nume);

			printf("Care este noul LINK ?\n");
			if(fgets(nume, 255, stdin)){
				nume[strlen(nume) - 1] = '\0';
				Aloca_memorie_LINK(&(aux_album)->LINK_YOUTUBE, nume);
			}
			else {
				Serializeaza(autor, out);
				break;
			}
			aux_autor->album = aux_album;
			Schimba_LINK(autor, aux_autor);
		}
	}

	fclose(in);
	fclose(out);
}
