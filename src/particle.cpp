#include "particle.h"

particle::particle(){
    
    x = ofRandom(600,850);
    y = ofRandom(ofGetHeight(),ofGetHeight()*1.2);
    r = ofRandom(1,20);
}
//--------------------------------------------------------------
void particle::update(){
    
    int posx = ofRandom(-3,3);
    int posy = ofRandom(-20);
    x += posx;
    y += posy;

}
//--------------------------------------------------------------
void particle::draw(){
    
    ofEnableAlphaBlending();
    ofNoFill();
    ofSetLineWidth(ofRandom(0.1,2));
    ofSetColor(255,255,255,50);
    ofCircle(x, y, r);
    ofCircle(x+ofRandom(-5,5), y+ofRandom(-5,5), r);
    ofCircle(x+ofRandom(-5,5), y+ofRandom(-5,5), r);
    
}
//--------------------------------------------------------------
void particle::reset(){
    x = ofRandom(550,900);
    y = ofRandom(ofGetHeight(),ofGetHeight()*3);
}