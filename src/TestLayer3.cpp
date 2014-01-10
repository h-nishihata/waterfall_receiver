#include "TestLayer3.h"
string state;

//--------------------------------------------------------------------------------------------------------------
void TestLayer3::setup(){
    
    ofSetFrameRate(60);
    vidPlayer.loadMovie("kegonfalls_2.mp4");
    
    colorImg.allocate(960,540);
    colorImgHSV.allocate(960,540);
    
	grayImage.allocate(960,540);
	grayBg.allocate(960,540);
	grayDiff.allocate(960,540);
    compositeImg.allocate(960,540);
    
	bLearnBakground = true;
    threshold = 225;
    
    for (int n=0; n<nPixels; n++) {
        r[n] = -45;
        g[n] = -40;
        b[n] = -35;
    }
//    r_ = 0;
//    g_ = 0;
//    b_ = 0;
    
    state = "";
    
}

//--------------------------------------------------------------------------------------------------------------
void TestLayer3::update(){
    
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
            if(time_ < 0.31 || time_ >= 0.65){
                compositeImgPixels[3*i] = sampleImgPixels[3*i]+r[i];
                compositeImgPixels[3*i+1] = sampleImgPixels[3*i+1]+g[i];
                compositeImgPixels[3*i+2] = sampleImgPixels[3*i+2]+b[i];
            }else if (time_ >= 0.31 && time_ < 0.65){
                
                if(compositeImgPixels[3*i] < 255)compositeImgPixels[3*i]++;
                if(compositeImgPixels[3*i+1] < 255)compositeImgPixels[3*i+1]++;
                if(compositeImgPixels[3*i+2] < 255)compositeImgPixels[3*i+2]++;
                
            }
            
        }
    }
    
    
    
    //          ********************   INTERACTIVE METHOD   ********************
    
    if(state == "found"){
        
        if(flag_thr == false){
            threshold--;
            if (threshold <= 0) {flag_thr = true;}
        }else{
            threshold+=2;
            if(threshold >= 255){flag_thr = false;}
        }
        
        
        
        for (int n=0; n<nPixels; n++) {
            if(flag_r == false){
                r[n]+=0.5;
                if(r[n] >= 255){flag_r = true;}
            }else{
                r[n]-=0.5;
                if(r[n] <= -45){flag_r = false;}
            }
            
            
            if(flag_g == false){
                g[n]+=0.7;
                if(g[n] >= 255){flag_g = true;}
            }else{
                g[n]-=0.7;
                if(g[n] <= -40){flag_g = false;}
            }
            
            
            if(flag_b == false){
                b[n]+=0.8;
                if(b[n] >= 255){flag_b = true;}
            }else{
                b[n]-=0.8;
                if(b[n] <= -30){flag_b = false;}
            }
        }
        
        
        
//        if(flag_r_ == false){
//            r_++; if(r_ >=255){flag_r = true;}
//        }else{
//            r_--;
//            if(r_ <= 0){flag_r_ = false;}
//        }
//        
//        
//        if(flag_g_ == false){
//            g_++; if(g_ >=255){flag_g = true;}
//        }else{
//            g_--;
//            if(g_ <= 0){flag_g_ = false;}
//        }
//        
//        
//        if(flag_b_ == false){
//            b_++; if(b_ >=255){flag_b = true;}
//        }else{
//            b_--;
//            if(b_ <= 0){flag_b_ = false;}
//        }
        
        
    }else if (state == "notFound"){
        
        if(threshold < 225) threshold++;
        
        
        
        for (int n=0; n<nPixels; n++) {
            if(r[n] > -45)r[n]-=0.8;
            if(g[n] > -40)g[n]-=0.8;
            if(b[n] > -35)b[n]-=0.8;
        }
        
        
//        if(r_ > 0)r_ -=0.8;
//        if(g_ > 0)g_ -=0.8;
//        if(b_ > 0)b_ -=0.8;
        
    }
    
    
    compositeImg.setFromPixels(compositeImgPixels,960,540);
    
}

//--------------------------------------------------------------------------------------------------------------
void TestLayer3::draw(){
    
    ofTranslate(-70, 0);
    
    ofEnableAlphaBlending();
    ofBackground(0,0,0,0);
    compositeImg.draw(0,0,ofGetWidth()*1.1,ofGetHeight()*1.1);
    
    ofNoFill();
    ofSetLineWidth(ofRandom(1,5));
    
    
    
    //          ********************    CIRCLES     ********************
    
    int num = contourFinder.blobs.size();
    int centerX[num], centerY[num];
    
    for (int n=0; n<num; n++) {
        centerX[n] = contourFinder.blobs[n].boundingRect.x;
        centerY[n] = contourFinder.blobs[n].boundingRect.y;
        
        red = compositeImgPixels[ (centerY[n] * 960 + centerX[n]) *3 ];
        green = compositeImgPixels[ (centerY[n] * 960 + centerX[n]) *3 +1];
        blue = compositeImgPixels[ (centerY[n] * 960 + centerX[n]) *3 +2];
        
        ofSetColor(red,green,blue);
        ofCircle(centerX[n],centerY[n],30*(red+green+blue)/765);
        ofCircle(centerX[n]+ofRandom(-5,5),centerY[n]+ofRandom(-5,5),30*(red+green+blue)/765);
        ofCircle(centerX[n]+ofRandom(-5,5),centerY[n]+ofRandom(-5,5),30*(red+green+blue)/765);
        ofCircle(centerX[n]+ofRandom(-5,5),centerY[n]+ofRandom(-5,5),30*(red+green+blue)/765);
    }
}




