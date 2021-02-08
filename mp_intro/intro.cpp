#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>

using namespace cs225;

void rotate(std::string inputFile, std::string outputFile) {
    PNG img = PNG();
    PNG original = img;
    original.readFromFile(inputFile);

    unsigned width = original.width();
    unsigned height = original.height();

    PNG output = PNG(width, height);
    for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
            output.getPixel(width - i - 1, height - j - 1) = original.getPixel(i, j);
        }
    }
    output.writeToFile(outputFile);
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
    cs225::PNG png(width, height);
    double start_h = 100;
    double final_h = 270;
    double start_s = 0.5;
    double final_s = 0.9;
    for (size_t i = 0; i < width; i++) {
        for (size_t j = 0; j < height; j++) {
            double w_p = (double) i / (double) width;
            double h_p = (double) j / (double) height;
            png.getPixel(i, j) = HSLAPixel(start_h + w_p * (final_h - start_h), start_s + h_p * (final_s - start_s),
                                           0.8);
        }
    }
    return png;
}
