#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <chrono>
#include <ctime>
#include <iomanip>
#include "lodepng.h"

struct v3{
    float x,y,z;
    v3(float x, float y, float z){
        this->x=x;
        this->y=y;
        this->z=z;
    }
    v3(){
        this->x=0;
        this->y=0;
        this->z=0;
    }
};

v3 c(int a, int b, int c){
    v3 v = v3();
    v.x = a/255.;
    v.y = b/255.;
    v.z = c/255.;
    return v;
}

#define NUM_COLORS 204
static const v3 colors[NUM_COLORS] = {c(89, 125, 39), c(109, 153, 48), c(127, 178, 56), c(67, 94, 29), c(174, 164, 115), c(213, 201, 140), c(247, 233, 163), c(130, 123, 86), c(140, 140, 140), c(171, 171, 171), c(199, 199, 199), c(105, 105, 105), c(180, 0, 0), c(220, 0, 0), c(255, 0, 0), c(135, 0, 0), c(112, 112, 180), c(138, 138, 220), c(160, 160, 255), c(84, 84, 135), c(117, 117, 117), c(144, 144, 144), c(167, 167, 167), c(88, 88, 88), c(0, 87, 0), c(0, 106, 0), c(0, 124, 0), c(0, 65, 0), c(180, 180, 180), c(220, 220, 220), c(255, 255, 255), c(135, 135, 135), c(115, 118, 129), c(141, 144, 158), c(164, 168, 184), c(86, 88, 97), c(106, 76, 54), c(130, 94, 66), c(151, 109, 77), c(79, 57, 40), c(79, 79, 79), c(96, 96, 96), c(112, 112, 112), c(59, 59, 59), c(45, 45, 180), c(55, 55, 220), c(64, 64, 255), c(33, 33, 135), c(100, 84, 50), c(123, 102, 62), c(143, 119, 72), c(75, 63, 38), c(180, 177, 172), c(220, 217, 211), c(255, 252, 245), c(135, 133, 129), c(152, 89, 36), c(186, 109, 44), c(216, 127, 51), c(114, 67, 27), c(125, 53, 152), c(153, 65, 186), c(178, 76, 216), c(94, 40, 114), c(72, 108, 152), c(88, 132, 186), c(102, 153, 216), c(54, 81, 114), c(161, 161, 36), c(197, 197, 44), c(229, 229, 51), c(121, 121, 27), c(89, 144, 17), c(109, 176, 21), c(127, 204, 25), c(67, 108, 13), c(170, 89, 116), c(208, 109, 142), c(242, 127, 165), c(128, 67, 87), c(53, 53, 53), c(65, 65, 65), c(76, 76, 76), c(40, 40, 40), c(108, 108, 108), c(132, 132, 132), c(153, 153, 153), c(81, 81, 81), c(53, 89, 108), c(65, 109, 132), c(76, 127, 153), c(40, 67, 81), c(89, 44, 125), c(109, 54, 153), c(127, 63, 178), c(67, 33, 94), c(36, 53, 125), c(44, 65, 153), c(51, 76, 178), c(27, 40, 94), c(72, 53, 36), c(88, 65, 44), c(102, 76, 51), c(54, 40, 27), c(72, 89, 36), c(88, 109, 44), c(102, 127, 51), c(54, 67, 27), c(108, 36, 36), c(132, 44, 44), c(153, 51, 51), c(81, 27, 27), c(17, 17, 17), c(21, 21, 21), c(25, 25, 25), c(13, 13, 13), c(176, 168, 54), c(215, 205, 66), c(250, 238, 77), c(132, 126, 40), c(64, 154, 150), c(79, 188, 183), c(92, 219, 213), c(48, 115, 112), c(52, 90, 180), c(63, 110, 220), c(74, 128, 255), c(39, 67, 135), c(0, 153, 40), c(0, 187, 50), c(0, 217, 58), c(0, 114, 30), c(91, 60, 34), c(111, 74, 42), c(129, 86, 49), c(68, 45, 25), c(79, 1, 0), c(96, 1, 0), c(112, 2, 0), c(59, 1, 0), c(147, 124, 113), c(180, 152, 138), c(209, 177, 161), c(110, 93, 85), c(112, 57, 25), c(137, 70, 31), c(159, 82, 36), c(84, 43, 19), c(105, 61, 76), c(128, 75, 93), c(149, 87, 108), c(78, 46, 57), c(79, 76, 97), c(96, 93, 119), c(112, 108, 138), c(59, 57, 73), c(131, 93, 25), c(160, 114, 31), c(186, 133, 36), c(98, 70, 19), c(72, 82, 37), c(88, 100, 45), c(103, 117, 53), c(54, 61, 28), c(112, 54, 55), c(138, 66, 67), c(160, 77, 78), c(84, 40, 41), c(40, 28, 24), c(49, 35, 30), c(57, 41, 35), c(30, 21, 18), c(95, 75, 69), c(116, 92, 84), c(135, 107, 98), c(71, 56, 51), c(61, 64, 64), c(75, 79, 79), c(87, 92, 92), c(46, 48, 48), c(86, 51, 62), c(105, 62, 75), c(122, 73, 88), c(64, 38, 46), c(53, 43, 64), c(65, 53, 79), c(76, 62, 92), c(40, 32, 48), c(53, 35, 24), c(65, 43, 30), c(76, 50, 35), c(40, 26, 18), c(53, 57, 29), c(65, 70, 36), c(76, 82, 42), c(40, 43, 22), c(100, 42, 32), c(122, 51, 39), c(142, 60, 46), c(75, 31, 24), c(26, 15, 11), c(31, 18, 13), c(37, 22, 16), c(19, 11, 8)};

