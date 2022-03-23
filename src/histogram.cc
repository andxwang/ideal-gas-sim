//
// Created by Andy Wang on 3/21/22.
//

#include "histogram.h"
#include <iostream>

namespace idealgas {

Histogram::Histogram(const std::pair<vec2, vec2> &coords,
                     const vector<float> &values,
                     const cinder::Color &hist_color)
    : coords_(coords), values_(values), hist_color_(hist_color) {
  if (values.size() == 0)
    throw std::invalid_argument("Values vector must have at least one value to create histogram!");
  frequencies_ = vector<int> (kNumBins, 0);
  for (float value : values_) {
    int idx = (int) (value / kBinSize);
    if (idx < frequencies_.size()) {
      frequencies_[idx]++;
    }
  }
}

void Histogram::Draw() {
  for (int i = 0; i < kNumBins; i++) {
    double bar_height = kBarHeightUnit * frequencies_[i];
    vec2 bar_bottom_right(coords_.first.x + kBarWidth * (i + 1),
                          coords_.second.y);
    vec2 bar_top_left(coords_.first.x + kBarWidth * i,
                      coords_.second.y - bar_height);
    // draw bar
    ci::Rectf bar(bar_top_left, bar_bottom_right);
    ci::gl::color(ci::Color(hist_color_));
    ci::gl::drawSolidRect(bar);
    // draw tick marks on x-axis
    ci::gl::color(ci::Color("white"));
    ci::gl::drawLine(bar_bottom_right,
                     vec2(bar_bottom_right.x, bar_bottom_right.y + 10));
    // draw x-axis increments
    ci::gl::drawStringCentered(std::to_string((i+1) * kBinSize),
                               bar_bottom_right,
                               ci::Color("white"),
                               ci::Font("arial", 10));
    // draw axes
    ci::gl::drawLine(coords_.first, vec2(coords_.first.x, coords_.second.y));
    ci::gl::drawLine(vec2(coords_.first.x, coords_.second.y), coords_.second);
  }
  // draw labels
  ci::gl::drawStringCentered("Speed",
                             vec2((coords_.second.x + coords_.first.x)/2,
                                  coords_.second.y + 10),
                             ci::Color("white"),
                             ci::Font("arial", 20));
  // draw tick marks on y-axis. kNumYTicks total
  ci::gl::color(ci::Color("white"));
  for (int i = 0; i < kNumYTicks; i++) {
    vec2 right = vec2(coords_.first.x,
                      coords_.second.y - (i+1) *
                      (coords_.second.y - coords_.first.y) / kNumYTicks);
    vec2 left = right - vec2(10, 0);
    ci::gl::drawLine(left, right);
    float y_val = (coords_.second.y-coords_.first.y)/kNumYTicks / kBarHeightUnit * (i+1);
    ci::gl::drawString(std::to_string(y_val),left);
  }
}

void Histogram::Update(const vector<float> &values) {
  values_ = values;
  // reset frequencies to 0
  std::fill(frequencies_.begin(), frequencies_.end(), 0);
  for (float value : values_) {
    int idx = (int) (value / kBinSize);
    if (idx < frequencies_.size()) {
      frequencies_[idx]++;
    }
  }
}

const std::pair<vec2, vec2> &Histogram::GetCoords() const {
  return coords_;
}

const vector<float> &Histogram::GetValues() const {
  return values_;
}

const vector<int> &Histogram::GetFrequencies() const {
  return frequencies_;
}

}