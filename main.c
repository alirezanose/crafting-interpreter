#include "chunk.h"
#include "common.h"
#include "memory.h"
#include "debug.h"

int main(int argc, char *argv[]) {
    // Buat sebuah chunk baru untuk menyimpan bytecode.
    Chunk chunk;
    // Inisialisasi chunk.
    initChunk(&chunk);

    int constant = addConstant(&chunk,1.2);
    writeChunk(&chunk, OP_CONSTANT);
    writeChunk(&chunk, constant);


    // Bebaskan memori yang digunakan oleh chunk setelah kita selesai menggunakannya.
    freeChunk(&chunk);
    
    return 0;
}
