//
// Created by mazrog on 14/11/17.
//

#ifndef ENGINE_PROGRAM_HPP
#define ENGINE_PROGRAM_HPP

#include <GL/glew.h>
#include <string>
#include <vector>

class ShaderProgram {
public:
    static int id_current_prog;
    static void useProgram(GLuint const& progId);

public:
    ShaderProgram();
    ShaderProgram(const char *vertexPath, const char *fragmentPath);

    ~ShaderProgram();

    /* ###################################################################################### */
    /* Deleting the copy operators */
    ShaderProgram(ShaderProgram const&) = delete;

    ShaderProgram& operator=(ShaderProgram const&) = delete;

    /* Move constructors + move operators */
    ShaderProgram(ShaderProgram && program) : _progId(std::move(program.getProgId())) { program.setProgId(0); }
    ShaderProgram& operator=(ShaderProgram && program) {
        _progId = std::move(program.getProgId());
        program.setProgId(0);
        return *this;
    }

    /* ###################################################################################### */

    void makeShader(std::string const& file, GLenum type);
    void linkProgram();

    void useProgram();


    /* Getters and Setters */
    GLuint getProgId() const;
    void setProgId(GLuint val) { _progId = val; }

private:
    GLuint _progId;

    std::vector<GLuint>     shaders;
};


#endif //ENGINE_PROGRAM_HPP
