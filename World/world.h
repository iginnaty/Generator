#pragma once

#include <vector>

#include "../main.h"
#include "../Math/Noise/noise_interface.hpp"
#include "../Math/Noise/simplex.h"
#include "Chunk/chunk.h"

namespace World {
    class World {
    public:
        static constexpr uint DEFAULT_RENDER_DISTANCE = 10;
    private:
        uint m_chunk_count;
        std::vector<Chunk *> m_loaded_chunks;
        Math::Noise::Simplex m_terrain_generator;
    public:
        World(uint a_render_distance = DEFAULT_RENDER_DISTANCE);
        ~World();
        void generateChunk(int a_x, int a_y);
        void generateAtPosition(float a_x, float a_y);
        Chunk * getChunk(int a_x, int a_y);
        Chunk * getChunkAtPosition(float a_x, float a_y);
    };
}
