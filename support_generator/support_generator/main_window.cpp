#include "MainWindow.h"
#include "photon_file.hpp"


using namespace System;
using namespace System::Windows::Forms;


[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	photon_file::read_file("E:/Dokumente/Programmieren/3d_printer/PhotonFileEditor/SamplePhotonFiles/3DBenchy.photon");
	supportgenerator::MainWindow form;
	Application::Run(% form);
}
