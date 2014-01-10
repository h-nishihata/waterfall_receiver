#include "particle.h"

particle::particle(){
    
    x = ofRandom(ofGetWidth(),ofGetWidth()*1.5);
    y = ofGetHeight()*1/4+ofRandom(-100,100);
    r = ofRandom(1,8);
}

//--------------------------------------------------------------
void particle::update(){
    
    int posx = ofRandom(-5,-20);
    int posy = ofRandom(-3,3);
    x += posx;
    y += posy;
    
}
//--------------------------------------------------------------
void particle::draw(){
    
    ofEnableAlphaBlending();
    
    ofSetColor(255,255,255,255);
    ofCircle(x, y, r);
    ofSetColor(255,255,255,100);
    ofCircle(x, y, r+3);
    ofSetColor(255,255,255,80);
    ofCircle(x, y, r+8);
    
}
//--------------------------------------------------------------
void particle::reset(){
    
    x = ofRandom(ofGetWidth(),ofGetWidth()*1.5);
    y = ofGetHeight()*1/4+ofRandom(-100,100);
    
}