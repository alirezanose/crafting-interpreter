// chunk.h - Deklarasi untuk struktur data 'Chunk'
// 'Chunk' adalah urutan bytecode. Ini adalah inti dari bagaimana kode sumber
// direpresentasikan setelah dikompilasi, sebelum dieksekusi oleh VM.

#ifndef CHUNK_H
#define CHUNK_H

#include "common.h"
#include "memory.h"
#include "value.h"

// OpCode (Operation Code) adalah instruksi satu-byte.
// Setiap OpCode memberitahu VM untuk melakukan operasi tertentu.
typedef enum {
    OP_CONSTANT,
    OP_RETURN, // Instruksi untuk kembali dari fungsi saat ini.
} OpCode;

// Chunk adalah array dinamis yang menyimpan bytecode.
typedef struct {
    int count;      // Jumlah byte yang saat ini ada di dalam chunk.
    int capacity;   // Jumlah byte yang bisa disimpan oleh array 'code' sebelum perlu diubah ukurannya.
    uint8_t* code;  // Pointer ke array bytecode itu sendiri.
    ValueArray* constants;
} Chunk;

// Menginisialisasi sebuah chunk baru (kosong).
void initChunk(Chunk *chunk);

// Menulis sebuah byte (biasanya OpCode) ke dalam chunk.
// Jika chunk tidak memiliki cukup kapasitas, chunk akan tumbuh secara otomatis.
void    writeChunk(Chunk *chunk, uint8_t byte);

// Membebaskan semua memori yang digunakan oleh sebuah chunk.
void freeChunk(Chunk *chunk);

int addConstant(Chunk *chunk, Value value);

#endif