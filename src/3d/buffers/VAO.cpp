#include "VAO.hpp"

VAO::VAO() : m_id(0) {}

VAO::~VAO() { release(); }

void VAO::init() { glGenVertexArrays(1, &m_id); }

void VAO::bind() const { glBindVertexArray(m_id); }

void VAO::unbind() const { glBindVertexArray(0); }

void VAO::release() {
  if (m_id != 0) {
    glDeleteVertexArrays(1, &m_id);
    m_id = 0;
  }
}