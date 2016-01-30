#include "ofMain.h"

#define str(A) #A
class GLSL{
    public:

    vector<string> setup(int NUM){
        vector<string> result;
        string version = "\n#version 120\n";
        string num = "\n#define MAX_NUM_LIGHT "+ofToString(NUM)+"\n";

        string frag = str(
            precision highp float;
            struct Lighting {
                vec2 position;
                float size;
                float focus;
                float brightness;
                vec4 colors;
            };

            uniform sampler2D texMap;
            uniform vec2 resol;
            uniform vec2 mouse;
            uniform float time;
            uniform Lighting LUCI[MAX_NUM_LIGHT];

            varying vec2 texCoordVarying;

            vec4 light(vec2 uv, vec2 Position, float Size, float Focus, float Brightness, vec4 colors) {
                float RColor = smoothstep(Focus, length(uv - Position), Size);
                return vec4(RColor, RColor, RColor, 1.0) * colors * Brightness;
            }

            void main() {
                vec2 uv = gl_FragCoord.xy/resol.xy;
                vec4 T  = texture2D(texMap,uv); 
                vec4 v  = vec4(0.);
                for(int i = 0; i < MAX_NUM_LIGHT; i++) {
                    v+=light(uv, vec2(LUCI[i].position.x,LUCI[i].position.y), LUCI[i].size, LUCI[i].focus, LUCI[i].brightness, LUCI[i].colors);
                }
                gl_FragColor = T*v;
            }
        );

        string vert = str(
                uniform mat4 modelViewProjectionMatrix;
                attribute vec4 position;
                attribute vec2 texcoord;
                varying vec2 texCoordVarying;

                void main() {
                    texCoordVarying = texcoord;
                    gl_Position = modelViewProjectionMatrix * position;
                }

        );

//        result.push_back(version+vert);
//        result.push_back(version+num+frag);

        result.push_back(vert);
        result.push_back(num+frag);

        return result;
    }
};

