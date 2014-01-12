#include "TestLayer3.h"
string state;

//--------------------------------------------------------------------------------------------------------------
void TestLayer3::setup(){
    
    ofSetFrameRate(60);
    vidPlayer.loadMovie("kegonfalls_02.mp4");
    
    colorImg.allocate(640,360);
    colorImgHSV.allocate(640,360);
    
	grayImage.allocate(640,360);
	grayBg.allocate(640,360);
	grayDiff.allocate(640,360);
    compositeImg.allocate(640,360);
    
	bLearnBakground = true;
    threshold = 100;
    
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
    
    colorImg.setFromPixels(vidPlayer.getPixels(), 640,360);
    colorImgHSV = colorImg;
    colorImgHSV.convertRgbToHsv();
    
    grayImage = colorImg;
    
    if (bLearnBakground == true){
        grayBg = grayImage;
        bLearnBakground = false;
    }
    
    grayDiff.absDiff(grayBg, grayImage);
    grayDiff.threshold(threshold);
    
    contourFinder.findContours(grayDiff, 20, (640*360)/3, 10, true);
	
    colorImgRGB = colorImg;
    colorImgRGB.convertHsvToRgb();
    
    
    
    //          ********************  COLORING ROUTINES   ********************
    
    unsigned char* grayPixels = grayDiff.getPixels();
    unsigned char* sampleImgPixels = colorImgRGB.getPixels();
    
    
    
    for (int i=0; i<nPixels; i++) {
        if (grayPixels[i] == 0) {
//            compositeImgPixels[3*i] = sampleImgPixels[3*i]+r_;
//            compositeImgPixels[3*i+1] = sampleImgPixels[3*i+1]+g_;
//            compositeImgPixels[3*i+2] = sampleImgPixels[3*i+2]+b_;
            
        }else{
//            if(time_ < 0.31 || time_ >= 0.65){
                compositeImgPixels[3*i] = (sampleImgPixels[3*i]+r[i])*2;
                compositeImgPixels[3*i+1] = (sampleImgPixels[3*i+1]+g[i])*2;
                compositeImgPixels[3*i+2] = (sampleImgPixels[3*i+2]+b[i])*2;
//            }else if (time_ >= 0.31 && time_ < 0.65){
//                
//                if(compositeImgPixels[3*i] < 255)compositeImgPixels[3*i]++;
//                if(compositeImgPixels[3*i+1] < 255)compositeImgPixels[3*i+1]++;
//                if(compositeImgPixels[3*i+2] < 255)compositeImgPixels[3*i+2]++;
//                
//            }
            
        }
    }
    
    
    
    //          ********************   INTERACTIVE METHOD   ********************
    
    if(state == "found"){
        
        if(flag_thr == false){
            threshold-=0.3;
            if (threshold <= 0) {flag_thr = true;}
        }else if(flag_thr == true){
            threshold+=0.3;
            if(threshold >= 255){flag_thr = false;}
        }
        
        
        
        for (int n=0; n<nPixels; n++) {
            if(flag_r == false){
                r[n]+=0.1;
                if(r[n] >= 255){flag_r = true;}
            }else if(flag_r == true){
                r[n]-=0.1;
                if(r[n] <= -45){flag_r = false;}
            }
            
            
            if(flag_g == false){
                g[n]+=0.2;
                if(g[n] >= 255){flag_g = true;}
            }else if(flag_g == true){
                g[n]-=0.2;
                if(g[n] <= -40){flag_g = false;}
            }
            
            
            if(flag_b == false){
                b[n]+=0.3;
                if(b[n] >= 255){flag_b = true;}
            }else if(flag_b == true){
                b[n]-=0.3;
                if(b[n] <= -30){flag_b = false;}
            }
        }
        
        
        
//        if(flag_r_ == false){
//            r_+=0.1;
//            if(r_ >=255){flag_r = true;}
//        }else if(flag_r_ == true){
//            r_-= 0.1;
//            if(r_ <= 0){flag_r_ = false;}
//        }
//        
//        
//        if(flag_g_ == false){
//            g_+=0.1;
//            if(g_ >=255){flag_g = true;}
//        }else if(flag_g_ == true){
//            g_-=0.1;
//            if(g_ <= 0){flag_g_ = false;}
//        }
//        
//        
//        if(flag_b_ == false){
//            b_+=0.1;
//            if(b_ >=255){flag_b = true;}
//        }else if(flag_b_ == true){
//            b_-=0.1;
//            if(b_ <= 0){flag_b_ = false;}
//        }
        
        
    }else if (state == "notFound"){
        
        if(threshold < 100){ threshold+=0.3; }
        else if (threshold > 100){ threshold-=0.3; }
        
        
        
        for (int n=0; n<nPixels; n++) {
            if(r[n] > -45){r[n]-=0.8;}
            if(g[n] > -40){g[n]-=0.8;}
            if(b[n] > -35){b[n]-=0.8;}
        }
        
        
//        if(r_ > 0){r_ -=0.1;}
//        if(g_ > 0){g_ -=0.1;}
//        if(b_ > 0){b_ -=0.1;}
        
    }
    
    
    compositeImg.setFromPixels(compositeImgPixels,640,360);
    
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
        
        red = compositeImgPixels[ (centerY[n] * 640 + centerX[n]) *3 ];
        green = compositeImgPixels[ (centerY[n] * 640 + centerX[n]) *3 +1];
        blue = compositeImgPixels[ (centerY[n] * 640 + centerX[n]) *3 +2];
        
        ofSetColor(red,green,blue);
        ofCircle(centerX[n],centerY[n],30*(red+green+blue)/765);
        ofCircle(centerX[n]+ofRandom(-5,5),centerY[n]+ofRandom(-5,5),30*(red+green+blue)/765);
        ofCircle(centerX[n]+ofRandom(-5,5),centerY[n]+ofRandom(-5,5),30*(red+green+blue)/765);
        ofCircle(centerX[n]+ofRandom(-5,5),centerY[n]+ofRandom(-5,5),30*(red+green+blue)/765);
    }
}




