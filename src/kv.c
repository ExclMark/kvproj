#include <kv.h>
#include <string.h>
#include <stdlib.h>

#define TOMBSTONE 0x1

size_t hash(char* val, int capacity) {
	size_t hash = 0x1337133713371337;

	while (*val) {
		hash ^= *val;
		hash = hash << 8;
		hash += *val;

		val++;
	}

	return hash % capacity;
}

/*
	params:
	- db: pointer to the db
	- key: pointer to the key value
	- value: pointer to the value itself
	returns:
	index of the key, 
	-1 on error,
	-2 on not found
*/
int kv_put(kv_t *db, char *key, char *value) {
	if (!db || !key || !value) return -1;

	size_t idx = hash(key, db->capacity);

	for (int i = 0; i < db->capacity - 1; i++) {
		size_t real_idx = (idx + i) % db->capacity;

		kv_entry_t *entry = &db->entries[real_idx];

		// key is alr set, update
		if (entry->key && entry->key != (void*)TOMBSTONE && !strcmp(entry->key, key)) {
			char *new_val = strdup(value);
			if (!new_val) return -1;
			entry->value = new_val;

			return 0;
		}

		// slot is NULL or TOMBSTONE
		if (!entry->key || entry->key == (void*)TOMBSTONE) {
			char *new_val = strdup(value);
			char *new_key = strdup(key);

			if (!new_val || !new_key) {
				free(new_key);
				free(new_val);
				return -1;
			}

			entry->value = new_val;
			entry->key = new_key;
			db->count++;

			return 0;
		}
	}

	return -2;
}

kv_t *kv_init(size_t capacity) {
	if (capacity == 0) return NULL;

	kv_t *table = malloc(sizeof(kv_t));
	if (table == NULL) return NULL;

	table->capacity = capacity;
	table->count = 0;

	table->entries = calloc(sizeof(kv_entry_t), capacity);
	if (table->entries == NULL) return NULL;

	return table;
}
