#include "data_model.hpp"

std::unique_ptr<support_generator::photon_file>
    support_generator::data_model::file;

void support_generator::data_model::erase_islands() {
    for (int l = 1; l < file->layer_count(); l++) {
        photon_file::explicit_layer& current_layer = file->layer(l);
        for (int i = 0; i < photon_file::X_SIZE; i++)
            for (int j = 0; j < photon_file::Y_SIZE; j++) {
                if (file->layer(l-1)[i][j] == photon_file::EMPTY) {
                    current_layer[i][j] = photon_file::EMPTY;
                }
        }
    }
}

void support_generator::data_model::shape_cylinder()
{
    for (int l = 0; l < file->layer_count(); l++) {
        photon_file::explicit_layer& current_layer = file->layer(l);
        for (int i = 0; i < photon_file::X_SIZE; i++)
            for (int j = 0; j < photon_file::Y_SIZE; j++) {
                if ((i - 100) * (i - 100) + ((j - 100) * (j - 100)) < 1000) {
                    current_layer[i][j] = photon_file::FILLED;
                }
                else {
                    current_layer[i][j] = photon_file::EMPTY;
                }
            }
    }
}
