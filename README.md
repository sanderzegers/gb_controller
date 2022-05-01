### PoC Gameboy USB Controller

Use a gameboy classic or gameboy advance as an USB Controller on a computer.

<p align="center">
<img src="https://github.com/sanderzegers/gb_controller/blob/main/images/gameboy_pocket.png" alt="Gameboy Pocket connected to Attiny85" width="350">
<img src="https://github.com/sanderzegers/gb_controller/blob/main/images/Animation.gif" alt="Windows Gamepad" width="350">
</p>


The arduino is pulling the gameboy joystick input via gamelink cable.

I tried to use the SPI functionality on the Arduino first. 
But this didn't seem to work very well in combination with the DigiJoystick Library. 
The control got out of sync after a while.

So now the Arduino just emulates the SPI Master in software by pulsing the clock manually.



## Hardware

- DigiSpark ATtiny85
- Krikkz EverDrive GB X3 (Flash Cartridge)
- Gameboy (Classic/Color/Pocket/Advance)
- Gameboy Link Cable

Cable connection:

<p align="center">
<img src="https://github.com/sanderzegers/gb_controller/blob/main/images/connections.png" alt="Windows Gamepad">
</p>


Point of view is the cable connector.
You might have to swap SOUT and SIN connection. Depending on which side of the cable is connected to the gameboy.


Link cable connection

```
Plug 1         Plug 2  
 SI ______  ______SI  
 SO ______><______SO  
 GND_____________GND  
 SD               SD  
 SC _____________ SC  
 Shield_______Shield  
```


