#include "Mesh.hpp"
#include "Shader.hpp"
#include "buffers/EBO.hpp"
#include "buffers/VAO.hpp"
#include "buffers/VBO.hpp"
#include <string>

class Model3D {
public:
  Model3D() = default;

  VAO get_vao() const { return m_vao; }
  void load_mesh(const std::string &path, const std::string &name);
  void setup_buffers();
  void render(glfeur::Shader &shader) const;

private:
  glfeur::Mesh m_mesh;

  VAO m_vao;
  VBO m_vbo;
  EBO m_ebo;

  void release() {
    m_vao.release();
    m_vbo.release();
    m_ebo.release();
  }
};
