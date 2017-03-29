#ifndef COUNTER_FACTORY_HPP
#define COUNTER_FACTORY_HPP

#include "counter.hpp"
#include "uci-counter.hpp"
#include "lfm-sketch-counter.hpp"
#include "fm-sketch-counter.hpp"

class CounterFactory{

public:

    static Counter* createCounter(char type) {
        Counter* counter = NULL;
        switch (type) {
            case 'U':
                counter = new UCICounter;
                break;
            case 'F':
                counter = new FMSketchCounter;
                break;
            case 'L':
                counter = new LFMSketchCounter;
                break;
        }
        return counter;
    }
};


#endif