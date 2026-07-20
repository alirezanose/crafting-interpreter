// chunk.c - Implementasi untuk struktur data 'Chunk'

#include <stdlib.h>
#include "chunk.h"
#include "memory.h"

// Menginisialisasi sebuah chunk ke keadaan kosong.
void initChunk(Chunk *chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    chunk->line = NULL;
    initValueArray(chunk->constants);
}

// Menambahkan sebuah byte ke akhir chunk.
void writeChunk(Chunk *chunk, uint8_t byte, int line) {
    // Periksa apakah array bytecode memiliki cukup ruang.
    // Jika tidak, kita perlu mengalokasikan lebih banyak memori.
    if (chunk->capacity < chunk->count + 1) {
        int oldCapacity = chunk->capacity;
        // Hitung kapasitas baru.
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        // Alokasikan ulang array ke ukuran yang lebih besar.
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);

        chunk->lines = GROW_ARRAY(int, chunk->lines, oldCapacity, chunk->capacity);
    }

    // Simpan byte di akhir array.
    chunk->code[chunk->count] = byte;
    chunk->lines[chunk->count] = line;
    // Naikkan jumlah byte yang digunakan.
    chunk->count++;
}

// Membebaskan memori yang digunakan oleh chunk.
void freeChunk(Chunk *chunk) {
    // Bebaskan array bytecode.
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(uint8_t, chunk->line, chunk->capacity);
    freeValueArray(chunk->constants);
    // Atur ulang chunk ke keadaan awalnya yang kosong untuk mencegah 'use-after-free'.
    initChunk(chunk);
}

int addConstant(Chunk *chunk, Value value) {
    writeValueArray(chunk->constants, value);
    return chunk->constants->count - 1;
}