#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
    finished_ = true;
}

ImageTraversal::Iterator::Iterator(ImageTraversal *traversal, const PNG& png, Point start, double tolerance) {
    traversal_ = traversal;
    start_ = start;
    curr_ = start;
    tolerance_ = tolerance;
    png_ = png;
    visited_.resize(png.width(), std::vector<bool>(png.height()));
    for(size_t i = 0; i < visited_.size(); i++) {
        for(size_t j = 0; j < visited_[i].size(); j++) {
            visited_[i][j] = false;
        }
    }
    if (shouldVisit(curr_)) {
        visited_[start.x][start.y] = true;
        finished_ = false;
    } else {
        finished_ = true;
    }
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
    visited_[curr_.x][curr_.y] = true;
    Point right = Point(curr_.x+1, curr_.y);
    Point down = Point(curr_.x, curr_.y+1);
    Point left = Point(curr_.x-1, curr_.y);
    Point up = Point(curr_.x, curr_.y-1);

    if(shouldVisit(right)) traversal_->add(right);
    if(shouldVisit(down)) traversal_->add(down);
    if(shouldVisit(left)) traversal_->add(left);
    if(shouldVisit(up)) traversal_->add(up);

    if(traversal_->empty()) {
        finished_ = true;
        return *this;
    }
    Point next = traversal_->pop();
    while(visited_[next.x][next.y]) {
        if(traversal_->empty()) {
            finished_ = true;
            return *this;
        }
        next = traversal_->pop();
    }
    // while(!traversal_->empty() && !shouldVisit(traversal_->peek())) {
    //     traversal_->pop();
    //     if(traversal_->empty()) {
    //         return *this;
    //     }
    // }

    // if(!traversal_->empty()) {
    //     curr_ = traversal_->peek();
    //     return *this;
    // } else {
    //     finished_ = true;
    //     return *this;
    // }
    // return *this;
    curr_ = next;
    visited_[curr_.x][curr_.y] = true;
    return *this;
}

bool ImageTraversal::Iterator::shouldVisit(Point p) {
    if( p.x >= png_.width()) {
        return false;
    }
    if(p.y >= png_.height()) {
        return false;
    }
    HSLAPixel start = png_.getPixel(start_.x, start_.y);
    HSLAPixel curr = png_.getPixel(p.x, p.y);
    if (calculateDelta(start, curr) <= tolerance_ && !visited_[p.x][p.y]) {
        return true;
    }
    return false;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  return curr_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  return finished_ != other.finished_;
}

