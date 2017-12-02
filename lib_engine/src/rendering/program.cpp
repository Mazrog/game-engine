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
        throw std::runtime_error("Shader source file not found !");
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

int ShaderProgram::id_current_prog = 0;

void ShaderProgram::useProgram(GLuint const& progId) {
    if(static_cast<int>(progId) != ShaderProgram::id_current_prog) {
        glUseProgram(progId); get_error("using prog");
        ShaderProgram::id_current_prog = progId;
    }
}


ShaderProgram::ShaderProgram() : _progId(0) {}

ShaderProgram::ShaderProgram(const char *vertexPath, const char *fragmentPath) {
    /* Vertex Shader creation */
    makeShader(vertexPath, GL_VERTEX_SHADER);
    /* Fragment Shader creation */
    makeShader(fragmentPath, GL_FRAGMENT_SHADER);

    /* Linking to the program */
    linkProgram();
}

ShaderProgram::~ShaderProgram() {
    destroy();
}

void ShaderProgram::destroy() {
    if(_progId) {
        glDeleteProgram(_progId);
        get_error("s");
        _progId = 0;
    }
}

void ShaderProgram::makeShader(std::string const& file, GLenum type) {
    /* Variables */
    int isCompiled; // results of shader compilation
    int maxLength; //Length of the log
    char * shaderLog; // Shaders logs
    GLchar * shaderSource; // Shader source code buffers
    GLuint shader; // Shader id

    /* Reading source code */
    shaderSource = filetobuf(file.c_str());

    /* Shader creation */
    shader = glCreateShader(type); get_error("create shader");
    glShaderSource(shader, 1, (const GLchar**)&shaderSource, nullptr); get_error("source");
    glCompileShader(shader); get_error("compile");

    /* Compilation errors test */
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled); get_error("log - 1");
    if(!isCompiled){
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength); get_error("log - 2");
        shaderLog = new char[maxLength];
        glGetShaderInfoLog(shader, maxLength, &maxLength, shaderLog); get_error("log - 3");
        std::cerr << "Compilation : " << type << " Shader Error => " << shaderLog << std::endl;
        delete [] shaderLog;
        return;
    }
    delete [] shaderSource;
    shaders.push_back(shader);
}

void ShaderProgram::linkProgram() {
    /* Variables */
    int isLinked; // result of linking shaders to program
    int maxLength;

    /* Program logs */
    char * shaderProgLog;

    /* Program creation */
    _progId = glCreateProgram(); get_error("create prog");

    /* Shaders attachment */
    for(auto const& shader : shaders) {
        glAttachShader(_progId, shader); get_error("attach");
    }

    glLinkProgram(_progId); get_error("link prog");

    /* Linking errors test */
    glGetProgramiv(_progId, GL_LINK_STATUS, &isLinked); get_error("prog log - 1");
    if(!isLinked){
        glGetProgramiv(_progId, GL_INFO_LOG_LENGTH, &maxLength); get_error("prog log - 1");
        shaderProgLog = new char[maxLength];
        glGetProgramInfoLog(_progId, maxLength, &maxLength, shaderProgLog);
        std::cerr << "Linking : Program Error => " << shaderProgLog << std::endl;
        delete [] shaderProgLog;
        return;
    }

    useProgram(_progId);

    /* Program is ok, we can detach, free and delete shaders */
    for(auto const& shader : shaders) {
        glDetachShader(_progId, shader); get_error("detach shader");
        glDeleteShader(shader); get_error("delete shader");
    }
    shaders.clear();
}

GLuint ShaderProgram::getProgId() const {
    return _progId;
}

void ShaderProgram::useProgram() {
    useProgram(_progId);
}