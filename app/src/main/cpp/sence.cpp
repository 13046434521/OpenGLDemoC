//
// Created by Administrator on 2019/4/14.
//
#include "sence.h"
void initGL(){
    glClearColor(0.1f,0.5f,0.9f,1.0f);
}
void surfaceChange(int width,int height){
    glViewport(0,0,width,height);
}
void drawFrame(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}
