package com.jtl.opengldemo.Surface;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;

import com.jtl.opengldemo.OpenGLNative;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * 作者:jtl
 * 日期:Created in 2019/4/13 16:48
 * 描述:
 * 更改:
 */
public class DemoGLSurface extends GLSurfaceView implements GLSurfaceView.Renderer {
    public DemoGLSurface(Context context) {
        this(context,null);
    }

    public DemoGLSurface(Context context, AttributeSet attrs) {
        super(context, attrs);

        init();
    }

    public void init(){
        setEGLContextClientVersion(2);
        setRenderer(this);
        setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        OpenGLNative.loadAssetContent(getContext().getAssets());
        OpenGLNative.initGL();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        OpenGLNative.surfaceChanged(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        OpenGLNative.drawFrame();
    }
}
