/**
 * the hashtable funxtions
 * @file: hashtable.c
 * @author: ist1113628 (Tiago Nogueira)
 */

#include "./../libraries/init.h"

/** get the index of the key on the table **/
// @param key		what the hash depends
unsigned int hashFunction(const char *key) {
	unsigned int hash = 0;
	while (*key) {
		hash += key[0];
		key++;
		// is the sum of all caracter of the userame
	}
	return hash % TABLESIZE;
}

/** insert the index of the innoc on the hash table **/
// @param sys		system information
// @param key		key of hash table
void insert(Sys *sys, const char *key) {
	unsigned int index = hashFunction(key);
	int cnt = sys->table[index].cnt;
	// resize the alocated memory
	if (cnt)
		sys->table[index].index = realloc(
			sys->table[index].index, sizeof(int) * (cnt + 1));
	// if first hash allocate memory
	else
		sys->table[index].index = malloc(sizeof(int) * (cnt + 1));
	sys->table[index].index[cnt] = sys->cnt_user;
	sys->table[index].cnt++;
}

/** delete index of innoc on hash table **/
// @param sys		system information
// @param i			index of innoc
void delete_hash(Sys *sys, int i) {
	unsigned int index = hashFunction(sys->user[i].name);
	for (int j = 0; j < sys->table[index].cnt; j++) {
		if (sys->table[index].index[j] == i) {
			// if it is the laste one free the allocated memory
			if (sys->table[index].cnt == 1)
				free(sys->table[index].index);
			// if more than one remove only the index
			memmove(&sys->table[index].index[j],
				&sys->table[index].index[j + 1],
				(sys->table[index].cnt - j - 1) * sizeof(int));
			sys->table[index].cnt--;
			break;
		}
	}
}

