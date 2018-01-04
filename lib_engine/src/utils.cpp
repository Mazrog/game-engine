//
// Created by mazrog on 19/11/17.
//

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <codecvt>
#include <locale>

#include "utils.hpp"

void get_error(const char * t){
    GLenum err;
    if((err = glGetError()) != GLEW_OK){
        std::cerr << t << std::endl;
        std::cerr << "Erreur OpenGL (" << err << ") : " << glewGetErrorString(err) << " -- " << gluErrorString(err) << std::endl;
    }
}

void glfw_error_callback(int error, const char * message) {
    std::cerr << "GLFW Error ( " << error << " ) : " <<  message << std::endl;
}

namespace Loader {

    std::wstring s_to_ws(wstring_converter & convert, std::string const& string) {
        std::wstring ws = convert.from_bytes(string.data());
        return ws;
    }

    Json::Value read_json(const char *pathFile) {
        std::ifstream file(pathFile, std::ios::binary);
        Json::Value root;

        if (file) { file >> root; }
        file.close();

        return root;
    }

    JsonData parse_json_data(const char * pathFile) {
        JsonData data;
        Json::Value root = read_json(pathFile);

        wstring_converter converter;

        auto keys = root.getMemberNames();

        for(auto const& key : keys) {
            if(!root[key].isArray()) {
                std::wstring ws(s_to_ws(converter, root[key].asString()));
                data[key].push_back(ws);
            }

        }

        return data;
    }

}

namespace Loader {
    using VertMap = std::map<Vertex, unsigned>;

    void processVertex3f(std::istringstream & sstr, vecf & vec) {
        float x, y, z;

        sstr >> x >> y >> z;
        vec.emplace_back(x, y, z);
    }

    void processVertex2f(std::istringstream & sstr, vec2f & vec) {
        float x, y;

        sstr >> x >> y;
        vec.emplace_back(x, y);
    }

    void parseVec(std::string & str, glm::ivec3 & vec) {
        std::string tmp;
        std::istringstream ssvert(str);

        for(int i = 0; i < 3; ++i) {
            tmp.clear();
            std::getline(ssvert, tmp, '/');
            vec[i] = std::atoi(tmp.c_str());
        }
    }

    void processVertLink(glm::ivec3 & vec, Model & model, VertMap & vmap) {
        Vertex cur(vec.x - 1, vec.y - 1, vec.z - 1);

        unsigned & val = vmap[cur];
        unsigned ind;

        if( !val ) {
            /* New Vertex */
            val = vmap.size();
        }
        ind = val;
        model.links.push_back(ind - 1);
    }

    void processFace(std::istringstream & sstr, Model & model, VertMap & vmap) {
        glm::ivec3  v1, v2, v3;
        std::string s1, s2, s3;
        sstr >> s1 >> s2 >> s3;

        parseVec(s1, v1);
        parseVec(s2, v2);
        parseVec(s3, v3);

        processVertLink(v1, model, vmap);
        processVertLink(v2, model, vmap);
        processVertLink(v3, model, vmap);
    }

    void parseMaterial(std::string const& filePath, std::istringstream & sstr, MtlLib & matlib) {
        /* Extract path */
        std::string prefix(filePath), mtlfile, path;
        auto it = prefix.end();
        while( *(--it) != '/' ) { prefix.erase(it); }
        sstr >> mtlfile;
        path = prefix + mtlfile;
        /* ------------ */

        /* Parsing mtl file */
        std::ifstream mtlfs(path);
        std::string line, word, tmp;
        Material * mat = nullptr;
        std::string mat_name;

        if(mtlfs) {

            do{
                line.clear();
                std::getline(mtlfs, line, '\n');

                if( !line.empty() ) {
                    std::istringstream linesstr(line);
                    linesstr >> word;

                    switch ( word[0] ) {
                        case 'K':
                            if ( mat ) {
                                switch (word[1]) {
                                    case 'a':
                                        break;
                                    case 'd':
                                        break;
                                    case 's':
                                        break;
                                    default:;
                                }
                            } else { throw std::runtime_error(std::string("Mtl file ill formed : ") + path); }
                            break;
                        case 'm':
                            if( mat ) {
                                tmp.assign(word);
                                tmp.erase(tmp.end() - 1);
                                if (tmp == "map_K") {
                                    switch (word[word.size() - 1]) {
                                        case 'a':
                                            break;
                                        case 'd':
                                            linesstr >> mat->map_Kd;
                                            mat->map_Kd = prefix + mat->map_Kd;
                                            break;
                                        case 's':
                                            break;
                                        default:;
                                    }
                                }
                            } else { throw std::runtime_error(std::string("Mtl file ill formed : ") + path); }
                            break;
                        case 'n':
                            if ( word == "newmtl" ) {
                                if(mat) {
                                    matlib[mat_name] = mat;
                                }

                                mat = new Material();
                                linesstr >> mat_name;
                            }
                            break;

                        default:;
                    }
                }

            } while( !mtlfs.eof() );

            if(mat) {
                matlib[mat_name] = mat;
            }
        }
    }

