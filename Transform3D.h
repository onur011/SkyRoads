#pragma once

#include <include/glm.h>

namespace Transform3D
{
	// Matrice trnaslatare
	inline glm::mat4 Translate(float tx, float ty, float tz)
	{
		return glm::transpose(glm::mat4(1, 0, 0, tx,
										0, 1, 0, ty,
										0, 0, 1, tz,
										0, 0, 0, 1));
	}

	// Matrice scalare
	inline glm::mat4 Scale(float sx, float sy, float sz)
	{
		return glm::transpose(glm::mat4(sx, 0, 0, 0,
										0, sy, 0, 0,
										0, 0, sz, 0,
										0, 0, 0, 1));
	}

	// Matrice de rotatie fata de Oz
	inline glm::mat4 RotateOZ(float u)
	{
		return glm::transpose(glm::mat4(cos(u),  sin(u), 0, 0,
										-sin(u), cos(u),  0, 0,
										  0,     0,      1, 0,
										  0,     0,      0, 1));
	}

	// Matrice de rotatie fata de Oy
	inline glm::mat4 RotateOY(float u)
	{
		return glm::transpose(glm::mat4(cos(u),  0, sin(u), 0,
										   0,    1,    0,   0,
										-sin(u), 0, cos(u), 0,
										   0,    0,    0,   1));
	}

	// Matrice de rotatie fata de Ox
	inline glm::mat4 RotateOX(float u)
	{
		return glm::transpose(glm::mat4( 1,    0,       0,    0,
										 0,  cos(u), -sin(u), 0,
										 0,  sin(u),  cos(u), 0,
										 0,    0,       0,    1));
	}
}
