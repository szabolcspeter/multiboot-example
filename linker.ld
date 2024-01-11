OUTPUT_FORMAT("elf32-i386")
ENTRY(start)
displ = 0x100000;
SECTIONS
{
  .text displ : AT(displ)
  {
    code = .;
    *(.text)
  }
  .data : AT(displ + (data - code))
  {
    data = .;
    *(.data)
  }
  .bss : AT(displ + (bss - code))
  {
    bss = .;
    *(.bss)
  }
}


