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

// Uses 4th octave noise value stored in alpha
// Normalized noise value is multiplied to give a broader range of wave heights
float getHeight(vec4 noise)
{
	return noise.a * Amp * 2.0f;
}

// Normal is assigned a completely random noise value
// This gives a 'warped' effect due to refraction of light in water
vec3 getNormal(vec4 noise)
{
	return noise.xyz;
}

void main()
{
	// Using noise to generate waves was based off a stack overflow solution
	// Source: https://stackoverflow.com/questions/30397320/opengl-water-waves-with-noise

	// Offset constantly changing as time passes
	vec2 offset = Time * Velocity * vec2(0.1f);

	// Changing offset animates the noise to move in the offset direction
	vec4 noise = texture(NoiseTex, TexCoords + offset);

	vec4 pos = vec4(VertexPosition, 1.0f);
	pos.y = getHeight(noise);

	VNormal = normalize(getNormal(noise));
	VPosition = vec3(ModelViewMatrix * pos);

	gl_Position = MVP * pos;
}