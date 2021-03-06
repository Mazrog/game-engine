//
// Created by mazrog on 19/11/17.
//

#ifndef ENGINE_UTILS_HPP
#define ENGINE_UTILS_HPP

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <locale>
#include <codecvt>
#include <jsoncpp/json/json.h>

#include "vector_utils.hpp"
#include "scenegraph/scenegraph.hpp"
#include "rendering/model.hpp"

void get_error(const char * t = "");

void glfw_error_callback(int error, const char * message);

namespace Loader {
    using wstring_converter = std::wstring_convert<std::codecvt_utf8<wchar_t >>;
    using JsonData = std::map<std::string, std::vector<std::wstring>>;

    std::wstring s_to_ws(wstring_converter & converter, std::string const& string);

    Json::Value read_json(const char * pathFile);

    JsonData parse_json_data(const char * pathFile);

    /* ------------------------------ OBJ LOADING ------------------------------ */
    struct Vertex {
        int vertex_index;
        int texture_index;
        int normal_index;

        Vertex(int v, int vt, int vn) : vertex_index(v), texture_index(vt), normal_index(vn) {}
        Vertex(glm::ivec3 const& vec) : vertex_index(vec.x), texture_index(vec.y), normal_index(vec.z) {}
    };

    /* Comparison operator */
    inline bool operator<(Vertex const& v1, Vertex const& v2) {
        if( v1.vertex_index < v2.vertex_index ) { return true; }
        else if( v1.vertex_index == v2.vertex_index ) {
            if( v1.texture_index < v2.texture_index ) { return true; }
            else if( v1.texture_index == v2.texture_index ) {
                return ( v1.normal_index < v2.normal_index );
            }
            return ( false );
        }

        return false;
    }

    /* Operator == overloading */
    inline bool operator==(Vertex const& v1, Vertex const& v2) {
        return (v1.vertex_index == v2.vertex_index) &&
                (v1.texture_index == v2.texture_index) && (v1.normal_index == v2.normal_index);
    }

    /* Operator != */
    inline bool operator!=(Vertex const& v1, Vertex const& v2) {
        return (v1.vertex_index != v2.vertex_index) ||
                (v1.texture_index != v2.texture_index) || (v1.normal_index != v2.normal_index);
    }

    void load_obj_element(const char * obj_file, Model & model);

    void load_obj_array(const char * obj_file, Model & model);
}

#endif //ENGINE_UTILS_HPP
