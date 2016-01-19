#include "ofMain.h"

#define str(A) #A
class GLSL{
    public:

    vector<string> setup(int NUM){
        vector<string> result;
        string version = "\n#version 150\n";
        string num = "\n#define MAX_NUM_LIGHT "+ofToString(NUM)+"\n";

        string frag = str(
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

            out vec4 fragColor;
            in vec2 texCoordVarying;

            vec4 light(vec2 uv, vec2 Position, float Size, float Focus, float Brightness, vec4 colors) {
                float RColor = smoothstep(Focus, length(uv - Position), Size);
                return vec4(RColor, RColor, RColor, 1.0) * colors * Brightness;
            }

            void main() {
                vec2 uv = texCoordVarying;
                vec4 Texel = texture2D(texMap, uv);
                vec4 v = vec4(0.);
                for(int i = 0; i < MAX_NUM_LIGHT; i++) {
                    v+=light(uv, vec2(LUCI[i].position.x,LUCI[i].position.y), LUCI[i].size, LUCI[i].focus, LUCI[i].brightness, LUCI[i].colors);
                }
                fragColor = v*Texel;
            }
        );

        string vert = str(
            uniform mat4 projectionMatrix;
            uniform mat4 modelViewMatrix;
            uniform mat4 modelViewProjectionMatrix;

            in  vec4 position;
            in  vec2 texcoord;
            out vec2 texCoordVarying;

            void main() {
                texCoordVarying = texcoord;
                gl_Position = modelViewProjectionMatrix * position;
            }
        );

        result.push_back(version+vert);
        result.push_back(version+num+frag);
        return result;
    }
};
