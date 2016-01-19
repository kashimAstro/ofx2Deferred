#include "ofMain.h"
#include "ofxGui.h"
#include "ofx2Deffered.h"

class ofApp : public ofBaseApp{

	public:
        ofxPanel gui;
        ofParameter<ofVec2f> position;
        ofParameter<float> size;
        ofParameter<float> focus;
        ofParameter<float> brightness;
        ofParameter<ofVec4f> colors;
        ofImage tex;

        ofxDefferedLight2D def;
        vector<ofIcoSpherePrimitive> ico;
        vector<ofVec2f> posIco;
        vector<ofColor> colorsIco;
        vector<ofVec2f> pos;
        vector<ofVec4f> col;
        vector<float>   siz,foc,bri;
        int NUM_LIGHT = 20;

        void init() {
            for(int i = 0; i < NUM_LIGHT; i++) {
                pos.push_back(ofVec2f(ofRandom(-0.1,1.0),ofRandom(-0.1,1.0)));
                col.push_back(ofVec4f(ofRandom(0.,1.),ofRandom(0.,1.),ofRandom(0.,1.),1.));
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
                ic.setPosition(posIco[i]);
                ico.push_back(ic);
            }
        }

        void setup(){
            ofSetVerticalSync(false);
            ofDisableArbTex();

            tex.load("texture1.jpg");
            init();

            gui.setup();
            gui.add(position.set("position",ofVec2f(0.5,0.5),ofVec2f(-1.),ofVec2f(1.)));
            gui.add(size.set("size",0.02,-1.,1.));
            gui.add(focus.set("focus",-0.0099999,-1.,5.));
            gui.add(brightness.set("brightness",0.55,-1.,10.));
            gui.add(colors.set("colors",ofVec4f(1.0,0.0,1.0,1.0),ofVec4f(-1.),ofVec4f(1.)));
        }

        void update(){
            //
            def.light[0].size=size;
            def.light[0].focus=focus;
            def.light[0].brightness=brightness;
            def.light[0].position=position;
            def.light[0].colors=colors;
            colorsIco[0]=ofColor(ofMap(colors->x,0.,1.,0,255),ofMap(colors->y,0.,1.,0,255),ofMap(colors->z,0.,1.,0,255),ofMap(colors->w,0.,1.,0,255));
            ico[0].setPosition(ofVec3f(ofMap(position->x,0.,1.,0,tex.getWidth()), ofMap(position->y,0.,1.,0,tex.getHeight()),0));
        }

        void draw(){
            ofEnableDepthTest();

            def.draw();

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
    s.width=1366;
    s.height=768;
    ofCreateWindow(s);
    ofRunApp(new ofApp());
}
