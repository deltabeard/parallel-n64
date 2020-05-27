#ifndef _3DMATH_H
#define _3DMATH_H

#ifdef __cplusplus
extern "C" {
#endif

enum gfx_plugin_type
{
#if HAVE_GLIDE64
   GFX_GLIDE64 = 0
#else
   GFX_GLN64 = 0
#endif
};

enum rsp_plugin_type
{
   RSP_HLE = 0,
};

extern enum gfx_plugin_type gfx_plugin;

#ifdef __cplusplus
}
#endif

#endif
