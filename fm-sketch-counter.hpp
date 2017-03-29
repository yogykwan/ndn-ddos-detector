#ifndef FM_SKETCH_COUNTER_HPP
#define FM_SKETCH_COUNTER_HPP


#include "lfm-sketch-counter.hpp"
#include <string>
#include <sstream>

class FMSketchCounter: public LFMSketchCounter{

public:

    void addItem(std::string item){
        int left1[720];
        getLeftmostOne(item, left1);
        for(int i=0;i<720;++i){
            if(left1[i] > bitmap[i]){
                bitmap[i] = left1[i];
            }
        }
    }
protected:

    void getLeftmostOne(std::string str, int* left1){
        int i,j;
        for(i=0; i<720; ++i){
//            long long hash = JShash(str, i);
        	std::stringstream ss;
        	std::string salt;
        	ss << i;
        	ss >> salt;
        	std::hash<std::string> hs;
            long long hash = hs(str + salt);
            for(j=0; j<18; ++j){
                if(hash&1) break;
                hash >>= 1;
            }
            left1[i] = j;
        }
    }

};


#endif
