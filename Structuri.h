#ifndef Structuri_FILE
#define Structuri_FILE

typedef struct Album
{

	char *LINK_YOUTUBE;

	char *nume_album;

	short nota_album;

	struct Album *next;

} *Album;

typedef struct Autor
{
	char *nume_autor;

	Album album;

	struct Autor *next;

	struct Autor *next_HashMap;

	struct Autor *prev_HashMap;

} *Autor;

typedef struct HashMap
{

	unsigned long long size;

	unsigned long long size_occupied;

	Autor *v;

} *HashMap;

#endif
