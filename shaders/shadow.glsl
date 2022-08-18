/*vec3 gridSamplingDisk[20] = vec3[]
(
   vec3(1, 1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1, 1,  1),
   vec3(1, 1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
   vec3(1, 1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1, 1,  0),
   vec3(1, 0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1, 0, -1),
   vec3(0, 1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0, 1, -1)
);

float Shadow() {
  float cosTheta = dot(normie, lightDeg);
  float bias = max(0.05 * (1.0 - dot(normie, lightDeg)), 0.005);

  vec3 fragToLight = fragPos - light.position;
  float currentDepth = length(fragToLight);
  float shadow = 0.0;
  int samples = 20;
  float viewDistance = length(viewPos - fragPos);
  float diskRadius = (1.0 + (viewDistance / far_plane)) / 30.0;
  for(int i = 0; i < samples; ++i) {
    float closestDepth = texture(depthMap, fragToLight + gridSamplingDisk[i] * diskRadius).r;
    closestDepth *= far_plane;
    if(currentDepth - bias > closestDepth)
      shadow += 1.0;
  }
  shadow /= float(samples);
  return shadow;
}*/
