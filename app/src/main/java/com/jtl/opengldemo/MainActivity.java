package com.jtl.opengldemo;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.jtl.opengldemo.Surface.DemoGLSurface;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
//        setContentView(R.layout.activity_main);
        DemoGLSurface demoGLSurface=new DemoGLSurface(this);
        setContentView(demoGLSurface);
    }
}
