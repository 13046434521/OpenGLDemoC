//
// Created by Administrator on 2019/4/13.
//
#include "sence.h"
static AAssetManager * aAssetManager = NULL;
unsigned char * loadFileContent(const char * path,int & filesize){
    unsigned  char * filecontent=NULL;
    AAsset *aAsset = AAssetManager_open(aAssetManager,path,AASSET_MODE_UNKNOWN);
    if (aAsset==NULL){
        return NULL;
    }

    filesize = AAsset_getLength(aAsset);
    filecontent = new unsigned char[filesize+1];
    AAsset_read(aAsset,filecontent,filesize);
    filecontent[filesize]='\0';//字符串加结尾，不容易出错
    return filecontent;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jtl_opengldemo_OpenGLNative_initGL(JNIEnv *env, jclass type) {
    initGL();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jtl_opengldemo_OpenGLNative_surfaceChanged(JNIEnv *env, jclass type, jint width,
        jint height) {
    surfaceChange(width,height);

}

extern "C"
JNIEXPORT void JNICALL
Java_com_jtl_opengldemo_OpenGLNative_drawFrame(JNIEnv *env, jclass type) {
   drawFrame();
}



extern "C"
JNIEXPORT void JNICALL
Java_com_jtl_opengldemo_OpenGLNative_loadAssetContent(JNIEnv *env, jclass type,
                                                      jobject assetManager) {
    aAssetManager=AAssetManager_fromJava(env,assetManager);
}
