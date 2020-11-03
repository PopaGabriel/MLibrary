#ifndef Structuri_FILE
#define Structuri_FILE

typedef struct Album
{

	char *LINK_YOUTUBE;

	char *name_album;

	short mark_album;

	struct Album *next;

} *Album;

typedef struct Author
{
	char *name_author;

	Album album;

	struct Author *next;

	struct Author *next_HashMap;

	struct Author *prev_HashMap;

} *Author;

typedef struct HashMap
{

	unsigned long long size;

	unsigned long long size_occupied;

	Author *v;

} *HashMap;

#endif
