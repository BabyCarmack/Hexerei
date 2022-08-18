#include "Overlord.h"
#define GLEW_STATIC
#include <GLFW/glfw3.h>
#include <stdbool.h>

int bol = 0;
unsigned int borg;
int vidx = 1080;
int vidy = 720;
GLFWwindow* window;
unsigned int mainShad;
vec3 camPos;

//camera data
float yaw   = -90.0f;
float pitch =  0.0f;
float lastX =  800.0f / 2.0;
float lastY =  600.0 / 2.0;
float height = 3.0f;

bool firstMouse = true;
vec3 movPos;
vec3 camFront;
vec3 movementFront;
vec3 camRight;
vec3 movementRight;
vec3 camUp;

//callback for first-person mouse movement
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch -= yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    vec3 front;
    vec3 right;
    front.x = cos(radians(yaw)) * cos(radians(pitch));
    front.y = sin(radians(pitch));
    front.z = sin(radians(yaw)) * cos(radians(pitch));
    camFront = normalize(front);
    front.x = cos(radians(yaw));
    front.z = sin(radians(yaw));
    movementFront = normalize(front);

    right.x = -cos(radians(yaw + 90.0f)) * cos(radians(pitch));
    right.y = -sin(radians(pitch));
    right.z = -sin(radians(yaw + 90.0f)) * cos(radians(pitch));
    camRight = normalize(right);
    right.x = -cos(radians(yaw + 90.0f));
    right.z = -sin(radians(yaw + 90.0f));
    movementRight = normalize(right);
}

static void errormsg(int error, const char* msg) {
    printf("Error: %s\n", msg);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void resolution() {
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    vidx = mode->width;
    vidy = mode->height;
}

void loop()
{
  double firstFrame, lastFrame;
  while (!glfwWindowShouldClose(window))
  {
    matrix4 view = matrix4Ident(1.0f);
    matrix4 proj = matrix4Ident(1.0f);

    glfwPollEvents();
    glfwSwapBuffers(window);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    double currentFrame = glfwGetTime();
    if (bol == 0)
    {
      firstFrame = glfwGetTime();
      lastFrame = firstFrame;
      bol = 1;
    }
    //double delta = currentFrame - firstFrame;
    double deltaT = (currentFrame - lastFrame);
    lastFrame = currentFrame;

    resolution();
    glViewport(0, 0, vidx, vidy);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
      glfwSetWindowShouldClose(window, true);
      printf("Closing...\n");
      break;
    }

    float camSpeed = 10.0f;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
      camPos = sub(camPos, mult((float)deltaT * camSpeed, Vec3(movementFront.x, 0.0f, movementFront.z)));
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
      camPos = ad(camPos, mult((float)deltaT * camSpeed, Vec3(movementFront.x, 0.0f, movementFront.z)));
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
      camPos = sub(camPos, mult((float)deltaT * camSpeed, Vec3(movementRight.x, 0.0f, movementRight.z)));
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
      camPos = ad(camPos, mult((float)deltaT * camSpeed, Vec3(movementRight.x, 0.0f, movementRight.z)));
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
      camPos.y -= (float)deltaT * camSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
      camPos.y += (float)deltaT * camSpeed;
    }

    useShad(mainShad);
    view = lookAt(camPos, ad(camPos, camFront), camUp);
    proj = perspective(radians(90.0f), (float)vidx / (float)vidy, 0.01f, 1000.0f);

    setMat4("view", view, mainShad);
    setMat4("proj", proj, mainShad);
    setVec3("viewPos", camPos, mainShad);
    RenderStuff(mainShad, deltaT, camPos);
  }
}

void gameBackend(const char* windowName) {
    glfwInit();
    resolution();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_SAMPLES, 8);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(vidx, vidy, windowName, glfwGetPrimaryMonitor(), NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetErrorCallback(errormsg);

    if (!window) {
        printf("ERROR: Window %s failed to initialize.\n", windowName);
        glfwTerminate();
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD\n");
    }

    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);

    glfwSwapInterval(1);
    mainShad = makeShadNoGeo("shaders/vertex.glsl", "shaders/fragment.glsl");
    camPos = Vec3(0.0f, 3.0f, 0.0f);
    camFront = Vec3(0.0f, 0.0f, -1.0f);
    camUp = Vec3(0.0f, 1.0f, 0.0f);

    createWorld(mainShad);
    loop();
    purgeThings();
}
