#include <catch2/catch_test_macros.hpp>
#include <VExercise3.h>
#include <cstdint>
#include <stdlib.h>

// calculate output of Mystery1
uint8_t mystery1(uint8_t a, uint8_t b, uint8_t c) {
  uint8_t d = 0;
  switch(a) {
    case 0: 
      d = ((b & 7) << 3) | (c & 7);
    case 1:
      d = (1 << 6) | ((c & 7) << 3) | (b & 7);
    case 2:
      d = b;
    case 3:
      d = c;
  }
  return d;
}

// calculate output of Mystery2
uint16_t mystery2(uint8_t a, uint8_t b, bool reset) {
  uint16_t out;
  uint8_t state = 0;
  if (reset) {
    out = (b << 8) | a);
    return out;
  }
  else {
    switch(state) {
      case 0:
        out = (a << 8) | (out & 255);
        state++;
        return out;
      case 1:
        out = (out & 65280) | (b & 255);
        state++;
        return out;
      case 2:
        out = (out << 8) | (out >> 8);
        state++;
        return out;
      case 3:
        out = (out << 12) | ((out & 240) << 4) | ((out & 3840) >> 4) | ((out & 61440) >> 12);
        state++;
        return out;
      case 4:
        bool xor_out = out & 1;
        for (int i = 0; i < 16; i++) {
          xor_out = xor_out ^ ((out >> i) & 1);
        }
        state = 0;
        return xor_out;
    }
  }
}

TEST_CASE("Exercise 3") {
  VExercise3 model;
  bool reset;
  bool clk;
  uint8_t a;
  uint16_t b;
  uint16_t c;
  uint16_t expected_out;
  
  for (int i = 0; i < 5000; i++) {
    a = rand() % 15;
    b = rand() % 65535;
    c = rand() % 65535;
    
    //setting initial state
    model.clk = 1;
    model.reset = 0;
    model.eval();
    
    //setting initial inputs & testing high reset
    model.clk = 0;
    model.reset = 1;
    model.a = a;
    model.b = b;
    model.c = c;
    model.eval();
    
    //test initial inputs & high reset
    uint8_t alpha = mystery1((a & 3), (b & 255), (c & 255));
    uint8_t beta = mystery((a >> 2), (b >> 8), (c >> 8));
    expected_out = mystery2(alpha, beta, 1);
    REQUIRE(model.out == expected_out);
    
    for (int i = 0; i < 5; i++) {
      //reset to initial state
      model.clk = 1;
      model.reset = 0;
      model.eval();
    
      //test low reset & 5 states of Mystery2
      model.clk = 0;
      model.reset = 0;
      model.a = a;
      model.b = b;
      model.c = c;
      model.eval();
      expected_out = mystery2(alpha, beta, 0);
      REQUIRE(model.out == expected_out);
    }
  }
}
