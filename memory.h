// memory.h - Deklarasi untuk manajemen memori
// Berkas ini berisi fungsionalitas untuk mengelola memori secara dinamis,
// seperti mengalokasikan, membebaskan, dan mengubah ukuran array.

#ifndef clox_memory_h
#define clox_memory_h

#include "common.h"

// Makro untuk menghitung kapasitas baru untuk array yang sedang tumbuh.
// Jika kapasitas lama kurang dari 8, kapasitas baru akan menjadi 8.
// Jika tidak, kapasitas baru akan menjadi dua kali lipat dari kapasitas lama.
#define GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (capacity) * 2)

// Makro untuk mengubah ukuran array (bisa untuk menumbuhkan atau menyusutkan).
// Ini menggunakan fungsi 'reallocate' untuk menangani alokasi memori.
#define GROW_ARRAY(type, pointer, oldCount, newCount) \
    (type*)reallocate(pointer, sizeof(type) * (oldCount), sizeof(type) * (newCount))

// Makro untuk membebaskan memori yang dialokasikan untuk sebuah array.
// Ini pada dasarnya adalah pembungkus untuk 'reallocate' dengan ukuran baru 0.
#define FREE_ARRAY(type, pointer, oldCount) \
    reallocate(pointer, sizeof(type) * (oldCount),0)

// Fungsi inti untuk semua manajemen memori dinamis.
// - Jika newSize adalah 0, ini membebaskan memori.
// - Jika oldSize adalah 0, ini mengalokasikan blok memori baru.
// - Jika newSize lebih kecil atau lebih besar dari oldSize, ini menyusutkan atau menumbuhkan blok memori yang ada.
void* reallocate(void* pointer, size_t oldSize, size_t newSize);

#endif
