#include <catch2/catch_test_macros.hpp>
#include <VExercise4.h>
#include <cstdint>
#include <stdlib.h>

TEST_CASE("Sel: Don't Care") {
  VExercise4 model;
  model.alpha = 0;
  model.beta = 1;
  model.gamma = 2;
  model.cs = 0;
  for (model.s = 0; model.s < 4; model.s++) {
    model.eval();
    REQUIRE(model.out == 0);
  }
}

TEST_CASE("Sel: 0-2") {
  VExercise4 model;
  model.alpha = 0;
  model.beta = 1;
  model.gamma = 2;
  model.cs = 0;
  for (model.s = 0; model.s < 3; model.s++) {
    model.eval();
    REQUIRE(model.out == model.s);
  }
}

TEST_CASE("Sel: 3"){
  VExercise4 model;
  model.alpha = 0;
  model.beta = 1;
  model.gamma = 2;
  model.eval();
  REQUIRE(model.out == (model.alpha & (model.beta | model.gamma)));
}
