#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxLayer.h"
#define OFX_LAYER_DEFINE_LAYER_CLASS(Klass) public: const char* getClassName() const { return #Klass; } \
unsigned int getClassID() const { return ofx::Layer::Type2Int<Klass>::value(); }

#include "particle.h"
#define NUM 10

class TestLayer2 : public ofxLayer::Layer{
public:
    
    OFX_LAYER_DEFINE_LAYER_CLASS(TestLayer2)
    
    void setup();
    void update();
    void draw();
    int checkY();

    float a;
    particle p[NUM];
    bool flag;
    ofxCvColorImage compositeImg;
};