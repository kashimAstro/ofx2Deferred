#include "ofMain.h"
#include "ofApp.h"

int main(){
	ofGLESWindowSettings settings;
	settings.glesVersion = 3;
	ofCreateWindow(settings);
	ofRunApp(new ofApp());
	return 0;
}