#define PI 3.14159265359
static v3 toxyz(v3 src){
    float r = src.x, g = src.y, b = src.z, x, y, z;
    r = (r > 0.04045) ? pow((r + 0.055) / 1.055, 2.4) : r / 12.92;
    g = (g > 0.04045) ? pow((g + 0.055) / 1.055, 2.4) : g / 12.92;
    b = (b > 0.04045) ? pow((b + 0.055) / 1.055, 2.4) : b / 12.92;
    x = (r * 0.4124 + g * 0.3576 + b * 0.1805) / 0.95047;
    y = (r * 0.2126 + g * 0.7152 + b * 0.0722) / 1.00000;
    z = (r * 0.0193 + g * 0.1192 + b * 0.9505) / 1.08883;
    return v3(x,y,z);
}

static v3 todin(v3 src){
    float r = src.x, g = src.y, b = src.z, x, y, z;
    r = (r > 0.04045) ? pow((r + 0.055) / 1.055, 2.4) : r / 12.92;
    g = (g > 0.04045) ? pow((g + 0.055) / 1.055, 2.4) : g / 12.92;
    b = (b > 0.04045) ? pow((b + 0.055) / 1.055, 2.4) : b / 12.92;
    x = (r * 0.4124 + g * 0.3576 + b * 0.1805) / 0.95047;
    y = (r * 0.2126 + g * 0.7152 + b * 0.0722) / 1.00000;
    z = (r * 0.0193 + g * 0.1192 + b * 0.9505) / 1.08883;
    v3 lab;
    x = (x > 0.008856) ? pow(x, 1./3.) : (7.787 * x) + 16./116.;
    y = (y > 0.008856) ? pow(y, 1./3.) : (7.787 * y) + 16./116.;
    z = (z > 0.008856) ? pow(z, 1./3.) : (7.787 * z) + 16./116.;
    lab.x = 116*y - 16;
    lab.y = 500*(x-y);
    lab.z = 200*(y-z);
    float L99 = 105.51 * log(1+0.0158*lab.x);
    float e99 = lab.y*cos(16*PI/180)+lab.z*sin(16*PI/180);
    float f = 0.7*(-lab.y*sin(16*PI/180)+lab.z*cos(16*PI/180));
    float G = sqrt(e99*e99+f*f);
    float k=log(1+0.045*G)/0.045;
    float a99 = k*e99/G;
    float b99 = k*f/G;
    return v3(L99, a99, b99);
}

static void copyColorsToBufXYZ(float* dst){
    for(int i = 0; i < NUM_COLORS; i++){
        v3 res = toxyz(colors[i]);
        dst[3*i+0] = res.x;
        dst[3*i+1] = res.y;
        dst[3*i+2] = res.z;
    }
}


