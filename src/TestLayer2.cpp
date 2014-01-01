#include "TestLayer2.h"

float time_;
string holes;
ofxCvGrayscaleImage grayDiff;

//--------------------------------------------------------------------------------------------------------------
void TestLayer2::setup(){
    
    flag = false;
    a = 180;
    grayDiff.allocate(960, 540);
    //    ofSetFrameRate(30);
}

//--------------------------------------------------------------------------------------------------------------
void TestLayer2::update(){

    unsigned char* grayPixels = grayDiff.getPixels();
    unsigned char* compositeImgPixels = new unsigned char[540*960*3];
    
    for (int i=0; i<540*960; i++) {
        if (grayPixels[i] == 0) {
            compositeImgPixels[3*i] = 255;
            compositeImgPixels[3*i+1] = 0;
            compositeImgPixels[3*i+2] = 0;
            compositeImgPixels[3*i+3] = 200;
        }else{
            compositeImgPixels[3*i] = 255;
            compositeImgPixels[3*i+1] = 255;
            compositeImgPixels[3*i+2] = 50;
            compositeImgPixels[3*i+3] = 0;
        }
    }
    compositeImg.setFromPixels(compositeImgPixels,960,540);
}
//--------------------------------------------------------------------------------------------------------------
void TestLayer2::draw(){
    
    ofEnableAlphaBlending();
    ofTranslate(855, 940);
    ofRotateZ(270);
    ofRotateX(180);
    ofSetColor(255, 235, 0, a);
    compositeImg.draw(0, 0,ofGetHeight()*1.09,506.25);
    
    int tempMax = p[0].y;
    
    ofBackground(0,0,0,0);
    
    //    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    
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