#include "chunk.h"
#include "common.h"
#include "memory.h"
#include "debug.h"

int main(int argc, char *argv[]) {
    // Buat sebuah chunk baru untuk menyimpan bytecode.
    Chunk chunk;
    // Inisialisasi chunk.
    initChunk(&chunk);

    writeConstant(&chunk, 1.2, 1);

    for (int i = 0 ; i < 257; i++) {
        addConstant(&chunk,(double)i);
    }

    // writeChunk(&chunk, OP_CONSTANT,123);
    // writeChunk(&chunk, constant,123);

    writeConstant(&chunk,55.55,123);

    writeChunk(&chunk, OP_RETURN,123);

    disassembleChunk(&chunk, "test chunk");
    // Bebaskan memori yang digunakan oleh chunk setelah kita selesai menggunakannya.
    freeChunk(&chunk);
    
    return 0;
}
