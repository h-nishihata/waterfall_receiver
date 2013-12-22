#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxLayer.h"
#define OFX_LAYER_DEFINE_LAYER_CLASS(Klass) public: const char* getClassName() const { return #Klass; } \
unsigned int getClassID() const { return ofx::Layer::Type2Int<Klass>::value(); }

extern bool start_mov;

extern     float time_;
extern float r[960*540];
extern float g[960*540];
extern float b[960*540];
extern int nPixels;
extern float threshold;

class TestLayer3 : public ofxLayer::Layer{
public:
    
    OFX_LAYER_DEFINE_LAYER_CLASS(TestLayer3)
    
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    ofVideoPlayer vidPlayer;
    
    ofxCvColorImage colorImg;
    ofxCvColorImage colorImgHSV;
    ofxCvColorImage colorImgRGB;
    
    ofxCvGrayscaleImage grayImage;
    ofxCvGrayscaleImage grayBg;
    ofxCvGrayscaleImage grayDiff;
    ofxCvContourFinder contourFinder;
    
    ofxCvColorImage compositeImg;
    

    bool bLearnBakground;
    
    
    

    float a[960*540];
    
    
    unsigned char* compositeImgPixels = new unsigned char[nPixels*3];
    
    
    
    
    bool end0 = true;
    bool end1 = false;
    bool end2 = false;
    bool end3 = false;
    bool end4 = false;
    
};