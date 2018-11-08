#include "world.h"

namespace World {
    World::World(uint a_render_distance) :
    m_chunk_count(a_render_distance), m_loaded_chunks(), m_terrain_generator() {
    }

    World::~World() {
        for (auto & f_chunk : m_loaded_chunks) {
            delete f_chunk;
        }
    }

    void World::generateChunk(int a_x, int a_y) {
        Chunk *f_chunk = nullptr;

        for (auto &f_match : m_loaded_chunks) {
            if (f_match->is(a_x, a_y)) {
                return;
            }
        }

        f_chunk = new Chunk(a_x, a_y);
        f_chunk->generate(&m_terrain_generator);

        m_loaded_chunks.push_back(f_chunk);
    }

    inline void World::generateAtPosition(float a_x, float a_y) {
        generateChunk(static_cast<int>(a_x / Chunk::WIDTH), static_cast<int>(a_y / Chunk::WIDTH));
    }

    Chunk * World::getChunk(int a_x, int a_y) {
        for (auto &f_match : m_loaded_chunks) {
            if (f_match->is(a_x, a_y)) {
                return f_match;
            }
        }

        return nullptr;
    }

    inline Chunk * World::getChunkAtPosition(float a_x, float a_y) {
        return getChunk(static_cast<int>(a_x / Chunk::WIDTH), static_cast<int>(a_x / Chunk::WIDTH));
    }
}
