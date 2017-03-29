#ifndef COUNTER_HPP
#define COUNTER_HPP

#include <string>


class Counter{

public:

    Counter(){};

    virtual ~Counter(){};

    virtual void addItem(std::string item){}

    virtual int count(){return -1;}

    int* getSketch() {return 0;}

    virtual void flush(){}
};


#endif
