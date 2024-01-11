
#include "screen.h"

struct multiboot_info
{
  unsigned int   flags;
  unsigned int   low_memory;
  unsigned int   high_memory;
  unsigned int   boot_device;
  unsigned int   kernel_param_string;
};


void kmain(struct multiboot_info* pinfo, unsigned int ID)
{
  int var = 0;
  void* ptr = pinfo;
  if (ID == 0x2badb002)
  {
    putf("Kernel loaded by Grub boot loader.\n\n");
    putf("Total memory: %u KB\n", pinfo->high_memory + pinfo->low_memory);
    putf("  - Low memory : %u KB\n", pinfo->low_memory);
    putf("  - Hihg memory: %u KB\n", pinfo->high_memory);
    putf("\nKernel parameters: %s\n", pinfo->kernel_param_string);
    var = pinfo->flags & 0x2;
    if (var == 0x2)
    {
      putf("\nBoot device: 0x%x\n", 0xFF & (*((char*)ptr+15)) );
      /*var = 0;
      var = pinfo->boot_device & 0xff000000;
      putf("\nBoot device: 0x%x, 0x%x\n", var, (var >> 24) & 0x000000ff);*/
    }
  } else
  {
    putf("Kernel loaded.");
  }
  
  
  return;
}