    void load_obj_element(const char * obj_file, Model & model) {
        std::ifstream file(obj_file);
        std::string line, word;

        if(file) {
            vecf vertices;
            vecf normals;
            vec2f uvs;
            VertMap vmap;
            MtlLib mat;

            unsigned count  = 0,
                    first   = 0;

            do {
                line.clear();
                std::getline(file, line, '\n');

                if(!line.empty()) {
                    std::istringstream sstr(line);
                    sstr >> word;

                    switch (line[0]) {
                        case 'm':
                            if ( word == "mtllib") {
                                parseMaterial(obj_file, sstr, mat);
                            }
                            break;
                        case 'u':
                            if ( word == "usemtl") {
                                sstr >> word;
                                mat.at(word)->vert_infos.emplace_back(first, count);

                                first += count;
                                count = 0;
                            }
                            break;
                        case 'v':
                            count++;
                            switch (line[1]) {
                                case 't':
                                    processVertex2f(sstr, uvs);
                                    break;
                                case 'n':
                                     processVertex3f(sstr, normals);
                                    break;
                                default:
                                    processVertex3f(sstr, vertices);
                                    break;
                            }
                            break;
                        case 'f':
                            processFace(sstr, model, vmap);
                            break;
                        default:;
                    }
                }
            } while(!file.eof());

            /* Total number of vertices */
            int size = *std::max_element(model.links.begin(), model.links.end()) + 1;

            /* Allocation of the vectors */
            model.vertices.resize(size);
            model.uvs.resize(size);
            model.normals.resize(size);

            /* Filling up with the map information */
            for(auto const& pair : vmap) {
                unsigned indice = pair.second - 1;
                model.vertices[indice] = vertices.at(pair.first.vertex_index);
                if(pair.first.texture_index >= 0) {
                    model.uvs[indice] = uvs.at(pair.first.texture_index);
                }
                if(pair.first.normal_index >= 0) {
                    model.normals[indice] = normals.at(pair.first.normal_index);
                }
            }

            model.mtlLib = std::move(mat);

        } else {
            std::cerr << "Error : Could not open OBJ file " << obj_file << std::endl;
        }
    }

    void processFaceArray(std::istringstream & sstr, Model & model,
                          vecf const& vertices, vec2f const& uvs, vecf const& normals) {
        glm::ivec3  verts[3];
        std::string split[3];
        sstr >> split[0] >> split[1] >> split[2];

        for(unsigned i = 0; i < 3; ++i) {
            parseVec(split[i], verts[i]);

            model.vertices.emplace_back(vertices[verts[i].x - 1]);
            if(!uvs.empty()) {
                model.uvs.emplace_back(uvs[verts[i].y - 1]);
            }
            if(!normals.empty()) {
                model.normals.emplace_back(normals[verts[i].z - 1]);
            }
        }
    }

    void load_obj_array(const char * obj_file, Model & model) {
        std::ifstream file(obj_file);
        std::string line, word, cur_mat_name;

        if(file) {

            vecf vertices;
            vecf normals;
            vec2f uvs;
            MtlLib mat;

            unsigned count  = 0,
                    first   = 0;

            do {
                line.clear();
                std::getline(file, line, '\n');

                if(!line.empty()) {
                    std::istringstream sstr(line);
                    sstr >> word;

                    switch (line[0]) {
                        case 'm':
                            if ( word == "mtllib") {
                                parseMaterial(obj_file, sstr, mat);
                            }
                            break;
                        case 'u':
                            if ( word == "usemtl") {
                                if( count && !cur_mat_name.empty() ) {
                                    mat.at(cur_mat_name)->vert_infos.emplace_back(first, count);
                                }
                                sstr >> cur_mat_name;

                                first += count;
                                count = 0;
                            }
                            break;
                        case 'v':
                            switch (line[1]) {
                                case 't':
                                    processVertex2f(sstr, uvs);
                                    break;
                                case 'n':
                                    processVertex3f(sstr, normals);
                                    break;
                                default:
                                    processVertex3f(sstr, vertices);
                                    break;
                            }
                            break;
                        case 'f':
                            count += 3;
                            processFaceArray(sstr, model, vertices, uvs, normals);
                            break;
                        default:;
                    }
                }
            } while(!file.eof());

            if( count && !cur_mat_name.empty() ) {
                mat.at(cur_mat_name)->vert_infos.emplace_back(first, count);
            }
            model.mtlLib = std::move(mat);

        } else {
            std::cerr << "Error : Could not open OBJ file " << obj_file << std::endl;
        }
    }
}