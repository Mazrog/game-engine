//
// Created by mazrog on 14/11/17.
//

#ifndef ENGINE_PROGRAM_HPP
#define ENGINE_PROGRAM_HPP

#include <GL/glew.h>


class ShaderProgram {
public:
    ShaderProgram() = default;
    ShaderProgram(const char *vertexPath, const char *fragmentPath);
    ~ShaderProgram();


    GLuint makeShader(std::string const& file, GLenum type);
    void linkProgram(GLuint& _progId, GLuint vertexShader, GLuint fragmentShader);
    GLuint getProgId() const;

    void useProgram();

private:
    GLuint _progId;
};


#endif //ENGINE_PROGRAM_HPP
