# OV7670-Driver-Experimental
Experimental Driver for OmniVision 7670 Camera

This driver not uses the hardware I2C device but use a bit-bang version of I2C protocol adapted to work as SCCB protocol.
The clock generation is made using the oscillator clock, divided by 5. A DCMI Interface is connected to the camera pinout
and a DMA transfer data from DCMI to the RAM. Data transfered are then transfered to the PC with a serial connection.

The Pinout is inside of the driver module.

EmbeddedHub
