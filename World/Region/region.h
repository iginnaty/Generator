#pragma once

#include "../../main.h"
#include "../Chunk/chunk.h"

namespace World {
    class Region {
    public:
        static constexpr uint SIZE = 16;
    private:
        Chunk *m_chunks[SIZE][SIZE];
    public:
        Region();
        ~Region();
        void offload();
        void load();
    };
}
