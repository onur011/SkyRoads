#include "Tema3.h"
#include <Core/Engine.h>
#include <Component/SimpleScene.h>
#include "Transform3D.h"

// Se genereaza pom
Mesh* Tema3::CreateChristmasTree(std::string name, glm::vec3 leftBottomCorner, glm::vec3 color)
{
	// Se construieste o piramida
	glm::vec3 corner = leftBottomCorner;
	std::vector<VertexFormat> vertices = {

		VertexFormat(corner, color, glm::vec3(0,1,-1), glm::vec2(0,1)),
		VertexFormat(corner, color, glm::vec3(-1,1,0),glm::vec2(1,1)),
		VertexFormat(corner + glm::vec3(1, 0, 0), color, glm::vec3(0,1,-1), glm::vec2(1,1)),
		VertexFormat(corner + glm::vec3(1, 0, 0), color, glm::vec3(1,1,0),glm::vec2(0,1)),
		VertexFormat(corner + glm::vec3(1, 0, 1), color, glm::vec3(1,1,0),glm::vec2(1,1)),
		VertexFormat(corner + glm::vec3(1, 0, 1), color, glm::vec3(0,1,1),glm::vec2(0,1)),
		VertexFormat(corner + glm::vec3(0, 0, 1), color, glm::vec3(0,1,1),glm::vec2(1,1)),
		VertexFormat(corner + glm::vec3(0, 0, 1), color, glm::vec3(-1,1,0),glm::vec2(0,1)),
		VertexFormat(corner + glm::vec3(0.5f, 1, 0.5f), color, glm::vec3(0,1,1),glm::vec2(0.5,0)),
		VertexFormat(corner + glm::vec3(0.5f, 1, 0.5f), color, glm::vec3(1,1,0),glm::vec2(0.5,0)),
		VertexFormat(corner + glm::vec3(0.5f, 1, 0.5f), color, glm::vec3(0,1,-1), glm::vec2(0.5,0)),
		VertexFormat(corner + glm::vec3(0.5f, 1, 0.5f), color, glm::vec3(-1,1,0),glm::vec2(0.5,0)),
	};

	std::vector<unsigned short> indices = { 
		10,2,0,
		9,4,3,
		8,6,5,
		11,1,7};

	Mesh* tree = new Mesh(name);	

	tree->InitFromData(vertices, indices);
	return tree;
}
