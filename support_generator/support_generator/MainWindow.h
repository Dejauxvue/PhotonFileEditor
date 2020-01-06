#pragma once
#include <cstdlib>
#include <iostream>
#include <ctime>

#include "MySample.h"
#include "photon_file.hpp"

namespace supportgenerator {

	using namespace System;
	using namespace Urho::Desktop;
	using namespace Urho::Extensions::WinForms;

	/// <summary>
	/// Summary for main_window
	/// </summary>
	public ref class MainWindow : public System::Windows::Forms::Form
	{
	public:
		MainWindow(void)
		{
			InitializeComponent();

			DesktopUrhoInitializer::AssetsDirectory = gcnew System::String("./Assets");

			surface = gcnew UrhoSurface();
			surface->Dock = Windows::Forms::DockStyle::Fill;
			urhoSurfacePlaceholder->Controls->Add(surface);
			surface->Show(MySample::typeid, gcnew ApplicationOptions("Data"));

		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: UrhoSurface^ surface;






	private: System::Windows::Forms::Button^ button1;

	private: System::Windows::Forms::PictureBox^ pictureBox1;

	private: System::Windows::Forms::Panel^ urhoSurfacePlaceholder;
	private: System::Windows::Forms::NumericUpDown^ numericUpDown1;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainWindow::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->urhoSurfacePlaceholder = (gcnew System::Windows::Forms::Panel());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(810, 38);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 6;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainWindow::button1_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(12, 158);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(1070, 724);
			this->pictureBox1->TabIndex = 8;
			this->pictureBox1->TabStop = false;
			// 
			// urhoSurfacePlaceholder
			// 
			this->urhoSurfacePlaceholder->Location = System::Drawing::Point(12, 12);
			this->urhoSurfacePlaceholder->Name = L"urhoSurfacePlaceholder";
			this->urhoSurfacePlaceholder->Size = System::Drawing::Size(505, 140);
			this->urhoSurfacePlaceholder->TabIndex = 10;
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Location = System::Drawing::Point(657, 38);
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(120, 20);
			this->numericUpDown1->TabIndex = 11;
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1108, 887);
			this->Controls->Add(this->numericUpDown1);
			this->Controls->Add(this->urhoSurfacePlaceholder);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->button1);
			this->Name = L"MainWindow";
			this->Text = L"main_window";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
		// Generate button
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		auto file = photon_file::read_file("E:/Dokumente/Programmieren/3d_printer/PhotonFileEditor/SamplePhotonFiles/3DBenchy.photon");
		auto explicit_layer = file.make_layer_explicit(System::Decimal::ToInt64(this->numericUpDown1->Value));
		System::Drawing::Image^ image = file.layer_to_image(explicit_layer);
		pictureBox1->Image = gcnew System::Drawing::Bitmap(image, this->pictureBox1->Size);
	}

	

};
}
