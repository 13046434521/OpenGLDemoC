package com.jtl.opengldemo;

/**
 * 作者:jtl
 * 日期:Created in 2019/4/13 16:26
 * 描述:
 * 更改:
 */
public class OpenGLNative {
    static {
        System.loadLibrary("opengl-lib");
    }

    public static native void initGL();

    public static native void drawFrame();

    public static native void surfaceChanged(int width,int height);
}
