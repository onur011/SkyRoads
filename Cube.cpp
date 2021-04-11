#include "Tema3.h"
#include <Core/Engine.h>
#include <Component/SimpleScene.h>
#include "Transform3D.h"

// Se genereaza cub
Mesh* Tema3::CreateCube(std::string name, glm::vec3 leftBottomCorner, glm::vec3 color)
{
	// Se construieste un cub
	glm::vec3 corner = leftBottomCorner;
	std::vector<VertexFormat> vertices = {

		VertexFormat(corner, color, glm::vec3(0,0,-1), glm::vec2(1,1)),
		VertexFormat(corner, color, glm::vec3(0,-1,0), glm::vec2(1,1)),
		VertexFormat(corner, color, glm::vec3(-1,0,0), glm::vec2(0,1)),
		VertexFormat(corner + glm::vec3(1,0,0), color, glm::vec3(0,0,-1), glm::vec2(0,1)),
		VertexFormat(corner + glm::vec3(1,0,0), color, glm::vec3(0,-1,0), glm::vec2(0,1)),
		VertexFormat(corner + glm::vec3(1,0,0), color, glm::vec3(1,0,0), glm::vec2(1,1)),
		VertexFormat(corner + glm::vec3(1,0,1), color, glm::vec3(0,0,1), glm::vec2(1,1)),
		VertexFormat(corner + glm::vec3(1,0,1), color, glm::vec3(1,0,0), glm::vec2(0,1)),
		VertexFormat(corner + glm::vec3(1,0,1), color, glm::vec3(0,-1,0), glm::vec2(0,0)),
		VertexFormat(corner + glm::vec3(0,0,1), color, glm::vec3(0,-1,0), glm::vec2(0,1)),
		VertexFormat(corner + glm::vec3(0,0,1), color, glm::vec3(-1,0,0), glm::vec2(1,1)),
		VertexFormat(corner + glm::vec3(0,0,1), color, glm::vec3(0,0,1), glm::vec2(1,0)),
		VertexFormat(corner + glm::vec3(0,1,1), color, glm::vec3(0,0,1), glm::vec2(0,0)),
		VertexFormat(corner + glm::vec3(0,1,1), color, glm::vec3(-1,0,0), glm::vec2(1,0)),
		VertexFormat(corner + glm::vec3(0,1,1), color, glm::vec3(0,1,0), glm::vec2(0,1)),
		VertexFormat(corner + glm::vec3(1,1,1), color, glm::vec3(0,0,1), glm::vec2(1,0)),
		VertexFormat(corner + glm::vec3(1,1,1), color, glm::vec3(1,0,0), glm::vec2(0,0)),
		VertexFormat(corner + glm::vec3(1,1,1), color, glm::vec3(0,1,0), glm::vec2(1,1)),
		VertexFormat(corner + glm::vec3(1,1,0), color, glm::vec3(1,0,0), glm::vec2(1,0)),
		VertexFormat(corner + glm::vec3(1,1,0), color, glm::vec3(0,0,-1), glm::vec2(0,0)),
		VertexFormat(corner + glm::vec3(1,1,0), color, glm::vec3(0,1,0), glm::vec2(1,0)),
		VertexFormat(corner + glm::vec3(0,1,0), color, glm::vec3(-1,0,0), glm::vec2(0,0)),
		VertexFormat(corner + glm::vec3(0,1,0), color, glm::vec3(0,0,-1), glm::vec2(1,0)),
		VertexFormat(corner + glm::vec3(0,1,0), color, glm::vec3(0,1,0), glm::vec2(0,0))
	};

	std::vector<unsigned short> indices = { 
		0, 19, 3,
		0, 22, 19,
		5, 16, 7,
		5, 18, 16,
		6, 15, 12,
		6, 12, 10,
		10, 13, 21,
		10, 21, 2,
		23, 17, 20,
		23, 14, 17,
		1, 4, 8,
		1, 8, 11
	};

	Mesh* cube = new Mesh(name);	

	cube->InitFromData(vertices, indices);
	return cube;
}

