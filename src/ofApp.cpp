#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //ofSetLogLevel(OF_LOG_VERBOSE);
    
    // Assets
    dfvLogo.load("den frie vilje logo white.png");
    
    // Fonts
    //TODO: fix naming based on folders
    ofTrueTypeFont::setGlobalDpi(72);
    
    string guiFontPath = "fonts/defaults/gui.otf";
    int guiFontSize = 10;
    
    guiFont.load(guiFontPath, guiFontSize, true, true);
    titleFont.load("fonts/defaults/title.otf", 100, true, true, true, 0.1);
    labelsFont.load("fonts/defaults/labels.otf", 100, true, true, true, 0.1);
    leaderFont.load("fonts/defaults/leader.otf", 100, true, true, true, 0.1);

    ofDirectory fontsDir;
    
    if(ofFile::doesFileExist("fonts/")){
        fontsDir.listDir("fonts/");
        fontsDir.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order
        
        // you can now iterate through the files and load them into the ofImage vector
        for(auto file : fontsDir.getFiles()){
            ofDirectory fileDir;
            if(file.isDirectory()){
                fileDir.listDir(file.path());
                fileDir.allowExt("otf");
                fileDir.allowExt("ttf");
                fileDir.sort();
                if(fileDir.size() > 0){
                    if(file.getBaseName() == "gui"){
                        guiFontPath = fileDir.getFile(0).path();
                        guiFont.load(fileDir.getFile(0).path(), guiFontSize, true, true);
                    }
                    if(file.getBaseName() == "title"){
                        titleFont.load(fileDir.getFile(0).path(), 100, true, true, true, 0.1);
                    }
                    if(file.getBaseName() == "lables"){
                        labelsFont.load(fileDir.getFile(0).path(), 100, true, true, true, 0.1);
                    }
                    if(file.getBaseName() == "leader"){
                        leaderFont.load(fileDir.getFile(0).path(), 100, true, true, true, 0.1);
                    }
                }
            }
        }
    }

    // Parameters
    
    graphParameters.setName("graph");
    graphParameters.add(graphFade.set("master", 1.0,0.0,1.0));
    graphParameters.add(graphSetup.set("setup", false));

    graphBackground.setName("background");
    graphBackground.add(graphBackgroundColor.set("color",
                                                 ofFloatColor(0.0),
                                                 ofFloatColor(0.0),
                                                 ofFloatColor(1.0)));
    graphBackground.add(graphBackgroundWidth.set("width",1920,10,3000));
    graphBackground.add(graphBackgroundHeight.set("height",1080,10,3000));
    graphBackground.add(graphBackgroundMargins.set("margins",
                                                   glm::vec2(0.1,0.1),
                                                   glm::vec2(0,0),
                                                   glm::vec2(0.5,0.5)));
    graphParameters.add(graphBackground);
    
    graphTitle.setName("title");
    graphTitle.add(graphTitleFade.set("fade", 1.0,0.0,1.0));
    graphTitle.add(graphTitleText.set("text", "Title"));
    graphTitle.add(graphTitleSize.set("size",100,0,500));
    graphTitle.add(graphTitleColor.set("color",
                                       ofFloatColor(1.0),
                                       ofFloatColor(0.0),
                                       ofFloatColor(1.0)));
    graphTitle.add(graphTitlePosition.set("position",
                                          glm::vec2(0.0,0.0),
                                          glm::vec2(-1.0,-1.0),
                                          glm::vec2(1.0,1.0)));
    graphParameters.add(graphTitle);
    
    graphLeader.setName("leader");
    graphLeader.add(graphLeaderFade.set("fade", 1.0,0.0,1.0));
    graphLeader.add(graphLeaderText.set("text", "Leader"));
    graphLeader.add(graphLeaderSize.set("size",40,0,500));
    graphLeader.add(graphLeaderColor.set("color",
                                       ofFloatColor(1.0),
                                       ofFloatColor(0.0),
                                       ofFloatColor(1.0)));
    graphLeader.add(graphLeaderPosition.set("position",
                                          glm::vec2(-1.0,-1.0),
                                          glm::vec2(-1.0,-1.0),
                                          glm::vec2(1.0,1.0)));
    graphParameters.add(graphLeader);
    
    graphLabels.setName("labels");
    graphLabels.add(graphLabelsColor.set("color",
                                         ofFloatColor(1.0),
                                         ofFloatColor(0.0),
                                         ofFloatColor(1.0)));
    graphLabels.add(graphLabelsSize.set("size", 20, 0, 500));

    graphLabelsLeft.setName("left");
    graphLabelsLeft.add(graphLabelsLeftFade.set("fade", 1.0, 0.0, 1.0));
    graphLabelsLeft.add(graphLabelsLeftText.set("text", "Left Label"));
    graphLabels.add(graphLabelsLeft);

    graphLabelsCenter.setName("center");
    graphLabelsCenter.add(graphLabelsCenterFade.set("fade", 1.0, 0.0, 1.0));
    graphLabelsCenter.add(graphLabelsCenterText.set("text", "Center Label"));
    graphLabels.add(graphLabelsCenter);

    graphLabelsRight.setName("right");
    graphLabelsRight.add(graphLabelsRightFade.set("fade", 1.0, 0.0, 1.0));
    graphLabelsRight.add(graphLabelsRightText.set("text", "Right Label"));
    graphLabels.add(graphLabelsRight);
    
    graphParameters.add(graphLabels);
    
    graphBars.setName("bars");
    graphBars.add(graphBarsColor.set("color",
                                         ofFloatColor(1.0),
                                         ofFloatColor(0.0),
                                         ofFloatColor(1.0)));
    graphBars.add(graphBarsMargins.set("margins",
                                             glm::vec2(0.025,0.05),
                                             glm::vec2(0,0),
                                             glm::vec2(0.1,0.5)));
    graphBarsStroke.setName("stroke");
    graphBarsStroke.add(graphBarsStrokeColor.set("color",
                                                 ofFloatColor(1.0),
                                                 ofFloatColor(0.0),
                                                 ofFloatColor(1.0)));
    graphBarsStroke.add(graphBarsStrokeWidth.set("width", 2,0,100));
    graphBarsStroke.add(graphBarsStrokeFade.set("fade", 0.0,0.0,1.0));
    graphBarsStroke.add(graphBarsStrokeFullHeight.set("full", false));
    graphBars.add(graphBarsStroke);

    graphBarsNumber.setName("numbers");
    graphBarsNumber.add(graphBarsNumberColor.set("color",
                                                 ofFloatColor(1.0),
                                                 ofFloatColor(0.0),
                                                 ofFloatColor(1.0)));
    graphBarsNumber.add(graphBarsNumberFade.set("fade", 1.0, 0.0, 1.0));
    graphBarsNumber.add(graphBarsNumberSize.set("size", 30, 0, 500));
    graphBarsNumber.add(graphBarsNumberPosition.set("position",
                                                    glm::vec2(0.0,0.5),
                                                    glm::vec2(-1.0,-1.0),
                                                    glm::vec2(1.0,1.0)));
    graphBars.add(graphBarsNumber);

    graphBarsPercent.setName("percents");
    graphBarsPercent.add(graphBarsPercentColor.set("color",
                                                 ofFloatColor(1.0),
                                                 ofFloatColor(0.0),
                                                 ofFloatColor(1.0)));
    graphBarsPercent.add(graphBarsPercentFade.set("fade", 1.0, 0.0, 1.0));
    graphBarsPercent.add(graphBarsPercentSize.set("size", 30, 0, 500));
    graphBarsPercent.add(graphBarsPercentPosition.set("position",
                                                    glm::vec2(0.0,-0.5),
                                                    glm::vec2(-1.0,-1.0),
                                                    glm::vec2(1.0,1.0)));
    graphBars.add(graphBarsPercent);
    
    for(int i = 0; i < numberBars;i++){
        ofParameterGroup graphBarsBar;
        graphBarsBar.setName(ofToString(i+1));
        ofParameter<float> graphBarsBarValue;
        graphBarsBarValue.set("value", 0.0, 0.0, 100.0);
        graphBarsBarsValue.push_back(graphBarsBarValue);
        graphBarsBar.add(graphBarsBarValue);
        ofParameter<float> graphBarsBarFade;
        graphBarsBarFade.set("fade", 1.0, 0.0, 1.0);
        graphBarsBarsFade.push_back(graphBarsBarFade);
        graphBarsBar.add(graphBarsBarFade);
        graphBarsBars.push_back(graphBarsBar);
        graphBars.add(graphBarsBar);
    }
    
    graphParameters.add(graphBars);
    
    // GUI General setup
    ofxGuiSetDefaultWidth(guiWidth);
    ofxGuiSetTextPadding(4);
    ofxGuiSetDefaultHeight(16);
    ofxGuiSetBorderColor(ofColor(64,255));
    ofxGuiSetHeaderColor(ofColor(64,255));
    ofxGuiSetFont(guiFontPath, guiFontSize);

    guiParameters.add(guiSaveToQlab.set("save to qlab", false));
    guiParameters.add(graphParameters);
    
    gui.setup(guiParameters);
    gui.getGroup("graph").maximize();
    gui.getGroup("graph").minimizeAll();
    

    // Window
    ofSetWindowTitle("Osc Syphon Graph");
    
    // Osc
    oscSync.setup((ofParameterGroup&)gui.getParameter().castGroup().get("graph"),6666,"localhost",6667);

    // Syphon
    grahpSyphonServer.setName("Graph Output");
    
    // Qlab
    qLab.setup();
    
    // Renderer
    ofSetCircleResolution(127);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    oscSync.update();
    qLab.update();
    if(guiSaveToQlab.get()){
        qLab.newGroupWithOscCuesFromParameterGroup((ofParameterGroup&)gui.getParameter().castGroup().get("graph"));
        guiSaveToQlab.set(false);
    }
    
    if(graphFbo.getWidth() != graphBackgroundWidth.get() ||
       graphFbo.getHeight() != graphBackgroundHeight.get()){
        // dimensions were changed and fbo must be reinitialised.
        graphFbo.allocate(graphBackgroundWidth.get(), graphBackgroundHeight.get(), GL_RGBA, 16);
        // with alpha, 8 bits red, 8 bits green, 8 bits blue, 8 bits alpha, from 0 to 255 in 256 steps
        graphFbo.begin();
        ofClear(255,255,255, 0);
        graphFbo.end();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(ofColor(40,40,40));
    
    // Draw graph in Fbo
    graphFbo.begin();
    {
        
        int width =graphBackgroundWidth.get();
        int height =graphBackgroundHeight.get();
        
        glm::vec2 margins = graphBackgroundMargins.get();
        margins *= width;
        margins.y = fminf(height*0.5, margins.y);

        ofRectangle viewPort = ofRectangle(0, 0, width, height);
        ofRectangle viewPortMinusMargins = ofRectangle(viewPort.x+margins.x, viewPort.y+margins.y,
                                                       viewPort.width - (margins.x*2), viewPort.height - (margins.y*2));
        


        // background
        ofDisableAlphaBlending();
        ofClear(graphBackgroundColor.get());

        ofEnableAlphaBlending();

        if(graphSetup.get()){
            // margins
            ofSetColor(255,255,0, 64);
            ofFill();
            ofDrawRectangle(viewPortMinusMargins);
            ofNoFill();
            ofSetLineWidth(2.0);
            ofSetColor(255, 255, 0);
            ofDrawRectangle(viewPortMinusMargins);

            // test
            ofSetColor(200, 200, 0, 64);
            ofDrawEllipse(width/2, graphBackgroundHeight.get()/2, width*0.2*sin(ofGetElapsedTimef()), width*0.2*sin(ofGetElapsedTimef()));
        }
        
        // bars
        
        glm::vec2 barMargins = graphBarsMargins.get();
        barMargins *= width;
        float maxBarMarginsWidth = viewPortMinusMargins.getWidth() / 9.0;
        barMargins.x = fminf(barMargins.x, maxBarMarginsWidth);
        barMargins.y = fminf(barMargins.y, viewPortMinusMargins.getHeight()/2.0);

        for(int i = 0; i < numberBars;i++){
            float barWidth = (viewPortMinusMargins.getWidth() - (9.0 * barMargins.x)) / 10.0;
            ofRectangle barRect(viewPortMinusMargins.getLeft() + ((barWidth+barMargins.x)*i), viewPortMinusMargins.getBottom() - barMargins.y, barWidth, - (viewPortMinusMargins.getHeight() - (2.0 * barMargins.y))
            );
            ofRectangle valueRect(barRect);
            valueRect.scaleHeight((graphBarsBarsValue[i].get()/100.0));
            
            ofPushStyle();
            if(graphSetup.get()){
                ofFill();
                ofSetColor(255,0,255,64);
                ofDrawRectangle(barRect);
                ofNoFill();
                ofSetLineWidth(2.0);
                ofSetColor(255,0,255);
                ofDrawRectangle(barRect);
            }
            ofFill();
            ofFloatColor barColor(graphBarsColor.get());
            barColor.a = graphBarsBarsFade[i].get();
            ofSetColor(barColor);
            ofDrawRectangle(valueRect);
            ofNoFill();
            ofSetLineWidth(graphBarsStrokeWidth.get());
            ofFloatColor strokeColor(graphBarsStrokeColor.get());
            strokeColor.a = graphBarsStrokeFade.get() * graphBarsBarsFade[i].get();
            ofSetColor(strokeColor);
            ofDrawRectangle(graphBarsStrokeFullHeight.get()?barRect:valueRect);
            
            ofFill();
            ofFloatColor numberColor(graphBarsNumberColor.get());
            numberColor.a = graphBarsNumberFade.get() * graphBarsBarsFade[i].get();
            ofSetColor(numberColor);
            
            drawStringAtSize(ofToString(i+1),
                             labelsFont,
                             graphBarsNumberSize.get(),
                             barRect.getCenter().x + (graphBarsNumberPosition.get().x*barRect.getWidth()*0.5),
                            barRect.getBottom() + graphBarsNumberPosition.get().y*barRect.getWidth()*0.5,
                             graphBarsNumberPosition.get().x);

            ofFloatColor percentColor(graphBarsPercentColor.get());
            percentColor.a = graphBarsPercentFade.get() * graphBarsBarsFade[i].get();
            ofSetColor(percentColor);
            
            drawStringAtSize(ofToString(graphBarsBarsValue[i].get(),0) + " %",
                             labelsFont,
                             graphBarsPercentSize.get(),
                             barRect.getCenter().x + (graphBarsPercentPosition.get().x*barRect.getWidth()*0.5),
                             (graphBarsStrokeFullHeight.get()?barRect:valueRect).getTop() + graphBarsPercentPosition.get().y*barRect.getWidth()*0.5,
                             graphBarsPercentPosition.get().x);

            ofPopStyle();
            
        }
        
        // labels
        
        ofFill();
        ofFloatColor labelsColor(graphLabelsColor.get());

        labelsColor.a = graphLabelsLeftFade.get();
        ofSetColor(labelsColor);
        drawStringAtSize(graphLabelsLeftText.get(), labelsFont, graphLabelsSize.get(), viewPortMinusMargins.getLeft(), viewPortMinusMargins.getBottom(), -1, -1);

        labelsColor.a = graphLabelsCenterFade.get();
        ofSetColor(labelsColor);
        drawStringAtSize(graphLabelsCenterText.get(), labelsFont, graphLabelsSize.get(), viewPortMinusMargins.getCenter().x, viewPortMinusMargins.getBottom(), 0, -1);
        
        labelsColor.a = graphLabelsRightFade.get();
        ofSetColor(labelsColor);
        drawStringAtSize(graphLabelsRightText.get(), labelsFont, graphLabelsSize.get(), viewPortMinusMargins.getRight(), viewPortMinusMargins.getBottom(), 1, -1);
        
        // title
        ofFill();
        ofFloatColor titleColor(graphTitleColor.get());
        titleColor.a = graphTitleFade.get();
        ofSetColor(titleColor);
        drawStringAtSize(graphTitleText.get(), titleFont, graphTitleSize.get(), viewPortMinusMargins.getCenter().x + (graphTitlePosition.get().x * viewPortMinusMargins.getWidth() * 0.5), viewPortMinusMargins.getCenter().y  + (graphTitlePosition.get().y * viewPortMinusMargins.getHeight() * 0.5), graphTitlePosition.get().x, graphTitlePosition.get().y);

        // leader
        ofFill();
        ofFloatColor leaderColor(graphLeaderColor.get());
        leaderColor.a = graphLeaderFade.get();
        ofSetColor(leaderColor);
        drawStringAtSize(graphLeaderText.get(), leaderFont, graphLeaderSize.get(), viewPortMinusMargins.getCenter().x + (graphLeaderPosition.get().x * viewPortMinusMargins.getWidth() * 0.5), viewPortMinusMargins.getCenter().y  + (graphLeaderPosition.get().y * viewPortMinusMargins.getHeight() * 0.5), graphLeaderPosition.get().x, graphLeaderPosition.get().y);
        

        // master fader
        ofFill();
        ofSetColor(ofFloatColor(0.0, 1.0-graphFade.get()));
        ofDrawRectangle(0, 0, width, height);
        
    }
    graphFbo.end();
    
    // Publish syphon
    grahpSyphonServer.publishTexture(&graphFbo.getTexture());
    
    // Draw preview
    int viewPortMargin = 40;
    ofRectangle viewPort = ofRectangle(guiWidth, 0, ofGetWidth()-guiWidth, ofGetHeight());
    ofRectangle viewPortMinusMargins = ofRectangle(viewPort.x+viewPortMargin, viewPort.y+viewPortMargin,
                                                   viewPort.width - (viewPortMargin*2), viewPort.height - (viewPortMargin*2));
    
    ofRectangle fboRect = ofRectangle(0,0,graphFbo.getWidth(), graphFbo.getHeight());
    fboRect.scaleTo(viewPortMinusMargins, OF_ASPECT_RATIO_KEEP);
    
    ofFill();
    ofSetColor(255,255);
    ofDisableAlphaBlending();
    graphFbo.draw(fboRect);
    ofEnableAlphaBlending();

    // Draw Boundingbox
    ofNoFill();
    ofSetLineWidth(1);
    ofSetColor(100, 255);
    ofDrawRectangle(fboRect);
    
    // Draw Gui Label
    
    ofFill();
    string graphOutputLabel = "Syphon Output";
    ofRectangle graphOutputLabelBoundingBox = guiFont.getStringBoundingBox(graphOutputLabel, 0, 0);
    graphOutputLabelBoundingBox.alignToHorz(fboRect, OF_ALIGN_HORZ_CENTER);
    graphOutputLabelBoundingBox.alignTo(fboRect, OF_ALIGN_HORZ_CENTER, OF_ALIGN_VERT_BOTTOM, OF_ALIGN_HORZ_CENTER, OF_ALIGN_VERT_TOP);
    
    graphOutputLabelBoundingBox.setY(graphOutputLabelBoundingBox.y + guiFont.getSize());
    
    ofDrawRectRounded(graphOutputLabelBoundingBox.x-5, graphOutputLabelBoundingBox.y-4, graphOutputLabelBoundingBox.width+10, graphOutputLabelBoundingBox.height+9, 3);
    
    ofSetColor(255,255);
    guiFont.drawString(graphOutputLabel, graphOutputLabelBoundingBox.x, graphOutputLabelBoundingBox.getBottom());
    
    // Draw gui

    ofSetColor(64,255);
    ofDrawRectangle(0, 0, guiWidth+1,ofGetHeight());

    ofSetColor(96,255);
    int logoWidth = 70;
    dfvLogo.draw(guiWidth-logoWidth-10, ofGetHeight()-logoWidth-10, logoWidth,logoWidth);

    gui.setPosition(0, 0);
    gui.draw();
    
}

