#include "ofApp.h"

static const int BUFFER_SIZE = 64;
static const int STEPS = 64;
static const float RADIUS = 300.0;
static const float LINE_HEIGHT = 50.0;

//--------------------------------------------------------------
void ofApp::setup(){

    soundStream.printDeviceList();

    buffers.assign(BUFFER_SIZE * STEPS, 0.0);

    soundStream.setup(this, 0, 1, 44100, BUFFER_SIZE, 4);

    angle = 0;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    //ofBackground(255);

    ofSetColor(0);

    ofVec2f center = ofVec2f(ofGetWidth()/2, ofGetHeight()/2);

    for (int j = 0; j < STEPS; j++) {

        for (int i = 0; i < BUFFER_SIZE - 1; i++) {

            ofVec2f dir(cos(angle), sin(angle));
            ofVec2f orth(-dir.y, dir.x);

            float pos1 = (float)i / BUFFER_SIZE;
            float pos2 = (float)i / BUFFER_SIZE;

            ofVec2f p1 = dir * ofMap( pos1, 0.0, 1.0, 0.0, RADIUS );
            ofVec2f p2 = dir * ofMap( pos2, 0.0, 1.0, 0.0, RADIUS );

            p1 += orth * buffers[j * STEPS + i] * LINE_HEIGHT * pos1;
            p2 += orth * buffers[j * STEPS + i+1] * LINE_HEIGHT * pos2;

            ofDrawLine(center + p1, center + p2);
        }

        angle = fmod((angle + (PI * 2) / STEPS), (PI * 2));
    }


    ofDrawBitmapString("FPS: "+ofToString(ofGetFrameRate()), 20, 20);

    //ofSleepMillis(100);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::audioIn(float * input, int bufferSize, int nChannels){

    //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
    for (int i = 0; i < bufferSize; i++){
        buffers[bufferIndex * STEPS + i]		= input[i];
    }

    bufferIndex = (bufferIndex + 1) % STEPS;
    
}
