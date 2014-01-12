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
    float threshold;
    float time_;

    int nPixels  = 640 * 360 ;
    unsigned char* compositeImgPixels = new unsigned char[nPixels*3];
    
    float r[640*360];
    float g[640*360];
    float b[640*360];
//    float r_;
//    float g_;
//    float b_;
    
    bool flag_r = false;
    bool flag_g = false;
    bool flag_b = false;
//    bool flag_r_ = false;
//    bool flag_g_ = false;
//    bool flag_b_ = false;
    bool flag_thr = false;
    
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    
};