#ifndef Serialise_FILE
#define Serialise_FILE

void Scrie_albumuri(char *nume_autor, Album album_head, FILE *out)
{
	while (album_head) {
		fprintf(out ,"%s@%s@%s@%d\n", nume_autor, album_head->nume_album, album_head->LINK_YOUTUBE ,album_head->nota_album);
		album_head = album_head->next;
	}
}
void Serialise(Autor autor_head, FILE *out, HashMap hashmap)
{
	while (autor_head) {
		Scrie_albumuri(autor_head->nume_autor, autor_head->album, out);
		autor_head = autor_head->next;
	}
	Free_HashMap(hashmap);
}

#endif
