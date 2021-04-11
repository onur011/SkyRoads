#version 330

uniform sampler2D texture_1;
 
in vec2 texcoord;
in vec3 frag_color;

layout(location = 0) out vec4 out_color;

void main()
{
	// Se verifica daca exista textura
	if(texcoord != vec2(0,0)) {
		
		// Se afiseaza doar textura
		if (texture2D(texture_1, texcoord).a < 0.5f) {
			discard;
		}

		out_color = texture2D(texture_1, texcoord)*vec4(frag_color, 1);
	} else {
		out_color = vec4(frag_color, 1);
	}
}	