static void copyColorsToBufDIN(float* dst){
    for(int i = 0; i < NUM_COLORS; i++){
        v3 res = todin(colors[i]);
        dst[3*i+0] = res.x;
        dst[3*i+1] = res.y;
        dst[3*i+2] = res.z;
    }
}

static const EGLint configAttribs[] = {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
        EGL_NONE
};

static const EGLint contextConfig[] = {
        EGL_CONTEXT_MAJOR_VERSION, 4,
        EGL_CONTEXT_MINOR_VERSION, 5,
//        EGL_CONTEXT_FLAGS_KHR, EGL_CONTEXT_OPENGL_DEBUG_BIT_KHR | EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR,
        EGL_NONE
};

void printEGLError(){
    switch (eglGetError()){
        case EGL_SUCCESS: return;
        case EGL_NOT_INITIALIZED:
            std::cout << "EGL_NOT_INITIALIZED" << std::endl;
            break;
        case EGL_BAD_ACCESS:
            std::cout << "EGL_BAD_ACCESS" << std::endl;
            break;
        case EGL_BAD_ALLOC:
            std::cout << "EGL_BAD_ALLOC" << std::endl;
            break;
        case EGL_BAD_ATTRIBUTE:
            std::cout << "EGL_BAD_ATTRIBUTE" << std::endl;
            break;
        case EGL_BAD_CONTEXT:
            std::cout << "EGL_BAD_CONTEXT" << std::endl;
            break;
        case EGL_BAD_CONFIG:
            std::cout << "EGL_BAD_CONFIG" << std::endl;
            break;
        case EGL_BAD_CURRENT_SURFACE:
            std::cout << "EGL_BAD_CURRENT_SURFACE" << std::endl;
            break;
        case EGL_BAD_DISPLAY:
            std::cout << "EGL_BAD_DISPLAY" << std::endl;
            break;
        case EGL_BAD_SURFACE:
            std::cout << "EGL_BAD_SURFACE" << std::endl;
            break;
        case EGL_BAD_MATCH:
            std::cout << "EGL_BAD_MATCH" << std::endl;
            break;
        case EGL_BAD_PARAMETER:
            std::cout << "EGL_BAD_PARAMETER" << std::endl;
            break;
        case EGL_BAD_NATIVE_PIXMAP:
            std::cout << "EGL_BAD_NATIVE_PIXMAP" << std::endl;
            break;
        case EGL_BAD_NATIVE_WINDOW:
            std::cout << "EGL_BAD_NATIVE_WINDOW" << std::endl;
            break;
        case EGL_CONTEXT_LOST:
            std::cout << "EGL_CONTEXT_LOST" << std::endl;
            break;
        default:
            std::cout << "Unknown error "<<eglGetError()<<std::endl;
            break;
    }
}

void debugMessageReceived(GLenum src, GLenum type, GLuint id, GLenum sev, GLsizei len, const GLchar* msg, const void* ignore){
    std::ostringstream oss;
    oss << "GL Debug: [";
    switch(src){
        case GL_DEBUG_SOURCE_API:
            oss << "API";
            break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            oss << "WINDOW_SYSTEM";
            break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            oss << "SHADER_COMPILER";
            break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            oss << "THIRD_PARTY";
            break;
        case  GL_DEBUG_SOURCE_APPLICATION:
            oss << "APPLICATION";
            break;
        case GL_DEBUG_SOURCE_OTHER:
            oss << "OTHER";
            break;
        default:
            oss << src;
    }
    oss << "][";
    switch(type){
        case GL_DEBUG_TYPE_ERROR:
            oss << "ERROR";
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            oss << "DEPRECATED_BEHAVIOR";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            oss << "UNDEFINED_BEHAVIOR";
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            oss << "PORTABILITY";
            break;
        case  GL_DEBUG_TYPE_PERFORMANCE:
            oss << "PERFORMANCE";
            break;
        case GL_DEBUG_TYPE_MARKER:
            oss << "MARKER";
            break;
        case GL_DEBUG_TYPE_PUSH_GROUP:
            oss << "PUSH_GROUP";
            break;
        case  GL_DEBUG_TYPE_POP_GROUP:
            oss << "POP_GROUP";
            break;
        case  GL_DEBUG_TYPE_OTHER:
            oss << "OTHER";
            break;
        default:
            oss << src;
    }
    oss << "][";
    switch(sev){
        case GL_DEBUG_SEVERITY_LOW:
            oss << "LOW";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            oss << "MEDIUM";
            break;
        case GL_DEBUG_SEVERITY_HIGH:
            oss << "HIGH";
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            oss << "NOTIFICATION";
            break;
        default:
            oss << src;
    }
    oss << "] "<<msg;
    if(len < 2 || msg[len-2] != '\n') oss << '\n';
    std::cout << oss.str() <<std::flush;
}

