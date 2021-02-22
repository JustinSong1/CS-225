#include "Image.h"

void Image::darken() {
    darken(0.1);
}

void Image::darken(double amount) {
    for (size_t x = 0; x < width(); x++) {
        for (size_t y = 0; y < height(); y++) {
            getPixel(x, y).l = std::max(getPixel(x, y).l - amount, 0.0);
        }
    }
}

void Image::desaturate() {
    desaturate(0.1);
}

void Image::desaturate(double amount) {
    for (size_t x = 0; x < width(); x++) {
        for (size_t y = 0; y < height(); y++) {
            getPixel(x, y).s = std::max(getPixel(x, y).s - amount, 0.0);
        }
    }
}

void Image::grayscale() {
    for (size_t x = 0; x < width(); x++) {
        for (size_t y = 0; y < height(); y++) {
            getPixel(x, y).s = 0.0;
        }
    }
}

void Image::illinify() {
    for (size_t x = 0; x < width(); x++) {
        for (size_t y = 0; y < height(); y++) {
            cs225::HSLAPixel &pixel = getPixel(x, y);
            double blue_dist = std::min(abs(pixel.h - 216), abs(pixel.h - (-144)));
            double orange_dist = std::min(abs(pixel.h - 371), abs(pixel.h - 11));
            if (blue_dist > orange_dist) {
                pixel.h = 11;
            } else {
                pixel.h = 216;
            }
        }
    }
}

void Image::lighten() {
    lighten(0.1);
}

void Image::lighten(double amount) {
    for (size_t x = 0; x < width(); x++) {
        for (size_t y = 0; y < height(); y++) {
            getPixel(x, y).l = std::min(getPixel(x, y).l + amount, 1.0);
        }
    }
}

void Image::rotateColor(double degrees) {
    for (size_t x = 0; x < width(); x++) {
        for (size_t y = 0; y < height(); y++) {
            getPixel(x, y).h = fmod((getPixel(x, y).h + degrees), 360.0);
        }
    }
}

void Image::saturate() {
    saturate(0.1);
}

void Image::saturate(double amount) {
    for (size_t x = 0; x < width(); x++) {
        for (size_t y = 0; y < height(); y++) {
            getPixel(x, y).s = std::min(getPixel(x, y).s + amount, 1.0);
        }
    }
}

void Image::scale(double factor) {
    PNG newImage = PNG(width() * factor, height() * factor);
    for (size_t x = 0; x < newImage.width(); x++) {
        for (size_t y = 0; y < newImage.height(); y++) {
            newImage.getPixel(x, y) = getPixel(x/factor, y/factor);
        }
    }
    resize(width() * factor, height() * factor);
    for (size_t x = 0; x < newImage.width(); x++) {
        for (size_t y = 0; y < newImage.height(); y++) {
            getPixel(x, y) = newImage.getPixel(x, y);
        }
    }
}

void Image::scale(unsigned int w, unsigned int h) {
    double wFactor = static_cast<double>(w)/static_cast<double>(width());
    double hFactor = static_cast<double>(h)/static_cast<double>(height());
    PNG newImage = PNG(w, h);
    for (size_t x = 0; x < newImage.width(); x++) {
        for (size_t y = 0; y < newImage.height(); y++) {
            newImage.getPixel(x, y) = getPixel(x/wFactor, y/hFactor);
        }
    }
    resize(w, h);
    for (size_t x = 0; x < newImage.width(); x++) {
        for (size_t y = 0; y < newImage.height(); y++) {
            getPixel(x, y) = newImage.getPixel(x, y);
        }
    }
}