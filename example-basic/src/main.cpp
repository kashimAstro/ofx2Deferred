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
        ofParameter<bool>    box;
        ofImage tex;

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
                bri.push_back(2.03);
            }
            def.setup(tex,NUM_LIGHT,pos,col,siz,foc,bri);
            posIco = def.getPositionRealCoord();
            colorsIco = def.getRealColors();
            for(int i = 0; i < posIco.size(); i++){
                ofIcoSpherePrimitive ic;
                ic.set(28,1);
                ic.setPosition(glm::vec3(posIco[i].x,posIco[i].y,0));
                ico.push_back(ic);
            }
        }

        void setup(){
            ofSetVerticalSync(false);
            ofDisableArbTex();

            gui.setup();
            gui.add(position.set("position",glm::vec2(0.5,0.5),glm::vec2(0.),glm::vec2(1.)));
            gui.add(size.set("size",0.02,-1.,1.));
            gui.add(focus.set("focus",-0.0099999,-1.,5.));
            gui.add(brightness.set("brightness",0.55,-1.,10.));
            gui.add(colors.set("colors",glm::vec4(1.0,0.0,1.0,1.0),glm::vec4(0.),glm::vec4(1.)));
            gui.add(NUM_LIGHT.set("set num Light",2,1,100));
            gui.add(box.set("show icosphere",true));

            tex.load("texture1.jpg");
            init();
        }

        void update(){
            ofSetWindowTitle(ofToString(ofGetFrameRate()));

            /* control single light */
            def.light[0].size=size;
            def.light[0].focus=focus;
            def.light[0].brightness=brightness;
            def.light[0].position=position;
            def.light[0].colors=colors;

            /* ico sphere */
            colorsIco[0]=ofColor(ofMap(colors->x,0.,1.,0,255),
                                 ofMap(colors->y,0.,1.,0,255),
                                 ofMap(colors->z,0.,1.,0,255),
                                 ofMap(colors->w,0.,1.,0,255));
            ico[0].setPosition(glm::vec3(ofMap(position->x,0.,1.,0,tex.getWidth()),
                                       ofMap(position->y,0.,1.,0,tex.getHeight()),
                                       0));
        }

        void draw(){
            ofEnableDepthTest();

            def.draw();

            if(box) {
                ofPushStyle();
                for(int i = 0; i < ico.size(); i++){
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
