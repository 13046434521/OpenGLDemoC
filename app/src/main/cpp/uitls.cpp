//
// Created by Administrator on 2019/4/14.
//
#include "utils.h"

GLuint CompileShader(GLenum shaderType, const char *shaderCode){
    GLuint  shader = glCreateShader(shaderType);
    glShaderSource(shader,1,&shaderCode, NULL);
    glCompileShader(shader);
    GLint  compileResult=GL_TRUE;
    glGetShaderiv(shader,GL_COMPILE_STATUS,&compileResult);
    if (compileResult==GL_FALSE){
        char szLog[1024]={0};
        GLsizei  logLen=0;
        glGetShaderInfoLog(shader,1024,&logLen,szLog);
        __android_log_print(ANDROID_LOG_INFO,"JTL_C++","Compile Shader:%s\n",szLog);
        glDeleteShader(shader);
        shader=0;
    }
    return shader;
}

GLuint CreateProgram(GLuint vsShader,GLuint fsShader){
    GLuint program=glCreateProgram();
    glAttachShader(program,vsShader);
    glAttachShader(program,fsShader);
    glLinkProgram(program);
    glDetachShader(program,vsShader);
    glDetachShader(program,fsShader);
    GLint  mResult;
    glGetProgramiv(program,GL_LINK_STATUS,&mResult);
    if (mResult==GL_FALSE){
        char szLog[1024]={0};
        GLsizei logLen=0;
        glGetProgramInfoLog(program,1024,&logLen,szLog);

        __android_log_print(ANDROID_LOG_INFO,"JTL_C++","Create Program:%s\n",szLog);

        glDeleteProgram(program);
    }
    return program;
}