//
// Created by Andy Wang on 3/23/22.
//

#include <catch2/catch.hpp>

#include <histogram.h>

using namespace idealgas;

TEST_CASE("Empty vector of values passed in") {
  REQUIRE_THROWS_AS(Histogram({vec2(100, 100), vec2(300, 300)},
                              vector<float> {},
                              ci::Color("blue")),
                    std::invalid_argument);
}

TEST_CASE("Frequencies vector is correct") {
  SECTION("Simple") {
    vector<float> v = {1, 2, 3};
    Histogram hist({vec2(100, 100), vec2(300, 300)}, v, ci::Color("red"));
    REQUIRE(vector<int>{0, 1, 1, 1, 0, 0, 0, 0, 0, 0} == hist.GetFrequencies());
  }

  SECTION("More complicated") {
    vector<float> v = {0.1, 0.2, 0.5, 0.5, 0.8,
                       1.0, 1.1, 1.1, 1.39,
                       2.69, 2.72,
                       5.892, 5.999,
                       7.01,
                       8.23, 8.47,
                       9.08, 9.99, 9.999};
    Histogram hist({vec2(100, 100), vec2(300, 300)}, v, ci::Color("red"));
    REQUIRE(vector<int> {5, 4, 2, 0, 0, 2, 0, 1, 2, 3} == hist.GetFrequencies());
  }
}