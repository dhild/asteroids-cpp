#include <glbinding/gl/gl.h>
#include <vector>
#include "Shader.hpp"

namespace {
  class GLShader {
  public:
    gl::GLuint shader;

    GLShader(gl::GLenum type, const std::string& source) : shader(0) {
      shader = gl::glCreateShader(type);
      const char* c_src = source.c_str();
      gl::glShaderSource(shader, 1, &c_src, nullptr);
      gl::glCompileShader(shader);

      gl::GLint status;
      gl::glGetShaderiv(shader, gl::GL_COMPILE_STATUS, &status);
      if ((gl::GLboolean) status != gl::GL_TRUE) {
        gl::GLint length;
        gl::glGetShaderiv(shader, gl::GL_INFO_LOG_LENGTH, &length);

        std::vector<gl::GLchar> log;
        log.reserve((std::size_t) length);
        gl::glGetShaderInfoLog(shader, length, nullptr, log.data());
        std::string errorMsg("Failed to compile shader: ");
        errorMsg += log.data();
        gl::glDeleteShader(shader);
        throw std::runtime_error(errorMsg);
      }
    }

    ~GLShader() {
      if (shader) {
        gl::glDeleteShader(shader);
      }
    }
  };
}

rendering::Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource)
        : program(0) {
  GLShader vertexShader(gl::GL_VERTEX_SHADER, vertexSource);
  GLShader fragmentShader(gl::GL_FRAGMENT_SHADER, fragmentSource);

  program = gl::glCreateProgram();
  gl::glAttachShader(program, vertexShader.shader);
  gl::glAttachShader(program, fragmentShader.shader);

  gl::glLinkProgram(program);

  gl::GLint status;
  gl::glGetProgramiv(program, gl::GL_LINK_STATUS, &status);
  if ((gl::GLboolean)status != gl::GL_TRUE) {
    gl::GLint length;
    gl::glGetProgramiv(program, gl::GL_INFO_LOG_LENGTH, &length);
    std::vector<gl::GLchar> log;
    log.reserve((std::size_t) length);
    gl::glGetProgramInfoLog(program, length, nullptr, log.data());
    std::string errorMsg("Failed to link shader: ");
    errorMsg += log.data();
    gl::glDeleteProgram(program);
    throw std::runtime_error(errorMsg);
  }
}

rendering::Shader::~Shader() {
  if (program) {
    gl::glDeleteShader(program);
  }
}

void rendering::Shader::activate() const {
  gl::glUseProgram(program);
}

void rendering::Shader::deactivate() const {
  gl::glUseProgram(0);
}

gl::GLint rendering::Shader::getUniformLocation(const char* name) const {
  return gl::glGetUniformLocation(program, name);
}
