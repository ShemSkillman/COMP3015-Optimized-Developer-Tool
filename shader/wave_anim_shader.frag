#version 460

in vec3 GPosition;
in vec3 GNormal;

flat in int GIsEdge;

layout (location = 0) out vec4 FragColor;

uniform struct LightInfo {
 vec3 Intensity; // Ambient light intensity
 vec4 Position;
} Light;

uniform struct MaterialInfo {
 vec3 Ka; // Ambient reflectivity
 vec3 Kd; // Diffuse reflectivity
 vec3 Ks; // Specular reflectivity
 float Shininess; // Specular shininess factor
} Material;

uniform vec4 LineColor;
uniform int Levels = 3;

const float scaleFactor = 1.0 / Levels;

vec3 toonShade()
{
	vec3 s = normalize(Light.Position.xyz - GPosition.xyz);
	vec3 ambient = Material.Ka;

	// How direct is the light shining on the surface?
	float cosine = dot(s, GNormal);

	// Diffuse colour is rounded to nearest shade
	vec3 diffuse = Material.Kd * ceil(cosine * Levels) * scaleFactor;

	return Light.Intensity * (ambient + diffuse);
}

void main()
{
	// Fragment is on sil. line, using sil. line colour
	if (GIsEdge == 1) {
		FragColor = LineColor;
	}
	else {
		FragColor = vec4(toonShade(), 1.0);
	}
}