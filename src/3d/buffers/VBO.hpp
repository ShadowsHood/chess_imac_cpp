#pragma once
#include <glad/glad.h>

class VBO {
public:
  VBO() = default;
  ~VBO();
  void init();
  void bind() const;
  void unbind() const;
  void set_data(const void *data, GLsizeiptr size);
  void release();

private:
  GLuint m_id{0};
};