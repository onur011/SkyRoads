#include "Tema3.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>
#include "Transform3D.h"

using namespace std;

// Genereaza platforma initiala
void Tema3::InitialPlatform() {
	Platforms aux;
	aux.sx = 10;
	aux.sy = 1;
	aux.sz = 20;

	aux.tx = 0;
	aux.ty = 0;
	aux.tz = 0;

	aux.last = true;
	aux.pos = 0;
	aux.color = glm::vec3(0.5f ,0, 0.5f);

	platforms.push_back(aux);
}

void Tema3::SpawnPlatform() {
	int i, k, plat_size = platforms.size();
	for (i = 0; i < plat_size; i++) {
		// Se verifica ultimile platforme care au trecut de pragul spawn_plat
		if (platforms[i].last && platforms[i].tz + intial_platform * platforms[i].sz < spawn_plat) {
			platforms[i].last = false;

			// Daca este platforma initiala
			if (platforms[i].pos == 0) {

				bool l = false, m = false, r = false;

				// Se adauga 3 platforme
				for (k = 0; k < 3; k++) {
					Platforms aux;
					aux.sx = 3.f;
					aux.sy = 1.f;
					// Se alege random lungimea platformei
					aux.sz = (float)Random(7, 15);

					//platforms[i].tz + intial_platform * platforms[i].s reprezinta lungimea
					// platfromei de la punctul platforms[i].tz , la care adaugam 2 
					//pentru a genera platformele la o distanta de 2
					aux.tz = platforms[i].tz + intial_platform * platforms[i].sz + 2.f;
					aux.ty = 0;
					// Se alege pozitia platformei, tinandu-se cont de pozitiile
					// platformelor alese deja
					while (1) {

						int position = Random(0, 2);

						if (position == 0 && l == false) {
							l = true;
							aux.pos = 3;
							aux.tx = 7.f;
							break;
						}

						if (position == 1 && m == false) {
							m = true;
							aux.pos = 2;
							aux.tx = 3.5f;
							break;
						}

						if (position == 2 && r == false) {
							r = true;
							aux.pos = 1;
							aux.tx = 0;
							break;
						}
					}

					int type = Random(1, 10);
					// Se alege culoare
					// Pentru rosu generam o probabilitate mai mica
					// Rosu 10%, celelalte au fiecare 30%
					if (type == 1) {
						aux.color = glm::vec3(1, 0, 0);
					}
					else if (type == 2 || type == 3 || type == 4) {
						aux.color = glm::vec3(1, 1, 0);
					}
					else if (type == 5 || type == 6 || type == 7) {
						aux.color = glm::vec3(1, 0.27f, 0);
					}
					else {
						aux.color = glm::vec3(0, 1, 0);
					}

					aux.last = true;

					// Se adauga in vector
					platforms.push_back(aux);
				}
			// Daca nu este platforma initiala
			} else {
				Platforms aux;
				aux.sx = 3.f;
				aux.sy = 1.f;
				// Se alege random lungimea platformei
				aux.sz = (float)Random(10, 20);
				
				// platforms[i].tz + intial_platform * platforms[i].s reprezinta lungimea
				// platfromei de la punctul platforms[i].tz, la care adaugam 2 pentru a
				// genera platformele la o distanta de 2
				aux.tz = platforms[i].tz + intial_platform * platforms[i].sz + 2.f;
				aux.ty = 0;
				// Se adauga platforma pe aceeasi pozitie
				aux.pos = platforms[i].pos;

				if (platforms[i].pos == 3) {
					aux.tx = 7.f;
				} else if (platforms[i].pos == 2) {
					aux.tx = 3.5f;
				} else if (platforms[i].pos == 1) {
					aux.tx = 0;
				}

				int type = Random(1, 10);
				// Se alege culoare
				// Pentru rosu generam o probabilitate mai mica
				// Rosu 10%, celelalte au fiecare 30%
				if (type == 1) {
					aux.color = glm::vec3(1, 0, 0);
				}
				else if (type == 2 || type == 3 || type == 4) {
					aux.color = glm::vec3(1, 1, 0);
				}
				else if (type == 5 || type == 6 || type == 7) {
					aux.color = glm::vec3(1, 0.27f, 0);
				}
				else {
					aux.color = glm::vec3(0, 1, 0);
				}

				// Se anunta ca este ultima platforma
				aux.last = true;

				// Se adauga in vector
				platforms.push_back(aux);
			}
		}
	}
}

// Afisare platforme
void Tema3::ShowPlatforms(float deltaTimeSeconds) {
	int i;

	for (i = 0; i < platforms.size(); i++) {
		glm::mat4 modelMatrix = glm::mat4(1);

		// Se transalteaza la pozitia dorita
		modelMatrix *= Transform3D::Translate(platforms[i].tx, platforms[i].ty,
			platforms[i].tz);

		// Se scleaza 
		modelMatrix *= Transform3D::Scale(platforms[i].sx, platforms[i].sy,
										platforms[i].sz);
		// Se translateaza cu coltul in origine
		modelMatrix *= Transform3D::Translate(intial_platform / 2.f,
			-intial_platform / 2.f, intial_platform / 2.f);
		
		platforms[i].tz -= deltaTimeSeconds*speed;

		RenderSimpleMesh(meshes["platform"], shaders["Tema3"], modelMatrix,
				platforms[i].color,false, false, mapTextures["stone"]);
	}
}

// Eliminare platforme
void Tema3::RemovePlatform() {
	int i;

	for (i = 0; i < platforms.size(); i++) {
		//Se elimina afisarea platformelor care nu se mai vad pe ecran
		if (platforms[i].tz + intial_platform*platforms[i].sz < 0) {
			platforms.erase(platforms.begin() + i);
			i--;
			continue;
		}
	}
}

// Afisare platforme terminare joc
void Tema3::ShowDeathPlatforms(float deltaTimeSeconds) {
	int i;

	for (i = 0; i < platforms.size(); i++) {
		glm::mat4 modelMatrix = glm::mat4(1);

		// Se transalteaza la pozitia dorita
		modelMatrix *= Transform3D::Translate(platforms[i].tx, platforms[i].ty,
			platforms[i].tz);

		// Se scleaza 
		modelMatrix *= Transform3D::Scale(platforms[i].sx, platforms[i].sy,
			platforms[i].sz);
		// Se translateaza cu coltul in origine
		modelMatrix *= Transform3D::Translate(intial_platform / 2.f,
			-intial_platform / 2.f, intial_platform / 2.f);
		
		// Platformele incep sa cada
		if (clk_death > time_camera) {
			platforms[i].ty -= deltaTimeSeconds * 3.f;
		}

		RenderSimpleMesh(meshes["platform"], shaders["Tema3"], modelMatrix,platforms[i].color, false, false, mapTextures["stone"]);
	}
}
