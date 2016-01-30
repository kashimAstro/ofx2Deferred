#include "ofMain.h"
#include "ofxGui.h"
#include "ofx2Deferred.h"

class ofApp : public ofBaseApp{

	public:
        ofxPanel gui;
        ofParameter<ofVec2f> position;
        ofParameter<float> size;
        ofParameter<float> focus;
        ofParameter<float> brightness;
        ofParameter<ofVec4f> colors;
        ofParameter<int>     NUM_LIGHT;
        ofParameter<int>     index;
        ofParameter<bool>     ref;
        ofImage tex;

        ofxDeferredLight2D def;
        vector<ofVec2f> pos;
        vector<ofVec4f> col;
        vector<float>   siz,foc,bri;

        void init();
        void setup();
        void update();
        void draw();
        void refresh(bool & value);
};
