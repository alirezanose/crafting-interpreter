// debug.h - Deklarasi untuk fungsi debugging bytecode
// Berkas ini berisi fungsi-fungsi untuk "membongkar" (disassemble) sebuah chunk,
// yaitu mengubah bytecode kembali menjadi format yang bisa dibaca manusia.
// Ini sangat berguna untuk debugging.

#ifndef DEBUG_H
#define DEBUG_H

#include "chunk.h"

// Membongkar semua instruksi dalam sebuah chunk dan mencetaknya ke konsol.
void disassembleChunk(Chunk *chunk,const char *name);

// Membongkar satu instruksi pada offset tertentu dalam sebuah chunk.
// Mengembalikan offset dari instruksi berikutnya.
int disassembleInstruction(Chunk *chunk, int offset);

#endif
