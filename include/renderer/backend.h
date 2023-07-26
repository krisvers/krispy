#ifndef KRISPY_RENDERER_BACKEND_H
#define KRISPY_RENDERER_BACKEND_H

#include <krispy.h>
#include <renderer/packet.h>

typedef enum RendererBackendSuccessEnum {
    RENDERER_BACKEND_PREPARE_ERROR = -4,
    RENDERER_BACKEND_INVALID_PACKET_ERROR = -3,
    RENDERER_BACKEND_DRAW_ERROR = -2,
    RENDERER_BACKEND_INITIALIZATION_ERROR = -1,
    RENDERER_BACKEND_SUCCESS = 0,
} renderer_backend_success_enum;

struct RendererBackend;
typedef renderer_backend_success_enum (*renderer_backend_init_callback)(struct RendererBackend * backend);
typedef renderer_backend_success_enum (*renderer_backend_prepare_callback)(struct RendererBackend * backend, renderer_packet_t * packet);
typedef renderer_backend_success_enum (*renderer_backend_draw_callback)(struct RendererBackend * backend, renderer_packet_t * packet);
typedef renderer_backend_success_enum (*renderer_backend_deinit_callback)(struct RendererBackend * backend);

typedef struct RendererBackend {
    renderer_backend_init_callback init;
    renderer_backend_prepare_callback prepare;
    renderer_backend_draw_callback draw;
    renderer_backend_deinit_callback deinit;
} renderer_backend_t;

#endif