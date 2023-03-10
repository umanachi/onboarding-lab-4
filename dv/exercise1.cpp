#include <catch2/catch_test_macros.hpp>
#include <VExercise1.h>
#include <cstdint>

void test(uint8_t opcode, uint8_t(op)(uint8_t, uint8_t)) {
  VExercise1 model;
  model.op = opcode;
  model.a = 0;
  model.b = 0;
  
  do {
    do {
      model.eval();
      uint8_t result {op(model.a, model.b)};
      REQUIRE(result == model.out);
    } while (++model.b);
  } while (++model.a);
}
 

TEST_CASE("Opcode 0, XOR") {
  test(0, [](uint8_t a, uint8_t b) -> uint8_t { return a ^ b; });
}

TEST_CASE("Opcode 1, Left Shift") {
  test(1, [](uint8_t a, uint8_t b) -> uint8_t { return a << b; });
}

TEST_CASE("Opcode 2, Mod") {
  test(2, [](uint8_t a, uint8_t b) -> uint8_t { return a % b; });
}

TEST_CASE("Opcode 3, ~(A & B)") {
  test(3, [](uint8_t a, uint8_t b) -> uint8_t { return ~(a&b); });
}
