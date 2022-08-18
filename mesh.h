#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF

unsigned int vao, vbo, ebo;
int numVerts = 10;

typedef struct
{
  unsigned int albedo1;
} Material;

typedef struct
{
  float* vertices;
  unsigned int* indices;
  unsigned int arrayID;
  vec3 Position;
} mesh;

//01234567
float vertices[336] = {
  //front
 -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,-1.0f, 1.0f, 0.0f, 0.0f, 0.0f,-1.0f, 0.0f, //bottom right front 0
  1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f,-1.0f, 1.0f, 0.0f, 0.0f, 0.0f,-1.0f, 0.0f, //bottom left front  1
 -1.0f,  1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f,-1.0f, 1.0f, 0.0f, 0.0f, 0.0f,-1.0f, 0.0f, //top right front    2
  1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f,-1.0f, 1.0f, 0.0f, 0.0f, 0.0f,-1.0f, 0.0f, //top left front     3

  //back
 -1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,-1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, //bottom right back  4
  1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,-1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, //bottom left back   5
 -1.0f,  1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,-1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, //top right back     6
  1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,-1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, //top left back      7

  //left
  1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,-1.0f, 0.0f, //bottom left front  8
  1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,-1.0f, 0.0f, //bottom left back   9
  1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,-1.0f, 0.0f, //top left front     10
  1.0f,  1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,-1.0f, 0.0f, //top left back      11

  //right
 -1.0f, -1.0f, -1.0f, 1.0f, 0.0f,-1.0f, 0.0f, 0.0f, 0.0f, 0.0f,-1.0f, 0.0f, 1.0f, 0.0f, //bottom right front 12
 -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,-1.0f, 0.0f, 0.0f, 0.0f, 0.0f,-1.0f, 0.0f, 1.0f, 0.0f, //bottom right back  13
 -1.0f,  1.0f, -1.0f, 1.0f, 1.0f,-1.0f, 0.0f, 0.0f, 0.0f, 0.0f,-1.0f, 0.0f, 1.0f, 0.0f, //top right front    14
 -1.0f,  1.0f,  1.0f, 0.0f, 1.0f,-1.0f, 0.0f, 0.0f, 0.0f, 0.0f,-1.0f, 0.0f, 1.0f, 0.0f, //top right back     15

  //top
 -1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, //top right front    16
  1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, //top left front     17
 -1.0f,  1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, //top right back     18
  1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, //top left back      19

  //bottom
 -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,-1.0f, 0.0f,-1.0f, 0.0f, 0.0f, 0.0f, 0.0f,-1.0f, //bottom right front 20
  1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,-1.0f, 0.0f,-1.0f, 0.0f, 0.0f, 0.0f, 0.0f,-1.0f, //bottom left front  21
 -1.0f, -1.0f,  1.0f, 0.0f, 1.0f, 0.0f,-1.0f, 0.0f,-1.0f, 0.0f, 0.0f, 0.0f, 0.0f,-1.0f, //bottom right back  22
  1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 0.0f,-1.0f, 0.0f,-1.0f, 0.0f, 0.0f, 0.0f, 0.0f,-1.0f  //bottom left back   23
};

unsigned int indices[36] = {
  //back
  0, 2, 3,
  0, 1, 3,
  //right
  12, 14, 15,
  12, 13, 15,
  //bottom
  20, 21, 22,
  22, 23, 21,
  //top
  16, 17, 18,
  18, 19, 17,
  //left
  8, 10, 11,
  11, 9, 8,
  //front
  4, 6, 7,
  7, 5, 4
};

void setupMesh()
{
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, 336 * sizeof(float), &vertices[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

  //set the vertex attribute pointers
  //vertex Positions
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)0);
  //vertex texture coords
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(3 * sizeof(float)));
  //vertex normals
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(5 * sizeof(float)));
  //vertex tangent
  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(8 * sizeof(float)));
  //vertex bitangent
  glEnableVertexAttribArray(4);
  glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(11 * sizeof(float)));

  glBindVertexArray(0);
}

unsigned int loadTexture(const char* path)
{
  unsigned int texID;
  glGenTextures(1, &texID);

  int width, height, numComponents;
  unsigned char* data = stbi_load(path, &width, &height, &numComponents, 0);

  if (data) {
        GLenum format;
        switch (numComponents)
        {
          case 1:
            format = GL_RED;
            break;
          case 2:
            format = GL_RG;
            break;
          case 3:
            format = GL_RGB;
            break;
          case 4:
            format = GL_RGBA;
            break;
          default:
            printf("Warning! Texture loader identified abnormal number of components!\n");
        }

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        float ani = 16.0f;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &ani);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, ani);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }
    else
    {
      printf("ERROR! Texture data failed to load! Path: %s\n", path);
      return 1;
    }
    return texID;
}

void Render()
{
  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);
  glBindVertexArray(0);
}
