#ifndef HashMap_FILE
#define HashMap_FILE

HashMap Alocate_HashMap (int size, int size_occupied)
{
	HashMap hashmap = malloc(sizeof(struct HashMap));
	hashmap->v = (Autor *)malloc(size * sizeof(Autor));

	for(int i = 0; i < size; i++)
		hashmap->v[i] = NULL;

	hashmap->size = size;
	hashmap->size_occupied = size_occupied;

	return hashmap;
}

unsigned long long String_to_Sum (char *word)
{
	unsigned long long Sum = 0;

	for (int i = 0; i < strlen(word); i++)
		Sum += word[i];

	return Sum;
}
void ce_este_in_Hashmap (HashMap hashmap)
{
	for (int i = 0; i < hashmap->size; i++) {
		if (hashmap->v[i] != NULL)
			printf("%s\n", hashmap->v[i]->nume_autor);
	}
}
Autor Look_up_Author (HashMap hashmap, char *name)
{
	unsigned long long Sum = String_to_Sum(name) % hashmap->size;
	Autor aux = NULL;

	aux = hashmap->v[Sum];
	while (aux) {
		if (strcmp(name, aux->nume_autor) == 0)
			return aux;
		aux = aux->next_HashMap;
	}
	return NULL;
}
void Adauga_autor_HashMap(Autor *autor_head, Autor autor)
{

	if(!autor)
		return;

	if (!(*autor_head)) {
		*autor_head = autor;
		return;
	}

	Autor next = (*autor_head)->next_HashMap;
	Autor current = *autor_head;

	while (next) {
		if (strcmp(current->nume_autor, autor->nume_autor) == 0)
			return;
		current = next;
		next = next->next_HashMap;
	}

	if (strcmp(current->nume_autor, autor->nume_autor) == 0)
			return;
	current->next_HashMap = autor;
	autor->prev_HashMap = current;
}

void push_HashMap (HashMap hashmap, Autor autor) {
	unsigned long long number;

	number = String_to_Sum(autor->nume_autor) % hashmap->size;
	hashmap->size_occupied++;
	Adauga_autor_HashMap(&hashmap->v[number], autor);
}

void Free_HashMap (HashMap hashmap) {
	free(hashmap->v);
	free(hashmap);
}

#endif
