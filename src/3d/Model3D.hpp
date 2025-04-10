#include "Mesh.hpp"
#include "Shader.hpp"
#include "buffers/EBO.hpp"
#include "buffers/VAO.hpp"
#include "buffers/VBO.hpp"
#include <string>

class Model3D {
public:
  Model3D() = default;

  // Chargement du mesh
  void load_mesh(const std::string &path, const std::string &name);

  // Configuration des buffers OpenGL
  void setup_buffers();

  // Rendu du modèle
  void render(glfeur::Shader &shader) const;

private:
  // Données du mesh
  glfeur::Mesh m_mesh;

  VAO m_vao;
  VBO m_vbo;
  EBO m_ebo;

  // Libération des ressources
  void release() {
    m_vao.release();
    m_vbo.release();
    m_ebo.release();
  }
};
