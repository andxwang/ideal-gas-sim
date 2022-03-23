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
  /**
   * Constructor for a Histogram object.
   * @param coords a pair of vec2 representing the top left
   * and bottom right coordinates of the histogram, respectively
   * @param values a vector of floats of the values
   * for the histogram to plot
   * @param hist_color the color of the histogram
   */
  Histogram(const std::pair<vec2, vec2> &coords, const vector<float> &values, const cinder::Color &hist_color);

  /**
   * Draws the histogram at the given coordinates.
   */
  void Draw();
  /**
   * Updates the histogram's values and frequencies.
   * @param values a vector of values to be plotted by the histogram
   */
  void Update(const vector<float> &values);
  const std::pair<vec2, vec2> &GetCoords() const;
  const vector<float> &GetValues() const;
  const vector<int> &GetFrequencies() const;

 private:
  std::pair<vec2, vec2> coords_; // first is top left, second is bottom right
  vector<float> values_;
  vector<int> frequencies_;
  const int kBinSize = 1; // bin size for speed
  const int kNumBins = 10; // binSize * numBins = max x
  const int kBarWidth = 30;
  const int kBarHeightUnit = 10;
  const int kNumYTicks = 8;
  ci::Color hist_color_;
};

}

#endif //IDEAL_GAS_MY_PROJECTS_IDEAL_GAS_ANDYW_GIT_INCLUDE_HISTOGRAM_H_
