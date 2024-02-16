#ifndef SHADER_H 
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>
class Shader // Thx to learnopengl :)
{
public:
    unsigned int shader_id;

    void use()
    {
        glUseProgram(shader_id);
    }

    void setBool(const std::string &name, bool value) const
    {         
        glUniform1i(glGetUniformLocation(shader_id, name.c_str()), (int)value); 
    }

    void setInt(const std::string &name, int value) const
    { 
        glUniform1i(glGetUniformLocation(shader_id, name.c_str()), value); 
    }

    void setFloat(const std::string &name, float value) const
    { 
        glUniform1f(glGetUniformLocation(shader_id, name.c_str()), value); 
    }
    void setVec2(const std::string &name, const glm::vec2 &value) const
    { 
        glUniform2fv(glGetUniformLocation(shader_id, name.c_str()), 1, &value[0]); 
    }

    void setVec3(const std::string &name, const glm::vec3 &value) const
    { 
        glUniform3fv(glGetUniformLocation(shader_id, name.c_str()), 1, &value[0]); 
    }

    void setVec4(const std::string &name, const glm::vec4 &value) const
    { 
        glUniform4fv(glGetUniformLocation(shader_id, name.c_str()), 1, &value[0]); 
    }

    void setMat2(const std::string &name, const glm::mat2 &mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(shader_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void setMat3(const std::string &name, const glm::mat3 &mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(shader_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(shader_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    

    Shader(const char* vertexPath = "/home/coa/Projects/Personal/OpenGLBetter/shaders/testshader.vert", const char* fragmentPath = "/home/coa/Projects/Personal/OpenGLBetter/shaders/testshader.frag")
    {
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();

        const char* vShaderCode = vertexCode.c_str();
        const char * fShaderCode = fragmentCode.c_str();
        // 2. compile shaders
        unsigned int vertex, fragment;
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
        // shader Program
        shader_id = glCreateProgram();
        glAttachShader(shader_id, vertex);
        glAttachShader(shader_id, fragment);
        glLinkProgram(shader_id);
        checkCompileErrors(shader_id, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }
private:
    void checkCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
};
#endif