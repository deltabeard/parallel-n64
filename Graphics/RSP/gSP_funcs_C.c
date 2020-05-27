#include "gSP_funcs_C.h"
#include "../plugin.h"
#include "../RSP/RSP_state.h"

void GSPCombineMatricesC(void)
{
   switch (gfx_plugin)
   {
#if HAVE_GLIDE64
      case GFX_GLIDE64:
         glide64gSPCombineMatrices();
         break;
#endif
#if HAVE_GLN64
      case GFX_GLN64:
         gln64gSPCombineMatrices();
         break;
#endif
   }
}

void GSPClipVertexC(uint32_t v)
{
   switch (gfx_plugin)
   {
#if HAVE_GLIDE64
      case GFX_GLIDE64:
         glide64gSPClipVertex(v);
         break;
#endif
#if HAVE_GLN64
      case GFX_GLN64:
         gln64gSPClipVertex(v);
         break;
#endif
   }
}

/* Loads a LookAt structure in the RSP for specular highlighting
 * and projection mapping.
 *
 * l             - The lookat structure address.
 */
void GSPLookAtC(uint32_t l, uint32_t n)
{
   switch (gfx_plugin)
   {
#if HAVE_GLIDE64
      case GFX_GLIDE64:
         glide64gSPLookAt(l, n);
         break;
#endif
#if HAVE_GLN64
      case GFX_GLN64:
         gln64gSPLookAt(l, n);
         break;
#endif
   }
}

/* Loads one light structure to the RSP.
 *
 * l             - The pointer to the light structure.
 * n             - The light number that is replaced (1~8)
 */
void GSPLightC(uint32_t l, int32_t n)
{
   switch (gfx_plugin)
   {
#if HAVE_GLIDE64
      case GFX_GLIDE64:
         glide64gSPLight(l, n);
         break;
#endif
#if HAVE_GLN64
      case GFX_GLN64:
         gln64gSPLight(l, n);
#endif
   }
}

/* Quickly changes the light color in the RSP.
 *
 * lightNum     - The light number whose color is being modified:
 *                LIGHT_1 (First light)
 *                LIGHT_2 (Second light)
 *                :
 *                LIGHT_u (Eighth light)
 *
 * packedColor - The new light color (32-bit value 0xRRGGBB??)
 *               (?? is ignored)
 * */

void GSPLightColorC(uint32_t lightNum, uint32_t packedColor )
{
   switch (gfx_plugin)
   {
#if HAVE_GLIDE64
      case GFX_GLIDE64:
         glide64gSPLightColor(lightNum, packedColor);
         break;
#endif
#if HAVE_GLN64
      case GFX_GLN64:
         gln64gSPLightColor(lightNum, packedColor);
         break;
#endif
   }
}

/* Loads the viewport projection parameters.
 *
 * v           - v is the segment address to the viewport
 *               structure "Vp".
 * */
void GSPViewportC(uint32_t v)
{
   switch (gfx_plugin)
   {
#ifdef HAVE_GLIDE64
      case GFX_GLIDE64:
         glide64gSPViewport(v);
         break;
#endif
#if HAVE_GLN64
      case GFX_GLN64:
         gln64gSPViewport(v);
         break;
#endif
   }
}

void GSPForceMatrixC(uint32_t mptr)
{
   switch (gfx_plugin)
   {
#ifdef HAVE_GLIDE64
      case GFX_GLIDE64:
         glide64gSPForceMatrix(mptr);
         break;
#endif
#if HAVE_GLN64
      case GFX_GLN64:
         gln64gSPForceMatrix(mptr);
         break;
#endif
   }
}

void GSPEndDisplayListC(void)
{
   if (__RSP.PCi > 0)
      __RSP.PCi --;
   else
   {
      /* Halt execution here */
      __RSP.halt = 1;
   }
}
