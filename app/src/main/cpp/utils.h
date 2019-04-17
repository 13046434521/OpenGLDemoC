//
// Created by Administrator on 2019/4/14.
//

#pragma once

#include "ggl.h"

unsigned char *loadFileContent(const char *path, int &filesSize);

GLuint CompileShader(GLenum shaderType, const char *shaderCode);

GLuint CreateProgram(GLuint vsShader,GLuint fsShader);