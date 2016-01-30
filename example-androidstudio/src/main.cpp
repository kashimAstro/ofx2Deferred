#include "ofMain.h"
#include "ofApp.h"
int main(){
    ofGLESWindowSettings settings;
    settings.glesVersion = 3;
    ofCreateWindow(settings);
    ofRunApp(new ofApp());
    return 0;
}

#ifdef TARGET_ANDROID
#include <jni.h>

//========================================================================
extern "C"{
        void Java_cc_openframeworks_OFAndroid_init( JNIEnv*  env, jobject  thiz ){
                main();
        }
}
#endif
