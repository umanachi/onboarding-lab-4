#include <catch2/catch_test_macros.hpp>
#include <VExercise2.h>
#include <cstdint>
#include <stdlib.h>

// calculate expected shifted output
uint16_t lfsr(uint16_t curr) {
  return (curr << 1) | ( ((curr >> 10) & 1) ^ ((curr >> 8) & 1) ^ ((curr >> 3) & 1) ^ ((curr >> 1) & 1));
}

void reading_rainbow(uint16_t input) {
  VExercise2 model;
    
  // initialize module & check reset output
  model.clk = 1;
  model.eval();
  model.clk = 0;
  model.reset = 1;
  model.init = input;
  model.eval();
  
  uint16_t previous = ~input;
  for (int i = 0; i < 10000; i++) {
    model.clk = 1;
    model.reset = 0;
    model.eval();
    model.clk = 0;
    model.reset = 0;
    model.eval();
    REQUIRE(model.out == lfsr(prev));
    previous = model.out;
  }
}

int main() {
  bool master_fail = false;
  for (int i = 0; i < 10; i++) {
    uint16_t test_val = rand() % 65535;
    master_fail = reading_rainbow(test_val);
    return failed;
  }
}

TEST_CASE("Exercise 2") {
  for (int i = 0; i < 15; i++) {
    uint16_t test_val = rand() % 65535;
    reading_rainbow(test_val);
  }
}
