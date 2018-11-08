#pragma once

namespace Math {
    namespace Noise {
        class NoiseInterface {
        public:
            virtual float noise(float a_x) = 0;
            virtual float noise(float a_x, float a_y) = 0;
            virtual float fractal(float a_x) = 0;
            virtual float fractal(float a_x, float a_y) = 0;
        };
    }
}
