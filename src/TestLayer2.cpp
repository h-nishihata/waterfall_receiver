#include "TestLayer2.h"

string holes;

//--------------------------------------------------------------------------------------------------------------
void TestLayer2::update(){
    
}
//--------------------------------------------------------------------------------------------------------------
void TestLayer2::draw(){
    
    ofTranslate(0, 900);
    ofRotateX(180);
    
    
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofBackgroundGradient(ofColor(255,0,0,220),ofColor(255,255,0,190), OF_GRADIENT_LINEAR);
    
    
    int tempMax = p[0].x;
    
    if (holes == "found"){
        flag = true;
    }
    
    if (flag == true) {
        
            for (int i=0; i<NUM; i++) {
                
                p[i].update();
                p[i].draw();
                if(p[i].x > tempMax) tempMax = p[i].x;
                
            }
            
            if (tempMax <= 0) {
                
                flag = false;
                for (int i=0; i<NUM; i++) {
                    p[i].reset();
                    tempMax = p[0].x;
                }
                
            }
        
    }
    
}