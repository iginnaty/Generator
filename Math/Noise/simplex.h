#pragma once

#include "noise_interface.hpp"

namespace Math {
    namespace Noise {
        class Simplex : public NoiseInterface {
        private:
            float m_frequency,
                  m_amplitude,
                  m_lacunarity,
                  m_persistance;
            int m_seed,
                m_octaves;
        public:
            explicit Simplex(float a_frequency = 0.125f, float a_amplitude = 1.0f, float a_lacunarity = 2.5f, float a_persistance = 0.4f, int a_seed = 0, int a_octaves = 16) :
                m_frequency(a_frequency), m_amplitude(a_amplitude), m_lacunarity(a_lacunarity), m_persistance(a_persistance), m_seed(a_seed), m_octaves(a_octaves) {
            };

            float noise(float a_x);
            float noise(float a_x, float a_y);
            float fractal(float a_x);
            float fractal(float a_x, float a_y);
        };
    }
}
