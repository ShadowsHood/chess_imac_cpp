#ifndef SHADER_DIR
#define SHADER_DIR "./shaders" // valeur de secours pour l'IDE
#endif

#include "Shader.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <array>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>


namespace glfeur {

void Shader::load_shader(const std::string &vertexPath,
                         const std::string &fragmentPath) {
  std::string vertexShaderPath = std::string(SHADER_DIR) + "/" + vertexPath;
  std::string fragmentShaderPath = std::string(SHADER_DIR) + "/" + fragmentPath;

  GLuint vertexShader = compile_shader(vertexShaderPath, GL_VERTEX_SHADER);
  GLuint fragmentShader =
      compile_shader(fragmentShaderPath, GL_FRAGMENT_SHADER);
  m_programID = glCreateProgram();
  glAttachShader(m_programID, vertexShader);
  glAttachShader(m_programID, fragmentShader);
  glLinkProgram(m_programID);

  GLint success{};
  glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
  if (!success) {
    std::array<char, 512> infoLog{};
    glGetProgramInfoLog(m_programID, 512, nullptr, infoLog.data());
    std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << infoLog.data() << '\n';
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

Shader::~Shader() { glDeleteProgram(m_programID); }

void Shader::use() const { glUseProgram(m_programID); }

GLuint Shader::getID() const { return m_programID; }

GLuint Shader::compile_shader(const std::string &path, GLenum type) {
  std::string sourceCode = read_file(path);
  if (sourceCode.empty()) {
    std::cerr << "Shader file is empty or could not be read: " << path << '\n';
  }
  const char *code = sourceCode.c_str();

  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &code, nullptr);
  glCompileShader(shader);

  GLint success{};
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    std::array<char, 512> infoLog{};
    glGetShaderInfoLog(shader, 512, nullptr, infoLog.data());
    std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n"
              << "Shader path: " << path << "\n"
              << infoLog.data() << '\n';
  }

  return shader;
}

std::string Shader::read_file(const std::string &path) {
  std::ifstream file(path, std::ios::in | std::ios::binary);
  if (!file) {
    std::cerr << "Failed to open shader file: " << path << '\n';
    return "";
  }
  std::ostringstream buffer;
  // std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

// - Uniforms
void Shader::set_uniform_matrix_4fv(const std::string &name,
                                    const glm::mat4 &value) {
  std::optional<GLint> location = get_uniform_location(name);
  if (location.has_value())
    glUniformMatrix4fv(location.value(), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::set_uniform_3fv(const std::string &name, const glm::vec3 &value) {
  std::optional<GLint> location = get_uniform_location(name);
  if (location.has_value())
    glUniform3fv(location.value(), 1, glm::value_ptr(value));
}

void Shader::set_uniform_1f(const std::string &name, const float value) {
  std::optional<GLint> location = get_uniform_location(name);
  if (location.has_value())
    glUniform1f(location.value(), value);
}

void Shader::set_uniform_1i(const std::string &name, const int value) {
  std::optional<GLint> location = get_uniform_location(name);
  if (location.has_value())
    glUniform1i(location.value(), value);
}

// - Uniform location
std::optional<GLint> Shader::get_uniform_location(const std::string &name) {
  if (m_uniform_cache.find(name) != m_uniform_cache.end()) {
    return m_uniform_cache[name];
  }
  GLint location = glGetUniformLocation(m_programID, name.c_str());
  if (location == -1) {
    // std::cerr << "Uniform " << name << " not found!" << std::endl;
    return std::nullopt;
  }
  m_uniform_cache[name] = location;
  return location;
}

} // namespace glfeur
