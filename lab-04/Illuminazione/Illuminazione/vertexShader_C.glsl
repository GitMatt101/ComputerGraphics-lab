#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2 ) in vec3 vertexNormal;

uniform mat4 Model;
uniform mat4 Projection;
uniform mat4 View;
uniform vec3 viewPos;

struct LightPoint {
	vec3 position;
	vec3 color;
	float power;
};
uniform LightPoint light;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
uniform Material material;

out vec4 ourColor;
out vec3 N, V, L, R;

void main()
{
	gl_Position = Projection*View*Model*vec4(aPos, 1.0);
    ourColor = aColor;
     
    vec4 eyePosition = View * Model * vec4(aPos, 1.0f);
    vec4 eyeLightPos = View * vec4(light.position, 1.0f);
    N = normalize(transpose(inverse(mat3(View * Model))) * vertexNormal);
    V = normalize(viewPos - eyePosition.xyz);
    L = normalize((eyeLightPos - eyePosition).xyz);
    R = reflect(-L, N);
}  