GLuint createShader(GLenum type, std::string fn){
    GLuint shader = glCreateShader(type);
    auto file = std::ifstream(fn, std::ios::binary | std::ios::ate);
    int size = file.tellg();
    file.seekg(0, std::ios::beg);
    char* data = new char[size];
    file.read(data, size);
    glShaderSource(shader, 1, &data, &size);
    glCompileShader(shader);
    delete[] data;
    GLint isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
        std::cout << "Shader "<<fn<<" failed to compile!"<<std::endl;
        std::cout << errorLog.data() << std::endl;
        glDeleteShader(shader); // Don't leak the shader.
        return 0;
    }
    return shader;
}

GLuint createProgram(GLuint vertexShader, GLuint fragmentShader){
    if(vertexShader == 0 || fragmentShader == 0) return 0;

    GLuint program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);
    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
        std::cout << "Program linking error: "<<infoLog.data()<<std::endl;
        glDeleteProgram(program);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return 0;
    }
    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);
    return program;
}

std::string glTypeToString(GLenum type)
{
    switch (type)
    {
        case GL_FLOAT: return "GL_FLOAT";
        case GL_FLOAT_VEC2: return "GL_FLOAT_VEC2";
        case GL_FLOAT_VEC3: return "GL_FLOAT_VEC3";
        case GL_FLOAT_VEC4: return "GL_FLOAT_VEC4";
        case GL_FLOAT_MAT2: return "GL_FLOAT_MAT2";
        case GL_FLOAT_MAT3: return "GL_FLOAT_MAT3";
        case GL_FLOAT_MAT4: return "GL_FLOAT_MAT4";
        case GL_FLOAT_MAT2x3: return "GL_FLOAT_MAT2x3";
        case GL_FLOAT_MAT2x4: return "GL_FLOAT_MAT2x4";
        case GL_FLOAT_MAT3x2: return "GL_FLOAT_MAT3x2";
        case GL_FLOAT_MAT3x4: return "GL_FLOAT_MAT3x4";
        case GL_FLOAT_MAT4x2: return "GL_FLOAT_MAT4x2";
        case GL_FLOAT_MAT4x3: return "GL_FLOAT_MAT4x3";
        case GL_INT: return "GL_INT";
        case GL_INT_VEC2: return "GL_INT_VEC2";
        case GL_INT_VEC3: return "GL_INT_VEC3";
        case GL_INT_VEC4: return "GL_INT_VEC4";
        case GL_UNSIGNED_INT: return "GL_UNSIGNED_INT";
        case GL_UNSIGNED_INT_VEC2: return "GL_UNSIGNED_INT_VEC2";
        case GL_UNSIGNED_INT_VEC3: return "GL_UNSIGNED_INT_VEC3";
        case GL_UNSIGNED_INT_VEC4: return "GL_UNSIGNED_INT_VEC4";
        case GL_DOUBLE: return "GL_DOUBLE";
        case GL_DOUBLE_VEC2: return "GL_DOUBLE_VEC2";
        case GL_DOUBLE_VEC3: return "GL_DOUBLE_VEC3";
        case GL_DOUBLE_VEC4: return "GL_DOUBLE_VEC4";
        case GL_DOUBLE_MAT2: return "GL_DOUBLE_MAT2";
        case GL_DOUBLE_MAT3: return "GL_DOUBLE_MAT3";
        case GL_DOUBLE_MAT4: return "GL_DOUBLE_MAT4";
        case GL_DOUBLE_MAT2x3: return "GL_DOUBLE_MAT2x3";
        case GL_DOUBLE_MAT2x4: return "GL_DOUBLE_MAT2x4";
        case GL_DOUBLE_MAT3x2: return "GL_DOUBLE_MAT3x2";
        case GL_DOUBLE_MAT3x4: return "GL_DOUBLE_MAT3x4";
        case GL_DOUBLE_MAT4x2: return "GL_DOUBLE_MAT4x2";
        case GL_DOUBLE_MAT4x3: return "GL_DOUBLE_MAT4x3";

        default: return "Not a GLSL shader type";
    }
}

