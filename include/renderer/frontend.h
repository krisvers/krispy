#ifndef KRISPY_RENDERER_FRONTEND_H
#define KRISPY_RENDERER_FRONTEND_H

#include <krispy.h>
#include <kapi.h>

typedef struct RenderPacket {
    f64 delta_time;
} render_packet_t;

KAPI b8 renderer_init(void);
KAPI void renderer_deinit(void);

#endif
