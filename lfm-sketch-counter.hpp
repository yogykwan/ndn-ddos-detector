#ifndef LFM_SKETCH_COUNTER_HPP
#define LFM_SKETCH_COUNTER_HPP

#include "counter.hpp"
#include <string>
#include <algorithm>
#include <cstring>
#include <cmath>

class LFMSketchCounter: public Counter{

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

    int count(){
        double sketch = 0.0;
        for(int i=0; i<720; ++i){
            sketch += bitmap[i];
        }
        sketch /= 720;
        int cnt = (int)pow(2, sketch);
        return cnt;
    }

    int* getSketch() {
    	return bitmap;
    }

    void flush(){
        memset(bitmap,0,sizeof(bitmap));
    }

protected:

    int bitmap[720];

    long long JShash(std::string str, int salt) {
        long long MOD = 262144;
        long long hash = 1315423911%MOD;
        for(int i = 0; str[i]; i++) {
            hash ^= ((hash << 5) + str[i] + (hash >> 2));
            hash %= MOD;
        }
        return (hash+hash*salt)%MOD;
    }

    void getLeftmostOne(std::string str, int* left1){
//        long long hash = JShash(str, 0);
    	std::hash<std::string> hs;
    	long long hash = hs(str);
        int hashCuts[6];
        for(int i=0;i<6;++i){
            int tmp = hash & 7;
            hashCuts[i] = 0;
            while(tmp){
                hashCuts[i]++;
                if(tmp&1) break;
                tmp>>=1;
            }
            hash >>= 3;
        }
        int id = 0;
        int per[6] = {0,1,2,3,4,5};
        do{
            int i;
            for(i=0; i<6; ++i){
                if(hashCuts[per[i]]){
                    break;
                }
            }
            left1[id] = 3*i + hashCuts[per[i]] - 1;
            id++;
        }while(std::next_permutation(per, per+6));
    }

};


#endif
