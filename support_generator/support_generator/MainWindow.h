#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <msclr/marshal_cppstd.h>

#include "MySample.h"

#include "data_model.hpp"
#include "photon_file.hpp"

namespace support_generator {

    using namespace System;
    using namespace Urho::Desktop;
    using namespace Urho::Extensions::WinForms;

    /// <summary>
    /// Summary for main_window
    /// </summary>
  public
    ref class MainWindow : public System::Windows::Forms::Form {
      public:
        MainWindow(void) {
            InitializeComponent();

            DesktopUrhoInitializer::AssetsDirectory =
                gcnew System::String("./Assets");

            surface = gcnew UrhoSurface();
            surface->Dock = Windows::Forms::DockStyle::Fill;
            urhoSurfacePlaceholder->Controls->Add(surface);
            surface->Show(MySample::typeid, gcnew ApplicationOptions("Data"));
        }

      protected:
        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        ~MainWindow() {
            if (components) {
                delete components;
            }
        }

      private:
        UrhoSurface ^ surface;

      private:
      private:
      private:
      private:
      private:
        System::Windows::Forms::OpenFileDialog ^ openFileDialog1;

      private:
      private:
        System::Windows::Forms::TabControl ^ tabControl1;

      private:
        System::Windows::Forms::TabPage ^ tabPage1;

      private:
        System::Windows::Forms::TabPage ^ tabPage2;

      private:
        System::Windows::Forms::Button ^ button1;

      private:
        System::Windows::Forms::PictureBox ^ pictureBox1;

      private:
        System::Windows::Forms::Panel ^ urhoSurfacePlaceholder;

      private:
        System::Windows::Forms::NumericUpDown ^ numericUpDown1;

      private:
        System::Windows::Forms::Button ^ button2;

      private:
        System::Windows::Forms::RichTextBox ^ logger_box;

      private:
        System::Windows::Forms::Button ^ save_button;

      private:
        System::Windows::Forms::SaveFileDialog ^ saveFileDialog1;

      private:


      private:
      private:
      private:
      private:
      private:
      protected:
      private:
        /// <summary>
        /// Required designer variable.
        /// </summary>
        System::ComponentModel::Container ^ components;

#pragma region Windows Form Designer generated code
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        void InitializeComponent(void) {
            this->openFileDialog1 =
                (gcnew System::Windows::Forms::OpenFileDialog());
            this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
            this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
            this->save_button = (gcnew System::Windows::Forms::Button());
            this->button2 = (gcnew System::Windows::Forms::Button());
            this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
            this->urhoSurfacePlaceholder =
                (gcnew System::Windows::Forms::Panel());
            this->numericUpDown1 =
                (gcnew System::Windows::Forms::NumericUpDown());
            this->button1 = (gcnew System::Windows::Forms::Button());
            this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
            this->logger_box = (gcnew System::Windows::Forms::RichTextBox());
            this->saveFileDialog1 =
                (gcnew System::Windows::Forms::SaveFileDialog());
            this->tabControl1->SuspendLayout();
            this->tabPage1->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(
                 this->pictureBox1))
                ->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(
                 this->numericUpDown1))
                ->BeginInit();
            this->tabPage2->SuspendLayout();
            this->SuspendLayout();
            //
            // openFileDialog1
            //
            this->openFileDialog1->FileName = L"openFileDialog1";
            this->openFileDialog1->Filter = L"Photon files (*.photon)|*.photon";
            this->openFileDialog1->FileOk +=
                gcnew System::ComponentModel::CancelEventHandler(
                    this, &MainWindow::openFileDialog1_FileOk);
            //
            // tabControl1
            //
            this->tabControl1->Anchor =
                static_cast<System::Windows::Forms::AnchorStyles>(
                    (((System::Windows::Forms::AnchorStyles::Top |
                       System::Windows::Forms::AnchorStyles::Bottom) |
                      System::Windows::Forms::AnchorStyles::Left) |
                     System::Windows::Forms::AnchorStyles::Right));
            this->tabControl1->Controls->Add(this->tabPage1);
            this->tabControl1->Controls->Add(this->tabPage2);
            this->tabControl1->Location = System::Drawing::Point(12, 12);
            this->tabControl1->Name = L"tabControl1";
            this->tabControl1->SelectedIndex = 0;
            this->tabControl1->Size = System::Drawing::Size(1065, 810);
            this->tabControl1->TabIndex = 13;
            //
            // tabPage1
            //
            this->tabPage1->Controls->Add(this->save_button);
            this->tabPage1->Controls->Add(this->button2);
            this->tabPage1->Controls->Add(this->pictureBox1);
            this->tabPage1->Controls->Add(this->urhoSurfacePlaceholder);
            this->tabPage1->Controls->Add(this->numericUpDown1);
            this->tabPage1->Controls->Add(this->button1);
            this->tabPage1->Location = System::Drawing::Point(4, 22);
            this->tabPage1->Name = L"tabPage1";
            this->tabPage1->Padding = System::Windows::Forms::Padding(3);
            this->tabPage1->Size = System::Drawing::Size(1057, 784);
            this->tabPage1->TabIndex = 0;
            this->tabPage1->Text = L"tabPage1";
            this->tabPage1->UseVisualStyleBackColor = true;
            //
            // save_button
            //
            this->save_button->Location = System::Drawing::Point(607, 98);
            this->save_button->Name = L"save_button";
            this->save_button->Size = System::Drawing::Size(75, 23);
            this->save_button->TabIndex = 13;
            this->save_button->Text = L"Save";
            this->save_button->UseVisualStyleBackColor = true;
            this->save_button->Click +=
                gcnew System::EventHandler(this, &MainWindow::Save_Click);
            //
            // button2
            //
            this->button2->Location = System::Drawing::Point(6, 6);
            this->button2->Name = L"button2";
            this->button2->Size = System::Drawing::Size(75, 23);
            this->button2->TabIndex = 12;
            this->button2->Text = L"Open";
            this->button2->UseVisualStyleBackColor = true;
            this->button2->Click +=
                gcnew System::EventHandler(this, &MainWindow::button2_Click);
            //
            // pictureBox1
            //
            this->pictureBox1->Location = System::Drawing::Point(6, 181);
            this->pictureBox1->Name = L"pictureBox1";
            this->pictureBox1->Size = System::Drawing::Size(1070, 724);
            this->pictureBox1->TabIndex = 8;
            this->pictureBox1->TabStop = false;
            //
            // urhoSurfacePlaceholder
            //
            this->urhoSurfacePlaceholder->Location =
                System::Drawing::Point(6, 35);
            this->urhoSurfacePlaceholder->Name = L"urhoSurfacePlaceholder";
            this->urhoSurfacePlaceholder->Size =
                System::Drawing::Size(505, 140);
            this->urhoSurfacePlaceholder->TabIndex = 10;
            //
            // numericUpDown1
            //
            this->numericUpDown1->Location = System::Drawing::Point(108, 6);
            this->numericUpDown1->Name = L"numericUpDown1";
            this->numericUpDown1->Size = System::Drawing::Size(120, 20);
            this->numericUpDown1->TabIndex = 11;
            //
            // button1
            //
            this->button1->Location = System::Drawing::Point(244, 3);
            this->button1->Name = L"button1";
            this->button1->Size = System::Drawing::Size(75, 23);
            this->button1->TabIndex = 6;
            this->button1->Text = L"button1";
            this->button1->UseVisualStyleBackColor = true;
            this->button1->Click +=
                gcnew System::EventHandler(this, &MainWindow::button1_Click);
            //
            // tabPage2
            //
            this->tabPage2->Controls->Add(this->logger_box);
            this->tabPage2->Location = System::Drawing::Point(4, 22);
            this->tabPage2->Name = L"tabPage2";
            this->tabPage2->Padding = System::Windows::Forms::Padding(3);
            this->tabPage2->Size = System::Drawing::Size(1057, 784);
            this->tabPage2->TabIndex = 1;
            this->tabPage2->Text = L"Logger";
            this->tabPage2->UseVisualStyleBackColor = true;
            //
            // logger_box
            //
            this->logger_box->Anchor =
                static_cast<System::Windows::Forms::AnchorStyles>(
                    (((System::Windows::Forms::AnchorStyles::Top |
                       System::Windows::Forms::AnchorStyles::Bottom) |
                      System::Windows::Forms::AnchorStyles::Left) |
                     System::Windows::Forms::AnchorStyles::Right));
            this->logger_box->Location = System::Drawing::Point(6, 6);
            this->logger_box->Name = L"logger_box";
            this->logger_box->Size = System::Drawing::Size(1045, 772);
            this->logger_box->TabIndex = 0;
            this->logger_box->Text = L"";
            //
            // saveFileDialog1
            //
            this->saveFileDialog1->FileOk +=
                gcnew System::ComponentModel::CancelEventHandler(
                    this, &MainWindow::saveFileDialog1_FileOk);
            //
            // MainWindow
            //
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1089, 834);
            this->Controls->Add(this->tabControl1);
            this->Name = L"MainWindow";
            this->Text = L"main_window";
            this->tabControl1->ResumeLayout(false);
            this->tabPage1->ResumeLayout(false);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(
                 this->pictureBox1))
                ->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize ^>(
                 this->numericUpDown1))
                ->EndInit();
            this->tabPage2->ResumeLayout(false);
            this->ResumeLayout(false);
        }
