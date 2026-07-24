#include "chunk.h"
#include "common.h"
#include "memory.h"
#include "debug.h"
#include "vm.h"

int main(int argc,const char *argv[]) {
    initVM();
    // Buat sebuah chunk baru untuk menyimpan bytecode.
    Chunk chunk;
    // Inisialisasi chunk.
    initChunk(&chunk);

    int constant = addConstant(&chunk, 1.2);
    writeChunk(&chunk,OP_CONSTANT, 123);
    writeChunk(&chunk,constant, 123);


    constant = addConstant(&chunk, 3.4);
    writeChunk(&chunk,OP_CONSTANT, 123);
    writeChunk(&chunk,constant, 123);

    writeChunk(&chunk, OP_ADD, 123);

    constant = addConstant(&chunk, 5.6);
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant, 123);

    writeChunk(&chunk, OP_DIVIDE,123);
    //
    // writeConstant(&chunk, 1.2, 1);
    //
    // for (int i = 0 ; i < 257; i++) {
    //     addConstant(&chunk,(double)i);
    // }
    //
    // // writeChunk(&chunk, OP_CONSTANT,123);
    // // writeChunk(&chunk, constant,123);
    //
    // writeConstant(&chunk,55.55,123);
    writeChunk(&chunk, OP_NEGATE,123);
    writeChunk(&chunk, OP_RETURN,123);

    disassembleChunk(&chunk, "test chunk");
    interpret(&chunk);
    freeVM();
    // Bebaskan memori yang digunakan oleh chunk setelah kita selesai menggunakannya.
    freeChunk(&chunk);
    
    return 0;
}