// Obiecte initiale
void Tema3::InitialObjects() {
	// Se adauga un obiect pe partea dreapta
	Objects aux;
	aux.pos = 0;
	aux.last = true;
	// Tipul 0 - pom de craciun
	// Tipul 1 - felinar
	aux.type = Random(0, 1);

	if (aux.type == 0) {
		aux.tx1 = -1;
		aux.ty1 = 0;
		aux.tz1 = 5;
		aux.sx1 = 1;
		aux.sy1 = 2;
		aux.sz1 = 1;
	} else {
		aux.tx1 = -1;
		aux.ty1 = 0;
		aux.tz1 = 5;
		aux.sx1 = 0.5f;
		aux.sy1 = 2;
		aux.sz1 = 0.5f;

		aux.tx2 = -1;
		aux.ty2 = 2;
		aux.tz2 = 5;
		aux.sx2 = 1;
		aux.sy2 = 0.5f;
		aux.sz2 = 0.5f;
	}

	objects.push_back(aux);
	
	// Se adauga un obiect pe partea stanga
	Objects aux1;
	aux1.pos = 1;
	aux1.last = true;
	// Tipul 0 - pom de craciun
	// Tipul 1 - felinar
	aux1.type = Random(0, 1);

	if (aux1.type == 0) {
		aux1.tx1 = 10;
		aux1.ty1 = 0;
		aux1.tz1 = 5;
		aux1.sx1 = 1;
		aux1.sy1 = 2;
		aux1.sz1 = 1;
	} else {
		aux1.tx1 = 10.5;
		aux1.ty1 = 0;
		aux1.tz1 = 5;
		aux1.sx1 = 0.5f;
		aux1.sy1 = 2;
		aux1.sz1 = 0.5f;

		aux1.tx2 = 10;
		aux1.ty2 = 2;
		aux1.tz2 = 5;
		aux1.sx2 = 1;
		aux1.sy2 = 0.5f;
		aux1.sz2 = 0.5f;
	}

	objects.push_back(aux1);
}

// Spawnare obiecte decor
void Tema3::SpawnObjects() {
	int i, k, size = objects.size();
	for (i = 0; i < size; i++) {
		// Se verifica daca ultimul obiect a trecut de pragul spawn_plat
		if (objects[i].last && objects[i].tz1 < spawn_plat) {
			objects[i].last = false;

			// Daca este de pe partea dreapta
			if (objects[i].pos == 0) {
				Objects aux;
				aux.last = true;
				aux.pos = 0;
				aux.type = Random(0, 1);
				if (aux.type == 0) {
					aux.tx1 = -1;
					aux.ty1 = 0;
					aux.tz1 = objects[i].tz1 + 5;
					aux.sx1 = 1;
					aux.sy1 = 2;
					aux.sz1 = 1;
				} else {
					aux.tx1 = -1;
					aux.ty1 = 0;
					aux.tz1 = objects[i].tz1 + 5;
					aux.sx1 = 0.5f;
					aux.sy1 = 2;
					aux.sz1 = 0.5f;

					aux.tx2 = -1;
					aux.ty2 = 2;
					aux.tz2 = objects[i].tz1 + 5;
					aux.sx2 = 1;
					aux.sy2 = 0.5f;
					aux.sz2 = 0.5f;
				}
				objects.push_back(aux);
			
			// Daca este pe partea stanga
			} else {
				Objects aux;
				aux.last = true;
				aux.pos = 1;
				aux.type = Random(0, 1);
				if (aux.type == 0) {
					aux.tx1 = 10;
					aux.ty1 = 0;
					aux.tz1 = objects[i].tz1 + 5;
					aux.sx1 = 1;
					aux.sy1 = 2;
					aux.sz1 = 1;
				} else {
					aux.tx1 = 10.5;
					aux.ty1 = 0.f;
					aux.tz1 = objects[i].tz1 + 5;
					aux.sx1 = 0.5f;
					aux.sy1 = 2.f;
					aux.sz1 = 0.5f;

					aux.tx2 = 10.f;
					aux.ty2 = 2.f;
					aux.tz2 = objects[i].tz1 + 5;
					aux.sx2 = 1.f;
					aux.sy2 = 0.5f;
					aux.sz2 = 0.5f;
				}
				objects.push_back(aux);
			}
		}
	}
}

