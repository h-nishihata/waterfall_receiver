#include "ofMain.h"

#include "ofxOpenCv.h"
#include "ofxLayer.h"
#define OFX_LAYER_DEFINE_LAYER_CLASS(Klass) public: const char* getClassName() const { return #Klass; } \
unsigned int getClassID() const { return ofx::Layer::Type2Int<Klass>::value(); }

extern bool start_mov;

class TestLayer3 : public ofxLayer::Layer{
public:
    
    OFX_LAYER_DEFINE_LAYER_CLASS(TestLayer3)
    
    void setup();
    void update();
    void draw();
    
    ofVideoPlayer vidPlayer;
    
    ofxCvColorImage colorImg;
    ofxCvColorImage colorImgHSV;
    ofxCvColorImage colorImgRGB;
    
    ofxCvGrayscaleImage grayImage;
    ofxCvGrayscaleImage grayBg;
    ofxCvGrayscaleImage grayDiff;
    
    ofxCvColorImage compositeImg;
    ofxCvContourFinder contourFinder;
    
    bool bLearnBakground;
    int threshold;
    float time_;

    int nPixels  = 960*540;
    unsigned char* compositeImgPixels = new unsigned char[nPixels*3];
    
    float r[960*540];
    float g[960*540];
    float b[960*540];
//    float r_;
//    float g_;
//    float b_;
    
    bool flag_r;
    bool flag_g;
    bool flag_b;
//    bool flag_r_;
//    bool flag_g_;
//    bool flag_b_;
    bool flag_thr;
    
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    
};