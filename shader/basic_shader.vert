#version 460

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

out vec3 VNormal;
out vec3 VPosition;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;

void main()
{
	VNormal = normalize(NormalMatrix * VertexNormal);
	VPosition = vec3(ModelViewMatrix * vec4(VertexPosition, 1.0f));

	gl_Position = MVP * vec4(VertexPosition, 1.0f);
}