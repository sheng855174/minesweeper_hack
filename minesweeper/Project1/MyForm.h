#include <windows.h>
#include <iostream>
#include <inttypes.h>
#include <stdint.h>
#include <string> 
#include<sstream>


#pragma once

namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MyForm 的摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
		}
		void appendLog(String^ msg) {
			richTextBox1->AppendText(msg);
		}
	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RichTextBox^ richTextBox1;
	private: System::Windows::Forms::Button^ button1;
	protected:

	protected:

	protected:

	protected:

	protected:

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(21, 12);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->ReadOnly = true;
			this->richTextBox1->Size = System::Drawing::Size(576, 372);
			this->richTextBox1->TabIndex = 0;
			this->richTextBox1->Text = L"";
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->button1->Location = System::Drawing::Point(622, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(115, 43);
			this->button1->TabIndex = 1;
			this->button1->Text = L"顯示地雷";
			this->button1->TextImageRelation = System::Windows::Forms::TextImageRelation::TextAboveImage;
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(749, 396);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->richTextBox1);
			this->Name = L"MyForm";
			this->Text = L"DLL";
			this->ResumeLayout(false);

		}


		private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
			char msg_buff[4096];
			System::String^ msg;

			//取得基址
			uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"Minesweeper.exe");
			moduleBase = (uintptr_t)GetModuleHandle(NULL);
			
			//取得時間
			uintptr_t* time = (uintptr_t*)(moduleBase + 0xAAA38);
			time = (uintptr_t*)(*time + 0x18);
			time = (uintptr_t*)(*time + 0x20);

			//轉LSB
			unsigned char float_byte[4];
			float result_float;
			for (int i = 0;i < 4;i++) {
				float_byte[i] = (*time >> 8*i) & 0xFF;
			}
			memcpy(&result_float, &float_byte, sizeof(float));

			this->appendLog("現在時間 : " + result_float.ToString() + "秒\n");

			//Minesweeper.exe+AAA38
			int size = 9;
			uintptr_t* sweepers = (uintptr_t*)(moduleBase + 0xAAA38);
			sweepers = (uintptr_t*)(*sweepers + 0x18);
			sweepers = (uintptr_t*)(*sweepers + 0x58);
			sweepers = (uintptr_t*)(*sweepers + 0x10);	
			

			for (uintptr_t y = 0; y < size ; y++) {
				for (uintptr_t x = 0; x < size ; x++) {
					uintptr_t* sweepers_tmp;
					sweepers_tmp = (uintptr_t*)(*sweepers + x*0x8);
					sweepers_tmp = (uintptr_t*)(*sweepers_tmp + 0x10);
					sweepers_tmp = (uintptr_t*)(*sweepers_tmp + y);
					this->appendLog(((byte)*sweepers_tmp).ToString() + " ");
				}
				this->appendLog("\n");
			}

			this->appendLog("==============================================\n");
			

		}



	};
}
