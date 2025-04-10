#include "Model3D.hpp"
#include <iostream>

void Model3D::load_mesh(const std::string &path, const std::string &name) {
  m_mesh.load(path, name);
}

void Model3D::setup_buffers() {
  // Lier et configurer les buffers pour les pieces (VBO, EBO)
  m_vbo.init();
  m_vbo.bind();
  m_vbo.set_data(m_mesh.get_vertices().data(),
                 m_mesh.get_vertices().size() * sizeof(glfeur::Vertex));
  m_vbo.unbind();

  m_ebo.init();
  m_ebo.bind();
  m_ebo.set_data(m_mesh.get_indices().data(),
                 m_mesh.get_indices().size() * sizeof(uint32_t));
  m_ebo.unbind();

  // Lier les matrices d'instance aux attributs de vertex
  m_vao.init();
  m_vao.bind();
  m_vbo.bind();
  m_ebo.bind();

  // Attributs de position, normal et texture pour chaque pièce
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glfeur::Vertex),
                        (const GLvoid *)offsetof(glfeur::Vertex, m_position));

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glfeur::Vertex),
                        (const GLvoid *)offsetof(glfeur::Vertex, m_normal));

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glfeur::Vertex),
                        (const GLvoid *)offsetof(glfeur::Vertex, m_tex_coord));

  m_vao.unbind();
}

// render mon mesh
void Model3D::render(glfeur::Shader &shader) const {
  m_vao.bind();

  for (const glfeur::Submesh &submesh : m_mesh.get_submeshes()) {
    glfeur::Material defaultMat; // une version par défaut si besoin
    const glfeur::Material *materialPtr = nullptr;
    if (submesh.m_material_id >= 0 &&
        submesh.m_material_id <
            static_cast<int>(m_mesh.get_materials().size())) {
      materialPtr = &m_mesh.get_materials()[submesh.m_material_id];
    } else {
      materialPtr = &defaultMat;
    }
    const glfeur::Material &material = *materialPtr;

    // Configurer les uniformes pour les propriétés du matériau
    shader.set_uniform_3fv("Kd", material.m_Kd);
    shader.set_uniform_3fv("Ka", material.m_Ka);
    shader.set_uniform_3fv("Ks", material.m_Ks);
    shader.set_uniform_1f("Ns", material.m_Ns);

    if (material.m_hasMapKd) {
      shader.set_uniform_1i("map_Kd", material.m_mapKd.getID());
      material.m_mapKd.bind(material.m_mapKd.getID());
      shader.set_uniform_1i("useTexture", true);
    } else {
      shader.set_uniform_1i("useTexture", false);
    }

    // On dessine !
    glDrawElements(GL_TRIANGLES, submesh.m_index_count, GL_UNSIGNED_INT,
                   (const GLvoid *)(submesh.m_index_offset * sizeof(uint32_t)));

    if (material.m_hasMapKd)
      material.m_mapKd.unbind();
  }

  m_vao.unbind();
}