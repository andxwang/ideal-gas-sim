//
// Created by Andy Wang on 3/23/22.
//

#include <catch2/catch.hpp>

#include <histogram.h>

using namespace idealgas;

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

TEST_CASE("Frequencies vector updates correctly") {
  SECTION("Simple") {
    Histogram hist({vec2(100, 100), vec2(300, 300)}, {}, ci::Color("red"));
    vector<float> new_v = {4, 5, 6};
    hist.Update(new_v);
    REQUIRE(vector<int> {0, 0, 0, 0, 1, 1, 1, 0, 0, 0} == hist.GetFrequencies());
  }

  SECTION("More complicated") {
    Histogram hist({vec2(100, 100), vec2(300, 300)}, {}, ci::Color("red"));
    vector<float> new_v = {0.1, 0.1, 0.9,
                           2.4, 2.8,
                           3.9,
                           5.0, 5.1, 5.2, 5.3, 5.4,
                           6.9, 6.99,
                           7.7, 7.77, 7.777,
                           9.9999};
    hist.Update(new_v);
    REQUIRE(vector<int> {3, 0, 2, 1, 0, 5, 2, 3, 0, 1} == hist.GetFrequencies());
  }
}