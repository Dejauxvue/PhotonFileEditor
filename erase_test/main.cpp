#include <photon_file.hpp>
#include <data_model.hpp>

using namespace support_generator;

int main() {
	data_model::file = std::make_unique<photon_file>(
		std::move(photon_file::read_file("../SamplePhotonFiles/3DBenchy.photon")));

	data_model::shape_cylinder();
	//data_model::file->layer(5);
	//data_model::file->test_layer_round_trip(5);

	data_model::file->write_file("../SamplePhotonFiles/output.photon");


}