#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

out vec3 NormalVec;
out vec3 fragPos;
out vec2 TexCoords;
out vec3 TanLPos;
out vec3 TanvPos;
out vec3 TfragPos;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;
uniform mat4 lightMat;

uniform vec3 viewPos;
uniform vec3 lPos;

void main() {
    fragPos = vec3(model * vec4(aPos, 1.0));
    TexCoords = aTexCoords;
    NormalVec = aNormal;

    vec3 T = normalize(mat3(model) * aTangent);
    //NormalVec = mat3(model) * aNormal;
    vec3 B = normalize(mat3(model) * aBitangent);
    T = normalize(T - dot(NormalVec, T));

    mat3 TBN = transpose(mat3(T, B, NormalVec));
    TfragPos = TBN * fragPos;
    TanvPos = TBN * viewPos;
    TanLPos = TBN * lPos;

    gl_Position = proj * view * vec4(fragPos, 1.0);
}
