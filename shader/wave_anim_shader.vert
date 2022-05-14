#version 460

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec2 TexCoords;

out vec3 VNormal;
out vec3 VPosition;

uniform float Time;

// Wave params
uniform float Freq = 2.5;
uniform float Velocity = 2.5;
uniform float Amp = 0.6;

uniform sampler2D NoiseTex;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;

float getHeight()
{
	vec2 offset = Time * Velocity * vec2(1.0f);
	vec4 noise = texture(NoiseTex, TexCoords + offset);
	return noise.a * Amp;
}

vec3 getNormal()
{
	vec2 offset = Time * Velocity * vec2(1.0f);
	vec4 noise = texture(NoiseTex, TexCoords + offset);
	return noise.xyz;
}

void main()
{

	vec4 pos = vec4(VertexPosition, 1.0f);
	pos.y = getHeight();

	VNormal = normalize(getNormal());
	VPosition = vec3(ModelViewMatrix * pos);

	// The position in clip coords
	gl_Position = MVP * pos;
}