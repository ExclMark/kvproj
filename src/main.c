#include <stdio.h>
#include <kv.h>

int main() {
	kv_t *table = kv_init(3);

	printf("table pointer : %p\n", table);
	printf("table capacity: %ld\n", table->capacity);

	kv_put(table, "lol", "kekw");
	kv_put(table, "pog", "kappa");

	printf("\ntable content:\n");
	for (int i = 0; i < table->capacity; i++) {
		if (table->entries[i].key) {
			printf("[%d] %s: %s\n", i, table->entries[i].key, table->entries[i].value);
		}
	}

	char *val1 = kv_get(table, "lol");
	char *val2 = kv_get(table, "non");

	printf("\nkv_get test:\nlol = %s\n", val1);
	printf("non = %s\n", val2);

	kv_delete(table, "lol");
	val1 = NULL;
	val1 = kv_get(table, "lol");

	printf("\nkv_delete test:\nlol = %s\n", val1);
	printf("non = %s\n", val2);
}