void ofApp::drawStringAtSize(string str, ofTrueTypeFont &font, float size, float x, float y, float hAlign, float vAlign){
    
    auto lines = ofSplitString(str, "\n");
    string mStr = "";
    for(int i = 0; i < lines.size(); i++){
        mStr += "M";
        if(i+1 < lines.size()){
            mStr+="\n";
        }
    }
    float mHeight = titleFont.stringHeight("M");
    float mLinesHeight = titleFont.stringHeight(mStr);
    
    mLinesHeight = ((lines.size()-1)*(mLinesHeight/lines.size()))+mHeight;
    
    float scale = size / font.getSize();
    
    ofPushMatrix();
    ofTranslate(x, y);
    ofPushMatrix();
    ofScale(scale, scale);
    
    int line = 1;
    float lineHeight = mLinesHeight/lines.size();
    
    for(auto l : lines){
        ofPushMatrix();
        float lineWidth = titleFont.stringWidth(l);
        ofTranslate(lineWidth*(-hAlign-1.0)/2.0, ((lineHeight*line*(-vAlign+1.0))/2.0)-((lines.size()-line)*lineHeight*ofMap(vAlign, -1.0, 1.0, 0.0, 1.0)));
        font.drawStringAsShapes(l, 0, 0);
        ofPopMatrix();
        line++;
    }
    
    ofPopMatrix();

    ofPopMatrix();
    
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
