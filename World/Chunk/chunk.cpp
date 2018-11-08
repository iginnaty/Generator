#include "chunk.h"

namespace World {
    Chunk::Chunk(int a_x_pos, int a_y_pos) :
    m_x_pos(a_x_pos), m_y_pos(a_y_pos), m_is_generated(false), m_data{0} {
    }

    void Chunk::generate(Math::Noise::NoiseInterface *a_generator) {
        long f_x_offset = m_x_pos * WIDTH,
             f_y_offset = m_y_pos * WIDTH;

        for (ChunkSize f_x = 0, f_y; f_x < WIDTH; ++f_x) {
            for (f_y = 0; f_y < WIDTH; ++f_y) {
                auto *f_index_data = &m_data[f_x][f_y];
                auto f_noise = a_generator->fractal(
                    static_cast<float>(f_x_offset + f_x),
                    static_cast<float>(f_y_offset + f_y)
                );
                unsigned char f_height = normalize(f_noise);

                if (f_height < 114) {
                    f_index_data->m_r = 0;
                    f_index_data->m_g = 0;
                    f_index_data->m_b = 128 + f_height;
                }
                else if (f_height < 120) {
                    f_index_data->m_r = 64;
                    f_index_data->m_g = 64 + f_height;
                    f_index_data->m_b = 96 + f_height;
                }
                else if (f_height < 126) {
                    f_index_data->m_r = 124 + f_height;
                    f_index_data->m_g = 92 + f_height;
                    f_index_data->m_b = 0;
                }
                else if (f_height < 192) {
                    f_index_data->m_r = 0;
                    f_index_data->m_g = f_height + 64;
                    f_index_data->m_b = 32;
                }
                else {
                    f_index_data->m_r = f_height;
                    f_index_data->m_g = f_height;
                    f_index_data->m_b = f_height;
                }
            }
        }
    }

    inline uint Chunk::normalize(float a_noise_height) {
        a_noise_height = (
            a_noise_height +
            (a_noise_height < 0.0f ? -2.0f : 2.0f) * a_noise_height * a_noise_height
        ) / 3.0f;

        a_noise_height = (a_noise_height + 1.0f) * 128.0f;

        return (static_cast<unsigned int>(a_noise_height) - 1) & 255;
    }
}
