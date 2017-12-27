//
// Created by mazrog on 22/12/17.
//

#ifndef ENGINE_TEXT_HPP
#define ENGINE_TEXT_HPP

#include <vector>
#include <string>

#include <GL/glew.h>
#include <glm/vec2.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "rendering/structs/vao.hpp"

using VecFonts = std::vector<FT_Face>;

class Text {
public:
    static FT_Library  ft;
    static void init(GLuint progId);

public:
    Text();
    ~Text();

    static int load_font(const char * fontFile);

    void write(unsigned fontIndex, unsigned fontSize, glm::vec2 const& position,
               std::wstring const& text, glm::vec2 const& limits = glm::vec2(1.f, -1.f));

    Dimension preview_text(unsigned fontIndex, unsigned fontSize, std::wstring const& text) const;

    void bindFont();


private:
    static VecFonts fonts;

    static GLuint   texId;
    static GLint    texLoc;

    GLuint      vao;
    GLuint      vbo;
};


#endif //ENGINE_TEXT_HPP
