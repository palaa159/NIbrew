#include "testApp.h"
#include "stdio.h"

//--------------------------------------------------------------
void testApp::setup() {
    
    stream.setup(this, 2, 0, 44100, 512, 4);
    soundBuffer = new float[512];
    sinWave.setup(44100);
    //    sinWave.setFrequency(440);
    sinWave.setVolume(0.07);
    
    // init spacebrew
    string host = "75.101.237.143"; // "localhost";
    string name = "senderNY";
    string description = "senderNY";
    
//    noteFreq.push_back(523.25); // C
//    noteFreq.push_back(587.33); // D
//    noteFreq.push_back(659.26); // E
//    noteFreq.push_back(783.99); // G
//    noteFreq.push_back(880.00); // A
//    noteFreq.push_back(1046.50); // HIGH C
    noteFreq.push_back(523.25); // C
    noteFreq.push_back(659.26); // D
    noteFreq.push_back(739.99); // E
    noteFreq.push_back(783.99); // G
    noteFreq.push_back(932.33); // A
    noteFreq.push_back(1046.50); // HIGH C
    // general setup
    ofSetFrameRate(30);
    
    spacebrew.addPublish("head.x", "range");
    spacebrew.addPublish("head.y", "range");
    spacebrew.addPublish("leftH.x", "range");
    spacebrew.addPublish("leftH.y", "range");
    spacebrew.addPublish("rightH.x", "range");
    spacebrew.addPublish("rightH.y", "range");
    spacebrew.addPublish("leftF.x", "range");
    spacebrew.addPublish("leftF.y", "range");
    spacebrew.addPublish("rightF.x", "range");
    spacebrew.addPublish("rightF.y", "range");
   
    spacebrew.addSubscribe("head.x", "range");
    spacebrew.addSubscribe("head.y", "range");
    spacebrew.addSubscribe("leftH.x", "range");
    spacebrew.addSubscribe("leftH.y", "range");
    spacebrew.addSubscribe("rightH.x", "range");
    spacebrew.addSubscribe("rightH.y", "range");
    spacebrew.addSubscribe("leftF.x", "range");
    spacebrew.addSubscribe("leftF.y", "range");
    spacebrew.addSubscribe("rightF.x", "range");
    spacebrew.addSubscribe("rightF.y", "range");
    
    spacebrew.connect( host, name, description );
    Spacebrew::addListener(this, spacebrew);
    
    // init OPENNI
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    openNIDevice.setup();
    openNIDevice.addImageGenerator();
    openNIDevice.addDepthGenerator();
    openNIDevice.setRegister(true);
    openNIDevice.setMirror(true);
    openNIDevice.addUserGenerator();
    openNIDevice.setMaxNumUsers(2);
    openNIDevice.start();
    
    yi.loadSound("sounds/chi01.mp3");
    er.loadSound("sounds/chi02.mp3");
    san.loadSound("sounds/chi03.mp3");
    liu.loadSound("sounds/2.wav");
    wu.loadSound("sounds/3.wav");
    Mi.loadSound("sounds/5.mp3");
//    yi.loadSound("sounds/chang1.wav");
//    er.loadSound("sounds/chang2.wav");
//    san.loadSound("sounds/chang3.wav");
//    liu.loadSound("sounds/star.mp3");
//    wu.loadSound("sounds/la.mp3");
//    Mi.loadSound("sounds/Mi.mp3");
//    chang1.loadSound("sounds/chang1.wav");
//    chang2.loadSound("sounds/chang2.wav");
//    chang3.loadSound("sounds/chang3.wav");
//    gugu.loadSound("sounds/gugu.mp3");
//    star.loadSound("sounds/star.mp3");
    
    bg.loadImage("pic/background.png");
    //life.loadImage("pic/life.tif");
    
    // set properties for all user masks and point clouds
    //openNIDevice.setUseMaskPixelsAllUsers(true); // if you just want pixels, use this set to true
    openNIDevice.setUseMaskTextureAllUsers(true); // this turns on mask pixels internally AND creates mask textures efficiently
    openNIDevice.setUsePointCloudsAllUsers(true);
    openNIDevice.setPointCloudDrawSizeAllUsers(2); // size of each 'point' in the point cloud
    openNIDevice.setPointCloudResolutionAllUsers(2); // resolution of the mesh created for the point cloud eg., this will use every second depth pixel
    
    // you can alternatively create a 'base' user class
    //    ofxOpenNIUser user;
    //    user.setUseMaskTexture(true);
    //    user.setUsePointCloud(true);
    //    user.setPointCloudDrawSize(2);
    //    user.setPointCloudResolution(2);
    //    openNIDevice.setBaseUserClass(user);
    
    ofTrueTypeFont::setGlobalDpi(72);

    verdana.loadFont(ofToDataPath("verdana.ttf"), 24);
    verdana14A.loadFont("verdana.ttf", 14, false);
	verdana14A.setLineHeight(18.0f);
	verdana14A.setLetterSpacing(1.037);


}

