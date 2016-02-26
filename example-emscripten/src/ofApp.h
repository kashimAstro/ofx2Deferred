#pragma once

#include "ofMain.h"
#include "glsl.h"

struct Lighting {
	ofVec2f position;
	float size;
	float focus;
	float brightness;
	ofVec4f colors;
};

class ofApp : public ofBaseApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		void init();
		void prepare_stage(int N,vector<ofVec2f> p,vector<ofVec4f> c,vector<float> s,vector<float> f,vector<float> b);

		ofImage img;
		ofFbo fbo;
		ofShader shader;
		GLSL glsl;
		vector<Lighting> light;
		vector<ofVec2f> pos;
		vector<ofVec4f> col;
		vector<float>   siz,foc,bri;
		ofParameter<int> NUM_LIGHT;
};
