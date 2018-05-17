#pragma once

#include "ofMain.h"
#include "ofx2Deferred.h"

class ofApp : public ofBaseApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		void init();
		void prepare_stage(int N,vector<glm::vec2> p,vector<glm::vec4> c,vector<float> s,vector<float> f,vector<float> b);

		ofImage img;
		ofFbo fbo;
		ofShader shader;
		GLSL glsl;
		vector<Lighting> light;
		vector<glm::vec2> pos;
		vector<glm::vec4> col;
		vector<float>   siz,foc,bri;
		ofParameter<int> NUM_LIGHT;
};