//--------------------------------------------------------------
void testApp::update(){
    openNIDevice.update();
    CX1+=1;
    CY1+=2.5;
    if (CY1>400) {
        CY1=0;
        CX1=60;
    }
    // update spacebrew
    if ( spacebrew.isConnected() ){
        spacebrew.sendRange("head.x", head.x);
        spacebrew.sendRange("head.y", head.y);
        spacebrew.sendRange("leftH.x", leftHand.x);
        spacebrew.sendRange("leftH.y", leftHand.y);
        spacebrew.sendRange("rightH.x", rightHand.x);
        spacebrew.sendRange("rightH.y", rightHand.y);
        spacebrew.sendRange("leftF.x", leftFoot.x);
        spacebrew.sendRange("leftF.y", leftFoot.y);
        spacebrew.sendRange("rightF.x", rightFoot.x);
        spacebrew.sendRange("rightF.y", rightFoot.y);
    }
    if (abs(leftHand.x+600-o_rightHand.x)<100&&abs(leftHand.y-o_rightHand.y)<100&&abs(head.y-o_head.y)<100&&abs(head.x+600-o_head.x)<100){
        R-=20,G+=50,B-=10;
        if (G>255) {
            R=leftHand.y*0.5+100,G=119,B=224;
        }
    }
    
    if (abs(leftHand.x+600-o_rightHand.x)<100&&abs(leftHand.y-o_rightHand.y)<100&&abs(rightFoot.y-o_leftFoot.y)<100&&abs(leftFoot.x+600-o_rightFoot.x)<100){
        R-=20,G+=50,B-=10;
        if (G>255) {
            R=leftHand.y*0.5+100,G=119,B=224;
        }

    }

}

