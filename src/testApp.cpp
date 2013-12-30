#include "testApp.h"

bool start_mov;

//--------------------------------------------------------------------------------------------------------------
void testApp::setup(){

    receiver.setup( PORT );
    ofSetVerticalSync(true);
    ofBackground(100,100,5);
    mng.setup(1440,900);
    
    layer1 = mng.createLayer<TestLayer1>();
    layer2 = mng.createLayer<TestLayer2>();
    layer3 = mng.createLayer<TestLayer3>();
    
    layer1->setVisible(true);
    layer1->setAlpha(255);
    
    layer2->setVisible(true);
    layer2->setAlpha(255);
    
    layer3->setVisible(true);
    layer3->setAlpha(255);
    
    start_mov = false;
    state = "";

}

//--------------------------------------------------------------------------------------------------------------
void testApp::update(){
    
    mng.update();
    while(receiver.hasWaitingMessages()){
        
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        
        if (m.getAddress() == "/start_mov"){
            start_mov = true;
        }
        
        if (m.getAddress() == "/blobs"){
            state = m.getArgAsString(0) ;
        }
        
        if (m.getAddress() == "/holes"){
            holes = m.getArgAsString(0) ;
        }
    }

}

//--------------------------------------------------------------------------------------------------------------
void testApp::draw(){
    
    ofEnableAlphaBlending();
    mng.draw();
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
    
}
