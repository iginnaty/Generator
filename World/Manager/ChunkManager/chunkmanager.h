#pragma once

#include "../../../main.h"
#include "../../Chunk/chunk.h"
#include "../../Region/region.h"

namespace World {
    namespace Manager {
        class ChunkManager {
        private:
            std::vector<World::Region *> m_regions;
        public:
            Chunk * getChunk();
            Chunk * generateChunk();
            void offloadChunks();
        };

        typedef ChunkManager;
    }
}
