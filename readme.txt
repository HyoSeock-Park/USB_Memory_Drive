1. Launch STM32CudeIDE -> File -> New -> STM32 project from ~(.ioc)
2. “FSMC-NandFlash.ioc” file browse -> finish -> In pop-up window, click 'Download'(or 'Continue')
( + If click Download, need some time. )
( + Use migrate after test Nand Flash using obsolete firmware to upgrade the firmware to new version. )
3. In CubeMX debug config -> save -> regenerate a code
( If pop up a window, just click 'Continue' )
4. Move “.git” folder of clone into STM32 project folder. 
5. Go to the next commit ( “Use obsolete version firmware to test Nand Flash” )
