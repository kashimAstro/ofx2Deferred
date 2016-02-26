#include "ofApp.h"

void ofApp::init() {
	for(int i = 0; i < NUM_LIGHT; i++) {
		pos.push_back(ofVec2f(ofRandom(0.0,1.0),ofRandom(1.0,0.0)));
		col.push_back(ofVec4f(ofRandom(0.0,1.0),ofRandom(0.0,1.0),ofRandom(0.0,1.0),1.0));
		siz.push_back(0.00222222);
		foc.push_back(-0.0099999);
		bri.push_back(25.5);
	}
}

void ofApp::prepare_stage(int N,vector<ofVec2f> p,vector<ofVec4f> c,vector<float> s,vector<float> f,vector<float> b) {
	light.clear();
	for(int i = 0; i < N; i++) {
		Lighting l;
		l.colors     = c[i];
		l.brightness = b[i];
		l.focus      = f[i];
		l.size       = s[i];
		l.position   = p[i];
		light.push_back(l);
	}
}

ofPlanePrimitive plane;

//--------------------------------------------------------------
void ofApp::setup(){
		NUM_LIGHT.set(25);

		ofDisableArbTex();
		vector<string> s = glsl.setup(NUM_LIGHT);
		shader.setupShaderFromSource(GL_VERTEX_SHADER,s[0]);
		shader.setupShaderFromSource(GL_FRAGMENT_SHADER,s[1]);
		shader.linkProgram();

		img.load("tex.jpg");

		init();
		prepare_stage(NUM_LIGHT,pos,col,siz,foc,bri);
		plane.set(ofGetScreenWidth()+ofGetScreenWidth(), ofGetScreenHeight()+ofGetScreenHeight(), 10, 10);
		plane.mapTexCoords(0, 0, img.getWidth(), img.getHeight());

}

//--------------------------------------------------------------
void ofApp::update(){
	light[0].position=ofVec2f(ofMap(mouseX,0,ofGetWidth(),0.,1.),ofMap(mouseY,0,ofGetHeight(),1.,0.));
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0,0,100);
	shader.begin();
	shader.setUniformTexture("texMap", img.getTexture(), 0);
	shader.setUniform2f("resol",ofGetWidth(),ofGetHeight());
	shader.setUniform1f("time",ofGetElapsedTimeMillis()*0.0005);
	for(int i = 0; i < light.size(); i++){
		shader.setUniform2f("LUCI["+ofToString(i)+"].position",light[i].position.x,light[i].position.y);
		shader.setUniform1f("LUCI["+ofToString(i)+"].size", light[i].size);
		shader.setUniform1f("LUCI["+ofToString(i)+"].focus",light[i].focus);
		shader.setUniform1f("LUCI["+ofToString(i)+"].brightness",light[i].brightness);
		shader.setUniform4f("LUCI["+ofToString(i)+"].colors",light[i].colors.x,light[i].colors.y,light[i].colors.z,light[i].colors.w);
	}
	plane.draw();
	shader.end();
	//ofDrawBitmapStringHighlight("fps:"+ofToString(ofGetFrameRate()),20,20);
}
