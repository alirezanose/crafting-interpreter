// debug.c - Implementasi untuk fungsi debugging bytecode

#include "debug.h"

#include <stdio.h>

// Mencetak nama chunk dan kemudian melakukan iterasi melalui semua bytecode,
// membongkar setiap instruksi.
void disassembleChunk(Chunk *chunk,const char *name) {
    printf("== %s ==\n", name);

    // Loop melalui bytecode, di mana setiap instruksi mungkin memiliki ukuran yang berbeda.
    for (int offset = 0; offset < chunk->count;) {
        // disassembleInstruction mengembalikan offset dari instruksi *berikutnya*.
        offset = disassembleInstruction(chunk, offset);
    }
}

static int constantInstruction(const char *name, Chunk *chunk, int offset) {
    uint8_t constant = chunk->code[offset + 1];
    printf("%-16s %4d '", name, constant);
    printValue(chunk->constants->values[constant]);
    printf("'\n");
    return offset + 2;
}

// Fungsi pembantu untuk membongkar instruksi sederhana yang hanya terdiri dari satu byte (opcode).
static int simpleInstruction(const char *name, int offset) {
    printf("%s\n", name);
    // Instruksi sederhana hanya memiliki panjang 1 byte.
    return offset + 1;
}

// Membaca satu instruksi pada offset tertentu, mencetaknya, dan mengembalikan offset berikutnya.
int disassembleInstruction(Chunk *chunk, int offset) {
    // Cetak offset byte untuk debugging.
    printf("%04d ", offset);

    // Baca byte instruksi (opcode).
    uint8_t instruction = chunk->code[offset];

    // Gunakan switch untuk menentukan jenis instruksi dan bagaimana cara mencetaknya.
    switch (instruction) {
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        case OP_CONSTANT:
            return constantInstruction("OP_CONSTANT", chunk, offset);
        default:
            // Jika kita menemukan opcode yang tidak kita kenali.
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;
    }
}