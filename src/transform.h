#include "matrices.h"

#ifndef TRANSFORM_H
#define TRANSFORM_H

typedef struct LXGTransform LXGTransform;

struct LXGTransform {
   Vec3F position;
   Vec3F rotation;
   Vec3F scale;
};

Mat4F lxg_transform_get_matrix(LXGTransform transform);

#endif
