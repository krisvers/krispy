#ifndef KRISPY_RENDERER_RENDER_MESH_H
#define KRISPY_RENDERER_RENDER_MESH_H

#include <krispy.h>

typedef struct RenderMesh {
    f32 position[3];
    f32 rotation[3];
    f32 scale[3];
    /* dynamic array of vertex positions (x, y, z) */
    f32 * vertices[3];
    u64 vertex_count;
    /* dynamic array of vertex indices (v0, v1, v2) */
    u32 * indices[3];
    u64 index_count;
    /* 1-based index, 0 represents no texture */
    u64 texture_id;
} render_mesh_t;

typedef enum RenderMeshSuccessEnum {

} render_mesh_success_enum;

#endif