//--------------------------------------------------------------
//--------------------------------------------------------------
void testApp::draw(){
    bShape.clear();
	//ofSetColor(255, 255, 255);
    
    ofPushMatrix();
    // draw debug (ie., image, depth, skeleton)
    openNIDevice.drawDebug();
    ofPopMatrix();
    
    ofPushMatrix();
    // use a blend mode so we can see 'through' the mask(s)
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    // get number of current users
    int numUsers = openNIDevice.getNumTrackedUsers();
    
    // iterate through users
    for (int i = 0; i < numUsers; i++){
        
        // get a reference to this user
        ofxOpenNIUser & user = openNIDevice.getTrackedUser(i);
        
        // draw the mask texture for this user
        user.drawMask();
        
        // get joint position
        head = user.getJoint(JOINT_HEAD).getProjectivePosition();
        leftHand = user.getJoint(JOINT_LEFT_HAND).getProjectivePosition();
        rightHand = user.getJoint(JOINT_RIGHT_HAND).getProjectivePosition();
        leftFoot = user.getJoint(JOINT_LEFT_FOOT).getProjectivePosition();
        rightFoot = user.getJoint(JOINT_RIGHT_FOOT).getProjectivePosition();
        
        ofPushMatrix();
        // move it a bit more central
        ofTranslate(320, 240, 10);
        user.drawPointCloud();
        
        ofPopMatrix();
    }
    
    ofDisableBlendMode();
    
    
    //SH group adding parts~
    
    ofSetColor(abs(255-rightHand.y*0.5),139, 240);
    
    bg.draw(-200, 0);
    life.draw(800,600);

    
    ofSetColor(leftHand.y,255,rightHand.y*50);
    ofFill();
    
    bShape.addVertex(head.x+600, head.y);
    bShape.addVertex(leftHand.x+600, leftHand.y);
    bShape.addVertex(leftFoot.x+600, leftFoot.y);
    bShape.addVertex(rightFoot.x+600, rightFoot.y);
    bShape.addVertex(rightHand.x+600, rightHand.y);
    bShape.close();
    bShape.draw();
    
    bShape_area = abs(bShape.getArea()/1000);
    noteIndex = ofMap(bShape_area, 0, 80, 0, 5);
    sinWave.setFrequency(noteFreq[noteIndex]);
    verdana.drawString(ofToString(bShape_area), 100, 100);
    
    ofSetColor(255,0,0);
    ofSetLineWidth(4);
    ofFill();
    
     
    ofSetColor(leftHand.y,100,rightHand.y*20);
    ofFill();
    ofSetPolyMode(OF_POLY_WINDING_NONZERO);
	ofBeginShape();
    ofVertex(o_leftFoot.x,o_leftFoot.y);
    ofVertex(o_leftHand.x,o_leftHand.y);
    ofVertex(o_head.x,o_head.y);
    ofVertex(o_rightHand.x,o_rightHand.y);
    ofVertex(o_rightFoot.x,o_rightFoot.y);
	ofEndShape();
    
    // color change
    //(100,150)
    if (abs(leftHand.x-100+600)>20&&abs(leftHand.y-150)>20)
    {
        ofSetColor(leftHand.y,100,rightHand.y*20);
        ofFill();
        ofBeginShape();
        ofVertex(72+ofRandom(10)+600,145+ofRandom(10));
        ofVertex(95+ofRandom(10)+600,115+ofRandom(10));
        ofVertex(130+ofRandom(10)+600,155+ofRandom(10));
        ofVertex(105+ofRandom(10)+600,180+ofRandom(10));
        ofEndShape();

    }
    else{
        ofSetColor(255,255,13);
        ofFill();
        ofBeginShape();
        ofVertex(72+600,145);
        ofVertex(95+600,115);
        ofVertex(130+600,155);
        ofVertex(105+600,180);
        ofEndShape();
    }

    //(400,100)
    if (abs(rightHand.x-400+600)>20&&abs(rightHand.y-100)>20)
    {
        ofSetColor(leftHand.y,100,rightHand.y*20);
        ofBeginShape();
        ofVertex(372+ofRandom(10)+600,95+ofRandom(10));
        ofVertex(410+ofRandom(10)+600,40+ofRandom(10));
        ofVertex(440+ofRandom(10)+600,110+ofRandom(10));
        ofVertex(400+ofRandom(10)+600,150+ofRandom(10));
        ofEndShape();
        
    }
    else{
        ofSetColor(0,255,250);
        
        ofBeginShape();
        ofVertex(372+600,95);
        ofVertex(410+600,40);
        ofVertex(440+600,110);
        ofVertex(400+600,150);
        ofEndShape();
    }
//(150,500)
    if (abs(leftFoot.x-150+600)>20&&abs(leftFoot.y-500)>20)
    {
        ofSetColor(leftHand.y,100,rightHand.y*20);
        ofBeginShape();
        ofVertex(112+ofRandom(10)+600,505+ofRandom(10));
        ofVertex(155+ofRandom(10)+600,445+ofRandom(10));
        ofVertex(190+ofRandom(10)+600,555+ofRandom(10));
        ofVertex(150+ofRandom(10)+600,580+ofRandom(10));
        ofEndShape();
        
    }
    else{
        ofSetColor(135,255,10);
        
        ofBeginShape();
        ofVertex(112+600,505);
        ofVertex(155+600,445);
        ofVertex(190+600,555);
        ofVertex(150+600,580);
        ofEndShape();
    }
//(500,400)
    if (abs(rightHand.x-500+600)>20&&abs(rightHand.y-400)>20)
    {
        ofSetColor(leftHand.y,100,rightHand.y*20);
        ofBeginShape();
        ofVertex(470+ofRandom(10)+600,405+ofRandom(10));
        ofVertex(505+ofRandom(10)+600,375+ofRandom(10));
        ofVertex(525+ofRandom(10)+600,395+ofRandom(10));
        ofVertex(500+ofRandom(10)+600,440+ofRandom(10));
        ofEndShape();
        
    }
    else{
        ofSetColor(255,175,13);
        
        ofBeginShape();
        ofVertex(470+600,405);
        ofVertex(505+600,375);
        ofVertex(525+600,395);
        ofVertex(500+600,440);
        ofEndShape();
    }
//(400,600)
    if (abs(rightFoot.x-150+600)>20&&abs(rightFoot.y-500)>20)
    {
        ofSetColor(leftHand.y,100,rightHand.y*20);
        ofFill();
        ofBeginShape();
        ofVertex(375+ofRandom(10)+600,600+ofRandom(10));
        ofVertex(400+ofRandom(10)+600,570+ofRandom(10));
        ofVertex(450+ofRandom(10)+600,610+ofRandom(10));
        ofVertex(410+ofRandom(10)+600,635+ofRandom(10));
        ofEndShape();
        
    }
    else{
        ofSetColor(255,158,212);
        ofFill();
        ofBeginShape();
        ofVertex(375+600,600);
        ofVertex(400+600,570);
        ofVertex(450+600,610);
        ofVertex(410+600,635);
        ofEndShape();
    }


    
    
    
    //lefthand
    if (abs(leftHand.x-100)<20&&abs(leftHand.y-150)<20) {
        yi.play();
    }
    if (abs(leftHand.x-400)<20&&abs(leftHand.y-100)<20) {
        er.play();
    }
    if (abs(leftHand.x-150)<20&&abs(leftHand.y-500)<20) {
        san.play();
    }
    if (abs(leftHand.x-500)<20&&abs(leftHand.y-400)<20) {
        wu.play();
    }
    if (abs(leftHand.x-400)<20&&abs(leftHand.y-600)<20) {
        liu.play();
    }
    
    //righthand
    if (abs(rightHand.x-100)<20&&abs(rightHand.y-150)<20) {
        yi.play();
    }
    if (abs(rightHand.x-400)<20&&abs(rightHand.y-100)<20) {
        er.play();
    }
    if (abs(rightHand.x-150)<20&&abs(rightHand.y-500)<20) {
        san.play();
    }
    if (abs(rightHand.x-500)<20&&abs(rightHand.y-400)<20) {
        wu.play();
    }
    if (abs(rightHand.x-400)<20&&abs(rightHand.y-600)<20) {
        liu.play();
    }
    
    //head
    if (abs(head.x-100)<20&&abs(head.y-150)<20) {
        yi.play();
    }
    if (abs(head.x-400)<20&&abs(head.y-100)<20) {
        er.play();
    }
    if (abs(head.x-150)<20&&abs(head.y-500)<20) {
        san.play();
    }
    if (abs(head.x-500)<20&&abs(head.y-400)<20) {
        wu.play();
    }
    if (abs(head.x-400)<20&&abs(head.y-600)<20) {
        liu.play();
    }
    
    //leftFoot
    if (abs(leftFoot.x-100)<20&&abs(leftFoot.y-150)<20) {
        yi.play();
    }
    if (abs(leftFoot.x-400)<20&&abs(leftFoot.y-100)<20) {
        er.play();
    }
    if (abs(leftFoot.x-150)<20&&abs(leftFoot.y-500)<20) {
        san.play();
    }
    if (abs(leftFoot.x-500)<20&&abs(leftFoot.y-400)<20) {
        wu.play();
    }
    if (abs(leftFoot.x-400)<20&&abs(leftFoot.y-600)<20) {
        liu.play();
    }
    
    //rightFoot
    if (abs(rightFoot.x-100)<20&&abs(rightFoot.y-150)<20) {
        yi.play();
    }
    if (abs(rightFoot.x-400)<20&&abs(rightFoot.y-100)<20) {
        er.play();
    }
    if (abs(rightFoot.x-150)<20&&abs(rightFoot.y-500)<20) {
        san.play();
    }
    if (abs(rightFoot.x-500)<20&&abs(rightFoot.y-400)<20) {
        wu.play();
    }
    if (abs(rightFoot.x-400)<20&&abs(rightFoot.y-600)<20) {
        liu.play();
    }
    
    
    //interactive between nyc and shg
//    if (abs(rightHand.x-o_leftHand.x)<20&&abs(rightHand.y-o_leftHand.y)<20&&abs(head.y-o_head.y)<20&&abs(head.x-o_head.x)<20) {
//        chang1.play();
//    }
//    if (abs(rightHand.x-o_leftHand.x)<20&&abs(rightHand.y-o_leftHand.y)<20&&abs(rightFoot.y-o_leftFoot.y)<20&&abs(rightFoot.x-o_leftFoot.x)<20) {
//        chang2.play();
//    }
//    
//    if (abs(rightHand.x-o_leftFoot.x)<20&&abs(rightHand.y-o_leftFoot.y)<20&&abs(head.y-o_leftHand.y)<20&&abs(head.x-o_leftHand.x)<20) {
//        chang3.play();
//    }
//    if (abs(rightHand.x-o_head.x)<20&&abs(rightHand.y-o_head.y)<20&&abs(rightFoot.y-o_leftHand.y)<20&&abs(rightFoot.x-o_leftHand.x)<20) {
//        si.play();
//    }
    if (abs(leftHand.x+600-o_rightHand.x)<100&&abs(leftHand.y-o_rightHand.y)<100&&abs(head.y-o_head.y)<100&&abs(head.x+600-o_head.x)<100) {
        yi.play();
    }
    
    if (abs(leftHand.x+600-o_rightHand.x)<100&&abs(leftHand.y-o_rightHand.y)<100&&abs(rightFoot.y-o_leftFoot.y)<100&&abs(leftFoot.x+600-o_rightFoot.x)<100){
        er.play();
    }
    
    //type fonts
    ofPushMatrix();
    string scaleA = "GHOST BEATS";
    ofRectangle bounds1 = verdana14A.getStringBoundingBox(scaleA, 0, 0);
    ofTranslate(600+bounds1.width/2,50+bounds1.height / 2, 0);
    ofScale(3.0 + cos(ofGetElapsedTimef()), 3.0 + cos(ofGetElapsedTimef()), 1.0);
    verdana14A.drawString(scaleA, -bounds1.width/2, bounds1.height/2 );
	ofPopMatrix();
   
    ofPushMatrix();
    string scaleB = "SH GHOST";
    ofRectangle bounds2 = verdana14A.getStringBoundingBox(scaleB, 0, 0);
    ofTranslate(100+bounds2.width/2,700+bounds2.height / 2, 0);
    ofScale(1.0 + sin(ofGetElapsedTimef()), 1.0 + sin(ofGetElapsedTimef()), 1.0);
    verdana14A.drawString(scaleB, -bounds2.width/2, bounds2.height/2 );
	ofPopMatrix();
    
    ofPushMatrix();
    string scaleC = "NY GHOST";
    ofRectangle bounds3 = verdana14A.getStringBoundingBox(scaleC, 0, 0);
    ofTranslate(1050+bounds3.width/2,700+bounds3.height / 2, 0);
    ofScale(1.0 + sin(ofGetElapsedTimef()), 1.0 + sin(ofGetElapsedTimef()), 1.0);
    verdana14A.drawString(scaleC, -bounds3.width/2, bounds3.height/2 );
	ofPopMatrix();

    
    
    
}

