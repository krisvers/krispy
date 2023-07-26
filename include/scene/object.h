#ifndef KRISPY_SCENE_OBJECT_H
#define KRISPY_SCENE_OBJECT_H

#include <krispy.h>

#define SCENE_OBJECT_MAX_ATTRIBUTES 16

typedef struct SceneObjectAttribute {
    union attr {
        u8 u8;
        u16 u16;
        u32 u32;
        u64 u64;
        i8 i8;
        i16 i16;
        i32 i32;
        i64 i64;
        f32 f32;
        f64 f64;
        void * ptr;
    };
} scene_object_attribute_t;

struct SceneObject;
typedef struct SceneObject {
    f32 position[3];
    f32 rotation[3];
    f32 scale[3];
    struct SceneObject * child;
    scene_object_attribute_t attributes[SCENE_OBJECT_MAX_ATTRIBUTES];
} scene_object_t;

#endif