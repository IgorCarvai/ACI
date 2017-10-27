#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCvHaarFinder.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	ofFbo fbo;
	ofImage backGround;

	int camWidth, camHeight;
	ofVideoGrabber vidGrabber;
	ofxCvHaarFinder finder;
	ofxCvColorImage rgb, hsb;
	ofxCvGrayscaleImage hue, sat, bri, filter1, filter2, finalImage;

	ofxCvContourFinder   contours;
	ofRectangle r, r2;
	int findHue, findSat;
	int frameChange = 1;
	int frameCheck = frameChange;
	int oldX, oldY, oldX2, oldY2;
	int rotX, rotY = 0;
	int oldH,oldW;
	int defaultHue, defaultSat;
	int defaultHueTol, defaultSatTol;
	int locDiff,locDiff2, oldLocDiff, oldLocDiff2;
	int locDiffy, oldLocDiffy;
	int hueRange,satRange;
	ofSpherePrimitive sphere;
	ofImage texture;

};