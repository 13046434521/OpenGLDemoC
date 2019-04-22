//
// Created by Administrator on 2019/4/14.
//
#include "utils.h"

GLuint CompileShader(GLenum shaderType, const char *shaderCode) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);
    GLint compileResult = GL_TRUE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
    if (compileResult == GL_FALSE) {
        char szLog[1024] = {0};
        GLsizei logLen = 0;
        glGetShaderInfoLog(shader, 1024, &logLen, szLog);
        __android_log_print(ANDROID_LOG_INFO, "JTL_C++", "Compile Shader:%s\n", szLog);
        glDeleteShader(shader);
        shader = 0;
    }
    return shader;
}

GLuint CreateProgram(GLuint vsShader, GLuint fsShader) {
    GLuint program = glCreateProgram();
    glAttachShader(program, vsShader);
    glAttachShader(program, fsShader);
    glLinkProgram(program);
    glDetachShader(program, vsShader);
    glDetachShader(program, fsShader);
    GLint mResult;
    glGetProgramiv(program, GL_LINK_STATUS, &mResult);
    if (mResult == GL_FALSE) {
        char szLog[1024] = {0};
        GLsizei logLen = 0;
        glGetProgramInfoLog(program, 1024, &logLen, szLog);

        __android_log_print(ANDROID_LOG_INFO, "JTL_C++", "Create Program:%s\n", szLog);

        glDeleteProgram(program);
    }
    return program;
}

unsigned char *DecodeBMP(unsigned char *bmpFileData, int &width, int &height) {
    if (0X4D42 == *((unsigned short *) bmpFileData)) {
        int pixelDataOffeset = *((int *) bmpFileData + 10);//像素数据起始位置
        width = *((int *) bmpFileData + 18);
        height = *((int *) bmpFileData + 22);
        unsigned char *pixelData = bmpFileData + pixelDataOffeset;
        //Bitmap 默认为BGR，这里把BGR => RGB
        for (int i = 0; i < width * height * 3; i += 3) {
            unsigned char temp = pixelData[i];
            pixelData[i] = pixelData[i + 2];
            pixelData[i + 2] = temp;
        }

        return pixelData;
    }

    return nullptr;
}
GLuint CreateTexture2D(unsigned char* pixelData,int width,int height,GLenum type){
    GLuint textureId;
    glGenTextures(0,&textureId);
    glBindTexture(GL_TEXTURE_2D,textureId);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D,0,type,width,height,0,type,GL_UNSIGNED_BYTE,pixelData);//从内存传到显卡上
    glBindTexture(GL_TEXTURE_2D,0);

    return textureId;
}
