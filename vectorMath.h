#ifndef VECTORMATH
#define VECTORMATH

#include <math.h>

typedef struct
{
  float x;
  float y;
  float z;
} vec3;

typedef struct
{
  float x;
  float y;
} vec2;

vec2 Vec2(float x, float y)
{
  vec2 vec;
  vec.x = x;
  vec.y = y;
  return vec;
};

vec3 Vec3(float x, float y, float z)
{
  vec3 vec;
  vec.x = x;
  vec.y = y;
  vec.z = z;
  return vec;
};

float radians(float deg)
{
  float pi = 3.14159f;
  float rad = deg * pi / 180;
  return rad;
}

float degrees(float rad)
{
  float pi = 3.14159f;
  float deg = rad * 180 / pi;
  return deg;
}

float clamp(float val, float min, float max)
{
  float out;
  if (val < min) out = min;
  if (val > max) out = max;
  if (val >= min && val <= max) out = val;
  return out;
}

vec3 normalize(vec3 bigAss)
{
  float length = sqrt((bigAss.x * bigAss.x) + (bigAss.y * bigAss.y) + (bigAss.z * bigAss.z));
  return Vec3(bigAss.x / length, bigAss.y / length, bigAss.z / length);
}

float normFlot(float bigAss)
{
  return 1 / bigAss;
}

vec2 normalize2(vec2 bigAss)
{
  float length = sqrt((bigAss.x * bigAss.x) + (bigAss.y * bigAss.y));
  return Vec2(bigAss.x / length, bigAss.y / length);
}

vec3 cross(vec3 a, vec3 b)
{
  vec3 c;
  c.x = (a.y * b.z) - (a.z * b.y);
  c.y = (a.z * b.x) - (a.x * b.z);
  c.z = (a.x * b.y) - (a.y * b.x);
  return c;
}

vec2 perp(vec2 a)
{
  vec2 c;
  c = Vec2(-a.y, a.x);
  return c;
}

vec3 mult(float f, vec3 vec)
{
  vec3 vector = vec;
  vector.x *= f;
  vector.y *= f;
  vector.z *= f;
  return vector;
}

vec3 divid(float f, vec3 vec)
{
  vec3 vector = vec;
  vector.x /= f;
  vector.y /= f;
  vector.z /= f;
  return vector;
}

float dot(vec3 a, vec3 b)
{
  float dot;
  dot = a.x * b.x + a.y * b.y + a.z * b.z;
  return dot;
}

vec3 ad(vec3 a, vec3 b)
{
  vec3 vector = a;
  vector.x += b.x;
  vector.y += b.y;
  vector.z += b.z;
  return vector;
}

vec3 sub(vec3 a, vec3 b)
{
  vec3 vector = a;
  vector.x = a.x - b.x;
  vector.y = a.y - b.y;
  vector.z = a.z - b.z;
  return vector;
}

#endif
