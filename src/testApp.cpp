#include "testApp.h"

bool start_mov;
float r[960*540];
float g[960*540];
float b[960*540];
int nPixels = 960*540;
float threshold = 100;
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
    number = "";
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
        
        if (m.getAddress() == "/holes"){
            state = m.getArgAsString(0) ;
            if (state == "found") {
                for (int i=0; i<nPixels; i++) {
                    if(r[i] < 255)r[i]+=0.1;else r[i] = -200;
                }
            }
        }
        
//        if (m.getAddress() == "/holes/number"){
//            state = m.getArgAsString(0) ;
//            if (number == "larger") {
//                if (threshold>20)threshold--;else threshold = 200;
//            }
//        }
    }
}

//--------------------------------------------------------------------------------------------------------------
void testApp::draw(){
    
    ofEnableAlphaBlending();
    mng.draw();
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
       if (key == ' ') {
          if (threshold>20)threshold--;else threshold = 200;
      }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
        for (int i=0; i<nPixels; i++) {
            if(r[i] < 255)r[i]+=0.5;else r[i] = -200;
            if(g[i] < 255)g[i]+=0.5;else g[i] = -200;
            if(b[i] < 255)b[i]+=0.5;else b[i] = -200;
        }
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
