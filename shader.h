#ifndef SHADER
#define SHADER

unsigned int ShaderID;
char vCode[5000];
char fCode[5000];

void checkCompileErrors(unsigned int shader, const char* type)
{
  int success;
  char infoLog[1024];
  if (strcmp(type, "PROGRAM") != 0)
  {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      glGetShaderInfoLog(shader, 1024, NULL, infoLog);
      printf("ERROR:SHADER_COMPILATION_ERROR of type: %s\n%s\n-- --------------------------------------------------- -- \n", type, infoLog);
    }
  }
  else
  {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success)
    {
      glGetProgramInfoLog(shader, 1024, NULL, infoLog);
      printf("ERROR:PROGRAM_LINKING_ERROR of type: %s\n%s\n-- --------------------------------------------------- -- \n", type, infoLog);
    }
  }
}

void preProcessIncludes(FILE* file, char* strin)
{
  char line[10000];

  int place = ftell(file);

  char* get = fgets(line, 10000, file);
  while (get != NULL)
  {
    if (strstr(line, ".glsl") != NULL)
    {
      line[strlen(line) - 1] = '\0';
      char source[10000] = "shaders/";
      strcat(source, line);

      FILE* secondaryFile;
      secondaryFile = fopen(source, "r");
      fread(line, 1, 10000, secondaryFile);
    }
    strcat(strin, line);
    place = ftell(file);
    get = fgets(line, 10000, file);
  }
}

unsigned int makeShadNoGeo(const char* vPath, const char* fPath)
{
    FILE* VSFile;
    FILE* FSFile;

    VSFile = fopen(vPath, "r");
    FSFile = fopen(fPath, "r");

    fseek(VSFile, 0, SEEK_SET);
    preProcessIncludes(VSFile, vCode);
    int size = sizeof(fCode);

    vCode[size] = '\0';

    fseek(FSFile, 0, SEEK_SET);
    preProcessIncludes(FSFile, fCode);
    size = sizeof(fCode);
    printf("%s\n", fCode);
    fCode[size] = '\0';

    const char* vShader = vCode;
    const char* fShader = fCode;

    int yeet;

    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShader, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &yeet);
    checkCompileErrors(vertex, "VERTEX");

    unsigned int frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &fShader, NULL);
    glCompileShader(frag);
    glGetShaderiv(frag, GL_COMPILE_STATUS, &yeet);
    checkCompileErrors(frag, "FRAGMENT");

    ShaderID = glCreateProgram();
    glAttachShader(ShaderID, vertex);
    glAttachShader(ShaderID, frag);
    glLinkProgram(ShaderID);
    checkCompileErrors(ShaderID, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(frag);

    fclose(VSFile);
    fclose(FSFile);
    return ShaderID;
}

void useShad(unsigned int ShadID)
{
  ShaderID = ShadID;
  glUseProgram(ShadID);
}
void setInt(const char* name, int value, unsigned int id)
{
  glUniform1i(glGetUniformLocation(id, name), value);
}
void setFloat(const char* name, float value, unsigned int id)
{
  glUniform1f(glGetUniformLocation(id, name), value);
}
void setMat4(const char* name, matrix4 gorg, unsigned int id) {
  glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, gorg.array);
}
void setVec3(const char* name, vec3 value, unsigned int id)
{
  glUniform3f(glGetUniformLocation(id, name), value.x, value.y, value.z);
}
void setVec2(const char* name, vec2 value, unsigned int id)
{
  glUniform2f(glGetUniformLocation(id, name), value.x, value.y);
}

#endif
