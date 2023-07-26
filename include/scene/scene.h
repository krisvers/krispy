#ifndef KRISPY_SCENE_SCENE_H
#define KRISPY_SCENE_SCENE_H

#include <krispy.h>
#include <scene/object.h>

#define SCENE_MAX_OBJECTS 256

typedef struct Scene {
    scene_object_t objects[SCENE_MAX_OBJECTS];
} scene_t;

#endif