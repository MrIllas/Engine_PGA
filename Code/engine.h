//
// engine.h: This file contains the types and functions relative to the engine.
//

#pragma once

#include "platform.h"
#include "BufferSuppFuncs.h"
#include "ModelLoaderFuncs.h"

typedef glm::vec2  vec2;
typedef glm::vec3  vec3;
typedef glm::vec4  vec4;
typedef glm::ivec2 ivec2;
typedef glm::ivec3 ivec3;
typedef glm::ivec4 ivec4;

struct Image
{
    void* pixels;
    ivec2 size;
    i32   nchannels;
    i32   stride;
};

struct Texture
{
    GLuint      handle;
    std::string filepath;
};

struct Program
{
    GLuint             handle;
    std::string        filepath;
    std::string        programName;
    u64                lastWriteTimestamp; // What is this for?
    ModelLoader::VertexShaderLayout shaderLayout;
};

struct Model
{
    u32 meshIdx;
    std::vector<u32> materialIdx;
};

struct SubMesh
{
    ModelLoader::VertexBufferLayout vertexBufferLayout;
    std::vector<float> vertices;
    std::vector<u32> indices;
    u32 vertexOffset;
    u32 indexOffset;

    std::vector<ModelLoader::VAO> vaos;
};

struct Mesh
{
    std::vector<SubMesh> submeshes;
    GLuint vertexBufferHandle;
    GLuint indexBufferHandle;
};

struct Material
{
    std::string name;
    vec3 albedo;
    vec3 emissive;
    f32 smoothness;
    u32 albedoTextureIdx;
    u32 emissiveTextureIdx;
    u32 specularTextureIdx;
    u32 normalsTextureIdx;
    u32 bumpTextureIdx;
};

enum Mode
{
    Mode_TexturedQuad,
    Mode_Count
};

struct VertexV3V2
{
    glm::vec3 pos;
    glm::vec2 uv;
};

const VertexV3V2 vertices[] =
{
    {glm::vec3(-0.5, -0.5, 0.0), glm::vec2(0.0, 0.0)},
    {glm::vec3(0.5, -0.5, 0.0), glm::vec2(1.0, 0.0)},
    {glm::vec3(0.5, 0.5, 0.0), glm::vec2(1.0, 1.0)},
    {glm::vec3(-0.5, 0.5, 0.5), glm::vec2(0.0, 1.0)},
};

const u16 indicex[] =
{
    0, 1, 2,
    0, 2, 3
};

struct App
{
    /*
    App() : deltaTime(0.0f),
        isRunning(true)
    {

    }
    */

    // Loop
    f32  deltaTime;
    bool isRunning;

    // Input
    Input input;

    // Graphics
    char gpuName[64];
    char openGlVersion[64];
    std::string openGLDebugInfo;

    ivec2 displaySize;

    std::vector<Texture>  textures;
    std::vector<Material> materials;
    std::vector<Mesh> meshes;
    std::vector<Model> models;
    std::vector<Program>  programs;

    // program indices
    u32 texturedGeometryProgramIdx = 0;
    u32 texturedMeshProgramIdx = 0;
    
    u32 patricioModel = 0;
    GLuint texturedMeshProgram_uTexture = 0;
    
    

    // texture indices
    u32 diceTexIdx;
    u32 whiteTexIdx;
    u32 blackTexIdx;
    u32 normalTexIdx;
    u32 magentaTexIdx;

    // Mode
    Mode mode;

    // Embedded geometry (in-editor simple meshes such as
    // a screen filling quad, a cube, a sphere...)
    GLuint embeddedVertices;
    GLuint embeddedElements;

    // Location of the texture uniform in the textured quad shader
    GLuint programUniformTexture;

    // VAO object to link our screen filling quad with our textured quad shader
    GLuint vao;


};

void Init(App* app);

void Gui(App* app);

void Update(App* app);

void Render(App* app);