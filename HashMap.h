#ifndef HashMap_FILE
#define HashMap_FILE

unsigned long long String_to_Sum (char *word)
{
	unsigned long long Sum = 0;

	for (int i = 0; i < strlen(word); i++)
		Sum += word[i];

	return Sum;
}

void Free_HashMap (HashMap hashmap)
{
	free(hashmap->v);
	free(hashmap);
}

HashMap Alocate_HashMap (int size)
{
	HashMap hashmap = malloc(sizeof(struct HashMap));
	hashmap->v = (Author *)malloc(size * sizeof(Author));

	for(int i = 0; i < size; i++)
		hashmap->v[i] = NULL;

	hashmap->size = size;
	hashmap->size_occupied = 0;

	return hashmap;
}
void Adauga_author_HashMap(Author *author_head, Author author)
{

	if(!author)
		return;

	if (!(*author_head)) {
		*author_head = author;
		return;
	}

	Author next = (*author_head)->next_HashMap;
	Author current = *author_head;

	while (next) {
		if (strcmp(current->name_author, author->name_author) == 0)
			return;
		current = next;
		next = next->next_HashMap;
	}

	if (strcmp(current->name_author, author->name_author) == 0)
			return;
	current->next_HashMap = author;
	author->prev_HashMap = current;
}
void push_HashMap (HashMap hashmap, Author author) {
	unsigned long long number;

	number = String_to_Sum(author->name_author) % hashmap->size;
	hashmap->size_occupied++;
	Adauga_author_HashMap(&hashmap->v[number], author);
}

void ce_este_in_Hashmap (HashMap hashmap)
{
	for (int i = 0; i < hashmap->size; i++) {
		if (hashmap->v[i] != NULL)
			printf("%s\n", hashmap->v[i]->name_author);
	}
}
Author Look_up_Author (HashMap hashmap, char *name)
{
	unsigned long long Sum = String_to_Sum(name) % hashmap->size;
	Author aux = NULL;

	aux = hashmap->v[Sum];
	while (aux) {
		if (strcmp(name, aux->name_author) == 0)
			return aux;
		aux = aux->next_HashMap;
	}
	return NULL;
}
HashMap Realloc_HashMap(HashMap hashmap)
{
	unsigned long long new_size = hashmap->size << 1;
	HashMap hashmap_aux = NULL;
	hashmap_aux = Alocate_HashMap(new_size);

	for (int i = 0; i < hashmap->size; i++)
		if (hashmap->v[i])
			push_HashMap(hashmap_aux, hashmap->v[i]);
	Free_HashMap(hashmap);
	return hashmap_aux;
}

HashMap check_memory_HashMap(HashMap hashmap) {
	if ((float)(hashmap->size / hashmap->size_occupied) > 0.7)
		return Realloc_HashMap(hashmap);
	return hashmap;
}

#endif