// Afisare obiecte decor
void Tema3::ShowObjects(float deltaTimeSeconds) {
	int i;

	for (i = 0; i < objects.size(); i++) {
		glm::mat4 modelMatrix = glm::mat4(1);
		if (objects[i].type == 0) {
			// Se transalteaza la pozitia dorita
			modelMatrix *= Transform3D::Translate(objects[i].tx1, objects[i].ty1,
				objects[i].tz1);

			// Se scleaza 
			modelMatrix *= Transform3D::Scale(objects[i].sx1, objects[i].sy1,
				objects[i].sz1);

			objects[i].tz1 -= deltaTimeSeconds * speed;


			RenderSimpleMesh(meshes["tree"], shaders["Tema3"], modelMatrix,
				glm::vec3(1, 1, 1), false, false, mapTextures["tree"]);
		} else {
			// Se transalteaza la pozitia dorita
			modelMatrix *= Transform3D::Translate(objects[i].tx1, objects[i].ty1,
				objects[i].tz1);

			// Se scleaza 
			modelMatrix *= Transform3D::Scale(objects[i].sx1, objects[i].sy1,
				objects[i].sz1);

			objects[i].tz1 -= deltaTimeSeconds * speed;

			RenderSimpleMesh(meshes["box"], shaders["Tema3"], modelMatrix,
				glm::vec3(1, 1, 1), false, false, mapTextures["metal"]);
			
			modelMatrix = glm::mat4(1);

			// Se transalteaza la pozitia dorita
			modelMatrix *= Transform3D::Translate(objects[i].tx2, objects[i].ty2,
				objects[i].tz2);

			// Se scleaza 
			modelMatrix *= Transform3D::Scale(objects[i].sx2, objects[i].sy2,
				objects[i].sz2);

			objects[i].tz2 -= deltaTimeSeconds * speed;

			RenderSimpleMesh(meshes["box"], shaders["Tema3"], modelMatrix,
				glm::vec3(1,1,1), false, false, mapTextures["metal"]);
		}
	}
}

// Eliminare obiecte decor
void Tema3::RemoveObjects() {
	int i;

	for (i = 0; i < objects.size(); i++) {
		//Se elimina afisarea obiectelor care nu se mai vad pe ecran
		if (objects[i].tz1 < 0) {

			objects.erase(objects.begin() + i);
			i--;
			continue;
		}
	}
}

// Generare obstacole/elemte colectabile
void Tema3::SpawnObstacle() {
	int size_platform = platforms.size();
	if (size_platform == 0) {
		return;
	}
	int ind = size_platform - 1;
	// Daca pe ultima platforma nu s-a incercat punerea unui element si platforma nu este cea initiala
	if (platforms[ind].obs_collect == false && platforms[ind].pos != 0) {
		int choice = Random(0, 4);

		// Sansa  ca platforma sa primeasca un obstacol
		if (choice == 1) {
			Obstacles aux;
			aux.tx = platforms[ind].tx;
			aux.ty = platforms[ind].ty;
			aux.tz = (float)Random(((int)(platforms[ind].tz + 2)), ((int)(platforms[ind].tz + platforms[ind].sz)));
			aux.sx = 3.f;
			aux.sy = 1;
			aux.sz = 1;
			aux.type = false;
			obstacles.push_back(aux);
		}
		// Sansa element colectabil
		else if (choice == 2) {
			Obstacles aux;
			aux.tx = platforms[ind].tx + 1;
			aux.ty = platforms[ind].ty + 1;
			aux.tz = (float)Random(((int)(platforms[ind].tz + 2)), ((int)(platforms[ind].tz + platforms[ind].sz)));
			aux.sx = 1;
			aux.sy = 1;
			aux.sz = 1;
			aux.type = true;
			obstacles.push_back(aux);
		}

		// Se memoreaza ca s-a pus un obstacol/ s-a incercat punerea unui obstacol, element colectabil
		platforms[size_platform - 1].obs_collect = true;
	}

}

