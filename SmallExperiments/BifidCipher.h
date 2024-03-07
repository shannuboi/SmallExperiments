// This code uses ranges library which is only available after c++20

#pragma once

#include <string>
#include <map>
#include <utility>
#include <algorithm>
#include <vector>
#include <assert.h>

class BifidCipher
{
    // Some type definitions for better code writability and readability
    typedef std::pair<int, int> Coord;
public:
    BifidCipher(const std::string& key);
    std::string Cipher(const std::string&);
    std::string Decipher(const std::string&);

private:
    // Bifid table represented using two maps
    std::map<Coord, char> coordToLet;
    std::map<char, Coord> letToCoord;
private:
    // Helper Functions
    std::string Preprocess(const std::string&);
};


BifidCipher::BifidCipher(const std::string& key) {
    assert(key.size() == 25);

    // Creating bifid table by filling in maps based on key
    int row = 1;
    int col = 1;
    for (const char& c : key) {
        Coord coord = { row,col };
        letToCoord[c] = coord;
        coordToLet[coord] = c;

        col++;
        if (col > 5) {
            col = 1;
            row++;
        }
    }
    letToCoord['j'] = letToCoord['i'];;
}

std::string BifidCipher::Cipher(const std::string& plaintext) {
    // Remove punctuation and capitalize
    std::string plain = Preprocess(plaintext);

    // Get the row and col of each letter separately
    std::vector<int> coordRows;
    std::vector<int> coordCols;
    for (const char& c : plain) {
        Coord coord = letToCoord[c];
        coordRows.push_back(coord.first);
        coordCols.push_back(coord.second);
    }

    // Combine in a single list with all rows first then all columns
    std::vector<int> flattenedCoords = std::move(coordRows);
    flattenedCoords.insert(
        flattenedCoords.end(),
        coordCols.begin(), coordCols.end()
    );

    // Each pair of ints is a new coord
    auto start = flattenedCoords.begin();
    auto end = flattenedCoords.end();
    std::string cipher;
    for (auto iter = start; iter != end;) {
        int newrow = *iter;
        iter++;
        int newcol = *iter;
        iter++;

        Coord newcoord = { newrow,newcol };
        cipher += coordToLet[newcoord];
    }

    return cipher;
}

std::string BifidCipher::Decipher(const std::string& ciphertext) {
    // Get coord and flatten in a single list with alternating rows and cols
    std::vector<int> flattenedCoords;
    for (const char& c : ciphertext) {
        Coord coord = letToCoord[c];
        flattenedCoords.push_back(coord.first);
        flattenedCoords.push_back(coord.second);
    }

    // Split along the middle. First half are rows, second half are cols
    auto start = flattenedCoords.begin();
    auto middle = flattenedCoords.begin() + flattenedCoords.size() / 2;
    auto end = flattenedCoords.end();

    std::vector<int> rows(start, middle);
    std::vector<int> cols(middle, end);

    // iterate through rows and cols and lookup the corresponding
    std::string decrypted;
    std::ranges::transform(rows, cols, std::back_inserter(decrypted),
        [this](int row, int col) {
            return coordToLet[Coord(row, col)];
        }
    );

    return decrypted;
}


std::string BifidCipher::Preprocess(const std::string& input) {
    // Capitalize
    std::string capitalized;
    std::ranges::transform(input, std::back_inserter(capitalized), toupper);

    // Remove punctuation
    std::string output;
    std::ranges::copy_if(capitalized, std::back_inserter(output), isalpha);

    return output;
}
