#include "TestLayer2.h"

float time_;
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
    
    int tempMax = p[0].y;
    
    if (holes == "found") flag = true;
    if (flag == true) {
        for (int i=0; i<NUM; i++) {
            p[i].update();
            p[i].draw();
            if(p[i].y > tempMax) tempMax = p[i].y;
        }
        
        if (tempMax <= -500) {
            flag = false;
            for (int i=0; i<NUM; i++) {
                p[i].reset();
                tempMax = p[0].y;
                
            }
        }
    }
    
    
    
    //    //　　暗転
    //    if (time_ < 0.01) {
    //        ofSetColor(0, 0, 0, 255);
    //        ofRect(0, 0, ofGetWidth(), ofGetHeight());
    //    }
    
}