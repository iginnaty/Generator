#pragma once

namespace Math {
    static inline int fastFloor(float a_number) {
        int f_number = static_cast<int>(a_number);

        if (f_number > a_number) {
            --f_number;
        }

        return f_number;
    }

    static inline int fastCeiling(float a_number) {
        int f_number = static_cast<int>(a_number);

        if (f_number < a_number) {
            ++f_number;
        }

        return f_number;
    }
}
