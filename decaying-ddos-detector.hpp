#ifndef DECAYING_DDOS_DETECTOR_HPP
#define DECAYING_DDOS_DETECTOR_HPP


#include "counter.hpp"
#include "counter-factory.hpp"

#include <sys/time.h>
#include <queue>
#include <cstring>
#include <iostream>
#include <cmath>
#include <ctime>
#include <algorithm>

class DecayingDDoSDetector {

public:
  DecayingDDoSDetector() {
    type = 'L';
    threshold = 1000;
    curSlot = 0;
    totSlot = (type == 'L') ? 10 : 1;
    counter = new Counter *[totSlot];

    for (int i = 0; i < totSlot; ++i) {
      counter[i] = CounterFactory::createCounter(type);
    }
    struct timeval tv;
    gettimeofday(&tv, NULL);
    start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
  }

  ~DecayingDDoSDetector() {
    for (int i = 0; i < totSlot; ++i) {
      delete counter[i];
    }
    delete[] counter;
  }

  std::string addItem(std::string item) {
//        clock_t now = gettimeofday();
    struct timeval tv;
    gettimeofday(&tv, NULL);
    clock_t now = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    if (now - start >= 100) {
      newSlot();
      start = now;
    }
    counter[curSlot]->addItem(item);

    if(isAttacking()) {
      return item;
    } else {
      return "safe";
    }
  }

  bool isAttacking() {
    int cnt = count();
    //std::cout << "cnt = " << cnt << std::endl;
    if (cnt > threshold) {
      //std::cout << "Attacking: " << cnt << std::endl;
      return true;
    }
    return false;
  }

  void newSlot() {
    if (type != 'U') {
      int nextSlot = (curSlot + 1) % totSlot;
      curSlot = nextSlot;
    }
    counter[curSlot]->flush();
  }

  int count() {
    if (type == 'U') {
      return counter[0]->count();
    } else {
      double sketch = 0.0;
      memset(bitmap, 0, sizeof(bitmap));
      for (int i = 0; i < totSlot; ++i) {
        int *slotBitmap = counter[i]->getSketch();
        for (int j = 0; j < 720; ++j) {
          bitmap[j] = std::max(bitmap[j], slotBitmap[j]);
        }
      }
      for (int i = 0; i < 720; ++i) {
        sketch += bitmap[i];
      }
      sketch /= 720;
      int cnt = (int) pow(2, sketch);
      return cnt;
    }
  }

private:
  int threshold;
  Counter **counter;
  int curSlot;
  int totSlot;
  clock_t start;
  int bitmap[720];
  char type;
};


#endif
