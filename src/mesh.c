#include "mesh.h"

void lxg_mesh_apply_bones(LXGMesh* mesh, LXGBone* bones) {
   if (!mesh->bounds) return;
   for (size_t i = 0; i < mesh->verticesCount; i++) {
      LXGMeshBoneBind bind = mesh->bounds[i];
      Vec3F position = mesh->initVertices[i].position;
      Vec3F normal = mesh->initVertices[i].normal;
      Vec3F aPos = {0};
      Vec3F aNorm = {0};
      float totalWeight = 0;
      for (size_t j = 0; j < bind.count; j++) {
         float weight = bind.boneWeights[j];
         if (weight == 0) continue;
         Mat4F boneMatrix = bones[bind.boneIds[j]].offsetMatrix;
         Vec4F mulPosition = mat4f_mul_vec(vec3f_aug(position, 1.f), boneMatrix);
         Vec4F mulNormal = mat4f_mul_vec(vec3f_aug(normal, 0.f), mat4f_transpose(mat4f_inverse(boneMatrix)));
         aPos = vec3f_add(aPos, vec3f_mul(vec4f_deaug(mulPosition), vec3fn(weight)));
         aNorm = vec3f_add(aNorm, vec3f_mul(vec4f_deaug(mulNormal), vec3fn(weight)));
         totalWeight += weight;
      }
      if (totalWeight < 1) {
         float remaining = 1.f - totalWeight;
         aPos = vec3f_add(aPos, vec3f_mul(position, vec3fn(remaining)));
         aNorm = vec3f_add(aNorm, vec3f_mul(normal, vec3fn(remaining)));
      }
      mesh->vertices[i].position = aPos;
      mesh->vertices[i].normal = aNorm;
   }
}

void lxg_model_apply_bones(LXGModel* model) {
   for (size_t i = 0; i < model->meshesCount; i++) {
      lxg_mesh_apply_bones(&model->meshes[i], model->bones);
   }
}

void lxg_bones_update(LXGBone* bones, size_t count) {
   for (size_t i = 0; i < count; i++) {
      LXGBone* bone = &bones[i];
      Mat4F initMat = lxg_transform_get_matrix(bone->initTransform);
      Mat4F currMat = lxg_transform_get_matrix(bone->transform);
      Mat4F inverse = mat4f_inverse(initMat);
      bone->offsetMatrix = mat4f_mul(inverse, currMat);
   }
}

void lxg_model_update_bones(LXGModel* model) {
   lxg_bones_update(model->bones, model->bonesCount);
}

void lxg_mesh_render(LXGDrawCtx* ctx, LXGMesh* mesh, Mat4F matrix, LXGModelRenderContextModifier* modifier, void* userdata) {

}

void lxg_model_render(LXGDrawCtx* ctx, LXGModel* model, Mat4F matrix, LXGModelRenderContextModifier* modifier, void* userdata) {
   
}
