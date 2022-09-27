// classic Phong fragment shader 
#version 410 

in vec4 vPosition;
in vec3 vNormal; 

uniform vec3 cameraPosition;

uniform vec3 AmbientColour;

uniform vec3 LightDirection; 
uniform vec3 LightColour;
 
const int MAX_LIGHTS = 4;
uniform int numLights;
uniform vec3 PointLightColour[MAX_LIGHTS];
uniform vec3 PointLightPosition[MAX_LIGHTS];

uniform vec3 Ka; // ambient material colour 
uniform vec3 Kd; // diffuse material colour 
uniform vec3 Ks; // specular material colour 
uniform float specularPower; // material specular power

out vec4 FragColour; 
 
// Added functions
vec3 diffuse(vec3 direction, vec3 colour, vec3 normal)
{
	return colour * max(0, dot( normal, -direction));
}

vec3 specular(vec3 direction, vec3 colour, vec3 normal, vec3 view)
{
	vec3 R = reflect(direction, normal);
	float specularTerm = pow( max(0, dot(R, view)), specularPower);
	return specularTerm * colour;
}

void main() { 
 
 // ensure normal and light direction are normalised 
 vec3 N = normalize(vNormal);
 vec3 L = normalize(LightDirection);

 // calculate diffuse from sunlight
 vec3 diffuseTotal = diffuse(L, LightColour, N);

 // calculate lambert term (negate light direction) 
 float lambertTerm = max( 0, min( 1, dot( N, -L ) ) );  

 // calculate view vector and reflection vector 
 vec3 V = normalize(cameraPosition - vPosition.xyz); 
 
 // calcualte specular lights from directional light
 vec3 specularTotal = specular(L, LightColour, N, V);

 // for loop to process multiple lights
 for (int i=0; i<numLights; i++) 
 { 
  vec3 direction = vPosition.xyz - PointLightPosition[i]; 
  float distance = length(direction); 
  direction = direction/distance; 
 
  // attenuate the light intensity with inverse square law 
  vec3 colour = PointLightColour[i]/(distance * distance); 
 
  diffuseTotal += diffuse(direction, colour, N); 
  specularTotal += specular(direction, colour, N, V); 
 } 

 // calculate each colour property 
 vec3 ambient = AmbientColour * Ka; 
 vec3 diffuse =  Kd * diffuseTotal; 
 vec3 specular = Ks * specularTotal; 

 FragColour = vec4( ambient + diffuse + specular, 1); 
}