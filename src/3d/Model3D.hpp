#include "Mesh.hpp"
#include "Shader.hpp"
#include "buffers/EBO.hpp"
#include "buffers/VAO.hpp"
#include "buffers/VBO.hpp"
#include <string>

class Model3D {
public:
  Model3D() = default;
  // ~Model3D() { release(); }

  // Model3D(const Model3D &other) = delete;
  // Model3D &operator=(const Model3D &other) = delete;

  // Model3D(Model3D &&other) noexcept
  //     : m_vao(std::move(other.m_vao)), m_vbo(std::move(other.m_vbo)),
  //       m_ebo(std::move(other.m_ebo)), m_mesh(std::move(other.m_mesh)) {
  //   // Réinitialiser l'objet source
  //   other.m_vao = VAO();
  //   other.m_vbo = VBO();
  //   other.m_ebo = EBO();
  // }

  // Model3D &operator=(Model3D &&other) noexcept {
  //   if (this != &other) {
  //     release();
  //     // Déplacer les ressources
  //     m_vao = std::move(other.m_vao);
  //     m_vbo = std::move(other.m_vbo);
  //     m_ebo = std::move(other.m_ebo);
  //     m_mesh = std::move(other.m_mesh);

  //     // Réinitialiser l'autre objet
  //     other.m_vao = VAO();
  //     other.m_vbo = VBO();
  //     other.m_ebo = EBO();
  //   }
  //   return *this;
  // }

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
