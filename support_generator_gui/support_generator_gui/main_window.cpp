#include "MainWindow.h"




using namespace System;
using namespace System::Windows::Forms;


[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);	
	support_generator::MainWindow form;
	Application::Run(% form);
}
