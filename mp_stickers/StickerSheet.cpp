#include "StickerSheet.h"
#include "Image.h"

StickerSheet::StickerSheet(const Image &picture, unsigned int max) {
    base_ = picture;
    max_ = max;
}

StickerSheet::~StickerSheet() {
    for(Image* img : images_) {
        delete img;
    }
    images_.clear();
    positions_.clear();
}

StickerSheet::StickerSheet(const StickerSheet &other) {
    base_ = other.base_;
    max_ = other.max_;
    for(size_t i = 0; i < other.images_.size();i ++) {
        images_.push_back(new Image(*other.images_[i]));
        positions_.push_back(std::vector<unsigned>{other.positions_[i][0], other.positions_[i][1]});
    }
}

int StickerSheet::addSticker(Image &sticker, unsigned int x, unsigned int y) {
    if(images_.size() == max_) {
        return -1;
    }
    images_.push_back(new Image(sticker));
    positions_.push_back(std::vector<unsigned>{x, y});
    return images_.size() - 1;
}

void StickerSheet::changeMaxStickers(unsigned int max) {
    if (max < max_) {
        for (size_t i = 0; i < images_.size(); i++) {
            if (i+1 > max) {
                delete images_[i];
            }
        }
    }
    if(images_.size() > max) {
        images_.resize(max);
        positions_.resize(max);
    }
    max_ = max;
}

Image* StickerSheet::getSticker(unsigned int index) {
    if(index >= images_.size() || index < 0) {
        return NULL;
    } else {
        return images_[index];
    }
}

const StickerSheet& StickerSheet::operator=(const StickerSheet &other) {
    for(Image* img : images_) {
        delete img;
    }
    images_.clear();
    positions_.clear();
    base_ = other.base_;
    max_ = other.max_;
    for(size_t i = 0; i < other.images_.size();i ++) {
        images_.push_back(new Image(*other.images_[i]));
        positions_.push_back(std::vector<unsigned>{other.positions_[i][0], other.positions_[i][1]});
    }
    return *this;
}

void StickerSheet::removeSticker(unsigned int index) {
    if(index >= 0 && index < images_.size()) {
        delete images_[index];
        images_.erase(images_.begin() + index);
        positions_.erase(positions_.begin() + index);
    }
}

Image StickerSheet::render() const {
    unsigned maxX = base_.width();
    unsigned maxY = base_.height();
    for(size_t i = 0; i < images_.size(); i++) {
        if(images_[i]->width() + positions_[i][0] > maxX) {
            std::cout << "RESIZING X";
            maxX = images_[i]->width() + positions_[i][0];
        }
        if(images_[i]->height() + positions_[i][1] > maxY) {
            maxY = images_[i]->height() + positions_[i][1];
        }
    }
    Image output = base_;
    output.resize(maxX, maxY);
    for(size_t i = 0; i < images_.size(); i++) {
        Image img = *images_[i];
        for(size_t x = 0; x < img.width(); x++) {
            for(size_t y = 0; y < img.height(); y++) {
                if(img.getPixel(x, y).a != 0) {
                    output.getPixel(x + positions_[i][0], y +  + positions_[i][1]).h = img.getPixel(x, y).h;
                    output.getPixel(x + positions_[i][0], y +  + positions_[i][1]).s = img.getPixel(x, y).s;
                    output.getPixel(x + positions_[i][0], y +  + positions_[i][1]).l = img.getPixel(x, y).l;
                    output.getPixel(x + positions_[i][0], y +  + positions_[i][1]).a = img.getPixel(x, y).a;
                }
            }
        }
    }
    return output;
}

bool StickerSheet::translate(unsigned int index, unsigned int x, unsigned int y) {
    if(index < 0 || index >= images_.size()) {
        return false;
    } else {
        positions_[index][0] = x;
        positions_[index][1] = y;
        return true;
    }
}