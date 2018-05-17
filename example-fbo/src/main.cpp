#include "ofMain.h"
#include "ofxGui.h"
#include "ofx2Deferred.h"

class ofApp : public ofBaseApp{

	public:
        ofxPanel gui;
        ofParameter<int>     NUM_LIGHT;
        ofParameter<bool>    box;
        ofFbo fbo;
        ofEasyCam cam;

        ofxDeferredLight2D def;
        vector<ofIcoSpherePrimitive> ico;
        vector<glm::vec2> posIco;
        vector<ofColor> colorsIco;
        vector<glm::vec2> pos;
        vector<glm::vec4> col;
        vector<float>   siz,foc,bri;

        void init() {
            for(int i = 0; i < NUM_LIGHT; i++) {
                pos.push_back(glm::vec2(ofRandom(0.2,0.8),ofRandom(0.2,0.8)));
                col.push_back(glm::vec4(ofRandom(0.,1.),ofRandom(0.,1.),ofRandom(0.,1.),1.));
                siz.push_back(0.00777777);
                foc.push_back(-0.0099999);
                bri.push_back(25.f);
            }
            def.setup(fbo,NUM_LIGHT,pos,col,siz,foc,bri);
            posIco = def.getPositionRealCoord();
            colorsIco = def.getRealColors();
            for(int i = 0; i < posIco.size(); i++){
                ofIcoSpherePrimitive ic;
                ic.set(28,1);
                ic.setPosition(glm::vec3(posIco[i].x,posIco[i].y,0));
                ico.push_back(ic);
            }
            /* trick fake global shadow */
            def.light[0].size=0;
            def.light[0].focus=-1;
            def.light[0].brightness=-1;
            def.light[0].position=glm::vec2(0.5,0.5);
            def.light[0].colors=glm::vec4(1,1,1,1);
        }

        void setup(){
            ofSetVerticalSync(false);
            ofDisableArbTex();

            gui.setup();
            gui.add(NUM_LIGHT.set("set num Light",4,1,100));
            gui.add(box.set("show icosphere",true));

            fbo.allocate(ofGetWidth(),ofGetHeight());
            fbo.begin();
            ofClear(255,0,0,255);
            fbo.end();

            init();
        }

        void update(){
            ofSetWindowTitle(ofToString(ofGetFrameRate()));

            fbo.begin();
            ofClear(0,0,0,255);
            ofEnableDepthTest();
            cam.begin();
            ofPushStyle();
                ofFill();
                ofSetColor(10,45,200);
                ofDrawSphere(100);
                ofNoFill();
                ofSetColor(255);
                ofSetLineWidth(2.5f);
                ofDrawSphere(105);
            ofPopStyle();
            cam.end();
            ofDisableDepthTest();
            fbo.end();
        }

        void draw(){
            ofEnableDepthTest();

            def.draw();

            if(box) {
                ofPushStyle();
                for(int i = 1; i < ico.size(); i++){
                    int r = colorsIco[i].r;
                    int g = colorsIco[i].g;
                    int b = colorsIco[i].b;
                    ofSetColor(r,g,b);
                    ico[i].draw();
                    ofSetColor(0);
                    ico[i].drawWireframe();
                }
                ofPopStyle();
            }

            ofDisableDepthTest();

            gui.draw();
        }

        void keyPressed(int key){
            if(key == 'f') ofToggleFullscreen();
            if(key == 'r') {
                pos.clear();
                col.clear();
                siz.clear();
                foc.clear();
                bri.clear();
                colorsIco.clear();
                posIco.clear();
                ico.clear();
                init();
            }
        }
};

int main( ){
    ofGLWindowSettings s;
    s.setGLVersion(3, 2);
    s.setSize(1366,768);
    ofCreateWindow(s);
    ofRunApp(new ofApp());
}
