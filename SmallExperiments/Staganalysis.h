#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <format>
#include <deque>

int runmain() {

	const unsigned char special_byte_1 = 0xe2;
	const unsigned char special_byte_2 = 0x80;
	const unsigned char special_byte_3v1 = 0x8c;
	const unsigned char special_byte_3v2 = 0x8d;

	std::ifstream f("B.txt");
	bool isCypheringBit = false;
	std::deque<unsigned char> buffer = { 0,0 };

	std::string msgBinary = "";
	while (f) {
		char c;
		f.get(c);
		buffer.push_back(c);

		std::string binary = std::format("{:0>8b}", buffer[2]);
		std::string hex = std::format("{:x}", buffer[2]);

		std::cout << "Char: " << c << "\t" << "bits: " << binary << '\t' << "hex: " << hex << '\n';

		if (buffer[0] != special_byte_1) {
			buffer.pop_front();
			continue;
		}
		if (buffer[1] != special_byte_2) {
			buffer.pop_front();
			continue;
		}
		
		msgBinary += (buffer[2] & 1) ? '1' : '0';
		buffer.pop_front();
	}

	std::cout << "\n\nHidden message in binary:\n" << msgBinary << '\n';

	return 0;
}