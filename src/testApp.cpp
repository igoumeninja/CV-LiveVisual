#include "testApp.h"
extern "C" {
#include "macGlutfix.h"
}

//--------------------------------------------------------------
void testApp::setup(){
	texture.allocate(640,640, GL_RGBA);
	image.allocate( 640, 640, OF_IMAGE_COLOR );

	bLearnBakground = true;
	threshold = 80;
	
	sender.setup(HOST, PORT);	
	
}
//--------------------------------------------------------------
void testApp::update(){
	int w = 640;
	int h = 640;
	unsigned char * data = pixelsBelowWindow(ofGetWindowPositionX(),ofGetWindowPositionY(),w,h);
	for (int i = 0; i < w*h; i++){
		unsigned char r1 = data[i*4]; // mem A
		data[i*4]   = data[i*4+1];
		data[i*4+1] = data[i*4+2];
		data[i*4+2] = data[i*4+3];
		data[i*4+3] = r1;
	}
	if (data!= NULL) texture.loadData(data, 600, 600, GL_RGBA);

	texture.draw(0,0, ofGetWidth(), ofGetHeight());
	
	image.grabScreen(0, 0, 640, 640);
	cvColorImage.setFromPixels(image.getPixels(), 640,640);
	
//	ofSetHexColor(0xffffff);
//	cvColorImage.draw(640,640);
	
	cvGrayImage = cvColorImage;
	if (bLearnBakground == true){
		cvGrayImageBg = cvGrayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
		bLearnBakground = false;
	}
	
	// take the abs value of the difference between background and incoming and then threshold:
	cvGrayImageDiff.absDiff(cvGrayImageBg, cvGrayImage);
	cvGrayImageDiff.threshold(threshold);
	
	// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
	// also, find holes is set to true so we will get interior contours as well....
	contourFinder.findContours(cvGrayImageDiff, 20, (640*480)/3, 1, false);	// find holes

	
	// send some data through OSC
    for (int i = 0; i < contourFinder.nBlobs; i++){
        contourFinder.blobs[i].draw(20,20);
		xPos = contourFinder.blobs[i].centroid.x;
		yPos = contourFinder.blobs[i].centroid.y;
		
		ofxOscMessage m;
		m.setAddress( "blob" );
		float xPosMapped = ofMap(xPos, 0, 640, 0.5, 0);
		float yPosMapped = ofMap(yPos, 0, 480, 0, 0.5);
		m.addFloatArg( xPosMapped);
		m.addFloatArg( yPosMapped);	
		sender.sendMessage( m );
    }	
	
	
}
//--------------------------------------------------------------
void testApp::draw(){
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){	
}
//--------------------------------------------------------------
void testApp::keyReleased(int key){
}
//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}
//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}
//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}
//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
}
//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
}
