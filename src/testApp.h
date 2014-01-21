#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxOsc.h"

#define HOST "localhost"
#define PORT 57120



class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

	
	ofTexture	texture;
	ofImage		image;
	
	ofxCvColorImage cvColorImage, cvColorImage2;
	ofxCvGrayscaleImage cvGrayImage, cvGrayImageBg, cvGrayImageDiff;
	ofxCvFloatImage cvFloatImage;
	ofxCvShortImage cvShortImage;  //Image with "unsigned short" pixels	
	
	
	ofxCvContourFinder 	contourFinder;
	
	int 				threshold;
	bool				bLearnBakground;
	
	float xPos, yPos;
	
	// OSC communication
	ofxOscSender sender;
	
};

#endif
