#include "region.h"

#include <string>
#include <fstream>

namespace World {
    Region::Region(int a_x, int a_y) :
    m_x(a_x), m_y(a_y), m_chunks{nullptr} {
    }

    Region::~Region() {
        for (uint f_x = 0; f_x < SIZE; ++f_x) {
            for (uint f_y = 0; f_y < SIZE; ++f_y) {
                if (m_chunks[f_x][f_y]) {
                    delete m_chunks[f_x][f_y];
                }
            }
        }
    }

    bool Region::offload() {
        std::ofstream f_file_out;
        std::string f_file_name = "region_" + std::to_string(m_x) + "_" + std::to_string(m_y);
        char zero = 0; // because file.write

        f_file_out.open(f_file_name.c_str(), std::ios::out | std::ios::binary | std::ios::trunc);
        if (!f_file_out.is_open()) {
            return false;
        }

        for (uint f_x = 0; f_x < SIZE; ++f_x) {
            for (uint f_y = 0; f_y < SIZE; ++f_y) {
                if (!m_chunks[f_x][f_y]) {
                    f_file_out.write(&zero, 1);
                }
                else {
                    m_chunks[f_x][f_y]->writeToFile(f_file_out);
                }
            }
        }

        return true;
    }
}