//--------------------------------------------------------------
void testApp::userEvent(ofxOpenNIUserEvent & event){
    // show user event messages in the console
    ofLogNotice() << getUserStatusAsString(event.userStatus) << "for user" << event.id << "from device" << event.deviceID;
}

//--------------------------------------------------------------
void testApp::exit(){
    openNIDevice.stop();
}

//--------------------------------------------------------------
// SPACEBREW
void testApp::onMessage( Spacebrew::Message & msg ){
    if(msg.name == "head.x") {
        o_head.x = ofToInt(msg.value);
    }else if(msg.name == "head.y") {
        o_head.y = ofToInt(msg.value);
    }else if(msg.name == "leftH.x") {
        o_leftHand.x = ofToInt(msg.value);
    }else if(msg.name == "leftH.y") {
        o_leftHand.y = ofToInt(msg.value);
    }else if(msg.name == "rightH.x") {
        o_rightHand.x = ofToInt(msg.value);
    }else if(msg.name == "rightH.y") {
        o_rightHand.y = ofToInt(msg.value);
    }else if(msg.name == "leftF.x") {
        o_leftFoot.x = ofToInt(msg.value);
    }else if(msg.name == "leftF.y") {
        o_leftFoot.y = ofToInt(msg.value);
    }else if(msg.name == "rightF.x") {
        o_rightFoot.x = ofToInt(msg.value);
    }else if(msg.name == "rightF.y") {
        o_rightFoot.y = ofToInt(msg.value);
    }
}

void testApp::audioOut(float * output, int bufferSize, int nChannels){
    
	for (int i = 0; i < bufferSize; i++){
        
        float sample = sinWave.getSample(); //ofRandom(-1,1);
        
        output[i*nChannels    ] = sample;
        output[i*nChannels + 1] = sample;
        
        soundBuffer[i] = sample;
	}
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
    san.play();
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}