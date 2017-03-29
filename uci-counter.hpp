#ifndef UCI_COUNTER_HPP
#define UCI_COUNTER_HPP

#include "counter.hpp"
#include <string>
#include <set>

class UCICounter: public Counter{

public:

    void addItem(std::string item){
        m_set.insert(item);
    }

    int count(){
        return m_set.size();
    }

    void flush(){
        m_set.clear();
    }

private:

    std::set <std::string> m_set;

};


#endif