#include "ofMain.h"
#include "ofApp.h"

void ofApp::init() {
    for(int i = 0; i < NUM_LIGHT; i++) {
        pos.push_back(ofVec2f(ofRandom(0.2,0.8),ofRandom(0.2,0.8)));
        col.push_back(ofVec4f(ofRandom(0.,1.),ofRandom(0.,1.),ofRandom(0.,1.),1.));
        siz.push_back(0.00777777);
        foc.push_back(-0.0099999);
        bri.push_back(25.03);
    }
    def.setup(tex,NUM_LIGHT,pos,col,siz,foc,bri);
}

void ofApp::setup(){
    ofSetVerticalSync(false);
    ofDisableArbTex();

    gui.setup();
    gui.add(position.set("position",ofVec2f(0.5,0.5),ofVec2f(0.),ofVec2f(1.)));
    gui.add(size.set("size",0.02,-1.,1.));
    gui.add(focus.set("focus",-0.0099999,-1.,5.));
    gui.add(brightness.set("brightness",0.55,-1.,10.));
    gui.add(colors.set("colors",ofVec4f(1.0,0.0,1.0,1.0),ofVec4f(0.),ofVec4f(1.)));
    gui.add(NUM_LIGHT.set("set num Light",2,1,100));
    gui.add(index.set("index",0,0,100));
    gui.add(ref.set("refresh",false));
    ref.addListener(this,&ofApp::refresh);

    tex.load("texture1.jpg");
    init();
}

void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    if(index >=NUM_LIGHT)
        index=0;
    /* control single light */
    def.light[0].size=size;
    def.light[0].focus=focus;
    def.light[0].brightness=brightness;
    def.light[0].position=position;
    def.light[0].colors=colors;
}

void ofApp::draw(){
    ofEnableDepthTest();
    def.draw();
    ofDisableDepthTest();
    gui.draw();
}

void ofApp::refresh(bool & value){
    if(value == true) {
        pos.clear();
        col.clear();
        siz.clear();
        foc.clear();
        bri.clear();
        init();
    }
}
