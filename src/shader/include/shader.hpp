#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// This file will be generated automatically when you run the CMake configuration step.
// It creates a namespace called `radiance`.
// You can modify the source template at `configured_files/config.hpp.in`.
#include <configured_files/config.hpp> // use this to get meta information about the build (version, etc)

namespace radiance::shader
{

    class Shader
    {
    public:
        unsigned int _ID;
        uint32_t _projection_matrix_location;
        uint32_t _model_matrix_location;
        uint32_t _view_matrix_location;
        uint32_t _model_matrix_update_location;

        // constructor generates the shader on the fly
        // ------------------------------------------------------------------------
        Shader(const char* vertexPath = (radiance::cmake::project_dir + std::string(R"(\resources\shader\shader1.vs)")).c_str(),
            const char* fragmentPath = (radiance::cmake::project_dir + std::string(R"(\resources\shader\shader1.fs)")).c_str() )
        {
            // 1. retrieve the vertex/fragment source code from filePath
            std::string vertexCode;
            std::string fragmentCode;
            std::ifstream vShaderFile;
            std::ifstream fShaderFile;
            // ensure ifstream objects can throw exceptions:
            vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            try
            {
                // open files
                vShaderFile.open(vertexPath);
                fShaderFile.open(fragmentPath);
                std::stringstream vShaderStream, fShaderStream;
                // read file's buffer contents into streams
                vShaderStream << vShaderFile.rdbuf();
                fShaderStream << fShaderFile.rdbuf();
                // close file handlers
                vShaderFile.close();
                fShaderFile.close();
                // convert stream into string
                vertexCode = vShaderStream.str();
                fragmentCode = fShaderStream.str();
            }
            catch (std::ifstream::failure& e)
            {
                std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
            }
            const char* vShaderCode = vertexCode.c_str();
            const char* fShaderCode = fragmentCode.c_str();
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
            _ID = glCreateProgram();
            glAttachShader(_ID, vertex);
            glAttachShader(_ID, fragment);
            glLinkProgram(_ID);
            checkCompileErrors(_ID, "PROGRAM");

            // get location of shader's transform uniforms
            _model_matrix_location = glGetUniformLocation(_ID, "modelMatrix");
            _view_matrix_location = glGetUniformLocation(_ID, "viewMatrix");
            _projection_matrix_location = glGetUniformLocation(_ID, "projectionMatrix");
            _model_matrix_update_location = glGetUniformLocation(_ID, "modelMatrixUpdate");

            // delete the shaders as they're linked into our program now and no longer necessary
            glDeleteShader(vertex);
            glDeleteShader(fragment);
        }
        // activate the shader
        // ------------------------------------------------------------------------
        void use()
        {
            glUseProgram(_ID);
        }
        // utility uniform functions
        // ------------------------------------------------------------------------
        void setBool(const std::string& name, bool value) const
        {
            glUniform1i(glGetUniformLocation(_ID, name.c_str()), (int)value);
        }
        // ------------------------------------------------------------------------
        void setInt(const std::string& name, int value) const
        {
            glUniform1i(glGetUniformLocation(_ID, name.c_str()), value);
        }
        // ------------------------------------------------------------------------
        void setFloat(const std::string& name, float value) const
        {
            glUniform1f(glGetUniformLocation(_ID, name.c_str()), value);
        }

        // might be a good place for a C++20 Mat4 concept...
        void setMat4(const std::string& name, float* value) const
        {
            uint32_t location = glGetUniformLocation(_ID, name.c_str());
            glUniformMatrix4fv( location, 1, GL_FALSE, value );
        }

        void setModelMatrix(float* value) const
        {
            glUniformMatrix4fv(_model_matrix_location, 1, GL_FALSE, value);
        }

        void setViewMatrix(float* value) const
        {
            glUniformMatrix4fv(_view_matrix_location, 1, GL_FALSE, value);
        }

        void setProjectionMatrix(float* value) const
        {
            glUniformMatrix4fv(_projection_matrix_location, 1, GL_FALSE, value);
        }

        void setModelMatrixUpdate(float* value) const
        {
            glUniformMatrix4fv(_model_matrix_update_location, 1, GL_FALSE, value);
        }

    private:
        // utility function for checking shader compilation/linking errors.
        // ------------------------------------------------------------------------
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

} // namespace radiance::shader
