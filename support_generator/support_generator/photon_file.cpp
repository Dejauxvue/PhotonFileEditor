#include "photon_file.hpp"
#include <fstream>
#include <iostream>

std::vector<photon_file::occupancy> photon_file::make_layer_explicit(int layer_index)const
{
	std::vector<occupancy> ret;
	ret.resize(header_.res_x * header_.res_y);
	int image_index = 0; // index for drawing in the explicit representation
	for (const std::byte& b : layer_data_[layer_index]) {
		int number = int(b & ~(std::byte{ 1 } << 7)); // last seven bit give line length
		occupancy color = b >> 7 == std::byte{ 0 } ? EMPTY : FILLED; //first bit tell color
		if (color == FILLED)
			System::Console::WriteLine(0);
		std::cout << color << std::endl;
		for (int i = 0; i < number; i++) {
			ret[image_index++] = color;
		}
	}
	return ret;
}

System::Drawing::Image^ photon_file::layer_to_image(const std::vector<photon_file::occupancy>& layer)
{
	System::Drawing::Bitmap^ ret = gcnew System::Drawing::Bitmap(header_.res_x, header_.res_y);
	for (int x = 0; x < ret->Width; x++)
		for (int y = 0; y < ret->Height; y++)
		{
			ret->SetPixel(x, y, layer[x + y * header_.res_x] == EMPTY ? System::Drawing::Color::Black : System::Drawing::Color::White);
		}
	ret->Save("E:/Dokumente/Programmieren/3d_printer/PhotonFileEditor/SamplePhotonFiles/debug.jpg");
	return ret;
}

photon_file photon_file::read_file(const std::string& path)
{
	std::ifstream in_file(path, std::ios::binary | std::ios::ate);
	int size = in_file.tellg();
	in_file.seekg(0, std::ios::beg);
	std::vector<std::byte> buffer;
	buffer.resize(size);
	in_file.read(reinterpret_cast<char*>(buffer.data()), size);
	photon_file ret;
	ret.header_ = *reinterpret_cast<file_header*>(buffer.data());
	ret.previews_[0].head = *reinterpret_cast<preview::head_str*>(buffer.data() + ret.header_.preview_0_offset);
	ret.previews_[0].image_data = std::vector<std::byte>();
	ret.previews_[0].image_data.resize(ret.previews_[0].head.data_length);
	ret.previews_[1].head = *reinterpret_cast<preview::head_str*>(buffer.data() + ret.header_.preview_1_offset);
	ret.previews_[1].image_data = std::vector<std::byte>();
	ret.previews_[1].image_data.resize(ret.previews_[1].head.data_length);

	for (int i = 0; i < ret.header_.count_layers; i++) {
		ret.layer_defs_.push_back(layer_def());
		ret.layer_defs_[i] = *reinterpret_cast<layer_def*>(buffer.data() + ret.header_.layer_defs_addr + i * sizeof(layer_def));

		ret.layer_data_.push_back(std::vector<std::byte>());
		ret.layer_data_[i].resize(ret.layer_defs_[i].data_length);
		std::memcpy(&ret.layer_data_[i][0], buffer.data() + ret.layer_defs_[i].image_address, ret.layer_defs_[i].data_length);
	}
	std::cout << "layers: " << ret.header_.count_layers << std::endl;
	return ret;
}
