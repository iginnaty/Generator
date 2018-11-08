#pragma once

#include "../../main.h"
#include "../../Math/Noise/noise_interface.hpp"

namespace World {
    typedef uint ChunkSize;

    struct Block {
        unsigned char m_r, m_g, m_b;
    };

    class Chunk {
    public:
        static constexpr ChunkSize
            WIDTH = 16,
            HEIGHT = 256;
    private:
        const int m_x_pos;
        const int m_y_pos;
        bool m_is_generated;
        Block m_data[WIDTH][WIDTH];
        uint normalize(float a_noise_height);
    public:
        Chunk() = delete;
        Chunk(int a_x_pos, int a_y_pos);
        void generate(Math::Noise::NoiseInterface *a_generator);
        // Accessors
        const int getXPos() const {
            return m_x_pos;
        };
        const int getYPos() const {
            return m_y_pos;
        };
        Block & at(ChunkSize a_x, ChunkSize a_y) {
            return m_data[a_x][a_y];
        }
        Block & safeAt(ChunkSize a_x, ChunkSize a_y) {
            if (a_x >= WIDTH) {
                a_x = WIDTH - 1;
            }
            if (a_y >= WIDTH) {
                a_y = WIDTH - 1;
            }
            return at(a_x, a_y);
        }
        const bool is(int a_x, int a_y) const {
            return (m_x_pos == a_x) && (m_y_pos == a_y);
        }
    };
}
