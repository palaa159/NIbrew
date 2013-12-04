#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    // init spacebrew
    string host = "75.101.237.143"; // "localhost";
    string name = "senderNYC";
    string description = "senderNYC";
    
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
    
    re.loadSound("sounds/re.mp3");
    so.loadSound("sounds/so.mp3");
    la.loadSound("sounds/la.mp3");
    Do.loadSound("sounds/Do.mp3");
    Do2.loadSound("sounds/Do2.mp3");
    Mi.loadSound("sounds/Mi.mp3");
    
    bg.loadImage("pic/background.png");
    
    CX1=80;
    CY1=0;
    CX2=240;
    CY2=0;
    
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
    
    verdana.loadFont(ofToDataPath("verdana.ttf"), 24);
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
}

//--------------------------------------------------------------
//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(255, 255, 255);
    
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
    
    ofSetColor(leftHand.y,100, rightHand.y*2);
    //ofSetColor(255, 255, 255);
    //ofRect(0, 0,1000, 1000);
    
    bg.draw(-200, 0);
    
    //    ofSetColor(255,255,255);
    //    ofSetLineWidth(3);
    //    ofLine(leftHand.x+10, leftHand.y+10, head.x+10, head.y+10);
    //    ofLine(head.x+20, head.y+10, rightHand.x+10, rightHand.y+15);
    //    ofLine(rightHand.x+8, rightHand.y+10, rightFoot.x+20, rightFoot.y+10);
    //    ofLine(rightFoot.x, rightFoot.y, leftFoot.x, leftFoot.y);
    //    ofLine(leftFoot.x,leftFoot.y, leftHand.x, leftHand.y);
    
    ofSetColor(255,255,255);
    ofCircle(leftHand.x+20, leftHand.y+20,10);
    ofCircle(rightHand.x+10, rightHand.y+10,6);
    
    
    
    ofSetColor(leftHand.y,100,rightHand.y*20);
    ofSetPolyMode(OF_POLY_WINDING_NONZERO);
	ofBeginShape();
    ofVertex(leftFoot.x,leftFoot.y);
    ofVertex(leftHand.x,leftHand.y);
    ofVertex(head.x,head.y);
    ofVertex(rightHand.x,rightHand.y);
    ofVertex(rightFoot.x,rightFoot.y);
	ofEndShape();
	
    ofCircle(100, 100, 20);
    ofCircle(250, 100, 20);
    ofCircle(400, 100, 20);
    
    
    a=rightHand.y;
    
    b=head.y;
    c=leftHand.y;
    
    if (abs(a-b<10)) {
        
        
        la.play();
    }
    if (abs(c-b<10)) {
        so.play();
    }
    if (abs(leftHand.x-100)<10&&abs(leftHand.y-100)<10) {
        Do.play();
    }
    if (abs(leftHand.x-250)<10&&abs(leftHand.y-100)<10) {
        re.play();
    }
    if (abs(leftHand.x-400)<10&&abs(leftHand.y-100)<10) {
        Mi.play();
    }
    if (abs(rightHand.x-100)<10&&abs(rightHand.y-100)<10) {
        Do.play();
    }
    if (abs(rightHand.x-250)<10&&abs(rightHand.y-100)<10) {
        re.play();
    }
    if (abs(rightHand.x-400)<10&&abs(rightHand.y-100)<10) {
        Mi.play();
    }
    
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
    } else if(msg.name == "head.y") {
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