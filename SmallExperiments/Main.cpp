#include <iostream>
#include <string>
#include "BifidCipher.h"

int main() {
	const std::string Key = "BGWKZQPNDSIOAXEFCLUMTHYVR";
	const std::string PlainText = "In cryptography the smallest mistakes can lead to the biggest secrets";

	BifidCipher encryptor(Key);
	std::cout << "Key: " << Key << "\n\n";
	std::cout << "Plain text:     \t" << PlainText << "\n";

	std::string encrypted = encryptor.Cipher(PlainText);
	std::cout << "Ciphered text:  \t" << encrypted << "\n";

	std::string decrypted = encryptor.Decipher(encrypted);
	std::cout << "Deciphered text:\t" << decrypted << "\n";
}