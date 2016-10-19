#ifndef ASTEROIDS_SHADER_HPP
#define ASTEROIDS_SHADER_HPP

#include <string>
#include <glbinding/gl/types.h>

namespace rendering {
  class Shader {
    gl::GLuint program;
  public:
    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    explicit Shader(const std::string& vertexSource,
                    const std::string& fragmentSource);
    ~Shader();

    void activate() const;
    void deactivate() const;

    gl::GLint getUniformLocation(const char* name) const;
  };
}


#endif //ASTEROIDS_SHADER_HPP
