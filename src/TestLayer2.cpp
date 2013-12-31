#include "TestLayer2.h"

float time_;
string holes;
//--------------------------------------------------------------------------------------------------------------
void TestLayer2::setup(){
    flag = false;
    a = 150;
    ofSetFrameRate(30);
}

//--------------------------------------------------------------------------------------------------------------
void TestLayer2::update(){
    
}
//--------------------------------------------------------------------------------------------------------------
void TestLayer2::draw(){

    int tempMax = p[0].y;

    ofBackground(0,0,0,0);
    ofSetColor(150, 50, 50, a);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    
    if (holes == "found") flag = true;
    if (flag == true) {
        for (int i=0; i<NUM; i++) {
            p[i].update();
            p[i].draw();
            if(p[i].y > tempMax) tempMax = p[i].y;
        }

        if (tempMax <= -5) {
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