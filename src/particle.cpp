#include "particle.h"

particle::particle(){
    
    x = ofRandom(550,900);
    y = ofRandom(ofGetHeight(),ofGetHeight()*3);
    r = ofRandom(1,15);
    a = 20;
}
//--------------------------------------------------------------
void particle::update(){
    
    int posx = ofRandom(-3,3);
    int posy = ofRandom(-20);
    x += posx;
    y += posy;
    a-=5;
    
}
//--------------------------------------------------------------
void particle::draw(){
    
    ofFill();
    ofSetColor(255,255,255,a);
    ofCircle(x, y, r);
    ofCircle(x+ofRandom(-5,5), y+ofRandom(-5,5), r);
    ofCircle(x+ofRandom(-5,5), y+ofRandom(-5,5), r);
    
}
//--------------------------------------------------------------
void particle::reset(){
    x = ofRandom(550,900);
    y = ofRandom(ofGetHeight(),ofGetHeight()*3);
}