struct triangle{
    float invm[3][4];
    GLuint vert1, vert2, vert3;
    float edgl;
};

struct pyramid{
    float invm[3][4];
    GLuint vert1, vert2, vert3, vert4;
    float edgl;
    char buff[12];
};

static const float quad[] = {
        -1., -1., 0., 0.,
        -1., +1., 0., 1.,
        +1., +1., 1., 1.,
        +1., +1., 1., 1.,
        +1., -1., 1., 0.,
        -1., -1., 0., 0.,
};

float readfloat(void* data){
    char rd[4];
    rd[0] = reinterpret_cast<char*>(data)[3];
    rd[1] = reinterpret_cast<char*>(data)[2];
    rd[2] = reinterpret_cast<char*>(data)[1];
    rd[3] = reinterpret_cast<char*>(data)[0];

    return *(reinterpret_cast<float*>(rd));
}

int main(){
//    auto eglGetPlatformDisplayEXT =
//            (PFNEGLGETPLATFORMDISPLAYEXTPROC)
//                    eglGetProcAddress("eglGetPlatformDisplayEXT");
//
//    EGLDisplay display= eglGetPlatformDisplayEXT(EGL_PLATFORM_DEVICE_EXT,
//                                      EGL_DEFAULT_DISPLAY, nullptr);
////    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
//    if(display == EGL_NO_DISPLAY){
//        std::cout << "No display!" << std::endl;
//        printEGLError();
//        return 0;
//    }
//    std::cout << "Got display" << std::endl;
//    EGLint major, minor;
//    eglInitialize(display, &major, &minor);
//    std::cout << "Version: "<<major<<"."<<minor << std::endl;
//    std::cout << "Vendor: "<<eglQueryString(display, EGL_VENDOR) << std::endl;
//    std::cout << "Client APIs: "<<eglQueryString(display, EGL_CLIENT_APIS) << std::endl;
//    std::cout << "Extensions: "<<eglQueryString(display, EGL_EXTENSIONS) << std::endl;
//    EGLint numConfigs;
//    EGLConfig conf;
//    eglChooseConfig(display, configAttribs, &conf, 1, &numConfigs);
//    std::cout << "Got "<<numConfigs<<" configs!"<<std::endl;
//    eglBindAPI(EGL_OPENGL_API);
//    EGLContext ctx = eglCreateContext(display, conf, EGL_NO_CONTEXT, contextConfig);
//    if(ctx == EGL_NO_CONTEXT){
//        std::cout << "Failed to create context!" << std::endl;
//        printEGLError();
//        return 0;
//    }
//    if(!eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, ctx)){
//        printEGLError();
//        return 0;
//    }
    int argc = 1;
    const char thingy[] = "dummy";
    char* argv = static_cast<char*> (malloc(sizeof(thingy)));
    memcpy(argv, thingy, sizeof(thingy));
    glutInit(&argc, &argv);
    free(argv);
    glutInitContextVersion (4, 5);
    glutInitContextFlags (GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);
    int window = glutCreateWindow("Palettegen - don't touch this!");
    GLenum err = glewInit();
    if(err != GLEW_OK && err != GLEW_ERROR_NO_GLX_DISPLAY){
        std::cout << "GLEW error: "<<glewGetErrorString(err) <<" ("<<err<<")"<< std::endl;
    }
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(&debugMessageReceived, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, true);
    glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_OTHER, 0x1234, GL_DEBUG_SEVERITY_NOTIFICATION, 13, "Debug Works!");
    const char *vstr = reinterpret_cast<const char *>(glGetString(GL_VENDOR));
    std::string ss(vstr);
    if(ss != "NVIDIA Corporation"){
        std::cout << "Use NVidia, not "<<ss<<"!"<<std::endl;
        return 0;
    }
    std::cout << "OpenGL version: "<<glGetString(GL_VERSION)<<std::endl;
    std::cout << "OpenGL vendor: "<<glGetString(GL_VENDOR)<<std::endl;
    std::cout << "OpenGL renderer: "<<glGetString(GL_RENDERER)<<std::endl;
    std::cout << "OpenGL SL version: "<<glGetString(GL_SHADING_LANGUAGE_VERSION)<<std::endl;
    glDisable(GL_DITHER);
    auto prog = createProgram(createShader(GL_VERTEX_SHADER, "vert.glsl"), createShader(GL_FRAGMENT_SHADER, "frag.glsl"));
    if(prog == 0)
        return 0;
    GLuint fb;
    glGenFramebuffers(1, &fb);
    glBindFramebuffer(GL_FRAMEBUFFER, fb);
    GLuint dstBuf[2];
    glGenRenderbuffers(2, dstBuf);
    glBindRenderbuffer(GL_RENDERBUFFER, dstBuf[0]);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8UI, 256, 256);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, dstBuf[0]);
    glBindRenderbuffer(GL_RENDERBUFFER, dstBuf[1]);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8UI, 256, 256);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_RENDERBUFFER, dstBuf[1]);
    GLenum dbuf[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
    glDrawBuffers(2, dbuf);
    glBindFramebuffer(GL_FRAMEBUFFER, fb);
    glViewport(0,0,256,256);
    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), reinterpret_cast<void *>(2 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glUseProgram(prog);


    GLint indices[3];
    indices[0] = glGetProgramResourceIndex(prog, GL_SHADER_STORAGE_BLOCK, "edges");
    indices[1] = glGetProgramResourceIndex(prog, GL_SHADER_STORAGE_BLOCK, "tris");
    indices[2] = glGetProgramResourceIndex(prog, GL_SHADER_STORAGE_BLOCK, "pyras");
    for(int ci = 0; ci < 3; ci++) {
        GLint nav;
        GLenum props_nav[] = {GL_NUM_ACTIVE_VARIABLES};
        GLenum props_avi[] = {GL_ACTIVE_VARIABLES};
        GLenum props_acp[] = {GL_NAME_LENGTH, GL_TYPE, GL_OFFSET, GL_ARRAY_STRIDE, GL_TOP_LEVEL_ARRAY_SIZE,
                              GL_TOP_LEVEL_ARRAY_STRIDE, GL_MATRIX_STRIDE, GL_IS_ROW_MAJOR};
        GLint len, lenb;
        glGetProgramResourceiv(prog, GL_SHADER_STORAGE_BLOCK, indices[ci], 1, props_nav, 1, &len, &nav);
        GLint *indi = new int[nav];
        glGetProgramResourceiv(prog, GL_SHADER_STORAGE_BLOCK, indices[ci], 1, props_avi, nav, &len, indi);
        for (int i = 0; i < len; i++) {
            GLint values[8];
            glGetProgramResourceiv(prog, GL_BUFFER_VARIABLE, indi[i], 8, props_acp, 8, &lenb, values);
            char *name = new char[values[0]];
            glGetProgramResourceName(prog, GL_BUFFER_VARIABLE, indi[i], values[0], nullptr, name);
            std::cout << "Variable " << i << ": " << name << " : " << glTypeToString(values[1]) << " - offset "
                      << values[2] << " - stride " << values[3] << " - TLoffset " << values[4] << " - TLstride "
                      << values[5] << " - matrix stride "<<values[6] << " - "<<(values[7]?"":"not ") << "row-major"<<std::endl;
            delete[](name);
        }
        delete[] indi;
    }

    std::cout << "Triangle struct size: "<<sizeof(triangle)<<std::endl;
    std::cout << "Triangle invm offset: "<<offsetof(triangle, invm)<<std::endl;
    std::cout << "Triangle vertices offset: "<<offsetof(triangle, vert1)<<std::endl;
    std::cout << "Triangle edgl offset: "<<offsetof(triangle, edgl)<<std::endl;
    std::cout << "Pyramid struct size: "<<sizeof(pyramid)<<std::endl;
    std::cout << "Pyramid invm offset: "<<offsetof(pyramid, invm)<<std::endl;
    std::cout << "Pyramid vertices offset: "<<offsetof(pyramid, vert1)<<std::endl;
    std::cout << "Pyramid edgl offset: "<<offsetof(pyramid, edgl)<<std::endl;


    auto fd = new float[204*3];
    copyColorsToBufDIN(fd);
    glUniform3fv(glGetUniformLocation(prog, "dinpal"), 204, fd);
    copyColorsToBufXYZ(fd);
    glUniform3fv(glGetUniformLocation(prog, "xyzpal"), 204, fd);
    delete[] fd;
    GLuint blueUni = glGetUniformLocation(prog, "blue");
    FILE* fin = fopen("out.data", "rb");
    unsigned char buffer[80];
    GLuint ssbos[3];
    glGenBuffers(3, ssbos);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbos[0]);
    fread(buffer, 4, 1, fin);
    int num = (unsigned int)buffer[3] | (unsigned int)buffer[2]<<8u | (unsigned int)buffer[1]<<16u | (unsigned int)buffer[0]<<24u;
    int* linedata = new int[2*num];
    std::cout << "Lines: "<<num<<std::endl;
    for(int i = 0; i < num; i++){
        fread(buffer, 2, 1, fin);
        linedata[2*i] = buffer[0];
        linedata[2*i+1] = buffer[1];
    }
    glBufferData(GL_SHADER_STORAGE_BUFFER, 8*num, linedata, GL_STATIC_COPY);
    delete[] linedata;
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, ssbos[0]);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbos[1]);
    fread(buffer, 4, 1, fin);
    num = (unsigned int)buffer[3] | (unsigned int)buffer[2]<<8u | (unsigned int)buffer[1]<<16u | (unsigned int)buffer[0]<<24u;
    std::cout << "Triangles: "<<num<<", requiring "<<(sizeof(triangle)*num) << " bytes"<<std::endl;
    auto* tridata = new triangle[num];
    for(int i = 0; i < num; i++){
        triangle* ctri = &tridata[i];
        fread(buffer, 44, 1, fin);
        ctri -> vert1 = buffer[0];
        ctri -> vert2 = buffer[1];
        ctri -> vert3 = buffer[2];
        ctri -> edgl = readfloat(&buffer[4]);
        for(int y = 0; y < 3; y++)
            for(int x = 0; x < 3; x++){
                ctri -> invm[y][x] = readfloat(&buffer[8+4*(3*y+x)]);
            }
    }
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(triangle)*num, tridata, GL_STATIC_COPY);
    delete[] tridata;
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, ssbos[1]);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbos[2]);


    fread(buffer, 4, 1, fin);
    num = (unsigned int)buffer[3] | (unsigned int)buffer[2]<<8u | (unsigned int)buffer[1]<<16u | (unsigned int)buffer[0]<<24u;
    std::cout << "Pyramids: "<<num<<", requiring "<<(sizeof(pyramid)*num) << " bytes"<<std::endl;
    auto* pydata = new pyramid[num];
    for(int i = 0; i < num; i++){
        pyramid* ctri = &pydata[i];
        fread(buffer, 44, 1, fin);
        ctri -> vert1 = buffer[0];
        ctri -> vert2 = buffer[1];
        ctri -> vert3 = buffer[2];
        ctri -> vert4 = buffer[3];
        ctri -> edgl = readfloat(&buffer[4]);
        for(int y = 0; y < 3; y++)
            for(int x = 0; x < 3; x++){
                ctri -> invm[y][x] = readfloat(&buffer[8+4*(3*y+x)]);
            }
    }
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(pyramid)*num, pydata, GL_STATIC_COPY);
    delete[] pydata;
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, ssbos[2]);

    auto data = new GLubyte[256*256*256*8];
    GLubyte* datap;
    auto start = std::chrono::system_clock::now();
    auto renderstart = std::chrono::system_clock::now();
    for(int b = 0; b < 256; b++){
        glUniform1f(blueUni, b/255.);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glFlush();
        datap = data + 4*(b+256*(b+256*b));
        glReadBuffer(GL_COLOR_ATTACHMENT0);
        glReadPixels(0,0,256,256,GL_RGBA_INTEGER,GL_UNSIGNED_BYTE, &data[256*256*b*8]);
        glReadBuffer(GL_COLOR_ATTACHMENT1);
        glReadPixels(0,0,256,256,GL_RGBA_INTEGER,GL_UNSIGNED_BYTE, &data[256*256*(b+256)*4]);
//        std::cout<<"Pixel ("<<b<<","<<b<<","<<b<<"): ("<<+datap[0]<<", "<<+datap[1]<<", "<<+datap[2]<<", "<<+datap[3]<<", "<<+datap[256*256*256*4+0]<<", "<<+datap[256*256*256*4+1]<<", "<<+datap[256*256*256*4+2]<<", "<<+datap[256*256*256*4+3]<<")"<<std::endl;
//        unsigned int p1 = datap[0]-4, p2 = datap[1]-4, p3 = datap[2]-4, p4 = datap[3]-4;
//        if(p1 >= 0 && p1 <= 204)  std::cout << "Palette 1: "<< colors[p1].x*255<<" "<< colors[p1].y*255<<" "<< colors[p1].z*255<<std::endl;
//        if(p2 >= 0 && p2 <= 204)  std::cout << "Palette 2: "<< colors[p2].x*255<<" "<< colors[p2].y*255<<" "<< colors[p2].z*255<<std::endl;
//        if(p3 >= 0 && p3 <= 204)  std::cout << "Palette 3: "<< colors[p3].x*255<<" "<< colors[p3].y*255<<" "<< colors[p3].z*255<<std::endl;
//        if(p4 >= 0 && p4 <= 204)  std::cout << "Palette 4: "<< colors[p4].x*255<<" "<< colors[p4].y*255<<" "<< colors[p4].z*255<<std::endl;
//        std::cout << "x < "<< +datap[256*256*256*4+0] <<" => A | x < " << +datap[256*256*256*4+1] <<" => B | x < " << +datap[256*256*256*4+2] << " => C | _ => D"<<std::endl;
//        std::cout << "LABDIN: "<<+datap[256*256*256*4+1]<<", "<<+datap[256*256*256*4+2]-100<<", "<<+datap[256*256*256*4+3]-100<<std::endl;
//        auto ss = std::ostringstream();
//        ss << "partimgs/img"<<b<<".png";
//        lodepng::encode(ss.str(), datap, 256, 256);
//if(b==1) return 5;
        auto renderend = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_secondsss = renderend-start;
        std::chrono::duration<double> elapsed_seconds = renderend-renderstart;
        renderstart = std::chrono::system_clock::now();
        float done=(b+1)/256., rem=1.-done;
        double trem = (elapsed_secondsss.count()*(rem/done));
        int hrem = ((int)trem)/3600;
        int mrem = ((int)trem) / 60 % 60;
        double srem = fmod(trem, 60.);
        std::cout << "Current iteration "<<b<<" took "<<elapsed_seconds.count()<<", total done: "<<elapsed_secondsss.count()<<", total rem: "<<hrem<<":"<<mrem<<":"<<srem<<std::endl;

        std::stringstream lss;
        lss << std::setw(3) << std::setfill('0') << b;
        std::string cit = lss.str();
        auto file = std::fstream("palparts/palA"+cit+".bin", std::ios::out | std::ios::binary);
        file.write(reinterpret_cast<char *>(&data[256*256*b*8]), 256 * 256 * 4);
        file.flush();
        file.close();
        file = std::fstream("palparts/palB"+cit+".bin", std::ios::out | std::ios::binary);
        file.write(reinterpret_cast<char *>(&data[256*256*(b+256)*4]), 256 * 256 * 4);
        file.flush();
        file.close();
    }

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::cout << "finished computation at " << std::ctime(&end_time) << "elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
    auto file = std::fstream("palette.bin", std::ios::out | std::ios::binary);
    file.write(reinterpret_cast<char *>(data), 256 * 256 * 256 * 8);
    file.flush();
    file.close();
//    eglTerminate(display);
}