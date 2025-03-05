#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>
#include <limits>
#include <fstream>
#include <utility>
#include <cctype>
#include <sstream> 
#include <queue>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <numeric>
#include <functional>
#include <cmath>
#include <bitset>
#include <random>
#include <chrono>

#include "lodepng.h"
#include "lettermaker.hpp"


using namespace std;



void saveGridAsPNG(const std::vector<std::vector<int>>& grid, const std::string& filename) {
        // Get grid dimensions
        size_t height = grid.size();
        if (height == 0) return; // Empty grid
        size_t width = grid[0].size();

        // Create a 1D array to store the image pixels
        std::vector<unsigned char> image(width * height * 4, 255); // Initialize to white (RGBA)

        for (size_t y = 0; y < height; ++y) {
            for (size_t x = 0; x < width; ++x) {
                size_t idx = 4 * (y * width + x); // Index in the 1D array
                if (grid[y][x] == 1) {
                    image[idx + 0] = 255; // Red
                    image[idx + 1] = 255; // Green
                    image[idx + 2] = 255; // Blue
                } else {
                    image[idx + 0] = 0;   // Red
                    image[idx + 1] = 0;   // Green
                    image[idx + 2] = 0;   // Blue
                }
                image[idx + 3] = 255; // Alpha (fully opaque)
            }
        }

        std::string fullPath = "pics/" + filename;
        // Encode the image as a PNG and save it to the file
        unsigned error = lodepng::encode(fullPath, image, width, height);
        if (error) {
            throw std::runtime_error("Error saving PNG: " + std::string(lodepng_error_text(error)));
        }
}

int main(){

    cout << "What letters do you want to combind?" << endl;
    string input;
    cin >> input;

    lettermaker me(input, 9);
    
    string filename = input + "_.png";

    // for(auto l : me.getVec()){
    //     for(auto c : l){
    //         cout << c;
    //     }
    //     cout << endl;
    // }

    saveGridAsPNG(me.getVec(), filename);
    cout << "Success " << endl;
    return 0;
}