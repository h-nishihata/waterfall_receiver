#include "TestLayer3.h"

string state;
//--------------------------------------------------------------------------------------------------------------
void TestLayer3::setup(){
    
    ofSetFrameRate(30);
    
    vidPlayer.loadMovie("kegonfalls_07.mp4");
    
    colorImg.allocate(960,540);
    colorImgHSV.allocate(960,540);
    
	grayImage.allocate(960,540);
	grayBg.allocate(960,540);
	grayDiff.allocate(960,540);
    compositeImg.allocate(960,540);
    
	bLearnBakground = true;
    threshold = 180;
    
    for (int n=0; n<nPixels; n++) {
        r[n] = -45;
        g[n] = -40;
        b[n] = -35;
        a[n] = -100;
    }

}

//--------------------------------------------------------------------------------------------------------------
void TestLayer3::update(){
    
    ofEnableAlphaBlending();
    //    if (start_mov == true) {
    vidPlayer.play();
    vidPlayer.update();
    //    }
    time_ = vidPlayer.getPosition();
    
    
    
    //      ********************    CONVERT IMAGE   ********************
    
    colorImg.setFromPixels(vidPlayer.getPixels(), 960,540);
    colorImgHSV = colorImg;
    colorImgHSV.convertRgbToHsv();
    
    grayImage = colorImg;
    
    if (bLearnBakground == true){
        grayBg = grayImage;
        bLearnBakground = false;
    }
    
    grayDiff.absDiff(grayBg, grayImage);
    grayDiff.threshold(threshold);
    
    contourFinder.findContours(grayDiff, 20, (960*540)/3, 10, true);
	
    colorImgRGB = colorImg;
    colorImgRGB.convertHsvToRgb();
    
    
    
    //          ********************  COLORING ROUTINES   ********************
    
    unsigned char* grayPixels = grayDiff.getPixels();
    unsigned char* sampleImgPixels = colorImgRGB.getPixels();
    
    
    
    for (int i=0; i<nPixels; i++) {
        if (grayPixels[i] == 0) {
            compositeImgPixels[3*i] = sampleImgPixels[3*i];
            compositeImgPixels[3*i+1] = sampleImgPixels[3*i+1];
            compositeImgPixels[3*i+2] = sampleImgPixels[3*i+2];
            
        }else{
            compositeImgPixels[3*i] = sampleImgPixels[3*i]+r[i];
            compositeImgPixels[3*i+1] = sampleImgPixels[3*i+1]+g[i];
            compositeImgPixels[3*i+2] = sampleImgPixels[3*i+2]+b[i];
            compositeImgPixels[3*i+3] = sampleImgPixels[3*i+3]+a[i];
        }
    }
    
    
    
    //          ********************   INTERACTIVE METHOD   ********************
    
    if(state == "found"){
        
        if(threshold > 0)threshold--;
        for (int n=0; n<nPixels; n++) {
            if(r[n]<0)  r[n]++;
            if(g[n]<0)  g[n]++;
            if(b[n]<0)  b[n]++;
        }
        
    }else if (state == "notFound"){
        
        if (threshold < 180)threshold+=0.6;
        for (int n=0; n<nPixels; n++) {
            if(r[n]>-45)  r[n]-=0.8;
            if(g[n]>-40)  g[n]-=0.8;
            if(b[n]>-35)  b[n]-=0.8;
        }
        
    }
    
    compositeImg.setFromPixels(compositeImgPixels,960,540);
    
}

//--------------------------------------------------------------------------------------------------------------
void TestLayer3::draw(){
    
    ofTranslate(855, -40);
    ofRotateZ(90);
    
    ofEnableAlphaBlending();
    ofBackground(0,0,0,0);
    compositeImg.draw(0,0,ofGetHeight()*1.09,506.25);
    
    
    
    //          ********************    CIRCLES     ********************
    
    int num = contourFinder.blobs.size();
    int centerX[num], centerY[num];
    
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    
    for (int n=0; n<num; n++) {
        centerX[n] = contourFinder.blobs[n].boundingRect.x;
        centerY[n] = contourFinder.blobs[n].boundingRect.y;
        
        red = compositeImgPixels[ (centerY[n] * 960 + centerX[n]) *3 ];
        green = compositeImgPixels[ (centerY[n] * 960 + centerX[n]) *3 +1];
        blue = compositeImgPixels[ (centerY[n] * 960 + centerX[n]) *3 +2];
        
        ofNoFill();
        ofSetLineWidth(ofRandom(1,5));
        ofSetColor(red,green,blue);
        ofCircle(2*centerX[n],2*centerY[n],30*(red+green+blue)/765);
        ofCircle(2*centerX[n]+ofRandom(-5,5),2*centerY[n]+ofRandom(-5,5),30*(red+green+blue)/765);
        ofCircle(2*centerX[n]+ofRandom(-5,5),2*centerY[n]+ofRandom(-5,5),30*(red+green+blue)/765);
        ofCircle(2*centerX[n]+ofRandom(-5,5),2*centerY[n]+ofRandom(-5,5),30*(red+green+blue)/765);
    }
    
}




