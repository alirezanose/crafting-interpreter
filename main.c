#include "chunk.h"
#include "common.h"
#include "memory.h"
#include "debug.h"

int main(int argc, char *argv[]) {
    // Buat sebuah chunk baru untuk menyimpan bytecode.
    Chunk chunk;
    // Inisialisasi chunk.
    initChunk(&chunk);
    
    // Tulis satu instruksi ke dalam chunk.
    // Di sini kita menulis OP_RETURN, yang memberitahu VM untuk menghentikan eksekusi.
    writeChunk(&chunk, OP_RETURN);

    // Bongkar chunk untuk melihat isinya dalam format yang bisa dibaca manusia.
    // Ini adalah langkah debugging untuk memastikan kita menulis bytecode yang benar.
    disassembleChunk(&chunk, "test chunk");

    // Bebaskan memori yang digunakan oleh chunk setelah kita selesai menggunakannya.
    freeChunk(&chunk);
    
    return 0;
}
