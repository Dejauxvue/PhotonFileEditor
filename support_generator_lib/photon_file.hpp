#pragma once
#include <array>
#include <cstddef>
#include <string>
#include <vector>
#include <list>

namespace support_generator {

    class photon_file {
      public:
        static const int X_SIZE = 1440;
        static const int Y_SIZE = 2560;

        enum occupancy { EMPTY = 0, FILLED = 1 };
        typedef std::array<std::array<occupancy, Y_SIZE>, X_SIZE>
            explicit_layer;

        const explicit_layer& layer(int layer_index) const;
        explicit_layer& layer(int layer_index);

       
        /**
        * test round trip of conversion raw -> explicit -> raw
        * for given layer index
        */
        void test_layer_round_trip(int index);

        static photon_file read_file(const std::string& path);
        void write_file(const std::string& path) const;

        int layer_count() const;

      private:
        photon_file() = default;
        void init_layer(int layer_index) const;
        mutable std::vector<bool> explicit_layers_initialized_;
        mutable std::vector<explicit_layer> explicit_layers_;

        static void append_bytes_to_byte_vector(std::vector<std::byte>& v,
                                                const std::byte* b,
                                                int length);
        template <typename T>
        static void append_object_to_byte_vector(std::vector<std::byte>& v,
                                                 T& o) {
           append_bytes_to_byte_vector(v, (std::byte*)&o, sizeof(T));
        }

        std::vector<std::byte> convert_explicit_layer_to_raw(
            const explicit_layer& l) const;

        /**
         * structure of the file on HDD
         */
        //@{
        struct file_header {
            std::byte header[8];
            float bed_x;
            float bed_y;
            float bed_z;
            int padding_0[3];
            float layer_height;
            float exp_time;
            float exp_bottom_time;
            float off_time;
            int count_bottom_layers;
            int res_x;
            int res_y;
            int preview_0_offset;
            int layer_defs_addr;
            int count_layers;
            int preview_1_offset;
            int unkown6;
            int proj_type_cast_mirror;
            int padding_1[6];
        };

        struct preview {
            // this is the part which cn be loaded by reinterpret cast from file
            struct head_str {
                int res_x;
                int res_y;
                int image_address;
                int data_length;
                int padding[4];
            } head;

            // IMPORTANT!: image_data must be the last member, else reinterpret
            // cast is undefined!!
            std::vector<std::byte> image_data;
        };

        struct layer_def {
            float layer_height;
            float exp_time;
            float off_time;
            int image_address;
            int data_length;
            int padding[4];
        };

        mutable file_header header_;
        mutable preview previews_[2];
        mutable std::vector<layer_def> layer_defs_;
        mutable std::vector<std::vector<std::byte>> raw_layer_data_;
        //@}
    };
} // namespace support_generator
