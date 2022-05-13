#version 460

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

out vec3 VNormal;
out vec3 VPosition;

uniform float Time;

// Wave params
uniform float Freq = 2.5;
uniform float Velocity = 2.5;
uniform float Amp = 0.6;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;

void main()
{
	vec4 pos = vec4(VertexPosition, 1.0);

	// Translate vertices on y coords
	float u = Freq * pos.x - Velocity * Time;
	float i = Freq * pos.z - Velocity * Time;

	pos.y = Amp * sin(u) + Amp * sin(i);

	// Compute the normal vector
	vec3 n = vec3(0.0);
	n.xyz = normalize(vec3(cos(u), 1.0, sin(i)));

	VNormal = normalize(NormalMatrix * n);
	VPosition = vec3(ModelViewMatrix * pos);

	// The position in clip coords
	gl_Position = MVP * pos;
}