// Afisare obstacol/ element colectabil
void Tema3::ShowObstacles(float deltaTimeSeconds) {
	int i;
	for (i = 0; i < obstacles.size(); i++) {
		glm::mat4 modelMatrix = glm::mat4(1);
		if (obstacles[i].type == false) {
			// Se transalteaza la pozitia dorita
			modelMatrix *= Transform3D::Translate(obstacles[i].tx, obstacles[i].ty,
				obstacles[i].tz);

			// Se scleaza 
			modelMatrix *= Transform3D::Scale(obstacles[i].sx, obstacles[i].sy,
				obstacles[i].sz);

			obstacles[i].tz -= deltaTimeSeconds * speed;

			RenderSimpleMesh(meshes["box"], shaders["Tema3"], modelMatrix,
				glm::vec3(1, 1, 1), false, false, mapTextures["box"]);
		} else {
			// Se transalteaza la pozitia dorita
			modelMatrix *= Transform3D::Translate(obstacles[i].tx, obstacles[i].ty,
				obstacles[i].tz);

			// Se scleaza 
			modelMatrix *= Transform3D::Scale(obstacles[i].sx, obstacles[i].sy,
				obstacles[i].sz);

			// Se genereaza o miscare pe axa OY
			obstacles[i].ty = sin(obstacles[i].time) + 1;
			obstacles[i].time += deltaTimeSeconds;
			obstacles[i].tz -= deltaTimeSeconds * speed;

			RenderSimpleMesh(meshes["box"], shaders["Tema3"], modelMatrix,
				glm::vec3(1, 1, 1), false, false, mapTextures["coin"]);
		}
	}
}

// Stergere obstacol/element colectabil
void Tema3::RemoveObstacles() {
	int i;

	for (i = 0; i < obstacles.size(); i++) {
		//Se elimina afisarea obstacolelor care nu se mai vad pe ecran
		if (obstacles[i].tz < 0) {
			obstacles.erase(obstacles.begin() + i);
			i--;
			continue;
		}
	}
}

// Coliziune player-obstacol/element colectabil
void Tema3::PlayervsObstacle() {
	int i;

	for (i = 0; i < obstacles.size(); i++) {
		if (CollisionTest(obstacles[i].tx, obstacles[i].ty, obstacles[i].tz, obstacles[i].tx + obstacles[i].sx,
			obstacles[i].ty + obstacles[i].sy, obstacles[i].tz + obstacles[i].sz, player_tx, player_ty,
			player_tz, 0.5f)) {
			// Loveste un obstacol
			if (obstacles[i].type == false) {
				is_death = true;
				break;
			
			// Loveste un element colectabil
			} else {
				score++;
				obstacles.erase(obstacles.begin() + i);
				i--;
				continue;
			}
		}
	}
}


// Verificare coliziune
bool Tema3::CollisionTest(float boxminX, float boxminY, float boxminZ,
	float boxmaxX, float boxmaxY, float boxmaxZ, 
	float spherex, float spherey, float spherez, float radius) {

	float x = glm::max(boxminX, glm::min(spherex, boxmaxX));
	float y = glm::max(boxminY, glm::min(spherey, boxmaxY));
	float z = glm::max(boxminZ, glm::min(spherez, boxmaxZ));

	float distance = glm::sqrt((x - spherex) * (x - spherex) +
		(y - spherey) * (y - spherey) +
		(z - spherez) * (z - spherez));
	if (distance < radius) {
		return true;
	} else {
		return false;
	}

}