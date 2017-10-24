#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <boolean.h>
#include "Gfx #1.3.h"
#include "m64p_types.h"
#include "m64p_config.h"

static unsigned angrylion_filtering = 0;
static unsigned angrylion_dithering = 1;

#include "core/core.h"
#include "core/rdram.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define DP_INTERRUPT    0x20

static uint32_t rdram_size;
static uint8_t* rdram_hidden_bits;
static struct core_config config;

extern GFX_INFO gfx_info;

int ProcessDListShown = 0;

int retro_return(int just_flipping);

void plugin_init(void)
{
   rdram_size = 0x800000;

   // mupen64plus plugins can't access the hidden bits, so allocate it on our own
   rdram_hidden_bits = malloc(rdram_size);
   memset(rdram_hidden_bits, 3, rdram_size);
}

void plugin_sync_dp(void)
{
    *gfx_info.MI_INTR_REG |= DP_INTERRUPT;
    gfx_info.CheckInterrupts();
}

uint32_t** plugin_get_dp_registers(void)
{
    // HACK: this only works because the ordering of registers in GFX_INFO is
    // the same as in dp_register
    return (uint32_t**)&gfx_info.DPC_START_REG;
}

uint32_t** plugin_get_vi_registers(void)
{
    // HACK: this only works because the ordering of registers in GFX_INFO is
    // the same as in vi_register
    return (uint32_t**)&gfx_info.VI_STATUS_REG;
}

uint8_t* plugin_get_rdram(void)
{
    return gfx_info.RDRAM;
}

uint8_t* plugin_get_rdram_hidden(void)
{
    return rdram_hidden_bits;
}

uint32_t plugin_get_rdram_size(void)
{
    return rdram_size;
}

uint8_t* plugin_get_dmem(void)
{
    return gfx_info.DMEM;
}

uint8_t* plugin_get_rom_header(void)
{
    return gfx_info.HEADER;
}

void plugin_close(void)
{
    if (rdram_hidden_bits)
        free(rdram_hidden_bits);
    rdram_hidden_bits = NULL;
}

void angrylion_set_filtering(unsigned filter_type)
{
   angrylion_filtering = filter_type;
}

void angrylion_set_dithering(unsigned dither_type)
{
   angrylion_dithering = dither_type;
}

void angrylionChangeWindow (void)
{
}

void CloseDLL (void)
{
}

void angrylionReadScreen2(void *dest, int *width, int *height, int front)
{
}
 
void angrylionDrawScreen (void)
{
}

void angrylionGetDllInfo(PLUGIN_INFO* PluginInfo)
{
    PluginInfo -> Version = 0x0103;
    PluginInfo -> Type  = 2;
    strcpy(
    PluginInfo -> Name, "angrylion's RDP"
    );
    PluginInfo -> NormalMemory = true;
    PluginInfo -> MemoryBswaped = true;
}

void angrylionSetRenderingCallback(void (*callback)(int))
{
}

int angrylionInitiateGFX (GFX_INFO Gfx_Info)
{
   return 0;
}

 
void angrylionMoveScreen (int xpos, int ypos)
{
}

 
void angrylionProcessDList(void)
{
   if (!ProcessDListShown)
      ProcessDListShown = 1;
}

void angrylionProcessRDPList(void)
{
   core_dp_update();
}

void angrylionRomClosed (void)
{
   core_close();
}

static m64p_handle l_ConfigAngrylion;
 
int angrylionRomOpen(void)
{
   /* TODO/FIXME: For now just force it to 640x480.
    *
    * Later on we might want a low-res mode (320x240)
    * for better performance as well in case screen_width
    * is 320 and height is 240.
    */
	core_config_defaults(&config);
	config.parallel = true;
	config.num_workers = 0;
	config.vi.mode = 0;
	config.vi.widescreen = 0;
	config.vi.overscan = 1;

	core_init(&config);
   return 1;
}

void angrylionUpdateScreen(void)
{
    static int counter;

#ifdef HAVE_FRAMESKIP
    if (counter++ < skip)
        return;
    counter = 0;
#endif
    core_vi_update();
    retro_return(true);
}

void angrylionShowCFB (void)
{
    angrylionUpdateScreen();
}


void angrylionViStatusChanged (void)
{
}

void angrylionViWidthChanged (void)
{
}

void angrylionFBWrite(unsigned int addr, unsigned int size)
{
}

void angrylionFBRead(unsigned int addr)
{
}

void angrylionFBGetFrameBufferInfo(void *pinfo)
{
}

m64p_error angrylionPluginGetVersion(m64p_plugin_type *PluginType, int *PluginVersion, int *APIVersion, const char **PluginNamePtr, int *Capabilities)
{
   /* set version info */
   if (PluginType != NULL)
      *PluginType = M64PLUGIN_GFX;

   if (PluginVersion != NULL)
      *PluginVersion = 0x016304;

   if (APIVersion != NULL)
      *APIVersion = 0x020100;

   if (PluginNamePtr != NULL)
      *PluginNamePtr = "MAME/Angrylion/HatCat/ata4 video Plugin";

   if (Capabilities != NULL)
      *Capabilities = 0;

   return M64ERR_SUCCESS;
}

#define MSG_BUFFER_LEN 256
void msg_error(const char * err, ...)
{
}

void msg_warning(const char* err, ...)
{
}

void msg_debug(const char* err, ...)
{
}