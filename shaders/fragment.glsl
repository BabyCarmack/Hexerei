version.glsl

out vec4 fragColor;

uniform sampler2D albedo;
uniform sampler2D normal;
uniform float texSize;

uniform vec3 viewPos;
uniform Light light;
uniform vec3 ambCol;
uniform float technique;

in vec3 NormalVec;
in vec3 fragPos;
in vec2 TexCoords;
in mat4 export;
in vec3 TanvPos;
in vec3 TanLPos;
in vec3 TfragPos;

uniform samplerCube depthMap;
uniform float far_plane;
uniform mat4 lightProj;

vec3 camVec;
vec3 lightDeg;
vec3 normie;

void main()
{
  normie = texture(normal, TexCoords * texSize).rgb;
  normie = normalize(NormalVec / normie * 2.0 - 1.0);
  //normie = normalize(NormalVec);
  camVec = normalize(viewPos - fragPos);
  lightDeg = normalize(light.position - fragPos);
  float diff = max(dot(normie, lightDeg), 0.0);

  float pi = 3.1415926535;
  vec3 specular;
  vec3 Reflec = reflect(-lightDeg, normie);
  vec3 halfVec = normalize(lightDeg + camVec);

  vec3 ambient;
  ambient = ambCol * texture(albedo, TexCoords * texSize).rgb;

  vec3 diffuse;
  diffuse = light.diffuse * diff * (diff * texture(albedo, TexCoords * texSize).rgb);

  //float roughness = texture(material.texture_roughness1, TexCoords).r / 10.0;
  float roughness = 0.04;
  float alpha = acos(dot(normie, halfVec));
  float cosi = float(pow(cos(alpha), 2.0));
  float tang = (1 - cosi) / (cosi * roughness);
  float Beckmann = float(exp(-tang) / (pi * roughness * pow(cosi, 2.0)));

  float Schlick = 0.13 + (1.0 - 0.13) * pow(1.0 - cos(dot(halfVec, camVec)), 5.0);

  float viewNorm = dot(camVec, normie);

  float eq1 = (2 * dot(halfVec, normie) * viewNorm) / dot(camVec, halfVec);
  float eq2 = (2 * dot(halfVec, normie) * dot(lightDeg, normie)) / dot(camVec, halfVec);
  float geo = min(min(1, eq1), eq2);

  float topHalf = Beckmann * Schlick * geo;
  float bottomHalf = float(pi * viewNorm * dot(normie, lightDeg));

  float final = topHalf / bottomHalf;

  float spec = final;
  specular = light.specular * spec;

  float shadow;
  if (dot(normie, lightDeg) < 0) shadow = 1.0;
  else shadow = 0.0;
    //shadow = Shadow();
  vec3 lighting = (ambient + diffuse + specular);

  fragColor = vec4(lighting, 1.0);
  //fragColor = vec4(texture(albedo, TexCoords).rgb, 1.0);
  //fragColor = vec4(TexCoords, 0.0, 1.0);
  //fragColor = vec4(normie.x, normie.y, normie.z, 1.0);
  //fragColor = vec4(NormalVec, 1.0);
}
