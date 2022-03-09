#include <catch2/catch.hpp>

#include <gas_container.h>

using namespace idealgas;

TEST_CASE("Placeholder test") {
  GasContainer container;
  container.AdvanceOneFrame();
  REQUIRE(1 > 0);
}

TEST_CASE("just testing") {
  vec2 v1(0, 0);
  vec2 v2(5, 12);
  REQUIRE(glm::distance(v1, v2) == 13);
}

/*
TODO: Rename this test file. You'll also need to modify CMakeLists.txt.

You can (and should) create more test files; this project is too big
for all tests to be in the same file. Remember that, for each file (foo.cc)
containing non-trivial code, you should have a corresponding test file
(foo_test.cc)

Make sure to add any files that you create to CMakeLists.txt.

TODO Delete this comment and the placeholder test before submitting your code.
*/
