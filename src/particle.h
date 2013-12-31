#ifndef _OF_PARTICLE
#define _OF_PARTICLE

#include "ofMain.h"

class particle{
    
public:
    
    int x;
    int y;
    int r;
    
    particle();
    void draw();
    void update();
    void reset();

};

#endif
