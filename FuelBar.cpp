#include "Tema3.h"
#include <Core/Engine.h>
#include <Component/SimpleScene.h>
#include "Transform3D.h"

// Se genereaza fuelbar
Mesh* Tema3::CreateFuelBar(std::string name, glm::vec4 leftBottomCorner, glm::vec3 color)
{
	float radius = 10;
	int ind = 0;
	// Se construieste un dreptunghi
	glm::vec4 corner = leftBottomCorner;
	std::vector<VertexFormat> vertices = {

		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec4(2, 0, 0, 0), color),
		VertexFormat(corner + glm::vec4(2, 1, 0, 0), color),
		VertexFormat(corner + glm::vec4(0, 1, 0, 0), color),
	};

	std::vector<unsigned short> indices = { 0,1,2,3 };

	Mesh* fuelBar = new Mesh(name);	
	fuelBar->SetDrawMode(GL_POLYGON);

	fuelBar->InitFromData(vertices, indices);
	return fuelBar;
}

void Tema3::ShowFuelBar() {
	glm::mat4 modelMatrix = glm::mat4(1);
	
	modelMatrix *= Transform3D::Translate(fuel_tx, fuel_ty, 0);
	
	// Se scaleaza in functie de fuel
	modelMatrix *= Transform3D::Scale( (fuel/max_fuel)*fuel_sx, fuel_sy,1.f);
	
	RenderSimpleMesh(meshes["fuelbar"], shaders["Tema3"], modelMatrix,glm::vec3(0,1,0), true,false, NULL);

	modelMatrix = glm::mat4(1);
	// Se aduga un dreptunghi alb in spate
	modelMatrix *= Transform3D::Translate(fuel_tx, fuel_ty, 0);
	
	modelMatrix *= Transform3D::Scale(fuel_sx, fuel_sy, 1.f);

	RenderSimpleMesh(meshes["fuelbar"], shaders["Tema3"], modelMatrix, glm::vec3(1, 1, 1), true,false, NULL);
}

// Se verifica daca mai exista combustibil
void Tema3::CheckFuel() {
	if (fuel < 0) {
		is_death = true;
	}
}

// Afisare scor
void Tema3::ShowScore() {
	glm::mat4 modelMatrix = glm::mat4(1);

	modelMatrix *= Transform3D::Translate(score_tx, score_ty, 0);

	// Se roteste la 180 grade pt ca scorul sa creasca spre stanga
	modelMatrix *= Transform3D::RotateOY(RADIANS(180));

	// Se scaleaza in functie de fuel
	modelMatrix *= Transform3D::Scale((score / score_max)*score_sx, score_sy, 1.f);

	RenderSimpleMesh(meshes["fuelbar"], shaders["Tema3"], modelMatrix, glm::vec3(0, 0, 1), true, false, NULL);

}