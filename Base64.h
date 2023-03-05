#pragma once

#include <string>
#include <vector>

#ifndef Base64_H
#define Base64_H

extern "C" {

	__declspec(dllexport) class Base64 {
	private:
		static const std::string base64_chars;
		std::string* value;

		std::vector<unsigned char> __stdcall stringToBytes(const std::string&);
		std::string __stdcall bytesToString(const std::vector<unsigned char>&);

		std::string __stdcall encodeInternal(const std::string&);
		std::string __stdcall decodeInternal(const std::string&);
	public:
		__stdcall Base64();

		void __stdcall init(std::string*);
		void __stdcall init(const char*);
		void __stdcall init(const std::vector<unsigned char>&);

		__stdcall ~Base64();

		 bool __stdcall isEmpty();
		 std::string __stdcall getValue();
		 const char* __stdcall get();
		 const std::vector<unsigned char> __stdcall getByteArray();

		 std::string __stdcall encodeAsString();
		 std::vector<unsigned char> __stdcall encodeAsBytes();

		 std::string __stdcall decodeAsString();
		 std::vector<unsigned char> __stdcall decodeAsBytes();

		 bool __stdcall isValid(const std::string&);
	};

}

#endif // !Base64_H
