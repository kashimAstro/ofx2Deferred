#include "ofMain.h"
#include "ofxGui.h"
#include "ofx2Deferred.h"

class ofApp : public ofBaseApp{

	public:
        ofxPanel gui;
        ofParameter<glm::vec2> position;
        ofParameter<float> size;
        ofParameter<float> focus;
        ofParameter<float> brightness;
        ofParameter<glm::vec4> colors;
        ofParameter<int>     NUM_LIGHT;
        ofParameter<int>     index;
        ofParameter<bool>     ref;
        ofImage tex;

        ofxDeferredLight2D def;
        vector<glm::vec2> pos;
        vector<glm::vec4> col;
        vector<float>   siz,foc,bri;

        void init();
        void setup();
        void update();
        void draw();
        void refresh(bool & value);
};
