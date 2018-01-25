//
// Created by mazrog on 22/12/17.
//

#include <iostream>

#include "engine.hpp"
#include "gui/text.hpp"

FT_Library Text::ft;
VecFonts Text::fonts;
GLuint Text::texId;
GLint Text::texLoc;

void Text::init(GLuint progId) {
    if( !Text::ft ) {
        if (FT_Init_FreeType(&Text::ft)) {
            throw std::runtime_error("FT initialisation error");
        }

        glGenTextures(1, &texId); get_error("gen texture");
        glBindTexture(GL_TEXTURE_2D, texId); get_error("bind texture");

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        texLoc = glGetUniformLocation(progId, "glyph_texture");

        if ( Text::fonts.empty() ) {
            load_font("sample/fonts/hackFont.ttf");
        }
    }
}

Text::Text() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void *) 0);
}

Text::~Text() {}

int Text::load_font(const char *fontFile) {
    FT_Face face;
    if( FT_New_Face(Text::ft, fontFile, 0, &face) ) {
        throw std::runtime_error("Error loading font");
    }
    Text::fonts.push_back(face);
    return Text::fonts.size() - 1;
}

void Text::write(unsigned fontIndex, unsigned fontSize, glm::vec2 const& position, std::wstring const &text, glm::vec2 const& limits) {
    if( fontIndex >= Text::fonts.size() ) {
        throw std::runtime_error("Font index out of range");
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texId);
    glUniform1i(texLoc, 0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    FT_Face face = Text::fonts.at(fontIndex);

    FT_Select_Charmap(face, FT_ENCODING_UNICODE);

    FT_Set_Pixel_Sizes(face, 0, fontSize);

    Display& display = Engine::engine.get_display();
    float sx = 2.f / display.get_windowWidth();
    float sy = 2.f / display.get_windowHeight();

    float cur_x = position.x, cur_y = position.y;

    for(auto const& c : text) {

        if( FT_Load_Char(face, c, FT_LOAD_RENDER) ) {
            std::cerr << "Could not load character " << c << std::endl;
            continue;
        }

        if ( c == '\n' || cur_x >= limits.x) {
            cur_x = position.x;
            cur_y -= (fontSize + 3) * sy;
            continue;
        }

        FT_GlyphSlot g = face->glyph;

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
                     g->bitmap.width,
                     g->bitmap.rows, 0,
                     GL_RED, GL_UNSIGNED_BYTE,
                     g->bitmap.buffer);

        float x2 = cur_x + g->bitmap_left * sx;
        float y2 = cur_y + g->bitmap_top * sy;
        float w = g->bitmap.width * sx;
        float h = g->bitmap.rows * sy;

        GLfloat box[16] = {
                x2, y2,         0, 0,
                x2, y2 - h,     0, 1,
                x2 + w, y2,     1, 0,
                x2 + w, y2 - h, 1, 1
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_STREAM_DRAW);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        cur_x += (g->advance.x / 64.f) * sx;
        cur_y += (g->advance.y / 64.f) * sy;
    }
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}

Dimension Text::preview_text(unsigned fontIndex, unsigned fontSize, std::wstring const &text) {
    if( fontIndex >= Text::fonts.size() ) {
        throw std::runtime_error("Font index out of range");
    }

    FT_Face face = Text::fonts.at(fontIndex);
    FT_Set_Pixel_Sizes(face, 0, fontSize);

    Display& display = Engine::engine.get_display();
    float sx = 2.f / display.get_windowWidth();
    float sy = 2.f / display.get_windowHeight();

    float cur_x = 0, cur_y = 0;
    Dimension dimension;
    float max_width = 0.f;

    for(auto const& c : text) {
        if( FT_Load_Char(face, c, FT_LOAD_RENDER) ) {
            std::cerr << "Could not load character " << c << std::endl;
            continue;
        }

        if ( c == '\n' ) {
            dimension.x = ( cur_x > dimension.x ) ? cur_x : dimension.x;
            cur_x = 0;
            cur_y -= fontSize * sy;
            continue;
        }

        FT_GlyphSlot g = face->glyph;

        max_width = std::max(max_width, g->bitmap.rows * sy);

        cur_x += (g->advance.x / 64.f) * sx;
        cur_y += (g->advance.y / 64.f) * sy;
    }
    dimension.x = ( cur_x > dimension.x ) ? cur_x : dimension.x;
    dimension.y = 0.07;

    return dimension;
}