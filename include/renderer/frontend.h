#ifndef KRISPY_RENDERER_FRONTEND_H
#define KRISPY_RENDERER_FRONTEND_H

#include <krispy.h>
#include <kapi.h>
#include <renderer/packet.h>

typedef enum RendererFrontendSuccessEnum {
    RENDERER_FRONTEND_DEINITIALIZATION_ERROR = -1,
    RENDERER_FRONTEND_INITIALIZATION_ERROR = -1,
    RENDERER_FRONTEND_SUCCESS = 0,
} renderer_frontend_success_enum;

renderer_frontend_success_enum renderer_init(void);
renderer_frontend_success_enum renderer_draw(renderer_packet_t * packet);
renderer_frontend_success_enum renderer_deinit(void);

#endif
