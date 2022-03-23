//
// Created by Andy Wang on 3/21/22.
//

#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "cinder/gl/gl.h"

using namespace glm;
using glm::vec2;
using std::vector;

#ifndef IDEAL_GAS_MY_PROJECTS_IDEAL_GAS_ANDYW_GIT_INCLUDE_HISTOGRAM_H_
#define IDEAL_GAS_MY_PROJECTS_IDEAL_GAS_ANDYW_GIT_INCLUDE_HISTOGRAM_H_

namespace idealgas {

class Histogram {

 public:
  Histogram(const std::pair<vec2, vec2> &coords, const vector<float> &values, const cinder::Color &hist_color);
  void Draw();
  const std::pair<vec2, vec2> &GetCoords() const;
  const vector<float> &GetValues() const;
  const vector<int> &GetFrequencies() const;
  double GetMaxY() const;
  double GetMaxX() const;

 private:
  std::pair<vec2, vec2> coords_; // first is top left, second is bottom right
  vector<float> values_;
  vector<int> frequencies_;
  const int kBinSize = 1; // bin size for speed
  const int kNumBins = 10; // binSize * numBins = max x
  const int kBarWidth = 30;
  const int kBarHeightUnit = 10;
  const int kNumYTicks = 8;
  double max_y_; // max frequency
  double max_x_; // max of values_
  ci::Color hist_color_;
};

}

#endif //IDEAL_GAS_MY_PROJECTS_IDEAL_GAS_ANDYW_GIT_INCLUDE_HISTOGRAM_H_
