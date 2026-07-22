// chunk.c - Implementasi untuk struktur data 'Chunk'

#include <stdlib.h>
#include "chunk.h"
#include "memory.h"

// Menginisialisasi sebuah chunk ke keadaan kosong.
void initChunk(Chunk *chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    chunk->lines = NULL;
    chunk->line_capacity = 0;
    chunk->line_count = 0;
    initValueArray(&chunk->constants);
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
    }

    // Simpan byte di akhir array.
    chunk->code[chunk->count] = byte;
    // Naikkan jumlah byte yang digunakan.
    chunk->count++;

    if (chunk->line_count > 0 && chunk->lines[chunk->line_count - 1].line == line) {
               // Cukup tingkatkan jumlah instruksi di run terakhir.
                 chunk->lines[chunk->line_count - 1].count++;
             } else {
                     // Jika tidak, kita perlu membuat run baru.
                     // Periksa kapasitas array lines
                     if (chunk->line_capacity < chunk->line_count + 1) {
                         int oldCapacity = chunk->line_capacity;
                         chunk->line_capacity = GROW_CAPACITY(oldCapacity);
                         chunk->lines = GROW_ARRAY(LineRun, chunk->lines, oldCapacity, chunk->line_capacity);
                     }

                     // Buat run baru.
                     LineRun* lineRun = &chunk->lines[chunk->line_count++];
                     lineRun->line = line;
                     lineRun->count = 1; // Run baru ini dimulai dengan 1 instruksi.
                 }
}

// Membebaskan memori yang digunakan oleh chunk.
void freeChunk(Chunk *chunk) {
    // Bebaskan array bytecode.
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(uint8_t, chunk->lines, chunk->line_capacity);
    freeValueArray(&chunk->constants);
    // Atur ulang chunk ke keadaan awalnya yang kosong untuk mencegah 'use-after-free'.
    initChunk(chunk);
}

int addConstant(Chunk *chunk, Value value) {
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}

void writeConstant(Chunk *chunk, Value value, int line) {
    int constant_index = addConstant(chunk, value);

    if (constant_index < 256) {
        writeChunk(chunk, OP_CONSTANT, line);
        writeChunk(chunk, (uint8_t)constant_index, line);
    }else {
        writeChunk(chunk, OP_CONSTANT_LONG, line);

        writeChunk(chunk,(uint8_t)(constant_index & 0xff), line);
        writeChunk(chunk,(uint8_t)((constant_index >> 8) & 0xff), line);
        writeChunk(chunk,(uint8_t)((constant_index >> 16) & 0xff), line);
    }

}

int getLine(Chunk *chunk, int instruction_offset) {
    int total_insruction = 0;
    for (int i = 0 ; i < chunk->line_count; i++) {
        total_insruction += chunk->lines[i].count;
        if (instruction_offset < total_insruction) {
            return chunk->lines[i].line;
        }
    }
    return 0;
}