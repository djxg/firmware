/*
 *****************************************************************************
 **
 **  File        : linker_stm32f10x_md.ld
 **
 **  Abstract    : Linker script for STM32F103CB Device with
 **                128KByte FLASH, 20KByte RAM
 **
 **                Set heap size, stack size and stack location according
 **                to application requirements.
 **
 **                Set memory bank area and size if external memory is used.
 **
 **  Target      : STMicroelectronics STM32
 **
 **  Environment : Eclipse-CDT and GNU Tools ARM Embedded.
 **
 *****************************************************************************
 */

/* default stack sizes.

These are used by the startup in order to allocate stacks for the different modes.
 */

__Stack_Size = 2048 ;

/* PROVIDE ( _Stack_Size = __Stack_Size ) ; */

__Stack_Init = _estack - __Stack_Size ;

/*"PROVIDE" allows to easily override these values from an object file or the commmand line.*/
/* PROVIDE ( _Stack_Init = __Stack_Init ) ; */

/*
There will be a link error if there is not this amount of RAM free at the end.
 */
_Minimum_Stack_Size = 0x200 ;

/* include the memory spaces definitions sub-script */
/*
Linker subscript for STM32F10x definitions with 128K Flash and 20K RAM */

/* Memory Spaces Definitions */

MEMORY
{
    SRAM (xrw)        : ORIGIN = 0x20000000, LENGTH = 20K
    APP_FLASH (rx)    : ORIGIN = 0x08000000, LENGTH = 20K
}

INCLUDE linker_stm32f103xb_common.ld
