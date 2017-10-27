#include "ofApp.h"

bool showStuff = false;
bool print = false;
//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);

	ofSetBackgroundAuto(true);
	backGround.loadImage("space.jpg");
	texture.loadImage("earth.jpg");
	ofBackground(0, 0, 0);
	camWidth = 640;
	camHeight = 480;
	findHue = 4;
	findSat = 231;
	defaultHue = findHue;
	defaultSat = findSat;

	hueRange = 83;
	satRange = 49;
	defaultHueTol = hueRange;
	defaultSatTol = satRange;
	vidGrabber.setDeviceID(0);
	vidGrabber.initGrabber(camWidth, camHeight);

	finder.setup("haarcascade_frontalface_default.xml");

	rgb.allocate(camWidth, camHeight);
	hsb.allocate(camWidth, camHeight);
	hue.allocate(camWidth, camHeight);
	sat.allocate(camWidth, camHeight);
	bri.allocate(camWidth, camHeight);
	filter1.allocate(camWidth, camHeight);
	filter2.allocate(camWidth, camHeight);
	finalImage.allocate(camWidth, camHeight);

	sphere.set(200, 20);
	sphere.setOrientation(ofQuaternion(0, .3, 0, -.2));

}

//--------------------------------------------------------------
void ofApp::update() {
	if (print) {
		cout << "curr " << r.getWidth() << endl;
		cout << "old " << oldW << endl;
		if (r.getWidth() > oldW&&r.getArea() > 3000)
			cout << "grow" << endl;
	}

	vidGrabber.update();
	if (r.getArea() > 3000 && r2.getArea() > 3000 && abs(r.x - r2.x) > 30 && abs(r2.y - oldY2) < 20 && abs(r.y - oldY) < 20) {
		if (abs(r.x - oldX) > 20 && abs(r2.x - oldX2) > 20) {
			oldLocDiff = locDiff;
			locDiff = abs(r.x - r2.x);
			if (oldLocDiff < locDiff) {
				if (sphere.getRadius() < 400)
					sphere.setRadius(sphere.getRadius() + 10);
			}
			else {
				if (sphere.getRadius() > 10)
					sphere.setRadius(sphere.getRadius() - 10);
			}
		}
	}

	if (r.getArea() > 7000 && r2.getArea() > 7000) {


		//left hand up (oldY - r.y) > 20 && (oldY>r.y)
		//left hadn down ((oldY - r.y) < -20 && (oldY<r.y)
		//left hand right (oldX - r.x) > 20 && (oldX > r.x)
		//left hand left (oldX - r.x) < -20 && (oldX < r.x)
		//if left hand right and up
		/*
		if (abs(oldY2 - r2.y) > 15 && (oldY2 > r2.y)) {
			cout << "----------up" << endl;
		}
		if (abs(oldY2 - r2.y) > 15 && (oldY2 < r2.y)) {
			cout << "----------------down" << endl;
		}
		if (abs(oldX2 - r2.x) > 30 && (oldX2 > r2.x)) {
			cout << "-----------------------------right" << endl;
		}
		if (abs(oldX2 - r2.x) > 30 && (oldX2 < r2.x)) {
			cout << "-------------------------------------------left" << endl;
		}
		*/
		//r = right hand
		//up and left

		//r2 =left hand
		//down and left

		//if 1 is going up and the other is going down
		if (((oldY2 - r2.y) > 15 && (oldY2 > r2.y) && ((oldY - r.y) < -15 && (oldY < r.y)))){
			cout << (r.x > r2.x) << endl;
			if ((r.x > r2.x) && abs(r.x - r2.x) > 10) {
				sphere.rotate(-10, 0, 0.0, 1.0);
			}
			else {
				sphere.rotate(10, 0, 0.0, 1.0);

			}
			
		}
		if((abs(oldY - r.y) > 15 && (oldY > r.y) && (abs(oldY2 - r2.y) > 15 && (oldY2 < r2.y)))) {
			if ((r.x < r2.x) && abs(r.x - r2.x) > 10) {
			}
		}
	



	}
	if (frameCheck == 0) {

		if (((r.x - oldX > 10 && r.x - oldX < 100) || (r.x - oldX<-10 && r.x - oldX>-100))&&r.getArea()>3000) {

			rotX = r.x - oldX;
			rotX *= -.2;
		}
		if (((r.y - oldY > 10 && r.y - oldY < 100) || (r.y - oldY<-10 && r.y - oldY>-100)) && r.getArea()>3000) {
			rotY = r.y - oldY;
			rotY *= -.2;
		}
		oldX = r.x;
		oldY = r.y;
		oldX2 = r2.x;
		oldY2 = r2.y;
		oldH = r.getHeight();
		oldW = r.getWidth();

		frameCheck = frameChange;
	}
	else {
		frameCheck = frameCheck - 1;
	}
	if (vidGrabber.isFrameNew())
	{
		rgb.setFromPixels(vidGrabber.getPixels());
		hsb = rgb;
		hsb.convertRgbToHsv();
		hsb.convertToGrayscalePlanarImages(hue, sat, bri);

		
		for (int i = 0; i < camWidth * camHeight; ++i) {
			filter1.getPixels()[i] = ofInRange(hue.getPixels()[i],
				findHue - hueRange,
				findHue + hueRange) ? 255 : 0;
		}
		filter1.flagImageChanged();

		
		for (int i = 0; i < camWidth * camHeight; ++i) {
			filter2.getPixels()[i] = ofInRange(sat.getPixels()[i],
				findSat - satRange,
				findSat + satRange) ? 255 : 0;
		}
		filter2.flagImageChanged();

		cvAnd(filter1.getCvImage(),
			filter2.getCvImage(),
			finalImage.getCvImage());
		finalImage.flagImageChanged();
		contours.findContours(finalImage,
			50,
			(camWidth*camHeight) / 3,
			3,
			false);

		finder.findHaarObjects(vidGrabber.getPixels());
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	if (showStuff) {
		ofSetColor(ofColor::white);
		vidGrabber.draw(0, 0, camWidth, camHeight);

		finalImage.draw(2048- 790,0, camWidth, camHeight);
	}
	backGround.draw(0, 0, 2048, 1536);
	ofColor c(255, 255, 255);
	for (int i = 0; i < contours.nBlobs; i++) {
		if (i == 0) {
			r = contours.blobs.at(i).boundingRect;
		}
		if (i == 1) {
			r2 = contours.blobs.at(i).boundingRect;
		}
	}

	sphere.setPosition(ofGetWidth()/2, ofGetHeight()/2, 0);
	sphere.rotate(rotY, 1.0, 0.0, 0.0);
	sphere.rotate(rotX, 0, 1.0, 0.0);
	rotX = 0;
	rotY = 0;
	ofEnableDepthTest();
	glMatrixMode(GL_TEXTURE);

	glPushMatrix();
	ofScale(2048, 1024);
	glMatrixMode(GL_MODELVIEW);

	ofPushMatrix();

	ofRotateX(rotX);
	ofRotateY(rotY);

	texture.getTextureReference().bind();
	sphere.draw();
	texture.getTextureReference().unbind();
	ofPopMatrix();

	glMatrixMode(GL_TEXTURE);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == ' ')
		showStuff = !showStuff;
	if (key == 'p')
		print = !print;

	if (key == 's') {
		defaultHue = findHue;
		defaultSat = findSat;
		defaultHueTol = hueRange;
		defaultSatTol = satRange;
		cout << "New Hue: " << defaultHue << endl;
		cout << "New Sat: " << defaultSat << endl;
		cout << "New HueTol: " << defaultHueTol << endl;
		cout << "New SatTold: " << defaultSatTol << endl;
	}
	//I K change hue
	if (key == 'i')
		findHue = findHue+1;
	if (key == 'k')
		findHue = findHue -1;
	//U J change Sat
	if (key == 'u')
		findSat = findSat + 1;
	if (key == 'j')
		findSat = findSat - 1;
	//Y H change hue tolerance
	if (key == 'y')
		hueRange = hueRange + 1;
	if (key == 'h')
		hueRange = hueRange - 1;
	//T G change sat tolerance
	if (key == 't')
		satRange = satRange + 1;
	if (key == 'g')
		satRange = satRange - 1;

	if (key == 'r') {
		sphere.setOrientation(ofQuaternion(0, .3, 0, -.2));
		cout << defaultHue << endl;
		findHue = defaultHue;
		findSat = defaultSat;
		hueRange = defaultHueTol;
		satRange = defaultSatTol;
	}
}		

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

	int mx = x % camWidth;
	int my = y % camHeight;

	findHue = hue.getPixels()[my*camWidth + mx];
	findSat = sat.getPixels()[my*camWidth + mx];

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}