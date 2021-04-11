#version 330

// TODO: get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 object_color;

uniform vec3 light_position;
uniform vec3 eye_position;
uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;
uniform int screen_object;
uniform int random;
uniform int texture;
uniform int time;

out vec3 frag_color;
out vec2 texcoord;

// Functie de generare valoarea random in functie de timp
float rand(vec2 co, int time){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453 * (time % 100));
}

void main()
{
	// Se calculeaza vectorii spartiului
	vec3 world_pos = (Model * vec4(v_position,1)).xyz;
	vec3 world_normal = normalize( mat3(Model) * v_normal );
	vec3 L = normalize( light_position - world_pos );
	vec3 V = normalize( eye_position - world_pos );
	vec3 H = normalize( L + V );

	// Daca este un obient de scena
	if(screen_object == 0) {

		// Se calculeaza lumina ambientala
		float ambient_light = 0.7f;
		float ambientala = material_kd * ambient_light;
	
		// Se calculeaza lumina difuza
		float intensitateLumina = 9.f;
		float difuza = material_kd * intensitateLumina * max (dot(world_normal,L), 0);

		// Se calculeaza lumina speculara
		float speculara = 0;
	
		if (difuza > 0) {
			speculara = material_ks * intensitateLumina  * pow(max(dot(world_normal, H), 0), 5);
		}

		// Se compune lumina
		float d = length(light_position - world_pos);
		float factorAtenuare = 1/pow(d,2);

		float intensitate = ambientala + factorAtenuare * ( difuza + speculara );

		// Se transmite culoarea catre fragment shader
		frag_color = object_color * intensitate;
	
	// Daca este un obiect de ecran
	} else {
		frag_color = object_color;
	}

	float zgomot;

	// Se calculeaza zgomotul
	if (random == 0) {
		zgomot = 0;
	} else {
		zgomot = rand(v_position.xy,time)*0.1f;
	}
	if(texture == 1){
		texcoord = v_texture_coord;
	} else {
		texcoord = vec2(0,0);
	}
	gl_Position = Projection * View * Model * vec4(v_position + vec3(zgomot,zgomot,zgomot)*v_normal , 1.0);
}
