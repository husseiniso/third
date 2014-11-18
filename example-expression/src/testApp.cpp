#include "testApp.h"

using namespace ofxCv;
using namespace cv;

void testApp::setup() {
    ofSetVerticalSync(true);
    cam.initGrabber(1280, 960);
    
    tracker.setup();
    tracker.setRescale(.5);
}

void testApp::update() {
    cam.update();
    if(cam.isFrameNew()) {
        if(tracker.update(toCv(cam))) {
            classifier.classify(tracker);
        }
    }
}

void testApp::draw() {
    ofPolyline noseBridge, noseBase, innerMouth, outerMouth;
    cam.draw(0, 0);
    
    //The Scene is of normal colors at the beginning
    ofSetColor(220,0,0);
    
    if(tracker.getFound()){
        tracker.draw();
        
        //Get the inner mouth, nose bridge and nose base features
        innerMouth = tracker.getImageFeature(ofxFaceTracker::INNER_MOUTH);
        noseBridge = tracker.getImageFeature(ofxFaceTracker::NOSE_BRIDGE);
        noseBase = tracker.getImageFeature(ofxFaceTracker::NOSE_BASE);
        
        int w = 100, h = 12;
        ofPushStyle();
        ofPushMatrix();
        ofTranslate(5, 10);
        int n = classifier.size();
        int primary = classifier.classify(tracker);
        ofPopMatrix();
        ofPopStyle();
        
        //Put all features vertices in corresponding vectors.
        vector<ofPoint> mouthVertices = innerMouth.getVertices();
        vector<ofPoint> noseBridgeVertices = noseBridge.getVertices();
        vector<ofPoint> noseBaseVertices = noseBase.getVertices();
        
        // Calculating the nose size.
        float PointNose1x = noseBridgeVertices[0].x;
        float PointNose1y = noseBridgeVertices[0].y;
        float PointNose2x = noseBaseVertices[4].x;
        float PointNose2y = noseBaseVertices[4].y;
        float NoseSize = sqrt( pow(abs(PointNose1x-PointNose2x),2) + pow(abs(PointNose1y-PointNose2y),2));
        
        // Calculating the mouth stretch so that if it is larger than a certain value for a certain face size(indicated by the nose size specifically), it denotes a smile.
        float PointMouth1x = mouthVertices[0].x;
        float PointMouth1y = mouthVertices[0].y;
        float PointMouth2x = mouthVertices[4].x;
        float PointMouth2y = mouthVertices[4].y;
        float MouthStretch = sqrt( pow(abs(PointMouth1x-PointMouth2x),2) + pow(abs(PointMouth1y-PointMouth2y),2));
        
        // Conditions for a smile detection.
        if ((NoseSize<40 && MouthStretch>50)||
            (NoseSize>64 && NoseSize<= 80 && MouthStretch>80)||
            (NoseSize>40 && NoseSize<= 50 && MouthStretch>57)||
            (NoseSize>50 && NoseSize<=64 && MouthStretch>80) || 
            (NoseSize>80 && MouthStretch>90))
            
           //Color the scene in colored
            ofSetColor(0,255,255);
        
    }
    
    ofPopMatrix();
    ofPopStyle();
    
    ofDrawBitmapString(ofToString((int) ofGetFrameRate()), ofGetWidth() - 20, ofGetHeight() - 10);
    drawHighlightString(
                        string() +
                        "smile",
                        14, ofGetHeight() - 7 * 12);

}

void testApp::keyPressed(int key) {
    if(key == 'r') {
        tracker.reset();
        classifier.reset();
    }
}