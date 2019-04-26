//
// Created by Administrator on 2019/4/14.
//
#include "sence.h"
#include "utils.h"

GLuint vbo;
GLuint  ebo;
GLuint program;
GLint positionLocation, modelMatrixLocation, viewMatrixLocation, projectMatrixLocation;
glm::mat4 modelMatrix, viewMatrix, projectMatrix;

void initGL() {
    glClearColor(0.1f, 0.5f, 0.9f, 1.0f);
    //VBO
    float data[] = {
            -0.2f, -0.2f, -0.6f, 1.0f,
            0.2f, -0.2f, -0.6f, 1.0f,
            0.0f, 0.2f, -0.6f, 1.0f,
    };

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, data, GL_STATIC_DRAW);//cpu内存块传到显卡上去
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //EBO
    unsigned short indexes[] = {0,1,2};
    float eboData[] = {
            -0.2f, -0.2f, -0.6f, 1.0f,
            0.2f, -0.2f, -0.6f, 1.0f,
            0.0f, 0.2f, -0.6f, 1.0f,
    };

    glGenBuffers(1,&ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short)*3,indexes,GL_STATIC_DRAW);//cpu内存块传到显卡上去
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);



    //加载Shader
    int len = 0;
    unsigned char *fileContent = loadFileContent("Res/vertex.glsl", len);
    GLuint vsShader = CompileShader(GL_VERTEX_SHADER, (char *) fileContent);
    delete[](fileContent);

    fileContent = loadFileContent("Res/fragment.glsl", len);
    GLuint fsShader = CompileShader(GL_FRAGMENT_SHADER, (char *) fileContent);
    delete[](fileContent);

    //放到GPU上了
    program = CreateProgram(vsShader, fsShader);
    glDeleteShader(vsShader);
    glDeleteShader(fsShader);

    positionLocation = glGetAttribLocation(program, "position");
    viewMatrixLocation = glGetUniformLocation(program, "viewMatrix");
    projectMatrixLocation = glGetUniformLocation(program, "projectionMatrix");
    modelMatrixLocation = glGetUniformLocation(program, "modelMatrix");
}

void surfaceChange(int width, int height) {
    glViewport(0, 0, width, height);

    projectMatrix = glm::perspective(45.0f, (float) width / (float) height, 0.1f, 1000.0f);
}

void drawFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program);

    //glUniformMatrix4fv(shader参数句柄,矩阵个数,是否转置,mat4矩阵的数据指针);
    //设置矩阵
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(projectMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectMatrix));
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
    //设置位置
    glEnableVertexAttribArray(positionLocation);
    //glVertexAttribPointer(位置，多少个元素,类型，是否单位化,每两个点之间的间隔，第一个点的起始位置)
    glVertexAttribPointer(positionLocation, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
    //glDrawArrays(形状，从第几个点开始画，连续画几个点)
//    glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);//VBO方式画图
    glDrawElements(GL_TRIANGLE_STRIP, 3,GL_UNSIGNED_SHORT,0);//EBO方式画图
    //解绑定
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    //程序解绑定
    glUseProgram(0);
}
