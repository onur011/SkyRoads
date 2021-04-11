#include "Tema3.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>
#include "Transform3D.h"

using namespace std;

void Tema3::SpawnPlayer() {
	player_tx = length / 2.f;
	player_ty = 0.5f;
	player_tz = 3.f;

}

// Afisare player
void Tema3::ShowPlayer(float deltaTime) {
	glm::mat4 modelMatrix = glm::mat4(1);
	
	// Saritura
	if (jump) {
		
		clk += deltaTime;
		// Se utlizeaza miscare de deplase cu acceleratia grevitationala pe Oy pentru
		// a simula o saritula
		player_ty = 0.5f + player_speed_ty * clk - gravity * clk * clk / 2.f;

		if (player_ty < 0.5f) {
		
			player_ty = 0.5f;
			jump = false;
		}
		
	}
	// Daca este first person, sfera nu mai este afisata
	if (first_person) {
		return;
	}
	// Se transalteaza la pozitia dorita
	modelMatrix *= Transform3D::Translate(player_tx, player_ty, player_tz);
	// Daca este abilitatea activata, se adauga o miscare neregulata playerului
	if (ability) {
		RenderSimpleMesh(meshes["player"], shaders["Tema3"], modelMatrix, glm::vec3(1, 0, 0), false, true, NULL);
	} else {
		RenderSimpleMesh(meshes["player"], shaders["Tema3"], modelMatrix, glm::vec3(1, 0, 0), false, false, NULL);
	}
}

void Tema3::PlayerOnPlatform() {
	int i;
	bool on_platform = false;

	// Daca player este in aer, nu se mai efectuaza verificarea
	if (player_ty != 0.5f) {
		return;
	}

	for (i = 0; i < platforms.size(); i++) {

		// Se verifica daca sfera se afla pe platforma
		if (platforms[i].tx <= player_tx && player_tx <= platforms[i].sx *
			intial_platform + platforms[i].tx && platforms[i].tz <= player_tz &&
			player_tz <= platforms[i].sz * intial_platform + platforms[i].tz) {
			
			on_platform = true;

			// Rosu: se termina jocul
			if (platforms[i].color == glm::vec3(1, 0, 0)) {
				is_death = true;

			// Galben: se scade combustibilul
			} else if (platforms[i].color == glm::vec3(1, 1, 0)) {

				fuel -= 3;

			// Portocaliu: se activraza abilitatea, daca nu este deja activata
			} else if (platforms[i].color == glm::vec3(1, 0.27f, 0) && ability == false) {

				last_speed = speed;
				speed = speed_ability;
				ability = true;

			// Verde: creste combustibilul
			} else if (platforms[i].color == glm::vec3(0, 1, 0)) {

				fuel += 5;
				if (fuel > max_fuel) {
					fuel = max_fuel;
				}
			}

			// Se schimba culoarea in mov
			platforms[i].color = glm::vec3(0.5f, 0, 0.5f);
			
		}

	}

	// Daca playerul nu se afla pe nicio platforma, jocul se termina
	if (on_platform == false) {
		is_death = true;
	}
}
// Functia de modificare in first person 
void Tema3::ChangeView() {
	//Se selectaza pozitia camerei in functie de first_person
	if (first_person) {
		camera_pos_x = player_tx;
		camera_pos_y = player_ty + 0.5f;
		camera_pos_z = player_tz;

		camera_center_x = player_tx;
		camera_center_y = player_ty;
		camera_center_z = player_tz + 2;
	} else {
		camera_pos_x = 5;
		camera_pos_y = 5;
		camera_pos_z = 0;

		camera_center_x = 5;
		camera_center_y = 1;
		camera_center_z = 4;
	}
	camera->Set(glm::vec3(camera_pos_x, camera_pos_y, camera_pos_z),
		glm::vec3(camera_center_x, camera_center_y, camera_center_z), glm::vec3(0, 1, 0));
}

// Se verifica de cat timp este activa abilitatea
void Tema3::CheckAbility(float deltaTimeSeconds) {
	clock_ability += deltaTimeSeconds;

	if (clock_ability > time_ability) {
		speed = last_speed;
		clock_ability = 0;
		ability = false;
	}
}

// Afisare animatie player terminare joc
void Tema3::ShowDeathPlayer(float deltaTimeSeconds) {
	glm::mat4 modelMatrix = glm::mat4(1);

	// Se transalteaza la pozitia dorita(sfera va urca, avand o miscare in forma unei spirale care
	// isi mareste raze)
	modelMatrix *= Transform3D::Translate(player_tx+sin(clk_death)*rad, player_ty, player_tz +
		cos(clk_death)*rad);
	player_ty += deltaTimeSeconds;
	rad += deltaTimeSeconds;
	RenderSimpleMesh(meshes["player"], shaders["Tema3"], modelMatrix, glm::vec3(1, 0, 0), false, false, NULL);
}
