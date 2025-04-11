#pragma once
#include <glad/glad.h>

class VAO {
public:
  VAO();
  ~VAO();
  void init();
  void bind() const;
  void unbind() const;
  void release();

  GLuint get_id() const { return m_id; }

private:
  GLuint m_id;
};