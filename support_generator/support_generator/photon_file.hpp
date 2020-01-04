#pragma once
#include <cstddef>
#include <vector>
#include <string>

class photon_file
{
public:
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
		//this is the part which cn be loaded by reinterpret cast from file
		struct head_str {
			int res_x;
			int res_y;
			int image_address;
			int data_length;
			int padding[4];
		} head;

		//IMPORTANT!: image_data must be the last member, else reinterpret cast is undefined!!
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

	file_header header_;
	preview previews_[2];
	std::vector<layer_def> layer_defs_;
	std::vector<std::vector<std::byte>> layer_data_;

	static photon_file read_file(const std::string& path);
};

