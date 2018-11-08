#include "simplex.h"
#include "../fast_round.hpp"

namespace Math {
    namespace Noise {
        static unsigned char s_simplexTable[256] = {
            151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225,
            140, 36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23, 190, 6, 148,
            247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32,
            57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175,
            74, 165, 71, 134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122,
            60, 211, 133, 230, 220, 105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54,
            65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 169,
            200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64,
            52, 217, 226, 250, 124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212,
            207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28, 42, 223, 183, 170, 213,
            119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9,
            129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 104,
            218, 246, 97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241,
            81, 51, 145, 235, 249, 14, 239, 107, 49, 192, 214, 31, 181, 199, 106, 157,
            184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254, 138, 236, 205, 93,
            222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180
        };

        static inline char hash(int a_index) {
            return s_simplexTable[a_index & 255];
        };

        static float gradient(int a_hash, float a_x) {
            const int f_hash = a_hash & 0x0F;
            float f_gradient = 1.0f + (f_hash & 7);

            if (f_hash & 8) {
                f_gradient = -f_gradient;
            }

            return f_gradient * a_x;
        }

        static float gradient(int a_hash, float a_x, float a_y) {
            const int f_hash = a_hash & 0x3F;
            const float
                f_vector_u = f_hash < 4 ? a_x : a_y,
                f_vector_v = f_hash < 4 ? a_y : a_x;
            return (
                ((f_hash & 1) ? -f_vector_u : f_vector_u) +
                ((f_hash & 2) ? -2.0f : 2.0f) * f_vector_v
            );
        }

        float Simplex::noise(float a_x) {
            float n0, n1;

            int
                i0 = Math::fastFloor(a_x),
                i1 = i0 + 1;

            float
                x0 = a_x - i0,
                x1 = x0 - 1.0f;

            float t0 = 1.0f - x0 * x0;
            t0 *= t0;
            t0 *= t0;
            n0 = t0 * gradient(hash(i0), x0);

            float t1 = 1.0f - x1 * x1;
            t1 *= t1;
            t1 *= t1;
            n1 = t1 * gradient(hash(i1), x1);

            return 0.395f * (n0 + n1);
        }

        float Simplex::noise(float a_x, float a_y) {
            a_x /= 32.0f;
            a_y /= 32.0f;
            float n[3], x[3], y[3];
            int gi[3];
            static const float
                F2 = 0.366025403f,  // (root2(3) - 1) / 2
                G2 = 0.211324865f; // (3 - root2(3)) / 6

            const float
                s = (a_x + a_y) * F2,
                xs = a_x + s,
                ys = a_y + s;

            const int
                i = Math::fastFloor(xs),
                j = Math::fastFloor(ys);

            const float
                t = static_cast<float>(i + j) * G2,
                X0 = i - t,
                Y0 = j - t;
            x[0] = a_x - X0,
            y[0] = a_y - Y0;

            int i1, j1;
            if (x[0] > y[0]) {
                i1 = 1;
                j1 = 0;
            }
            else {
                i1 = 0;
                j1 = 1;
            }

            x[1] = x[0] - i1 + G2,
            y[1] = y[0] - j1 + G2,
            x[2] = x[0] - 1.0f + 2.0f * G2,
            y[2] = y[0] - 1.0f + 2.0f * G2;

            gi[0] = hash(i + hash(j)),
            gi[1] = hash(i + i1 + hash(j + j1)),
            gi[2] = hash(i + 1 + hash(j + 1));

            for (int i = 0; i < 3; ++i) {
                float t = 0.5f - x[i] * x[i] - y[i] * y[i];
                if (t < 0.0f) {
                    n[i] = 0.0f;
                }
                else {
                    t *= t;
                    t *= t;
                    n[i] = t * gradient(gi[i], x[i], y[i]);
                }
            }

            return 45.23065f * (n[0] + n[1] + n[2]);
        }

        // TODO: implement 1D Simplex noise
        float Simplex::fractal(float a_x) {
            return a_x;
        }

        float Simplex::fractal(float a_x, float a_y) {
            float
                f_output = 0.0f,
                f_max_amplitude = 0.0f,
                f_frequency = m_frequency,
                f_amplitude = m_amplitude;

            for (int f_index = 0; f_index < m_octaves; ++f_index) {
                f_output += (f_amplitude * noise(a_x * f_frequency, a_y * f_frequency));
                f_max_amplitude += f_amplitude;

                f_frequency *= m_lacunarity;
                f_amplitude *= m_persistance;
            }

            return f_output / f_max_amplitude;
        }
    }
}
