#include "vectors.h"
#include "transform.h"
#include "shapes.h"
#ifndef MESH_H
#define MESH_H

typedef struct LXGBone LXGBone;
typedef struct LXGMeshBoneBind LXGMeshBoneBind;
typedef struct LXGMeshVertex LXGMeshVertex;
typedef struct LXGMesh LXGMesh;
typedef struct LXGModel LXGModel;

typedef struct LXGModelRenderContext LXGModelRenderContext;

typedef void (LXGModelRenderContextModifier)(LXGModelRenderContext* ctx);

struct LXGBone {
   LXGTransform initTransform;
   LXGTransform transform;
   Mat4F offsetMatrix;
   int parent;
};

struct LXGMeshVertex {
   Vec3F position;
   Vec3F normal;
   Vec2F uv;
   Vec2F uv2;
};

struct LXGMeshBoneBind {
   int count;
   int* boneIds;
   float* boneWeights;
};

struct LXGMesh {
   LXGMeshVertex* initVertices;
   LXGMeshVertex* vertices;
   size_t verticesCount;
   int* indices;
   size_t indicesCount;
   int* boneIds;
   float* boneWeights;
   LXGMeshBoneBind* bounds;
   int textureId;
};

struct LXGModel {
   LXGMesh* meshes;
   size_t meshesCount;
   LXGBone* bones;
   size_t bonesCount;
};

struct LXGModelRenderContext {
   void* userdata;
   size_t textureId;
   LXGTrianglePainter* painter;
};

void lxg_mesh_apply_bones(LXGMesh* mesh, LXGBone* bones);
void lxg_model_apply_bones(LXGModel* model);

void lxg_bones_update(LXGBone* bones, size_t count);
void lxg_model_update_bones(LXGModel* model);

void lxg_mesh_render(LXGDrawCtx* ctx, LXGMesh* mesh, Mat4F matrix, LXGModelRenderContextModifier* modifier, void* userdata);
void lxg_model_render(LXGDrawCtx* ctx, LXGModel* model, Mat4F matrix, LXGModelRenderContextModifier* modifier, void* userdata);

#endif
