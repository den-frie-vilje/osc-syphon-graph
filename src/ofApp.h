#pragma once

#include "ofMain.h"
#include "ofxSyphon.h"
#include "ofxOsc.h"
#include "ofxGui.h"
#include "ofxOscParameterSync.h"
#include "qLabController.hpp"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void drawStringAtSize(string str, ofTrueTypeFont &font, float size, float x, float y, int hAlign = 0, int vAlign = 0);
    
    ofFbo graphFbo;
    ofxSyphonServer grahpSyphonServer;
    
    ofxOscParameterSync oscSync;
    
    ofParameterGroup graphParameters;
    ofParameter<float> graphFade;
    ofParameter<bool> graphSetup;

    // background
    
    ofParameterGroup graphBackground;
    ofParameter<int> graphBackgroundWidth;
    ofParameter<int> graphBackgroundHeight;
    ofParameter<glm::vec2> graphBackgroundMargins;
    ofParameter<ofFloatColor> graphBackgroundColor;

    // title
    
    ofParameterGroup graphTitle;
    ofParameter<ofFloatColor> graphTitleColor;
    ofParameter<float> graphTitleSize;
    ofParameter<string> graphTitleText;
    ofParameter<float> graphTitleFade;

    // labels
    
    ofParameterGroup graphLabels;
    ofParameter<ofFloatColor> graphLabelsColor;
    ofParameter<float> graphLabelsSize;

    ofParameterGroup graphLabelsLeft;
    ofParameter<string> graphLabelsLeftText;
    ofParameter<float> graphLabelsLeftFade;

    ofParameterGroup graphLabelsCenter;
    ofParameter<string> graphLabelsCenterText;
    ofParameter<float> graphLabelsCenterFade;

    ofParameterGroup graphLabelsRight;
    ofParameter<string> graphLabelsRightText;
    ofParameter<float> graphLabelsRightFade;

    // bars
    
    const int numberBars = 10;
    
    ofParameterGroup graphBars;
    ofParameter<ofFloatColor> graphBarsColor;
    ofParameter<glm::vec2> graphBarsMargins;
    ofParameterGroup graphBarsStroke;
    ofParameter<ofFloatColor> graphBarsStrokeColor;
    ofParameter<float> graphBarsStrokeWidth;
    ofParameter<float> graphBarsStrokeFade;
    ofParameter<bool> graphBarsStrokeFullHeight;
    ofParameterGroup graphBarsNumber;
    ofParameter<ofFloatColor> graphBarsNumberColor;
    ofParameter<float> graphBarsNumberFade;
    ofParameter<float> graphBarsNumberSize;
    ofParameter<glm::vec2> graphBarsNumberPosition;
    ofParameterGroup graphBarsPercent;
    ofParameter<ofFloatColor> graphBarsPercentColor;
    ofParameter<float> graphBarsPercentFade;
    ofParameter<float> graphBarsPercentSize;
    ofParameter<glm::vec2> graphBarsPercentPosition;


    std::vector< ofParameterGroup > graphBarsBars;
    std::vector< ofParameter<float> > graphBarsBarsValue;
    std::vector< ofParameter<float> > graphBarsBarsFade;
    
    qLabController qLab;

    int guiWidth = 300;
    ofxPanel gui;
    ofTrueTypeFont guiFont;
    ofTrueTypeFont titleFont;
    ofTrueTypeFont labelsFont;
    ofImage dfvLogo;
    
    bool saveToQlab = false;

};
