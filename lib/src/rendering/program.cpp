//
// Created by mazrog on 14/11/17.
//

#include <iostream>
#include <GL/glew.h>

#include "display.hpp"
#include "rendering/program.hpp"

char * filetobuf(const char *file) {
    FILE * fptr;
    long length;
    char * buf;

    if(!(fptr = fopen(file, "rb"))){
        return nullptr;
    }
    fseek(fptr, 0, SEEK_END);
    length = ftell(fptr);
    buf = new char[length+1];
    fseek(fptr, 0, SEEK_SET);
    fread(buf, length, 1, fptr);
    fclose(fptr);
    buf[length] = 0;

    return buf;
}

ShaderProgram::ShaderProgram(const char *vertexPath, const char *fragmentPath) {
    /* Shaders id */
    GLuint vertexShader, fragmentShader;

    /* Vertex Shader creation */
    vertexShader = makeShader(vertexPath, GL_VERTEX_SHADER);
    /* Fragment Shader creation */
    fragmentShader = makeShader(fragmentPath, GL_FRAGMENT_SHADER);
    /* Linking to the program */
    linkProgram(_progId, vertexShader, fragmentShader);
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(_progId); get_error();
}

GLuint ShaderProgram::makeShader(std::string const& file, GLenum type) {
    /* Variables */
    int isCompiled; // results of shader compilation
    int maxLength; //Length of the log
    char * shaderLog; // Shaders logs
    GLchar * shaderSource; // Shader source code buffers
    GLuint shader; // Shader id

    /* Reading source code */
    shaderSource = filetobuf(file.c_str()); get_error();

    /* Shader creation */
    shader = glCreateShader(type); get_error();
    glShaderSource(shader, 1, (const GLchar**)&shaderSource, nullptr); get_error();
    glCompileShader(shader); get_error();

    /* Compilation errors test */
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled); get_error();
    if(!isCompiled){
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength); get_error();
        shaderLog = new char[maxLength];
        glGetShaderInfoLog(shader, maxLength, &maxLength, shaderLog); get_error();
        std::cerr << "Compilation : " << type << " Shader Error => " << shaderLog << std::endl;
        delete shaderLog;
        return 0;
    }
    delete shaderSource;
    return shader;
}

void ShaderProgram::linkProgram(GLuint& _progId, GLuint vertexShader, GLuint fragmentShader) {
    /* Variables */
    int isLinked; // result of linking shaders to program
    int maxLength;

    /* Program logs */
    char * shaderProgLog;

    /* Program creation */
    _progId = glCreateProgram(); get_error();

    /* Shaders attachment */
    glAttachShader(_progId, vertexShader); get_error();
    glAttachShader(_progId, fragmentShader); get_error();
    glLinkProgram(_progId); get_error();

    /* Linking errors test */
    glGetProgramiv(_progId, GL_LINK_STATUS, &isLinked); get_error();
    if(!isLinked){
        glGetProgramiv(_progId, GL_INFO_LOG_LENGTH, &maxLength); get_error();
        shaderProgLog = new char[maxLength];
        glGetProgramInfoLog(_progId, maxLength, &maxLength, shaderProgLog);
        std::cerr << "Linking : Program Error => " << shaderProgLog << std::endl;
        delete shaderProgLog;
        return;
    }

    glUseProgram(_progId); get_error();

    /* Program is ok, we can detach, free and delete shaders */
    glDetachShader(_progId, vertexShader); get_error();
    glDetachShader(_progId, fragmentShader); get_error();
    glDeleteShader(vertexShader); get_error();
    glDeleteShader(fragmentShader); get_error();
}

GLuint ShaderProgram::getProgId() const {
    return _progId;
}

void ShaderProgram::useProgram() {
    glUseProgram(_progId); get_error();
}