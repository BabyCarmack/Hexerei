#include "vectorMath.h"
#include <math.h>

typedef struct
{
  float array[16];
} matrix4;

typedef struct
{
  float array[9];
} matrix3;

matrix4 matrix4Ident()
{
  matrix4 mat;
  mat.array[0] = 1.0f;
  mat.array[1] = 0.0f;
  mat.array[2] = 0.0f;
  mat.array[3] = 0.0f;
  mat.array[4] = 0.0f;
  mat.array[5] = 1.0f;
  mat.array[6] = 0.0f;
  mat.array[7] = 0.0f;
  mat.array[8] = 0.0f;
  mat.array[9] = 0.0f;
  mat.array[10] = 1.0f;
  mat.array[11] = 0.0f;
  mat.array[12] = 0.0f;
  mat.array[13] = 0.0f;
  mat.array[14] = 0.0f;
  mat.array[15] = 1.0f;
  return mat;
}

matrix4 translate(matrix4 inMat, vec3 invec)
{
  matrix4 out = inMat;
  out.array[12] = invec.x;
  out.array[13] = invec.y;
  out.array[14] = invec.z;
  return out;
}

matrix4 scale(matrix4 inMat, vec3 invec)
{
  matrix4 out = inMat;
  out.array[0] *= invec.x;
  out.array[5] *= invec.y;
  out.array[10] *= invec.z;
  return out;
}

vec3 mat3Vec(matrix3 inMat, vec3 inVec)
{
  vec3 outvec = Vec3(inMat.array[0] * inVec.x + inMat.array[1] * inVec.y + inMat.array[2] * inVec.z,
    inMat.array[3] * inVec.x + inMat.array[4] * inVec.y + inMat.array[5] * inVec.z,
    inMat.array[6] * inVec.x + inMat.array[7] * inVec.y + inMat.array[8] * inVec.z);
  return outvec;
}

matrix4 perspective(float fov, float aspectRat, float zNear, float zFar)
{
  if (zNear == zFar)
  {
    printf("Your near clip and far clip are the same wtf\n");
    return matrix4Ident();
  }
  if (aspectRat == 0.f)
  {
    printf("Dude... your aspect ratio is 0.\n");
    return matrix4Ident();
  }

  const float rad = fov;
  const float tanHalfFov = tan(rad / 2.0f);

  matrix4 out = matrix4Ident();
  out.array[0] = 1.0f / (aspectRat * tanHalfFov);
  out.array[5] = 1.0f / tanHalfFov;
  out.array[10] = -(zFar + zNear) / (zFar - zNear);
  out.array[11] = -1.0f;
  out.array[14] = -(2.0f * zFar * zNear) / (zFar - zNear);

  return out;
}

matrix4 lookAt(vec3 eye, vec3 center, vec3 up)
{
  matrix4 mat;
  vec3 x, y, z;

  z = normalize(sub(center, eye));
  x = normalize(cross(up, z));
  y = cross(z, x);

  mat.array[0] = x.x;
  mat.array[1] = y.x;
  mat.array[2] = z.x;
  mat.array[3] = 0.0f;
  mat.array[4] = x.y;
  mat.array[5] = y.y;
  mat.array[6] = z.y;
  mat.array[7] = 0.0f;
  mat.array[8] = x.z;
  mat.array[9] = y.z;
  mat.array[10] = z.z;
  mat.array[11] = 0.0f;
  mat.array[12] = -dot(x, eye);
  mat.array[13] = -dot(y, eye);
  mat.array[14] = -dot(z, eye);
  mat.array[15] = 1.0f;

  return mat;
}
