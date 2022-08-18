#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <vectorMath.h>
#include <string.h>
#include <glad/glad.h>
#include "matrixMath.h"
#include "shader.h"
#include "mesh.h"

typedef struct
{
  vec3 Position;
  vec3 Scale;
  unsigned int albedo;
  unsigned int normalMap;
  bool deleted;
} Thing;

Thing* things;
float lightSped = 0.5f;
bool up = true;

int numTexts = 1;
int numThings = 1;

void createWorld(unsigned int shad)
{
  setupMesh();

  FILE* sceneFile = fopen("Scenes/Test.scen", "r");
  char stuff[20];

  fseek(sceneFile, 0, SEEK_SET);
  fgets(stuff, 20, sceneFile);
  if (strstr(stuff, "scen") == NULL)
  {
    printf("Scene failed to load, unrecognized file type\n");
  }

  for (int line = 0; line < 2; line++)
  {
    char num[50];
    fseek(sceneFile, 0, SEEK_CUR);
    fgets(stuff, 20, sceneFile);
    if (strstr(stuff, "numThings") != NULL)
    {
      fseek(sceneFile, -3, SEEK_CUR);
      fread(num, 1, 2, sceneFile);
      printf("%s\n", num);
      fseek(sceneFile, 1, SEEK_CUR);
      numThings = atoi(num);
    }
    if (strstr(stuff, "numTexts") != NULL)
    {
      fseek(sceneFile, -3, SEEK_CUR);
      fread(num, 1, 2, sceneFile);
      printf("%s\n", num);
      fseek(sceneFile, 1, SEEK_CUR);
      numTexts = atoi(num);
    }
  }

  unsigned int textures[numTexts];
  for (int line = 0; line < numTexts; line++)
  {
    fgets(stuff, 20, sceneFile);
    stuff[strlen(stuff) - 1] = '\0';
    printf("%s\n", stuff);
    textures[line] = loadTexture(stuff);
  }

  fseek(sceneFile, 0, SEEK_CUR);

  things = calloc(numThings, sizeof(Thing));

  for (int line = 0; line < numThings; line++)
  {
    char flot[9];
    char te[2];
    fread(flot, 8, 1, sceneFile);
    things[line].Position.x = atof(flot);
    fseek(sceneFile, 1, SEEK_CUR);

    fread(flot, 8, 1, sceneFile);
    things[line].Position.y = atof(flot);
    fseek(sceneFile, 1, SEEK_CUR);

    fread(flot, 8, 1, sceneFile);
    things[line].Position.z = atof(flot);
    fseek(sceneFile, 1, SEEK_CUR);

    fread(flot, 8, 1, sceneFile);
    things[line].Scale.x = atof(flot);
    fseek(sceneFile, 1, SEEK_CUR);

    fread(flot, 8, 1, sceneFile);
    things[line].Scale.y = atof(flot);
    fseek(sceneFile, 1, SEEK_CUR);

    fread(flot, 8, 1, sceneFile);
    things[line].Scale.z = atof(flot);
    fseek(sceneFile, 1, SEEK_CUR);

    fread(te, 1, 1, sceneFile);
    int tex = atoi(te);
    things[line].albedo = textures[tex];
    fseek(sceneFile, 1, SEEK_CUR);
    fread(te, 1, 1, sceneFile);

    tex = atoi(te);
    things[line].normalMap = textures[tex];
    fseek(sceneFile, 1, SEEK_CUR);

    things[line].deleted = false;
  }
  useShad(shad);
  setInt("albedo", 0, shad);
  setInt("normal", 1, shad);
  setFloat("texSize", 1.0f, shad);
  fclose(sceneFile);
}

void RenderStuff(unsigned int shad, double deltaT, vec3 camPos)
{
  useShad(shad);
  for (int ids = 0; ids < numThings; ids++)
  {

    if (lightSped < 10.0f && up == true)
    {
      lightSped += 0.2f * deltaT;
    } else up = false;
    if (lightSped > 0.5f && up == false)
    {
      lightSped -= 0.2f * deltaT;
    } else up = true;

    matrix4 model = matrix4Ident(1.0f);
    model = translate(model, Vec3(things[ids].Position.x, things[ids].Position.y, things[ids].Position.z));
    model = scale(model, Vec3(things[ids].Scale.x, things[ids].Scale.y, things[ids].Scale.z));
    setMat4("model", model, shad);
    setVec3("light.position", Vec3(0.0f, lightSped, 0.0f), shad);
    setVec3("light.diffuse", Vec3(1.0f, 1.0f, 1.0f), shad);
    setVec3("light.specular", Vec3(1.0f, 1.0f, 1.0f), shad);
    setVec3("ambCol", Vec3(0.1f, 0.1f, 0.1f), shad);

    if (things[ids].albedo != 1)
    {
      setFloat("texSize", 4.0f, shad);
    }
    else
    {
      setFloat("texSize", 1.0f, shad);
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, things[ids].albedo);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, things[ids].normalMap);

    Render();

    if (things[ids].deleted == true)
    {
      for (int real = ids + 1; real < numThings; real++)
      {
        things[real - 1] = things[real];
      }
      numThings -= 1;
      things = realloc(things, numThings * sizeof(Thing));
      ids -= 1;
    }
  }
}

void purgeThings()
{
  free(things);
}
