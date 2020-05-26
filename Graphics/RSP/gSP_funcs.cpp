#include "gSP_funcs.h"
#include "../plugin.h"

void GSPCombineMatrices(void)
{
	gln64gSPCombineMatrices();
}

void GSPDlistCount(uint32_t count, uint32_t v)
{
	gln64gSPDlistCount(count, v);
}

void GSPClipVertex(uint32_t v)
{
	gln64gSPClipVertex(v);
}

/* Loads a LookAt structure in the RSP for specular highlighting
 * and projection mapping.
 *
 * l             - The lookat structure address.
 */
void GSPLookAt(uint32_t l, uint32_t n)
{
	gln64gSPLookAt(l, n);
}

/* Loads one light structure to the RSP.
 *
 * l             - The pointer to the light structure.
 * n             - The light number that is replaced (1~8)
 */
void GSPLight(uint32_t l, int32_t n)
{
	gln64gSPLight(l, n);
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

void GSPLightColor(uint32_t lightNum, uint32_t packedColor )
{
	gln64gSPLightColor(lightNum, packedColor);
}

/* Loads the viewport projection parameters.
 *
 * v           - v is the segment address to the viewport
 *               structure "Vp".
 * */
void GSPViewport(uint32_t v)
{
	gln64gSPViewport(v);
}

void GSPForceMatrix(uint32_t mptr)
{
	gln64gSPForceMatrix(mptr);
}

extern "C" void GSPEndDisplayListC(void);

void GSPEndDisplayList(void)
{
   GSPEndDisplayListC();
}
