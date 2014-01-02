#include "particle.h"

particle::particle(){
    
    x = ofRandom(600,850);
    y = ofRandom(ofGetHeight(),ofGetHeight()*1.5);
    r = ofRandom(1,8);
    
}
//--------------------------------------------------------------
void particle::setup(){
    ofSetFrameRate(30);
}

//--------------------------------------------------------------
void particle::update(){
    
    int posx = ofRandom(-3,3);
    int posy = ofRandom(-5,-20);
    x += posx;
    y += posy;

}
//--------------------------------------------------------------
void particle::draw(){
    
    ofEnableAlphaBlending();
//    ofNoFill();
//    ofSetLineWidth(ofRandom(0.1,2));
    ofSetColor(255,255,255,255);
    ofCircle(x, y, r);
    ofSetColor(255,255,255,100);
    ofCircle(x, y, r+3);
    ofSetColor(255,255,255,80);
    ofCircle(x, y, r+8);
    
}
//--------------------------------------------------------------
void particle::reset(){
    
    x = ofRandom(680,830);
    y = ofRandom(ofGetHeight(),ofGetHeight()*1.5);
    
}