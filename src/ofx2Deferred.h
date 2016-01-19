#include "ofMain.h"
#include "glsl.h"

struct Lighting {
    ofVec2f position;
    float size;
    float focus;
    float brightness;
    ofVec4f colors;
};

class ofxDeferredLight2D {
  public:
    GLSL glsl;
    ofShader shader;
    ofFbo fbo;
    vector<Lighting> light;
    vector<ofVec2f> light_position;
    vector<ofColor> light_colors;

    void stage( int NUM_LIGHT,vector<ofVec2f> position, vector<ofVec4f> colors, vector<float> size, vector<float> focus, vector<float> brightness ) {
        light.clear();
        light_position.clear();
        light_colors.clear();
        for(int i = 0; i < NUM_LIGHT; i++) {
            Lighting l;
            l.colors     = colors[i];
            l.brightness = brightness[i];
            l.focus      = focus[i];
            l.size       = size[i];
            l.position   = position[i];
            light.push_back(l);

            ofVec2f pos = ofVec2f(ofMap(position[i].x,0.,1.,0,fbo.getWidth()),ofMap(position[i].y,0.,1.,0,fbo.getHeight()));
            light_position.push_back(pos);
            ofColor col = ofColor(
                                  (int)ofMap(colors[i].x,0.,1.,0,255),
                                  (int)ofMap(colors[i].y,0.,1.,0,255),
                                  (int)ofMap(colors[i].z,0.,1.,0,255),
                                  (int)ofMap(colors[i].w,0.,1.,0,255)
                                 );
            light_colors.push_back(col);
        }
    }

    vector<ofVec2f> getPositionRealCoord() {
        return light_position;
    }

    vector<ofColor> getRealColors() {
        return light_colors;
    }

    void setup(ofImage img,int NUM_LIGHT, vector<ofVec2f> position,vector<ofVec4f> colors, vector<float> size, vector<float> focus, vector<float> brightness) {
        vector<string> v = glsl.setup(NUM_LIGHT);
        shader.setupShaderFromSource(GL_VERTEX_SHADER,v[0]);
        shader.setupShaderFromSource(GL_FRAGMENT_SHADER,v[1]);
        if(ofIsGLProgrammableRenderer()) {
            shader.bindDefaults();
        }
        shader.linkProgram();

        fbo.allocate(img.getWidth(),img.getHeight());
        fbo.begin();
        ofClear(0,0,0,0);
            img.draw(0,0);
        fbo.end();

        stage(NUM_LIGHT,position,colors,size,focus,brightness);
    }

    void setup(ofFbo &_fbo, int NUM_LIGHT, vector<ofVec2f> position,vector<ofVec4f> colors, vector<float> size, vector<float> focus, vector<float> brightness) {
        vector<string> v = glsl.setup(NUM_LIGHT);
        shader.setupShaderFromSource(GL_VERTEX_SHADER,v[0]);
        shader.setupShaderFromSource(GL_FRAGMENT_SHADER,v[1]);
        if(ofIsGLProgrammableRenderer()) {
            shader.bindDefaults();
        }
        shader.linkProgram();
        fbo=_fbo;
        stage(NUM_LIGHT,position,colors,size,focus,brightness);
    }

    void update(){

    }

    void draw(){
        shader.begin();
        shader.setUniformTexture("tex",fbo.getTexture(),1);
        shader.setUniform2f("resol",ofGetWidth(),ofGetHeight());
        shader.setUniform1f("time",ofGetElapsedTimeMillis()*0.0005);
        for(int i = 0; i < light.size(); i++){
            shader.setUniform2f("LUCI["+ofToString(i)+"].position",light[i].position.x,light[i].position.y);
            shader.setUniform1f("LUCI["+ofToString(i)+"].size", light[i].size);
            shader.setUniform1f("LUCI["+ofToString(i)+"].focus",light[i].focus);
            shader.setUniform1f("LUCI["+ofToString(i)+"].brightness",light[i].brightness);
            shader.setUniform4f("LUCI["+ofToString(i)+"].colors",light[i].colors.x,light[i].colors.y,light[i].colors.z,light[i].colors.w);
        }
        fbo.draw(0,0);
        shader.end();
    }
};
