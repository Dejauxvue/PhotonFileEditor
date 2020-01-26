#pragma once
#include <memory>
#include "photon_file.hpp"

namespace support_generator {
    class data_model {
      public:
        static std::unique_ptr<photon_file> file;

        static void erase_islands();

        static void shape_cylinder();
    };
} // namespace support_generator
