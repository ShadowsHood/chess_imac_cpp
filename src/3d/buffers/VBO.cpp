#include "VBO.hpp"

void VBO::init() { glGenBuffers(1, &m_id); }

VBO::~VBO() {
  release();
}

void VBO::bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_id); }

void VBO::unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

void VBO::set_data(const void *data, GLsizeiptr size) {
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VBO::release() {
  if (m_id != 0) {
    glDeleteBuffers(1, &m_id);
    m_id = 0;
  }
}