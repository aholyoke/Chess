#ifndef __PRNG_H__
#define __PRNG_H__
#include <tr1/cstdint>

class PRNG {
  uint32_t seed_ ; // same results on 32/64-bit architectures
public:
  PRNG( uint32_t s = 362436069 ) { // set seed
    seed_ = s;
  }
  void seed( uint32_t s ) { // reset seed
    // set seed
    seed_ = s;
  }
  // [0,UINT MAX]
  uint32_t operator()() {
    seed_ = 36969 * (seed_ & 65535) + (seed_ >> 16); // scramble bits
    return seed_ ;
  }
  uint32_t operator()( uint32_t u ) { // [0,u]
    return operator()() % (u + 1); // call operator()()
  }
  uint32_t operator()( uint32_t l, uint32_t u ) { // [l,u]
    return operator()( u - l ) + l; // call operator()( uint32_t )
  }
};

#endif
