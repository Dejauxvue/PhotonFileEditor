#include "photon_file_adapter.hpp"

namespace support_generator {

    /*System::Drawing::Image ^ photon_file_adapter::layer_to_image(
                                 const photon_file::explicit_layer& layer) {
        System::Drawing::Bitmap ^ ret = gcnew System::Drawing::Bitmap(
            photon_file::X_SIZE, photon_file::Y_SIZE);
        for (int x = 0; x < ret->Width; x++)
            for (int y = 0; y < ret->Height; y++) {
                ret->SetPixel(x,
                              y,
                              layer[x][y] == photon_file::EMPTY
                                  ? System::Drawing::Color::Black
                                  : System::Drawing::Color::White);
            }
        ret->Save("E:/Dokumente/Programmieren/3d_printer/PhotonFileEditor/"
                  "SamplePhotonFiles/debug.jpg");
        return ret;
    }*/

} // namespace support_generator