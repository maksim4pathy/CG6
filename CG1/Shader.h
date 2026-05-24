#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "glm.hpp"
#include "glm/gtc/type_ptr.hpp"

class Shader {
public:
    GLuint ID;

    Shader(const char* vertexPath, const char* fragmentPath) {
        std::string vertexCode, fragmentCode;
        std::ifstream vFile(vertexPath), fFile(fragmentPath);
        std::stringstream vStream, fStream;
        vStream << vFile.rdbuf();
        fStream << fFile.rdbuf();
        vFile.close(); fFile.close();

        vertexCode = vStream.str();
        fragmentCode = fStream.str();

        const char* vCode = vertexCode.c_str();
        const char* fCode = fragmentCode.c_str();

        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &vCode, NULL);
        glCompileShader(vs);

        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &fCode, NULL);
        glCompileShader(fs);

        ID = glCreateProgram();
        glAttachShader(ID, vs);
        glAttachShader(ID, fs);
        glLinkProgram(ID);

        glDeleteShader(vs);
        glDeleteShader(fs);
    }

    void use() { glUseProgram(ID); }

    void setMat4(const char* name, const glm::mat4& mat) {
        glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(mat));
    }

    void setMat3(const char* name, const glm::mat3& mat) {
        glUniformMatrix3fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(mat));
    }

    void setVec3(const char* name, float x, float y, float z) {
        glUniform3f(glGetUniformLocation(ID, name), x, y, z);
    }

    void setFloat(const char* name, float value) {
        glUniform1f(glGetUniformLocation(ID, name), value);
    }
};

#endif
