#ifndef _TEST_APP
#define _TEST_APP

#include "ofxOpenNI.h"
#include "ofMain.h"
#include "oscillator.h"
#import "ofxSpacebrew.h"

class testApp : public ofBaseApp{
    
public:
    
	void setup();
	void update();
	void draw();
    void exit();
    
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
    
    void userEvent(ofxOpenNIUserEvent & event);
    
	ofxOpenNI openNIDevice;
    // me
    ofPoint head;
    ofPoint leftHand;
    ofPoint rightHand;
    ofPoint leftFoot;
    ofPoint rightFoot;
    // you
    ofPoint o_head;
    ofPoint o_leftHand;
    ofPoint o_rightHand;
    ofPoint o_leftFoot;
    ofPoint o_rightFoot;
    
    
    int array_size;
    int a;
    int b,c,CX1,CY1,CX2,CY2;
    ofSoundPlayer   yi;
    ofSoundPlayer   er,chang1,chang2,chang3,gugu,star;
    ofSoundPlayer   san,si,wu,liu,Mi;
    ofImage bg,life;
    
    int nCurveVertices;
    
    ofTrueTypeFont verdana;
    
    // create your spacebrew object
    Spacebrew::Connection spacebrew;
    void onMessage( Spacebrew::Message & msg );
    int R,G,B;
    ofTrueTypeFont	verdana14A;
    
    // for oscillator
    void audioOut(float * input, int bufferSize, int nChannels);
    
    ofSoundStream stream;
    
    float * soundBuffer;
    
    oscillator sinWave;
    
    // for shape
    ofPolyline bShape;
    float bShape_area;
    
    vector<int> noteFreq;
    int noteIndex;
};

#endif
