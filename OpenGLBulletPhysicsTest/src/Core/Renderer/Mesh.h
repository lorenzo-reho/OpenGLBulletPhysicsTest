#ifndef MESH_H
#define MESH_H

#include "../Common.h"
#include "../GL.h"
#include "Shader.h"
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textCoord;
};

struct Texture {
	unsigned int ID;
	string type;
	string path;
};

class Mesh {
public:
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures) {
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;
		SetupMesh();
	}

	void Draw(Shader *shader) {
		
		// sistemare le texture (diffuse e specular)
		unordered_map<string, int> mp;

		shader->SetFloat("material.shininess", 64.0);
		for (int i = 0; i < textures.size(); i++) {
			string name = textures[i].type;
			mp[name]++;

			glActiveTexture(GL_TEXTURE0 + i);
			shader->SetInt(("material."+name+to_string(mp[name])).c_str(), i);
			glBindTexture(GL_TEXTURE_2D, textures[i].ID);
		}


		glBindVertexArray(_VAO);

		glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

	}

private:
	unsigned int _VAO, _VBO, _EBO;

	void SetupMesh() {
		glGenVertexArrays(1, &_VAO);
		glGenBuffers(1, &_VBO);
		glGenBuffers(1, &_EBO);

		glBindVertexArray(_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, _VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textCoord));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);
	}

};

#endif