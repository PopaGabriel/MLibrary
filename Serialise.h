#ifndef Serialise_FILE
#define Serialise_FILE

void Scrie_albumuri(char *name_author, Album album_head, FILE *out)
{
	while (album_head) {
		fprintf(out ,"%s@%s@%s@%d\n", name_author, album_head->name_album, album_head->LINK_YOUTUBE ,album_head->mark_album);
		album_head = album_head->next;
	}
}
void Serialise(Author author_head, FILE *out, HashMap hashmap)
{
	while (author_head) {
		Scrie_albumuri(author_head->name_author, author_head->album, out);
		author_head = author_head->next;
	}
	Free_HashMap(hashmap);
}

#endif
