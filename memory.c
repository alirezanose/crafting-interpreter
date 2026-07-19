// memory.c - Implementasi untuk manajemen memori

#include "memory.h"

#include <stdlib.h>

// Fungsi inti untuk semua manajemen memori dinamis.
void* reallocate(void *pointer, size_t oldSize, size_t newSize) {
    // Jika newSize adalah 0, kita ingin membebaskan memori.
    if (newSize == 0) {
        free(pointer);
        return NULL;
    }

    // Jika newSize bukan 0, kita menggunakan realloc dari C.
    // realloc menangani alokasi (jika pointer adalah NULL),
    // penyusutan, dan pertumbuhan blok memori.
    void *result = realloc(pointer, newSize);

    // Jika realloc gagal mengalokasikan memori (misalnya, karena kehabisan memori),
    // kita hentikan program karena tidak ada cara untuk melanjutkan.
    if (result == NULL) exit(1);
    
    return result;
}
