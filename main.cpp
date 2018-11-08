#include <iostream>
#include <fstream>

/*
VARIABLE SEMANTICS
    f_(name) => function variable
    m_(name) => member variable
    a_(name) => argument variable
    g_(name) => global variable
    s_(name) => static variable

    words separated by underscore only

FUNCTION SEMANTICS
    Camel case only

CLASS SEMANTICS
    First letter capital on all words
*/

#include "main.h"
#include "Math/Noise/simplex.h"
#include "World/Chunk/chunk.h"

int main(int argc, char *argv[]) {

    std::cout << ";generator\n";

    std::ofstream f_ppm("test.ppm", std::ios::binary);

    if (!f_ppm) {
        return 1;
    }

    Math::Noise::Simplex f_simplex;
    World::Chunk *f_chunk = nullptr;

    /*
    f_ppm <<
        "P6\n" <<
        (World::Chunk::WIDTH * 16) << ' ' << (World::Chunk::WIDTH * 16) <<
        "\n255\n";

    World::Block f_export[World::Chunk::WIDTH][World::Chunk::WIDTH * 16];

    for (int f_row = 0; f_row < 16; ++f_row) {
        for (int f_column = 0; f_column < 16; ++f_column) {
            f_chunk = new World::Chunk(f_row, f_column);
            f_chunk->generate(&f_simplex);

            for (World::ChunkSize f_x = 0; f_x < World::Chunk::WIDTH; ++f_x) {
                for (World::ChunkSize f_y = 0; f_y < World::Chunk::WIDTH; ++f_y) {
                    f_export
                        [f_x]
                        [f_column * World::Chunk::WIDTH + f_y] = f_chunk->at(f_x, f_y);
                }
            }

            delete f_chunk;
        }

        for (World::ChunkSize f_x = 0; f_x < World::Chunk::WIDTH; ++f_x) {
            World::ChunkSize f_l = World::Chunk::WIDTH * 16;
            for (World::ChunkSize f_y = 0; f_y < f_l; ++f_y) {
                f_ppm.write((char *)(&f_export[f_x][f_y]), sizeof(World::Block));
            }
        }
    }
    */

    f_ppm.close();
}
