#ifndef TRANSFORM_H
#define TRANSFORM_H

typedef struct Transform Transform;

struct Transform {
   Vec3F position;
   Vec3F rotation;
   Vec3F scale;
};

Mat4F lxg_transform_get_matrix(Transform transform);

#endif
