#ifndef OBJLOADER_H_
#define OBJLOADER_H_

// Pro C++ Tip: only include header of types/classes you use in your
// header file (.h), other headers you need should go in your source
// file (.cpp / .cc)

#include "vertex.h"

#include <string>
#include <vector>

class OBJLoader
{
    bool d_hasTexCoords;

    struct vec3
    {
        float x;
        float y;
        float z;
    };

    struct vec2
    {
        float u;
        float v;
    };

    std::vector<vec3> d_coordinates;
    std::vector<vec3> d_normals;
    std::vector<vec2> d_texCoords;

    /**
     * @brief The Vertex struct
     * Contains indices into the above
     * QVectors to be able to reconstruct
     * the model
     */
    struct Vertex_idx
    {
        size_t d_coord;
        size_t d_norm;
        size_t d_tex;
    };

    std::vector<Vertex_idx> d_vertices;

    typedef std::vector<std::string> StringList;

    public:

        /**
         * @brief OBJLoader
         * @param filename
         */
        explicit OBJLoader(std::string const &filename);

        /**
         * @brief vertex_data
         * @return interleaved vertex data, see vertex.h
         *
         * @note texCoord is only valid when hasTexCoords() returns
         *  true
         */
        std::vector<Vertex> vertex_data() const;

        unsigned numTriangles() const;

        bool hasTexCoords() const;

        /**
         * @brief unitize: scale mesh to fit in unitcube
         *
         * TODO: Implement this method yourself!
         */
        void unitize();

    private:

        void parseFile(std::string const &filename);
        void parseLine(std::string const &line);
        void parseVertex(StringList const &tokens);
        void parseNormal(StringList const &tokens);
        void parseTexCoord(StringList const &tokens);
        void parseFace(StringList const &tokens);

        StringList split(std::string const &str,
                             char splitChar,
                             bool keepEmpty = true);

};

#endif // OBJLOADER_H_
