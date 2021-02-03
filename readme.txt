1. Nand BSP added
2. Include path setting added for BSP
3. main.c modified for Nand Flash test
4. uart.c modified for printf
5. stm32f4xx_hal_nand.h modifed along Attention of readme(WaveShare).txt 

---------------------------------------------------------------------

If you haven't created a project yet,

Creat Nand Flash STM32 Project from .ioc file

1. Launch STM32CudeIDE -> File -> New -> STM32 project from ~(.ioc)
2. “FSMC-NandFlash.ioc” file browse -> finish -> In pop-up window, click 'Download'(or 'Continue')
( + If click Download, need some time. )
( + Use migrate after test Nand Flash using obsolete firmware to upgrade the firmware to new version. )
3. In CubeMX debug config -> save -> regenerate a code
( If pop up a window, just click 'Continue' )
4. Move “.git” folder and other things of clone into STM32 project folder.
