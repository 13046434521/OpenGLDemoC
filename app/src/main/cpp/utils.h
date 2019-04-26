//
// Created by Administrator on 2019/4/14.
//

#pragma once

#include "ggl.h"

unsigned char *loadFileContent(const char *path, int &filesSize);

GLuint CompileShader(GLenum shaderType, const char *shaderCode);

GLuint CreateProgram(GLuint vsShader, GLuint fsShader);

unsigned char *DecodeBMP(unsigned char *bmpFileData, int &width, int &height);

GLuint CreateTexture2D(unsigned char *pixelData, int width, int height, GLenum type);
