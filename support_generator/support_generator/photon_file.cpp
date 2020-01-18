#include "photon_file.hpp"
#include <fstream>
#include <iostream>

namespace support_generator {
    const photon_file::explicit_layer& photon_file::layer(
        int layer_index) const {
        init_layer(layer_index);
        return explicit_layers_[layer_index];
    }

    photon_file::explicit_layer& photon_file::layer(int layer_index) {
        return const_cast<photon_file::explicit_layer&>(
            ((const photon_file*)this)->layer(layer_index));
    }

    System::Drawing::Image ^
        photon_file::layer_to_image(const photon_file::explicit_layer& layer) {
        System::Drawing::Bitmap ^ ret =
            gcnew System::Drawing::Bitmap(X_SIZE, Y_SIZE);
        for (int x = 0; x < ret->Width; x++)
            for (int y = 0; y < ret->Height; y++) {
                ret->SetPixel(x,
                              y,
                              layer[x][y] == EMPTY
                                  ? System::Drawing::Color::Black
                                  : System::Drawing::Color::White);
            }
        ret->Save("E:/Dokumente/Programmieren/3d_printer/PhotonFileEditor/"
                  "SamplePhotonFiles/debug.jpg");
        return ret;
    }

    photon_file photon_file::read_file(const std::string& path) {
        std::ifstream in_file(path, std::ios::binary | std::ios::ate);
        int size = in_file.tellg();
        in_file.seekg(0, std::ios::beg);
        std::vector<std::byte> buffer;
        buffer.resize(size);
        in_file.read(reinterpret_cast<char*>(buffer.data()), size);
        photon_file ret;
        ret.header_ = *reinterpret_cast<file_header*>(buffer.data());
        ret.previews_[0].head = *reinterpret_cast<preview::head_str*>(
            buffer.data() + ret.header_.preview_0_offset);
        ret.previews_[0].image_data = std::vector<std::byte>();
        ret.previews_[0].image_data.resize(ret.previews_[0].head.data_length);
        std::memcpy(ret.previews_[0].image_data.data(),
                    buffer.data() + ret.previews_[0].head.image_address,
                    ret.previews_[0].head.data_length);

        ret.previews_[1].head = *reinterpret_cast<preview::head_str*>(
            buffer.data() + ret.header_.preview_1_offset);
        ret.previews_[1].image_data = std::vector<std::byte>();
        ret.previews_[1].image_data.resize(ret.previews_[1].head.data_length);
        std::memcpy(ret.previews_[1].image_data.data(),
                    buffer.data() + ret.previews_[1].head.image_address,
                    ret.previews_[1].head.data_length);

        for (int i = 0; i < ret.header_.count_layers; i++) {
            ret.layer_defs_.push_back(layer_def());
            ret.layer_defs_[i] = *reinterpret_cast<layer_def*>(
                buffer.data() + ret.header_.layer_defs_addr +
                i * sizeof(layer_def));

            ret.raw_layer_data_.push_back(std::vector<std::byte>());
            ret.raw_layer_data_[i].resize(ret.layer_defs_[i].data_length);
            std::memcpy(&ret.raw_layer_data_[i][0],
                        buffer.data() + ret.layer_defs_[i].image_address,
                        ret.layer_defs_[i].data_length);
        }
        std::cout << "layers: " << ret.header_.count_layers << std::endl;
        ret.explicit_layers_initialized_.resize(ret.header_.count_layers);
        for (auto& x : ret.explicit_layers_initialized_)
            x = false;
        return ret;
    }

    void photon_file::write_file(const std::string& path) const {
        for (int i = 0; i < explicit_layers_initialized_.size(); i++) {
            if (explicit_layers_initialized_[i]) {
                raw_layer_data_[i] =
                    convert_explicit_layer_to_raw(explicit_layers_[i]);
            }
        }

        header_.count_layers = layer_defs_.size();
        header_.preview_0_offset = sizeof(file_header);
        header_.preview_1_offset =
            header_.preview_0_offset + sizeof(preview::head_str);
        previews_[0].head.image_address =
            header_.preview_1_offset + sizeof(preview::head_str);
        previews_[0].head.data_length = previews_[0].image_data.size();
        previews_[1].head.image_address =
            previews_[0].head.image_address + previews_[0].head.data_length;
        previews_[1].head.data_length = previews_[1].image_data.size();
        header_.layer_defs_addr =
            previews_[1].head.image_address + previews_[1].head.data_length;

        int layer_offset =
            header_.layer_defs_addr + header_.count_layers * sizeof(layer_def);
        for (int i = 0; i < header_.count_layers; i++) {
            layer_defs_[i].image_address = layer_offset;
            layer_defs_[i].data_length = raw_layer_data_[i].size();
            layer_offset += raw_layer_data_[i].size();
        }

        std::vector<std::byte> raw_file;
        append_object_to_byte_vector(raw_file, header_);
        append_object_to_byte_vector(raw_file, previews_[0].head);
        append_object_to_byte_vector(raw_file, previews_[1].head);
        append_bytes_to_byte_vector(raw_file,
                                    previews_[0].image_data.data(),
                                    previews_[0].image_data.size());
        append_bytes_to_byte_vector(raw_file,
                                    previews_[1].image_data.data(),
                                    previews_[1].image_data.size());
        for (const auto& l : layer_defs_) {
            append_object_to_byte_vector(raw_file, l);
        }
        for (const auto& l : raw_layer_data_) {
            append_bytes_to_byte_vector(raw_file, l.data(), l.size());
        }

        std::ofstream out_file(path, std::ios::binary);
        out_file.write((char*)raw_file.data(), raw_file.size());
            //std::runtime_error("not implemented");
    }

    void photon_file::init_layer(int layer_index) const {
        if (explicit_layers_initialized_[layer_index])
            return;
        if (explicit_layers_.size() <= layer_index + 1)
            explicit_layers_.resize(layer_index + 1);

        auto& layer = explicit_layers_.at(layer_index);
        int image_index = 0; // index for drawing in the explicit representation
        for (const std::byte& b : raw_layer_data_[layer_index]) {
            int number = int(
                b & ~(std::byte{1} << 7)); // last seven bit give line length
            occupancy color =
                b >> 7 == std::byte{0} ? EMPTY : FILLED; // first bit tell color

            std::cout << color << std::endl;
            for (int i = 0; i < number; i++) {
                layer[image_index % X_SIZE][image_index / X_SIZE] = color;
                image_index++;
            }
        }
        explicit_layers_initialized_[layer_index] = true;
    }
    void photon_file::append_bytes_to_byte_vector(std::vector<std::byte>& v,
                                                  const std::byte* b,
                                                  int length) {
        int prev_size = v.size();
        v.resize(prev_size + length);
        std::memcpy(&v[prev_size], b, length);
    }

    std::vector<std::byte> photon_file::convert_explicit_layer_to_raw(
        const explicit_layer& l) const {
        std::vector<std::byte> ret;
        int count = 0;
        int color = 0;
        for (int i = 0; i < X_SIZE * Y_SIZE; i++) {
            int curr_color = l[i % X_SIZE][i / X_SIZE] == EMPTY ? 0 : 1;
            // begin new sequence
            if (count == 0) {
                color = curr_color;
            }
            if (color == curr_color) {
                count++;
            }
            if (color != curr_color || count == 128 ||
                i == X_SIZE * Y_SIZE - 1) {

                ret.push_back((std::byte(color) << 7) | std::byte(color));
                count = 0;
            }
        }
        return ret;
    }
} // namespace support_generator
