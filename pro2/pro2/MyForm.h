#include <Winsock2.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")

using namespace System;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Text;

namespace pro2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	private:
		UdpClient^ udpClient;
		int serverPort = 12345;
	private: System::Windows::Forms::Button^ button1;

	private: System::Windows::Forms::TextBox^ textBox1;

		   String^ serverIPAddress = "127.0.0.1";
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
			udpClient = gcnew UdpClient();
		}

	private:
		void SendMessage(String^ message)
		{
			array<Byte>^ sendBytes = Encoding::ASCII->GetBytes(message);
			udpClient->Send(sendBytes, sendBytes->Length, serverIPAddress, serverPort);
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
		void SendMessageButton_Click(Object^ sender, EventArgs^ e)
		{
			String^ messageToSend = "Привет, сервер!";
			SendMessage(messageToSend);
		}

	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 91);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(137, 53);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Нарисовать";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox1->Location = System::Drawing::Point(12, 35);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(575, 38);
			this->textBox1->TabIndex = 3;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(599, 172);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}

		void SendImageToServer(Bitmap^ image)
		{
			int width = image->Width;
			int height = image->Height;
			array<Color>^ pixelData = gcnew array<Color>(width * height);

			for (int x = 0; x < width; x++)
			{
				for (int y = 0; y < height; y++)
				{
					pixelData[x + y * width] = image->GetPixel(x, y);
				}
			}


			array<Byte>^ imageData = gcnew array<Byte>(width * height * 4);

			for (int i = 0; i < width * height; i++)
			{
				imageData[i * 4] = pixelData[i].A;
				imageData[i * 4 + 1] = pixelData[i].R;
				imageData[i * 4 + 2] = pixelData[i].G;
				imageData[i * 4 + 3] = pixelData[i].B;
			}

			UdpClient^ udpClient = gcnew UdpClient("127.0.0.1", 12345);
			IPEndPoint^ endPoint = gcnew IPEndPoint(IPAddress::Parse("127.0.0.1"), 12345);

			udpClient->Send(imageData, imageData->Length, endPoint);
			udpClient->Close();
		}

#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ buf_com = textBox1->Text;
		SendMessage(buf_com);
	}

	};
}
