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
}
