
#include "Base64.h"
#include <string>

const std::string Base64::base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

bool __stdcall Base64::isEmpty() {
	return value->length() == 0;
}

__stdcall Base64::Base64() {
	value = nullptr;
}

void __stdcall Base64::init(std::string* value) {
	this->value = value;
}

void __stdcall Base64::init(const char* str) {
	this->value = new std::string(str);
}

void __stdcall Base64::init(const std::vector<unsigned char>& byteArray) {
	this->value = new std::string(this->bytesToString(byteArray).c_str());
}

__stdcall Base64::~Base64() {
	delete value;
}

 std::string __stdcall Base64::getValue() {
	 return std::string(this->value->c_str());
}

 const char* __stdcall Base64::get() {
	 return this->value->c_str();
 }

 std::vector<unsigned char> __stdcall Base64::stringToBytes(const std::string& input) {
	 std::vector<unsigned char> output(input.size());
	 for (std::size_t i = 0; i < input.size(); ++i) {
		 output[i] = static_cast<unsigned char>(input[i]);
	 }
	 return output;
 }

 std::string __stdcall Base64::bytesToString(const std::vector<unsigned char>& input) {
	 return std::string(input.begin(), input.end());
 }

 const std::vector<unsigned char> __stdcall Base64::getByteArray() {
	 return this->stringToBytes(*value);
 }


 std::string __stdcall Base64::encodeInternal(const std::string& input) {
	 std::string encoded;
	 int i = 0;
	 int current_byte;
	 int next_byte;
	 while (i < input.size()) {
		 current_byte = (unsigned char)input[i] >> 2;
		 encoded += base64_chars[current_byte];
		 current_byte = (input[i] & 0x03) << 4;
		 if (i + 1 < input.size()) {
			 next_byte = (unsigned char)input[i + 1] >> 4;
			 encoded += base64_chars[current_byte | next_byte];
			 current_byte = (input[i + 1] & 0x0F) << 2;
			 if (i + 2 < input.size()) {
				 next_byte = (unsigned char)input[i + 2] >> 6;
				 encoded += base64_chars[current_byte | next_byte];
				 encoded += base64_chars[input[i + 2] & 0x3F];
			 }
			 else {
				 encoded += base64_chars[current_byte];
				 encoded += "=";
			 }
		 }
		 else {
			 encoded += base64_chars[current_byte];
			 encoded += "==";
		 }
		 i += 3;
	 }
	 return encoded;
 }

 std::string __stdcall Base64::encodeAsString() {
	 return encodeInternal(*value);
 }

 std::vector<unsigned char> __stdcall Base64::encodeAsBytes() {
	 return stringToBytes(encodeInternal(*value));
 }

 std::string __stdcall Base64::decodeInternal(const std::string& input) {
	std::string decoded;
	int i = 0;
	int index = 0;
	while (i < input.size()) {
		index = base64_chars.find(input[i]) << 18;
		if (i + 1 < input.size()) {
			index |= base64_chars.find(input[i + 1]) << 12;
			if (i + 2 < input.size() && input[i + 2] != '=') {
				index |= base64_chars.find(input[i + 2]) << 6;
				if (i + 3 < input.size() && input[i + 3] != '=') {
					index |= base64_chars.find(input[i + 3]);
				}
			}
		}
		decoded += (unsigned char)(index >> 16);
		if (i + 2 < input.size() && input[i + 2] != '=') {
			decoded += (unsigned char)(index >> 8);
			if (i + 3 < input.size() && input[i + 3] != '=') {
				decoded += (unsigned char)index;
			}
		}
		i += 4;
	}
	return decoded;
 }

 std::string __stdcall Base64::decodeAsString() {
	 return decodeInternal(*value);
 }

 std::vector<unsigned char> __stdcall Base64::decodeAsBytes() {
	 return stringToBytes(decodeInternal(*value));
 }

 bool __stdcall Base64::isValid(const std::string& input) {
	 // Check if the length of the input string is a multiple of 4
	 if (input.length() % 4 != 0) {
		 return false;
	 }

	 // Check if all characters in the input string are valid Base64 characters
	 for (std::size_t i = 0; i < input.length(); ++i) {
		 if (input[i] != '=' && base64_chars.find(input[i]) == std::string::npos) {
			 return false;
		 }
	 }

	 return true;
 }