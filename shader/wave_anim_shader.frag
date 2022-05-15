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
	float cosine = dot(s, GNormal);
	vec3 diffuse = Material.Kd * ceil(cosine * Levels) * scaleFactor;

	return Light.Intensity * (ambient + diffuse);
}

vec4 blinnPhong(vec4 vertexPos, vec3 n)
{
	//calculate ambient here
	vec3 ambient = Material.Ka * Light.Intensity;

	//calculate diffuse here
	vec3 s = vec3(normalize(Light.Position - vertexPos));
	float sDotN = max(dot(s, n), 0.0f);
	vec3 diffuse = Material.Kd * sDotN;

	//calculate specular here
	vec3 v = normalize(-vertexPos.xyz);
	vec3 h = normalize(v + s);

	vec3 spec = Material.Ks * pow(max(dot(h, n), 0.0f), Material.Shininess);
	 
	return vec4(ambient + Light.Intensity * (diffuse + spec), 1.0);
}

void main()
{
	if (GIsEdge == 1) {
		FragColor = LineColor;
	}
	else {
		FragColor = vec4(toonShade(), 1.0);
	}
}