#pragma endregion
        // Generate button
      private:
        System::Void button1_Click(System::Object ^ sender,
                                   System::EventArgs ^ e) {

            auto& explicit_layer = data_model::file->layer(
                System::Decimal::ToInt64(this->numericUpDown1->Value));
            System::Drawing::Image ^ image =
                data_model::file->layer_to_image(explicit_layer);
            pictureBox1->Image =
                gcnew System::Drawing::Bitmap(image, this->pictureBox1->Size);
        }

      private:
        System::Void openFileDialog1_FileOk(
            System::Object ^ sender,
            System::ComponentModel::CancelEventArgs ^ e) {
            this->Activate();
            array<System::String ^> ^ file_names = openFileDialog1->FileNames;

            System::String ^cs_string = file_names[0];
           
            std::string cpp_string =
                msclr::interop::marshal_as<std::string>(cs_string);
            data_model::file = std::make_unique<photon_file>(
                std::move(photon_file::read_file(cpp_string)));
            logger_box->AppendText("selected open file: " + file_names->GetValue(0) +
                                   "\n");
        }

      private:
        System::Void button2_Click(System::Object ^ sender,
                                   System::EventArgs ^ e) {
            openFileDialog1->ShowDialog();
        }

      private:
        System::Void Save_Click(System::Object ^ sender,
                                System::EventArgs ^ e) {
            saveFileDialog1->ShowDialog();
        }

      private:
        System::Void saveFileDialog1_FileOk(
            System::Object ^ sender,
            System::ComponentModel::CancelEventArgs ^ e) {
            this->Activate();
            array<System::String ^> ^ file_names = saveFileDialog1->FileNames;

            System::String ^ cs_string = file_names[0];

            std::string cpp_string =
                msclr::interop::marshal_as<std::string>(cs_string);
            data_model::file->write_file(cpp_string);          
            logger_box->AppendText("selected save file: " + file_names->GetValue(0) +
                                   "\n");
        }
    };
} // namespace support_generator
