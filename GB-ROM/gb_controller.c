#include <gb/gb.h>
#include <stdint.h>
#include <stdio.h>

#include "tileset.h"
#include "tilemap.h"
#include "buttons.h"

volatile unsigned char joypad_value;


uint8_t i = 0;

/** Send byte but use external clock, slightly modified GBDK send_byte() function. */
void send_byte2() __naked
{
__asm
        XOR	A
        LD      (__io_status),A ; Store status = IO_IDLE
        XOR	A
        LDH     (2),A         ; Use external clock instead of internal
        LD      A,(_joypad_value)
//        LD      A,#0x01
        LDH     (1),A         ; Send data byte
        LD      A,#0x80
        LDH     (2),A         ; Use external clock instead of internal
        RET
__endasm;
}

/** receive byte use internal clock */
void read_byte2() __naked
{
__asm
        LD      A,#0x02		; //__IO_RECEIVING
        LD      (__io_status),A ; Store status
        LD	A,#0x01
        LDH     (2),A         ; Use internal clock
        LD      A,#0x11		; // DT_RECEIVING
        LDH     (1),A         ; Send RECEIVING byte
        LD      A,#0x81
        LDH     (2),A         ; Use internal clock
        RET
__endasm;

}



void serial_interrupt(void){
	joypad_value = joypad();
	send_byte2();
}




void main(void)
{


  int counter = 0;

  set_bkg_data(0, TILESET_TILE_COUNT, TILESET);
  set_bkg_tiles(0, 0, TILEMAP_WIDTH, TILEMAP_HEIGHT, TILEMAP);
  SHOW_BKG;


  set_sprite_data(0, 3, buttons);

  set_sprite_tile(0,0); // Start
  move_sprite(0,0x50,0x7f);
  scroll_sprite(0,0,-125);

  set_sprite_tile(1,0); // Select
  move_sprite(1,0x58,0x7f);
  scroll_sprite(1,0,-125);

  set_sprite_tile(2,1); // Left
  move_sprite(2,0x38,0x70);

  set_sprite_tile(3,1); // Right
  move_sprite(3,0x48,0x70);

  set_sprite_tile(4,1); // Up
  move_sprite(4,0x40,0x68);

  set_sprite_tile(5,1); // Down
  move_sprite(5,0x40,0x78);

  set_sprite_tile(6,2);  // ButtonB 1
  move_sprite(6,0x60,0x70);

  set_sprite_tile(7,2);
  set_sprite_prop(7,S_FLIPX); // ButtonB 2
  move_sprite(7,0x67,0x70);

  set_sprite_tile(8,2);
  set_sprite_prop(8,S_FLIPX | S_FLIPY); // ButtonB 3
  move_sprite(8,0x67,0x77);

  set_sprite_tile(9,2);
  set_sprite_prop(9,S_FLIPY); // ButtonB 4
  move_sprite(9,0x60,0x77);


  set_sprite_tile(10,2);  // ButtonA 1
  move_sprite(10,0x6D,0x66);

  set_sprite_tile(11,2);
  set_sprite_prop(11,S_FLIPX); // ButtonA 2
  move_sprite(11,0x74,0x66);

  set_sprite_tile(12,2);
  set_sprite_prop(12,S_FLIPX | S_FLIPY); // ButtonA 3
  move_sprite(12,0x74,0x6e);

  set_sprite_tile(13,2);
  set_sprite_prop(13,S_FLIPY); // ButtonA 4
  move_sprite(13,0x6c,0x6e);

  



//move_sprite(2,,);  
SHOW_SPRITES; 


int spriteID = 0;
int maxSpriteID = 13;


  CRITICAL {
        add_SIO(serial_interrupt);    // disable waiting VRAM state before return
        set_interrupts(VBL_IFLAG | SIO_IFLAG);      // disable other interrupts
      }


while (1){
	
	UINT8 keys = joypad();

	if (keys & J_SELECT)
		scroll_sprite(0,0,0x7f);
	if (keys & J_START)
		scroll_sprite(1,0,0x7f);
 	if (keys & J_LEFT)
		scroll_sprite(2,0,0x70);
	if (keys & J_RIGHT)
		scroll_sprite(3,0,0x70);
	if (keys & J_UP)
		scroll_sprite(4,0,0x68);
	if (keys & J_DOWN)
		scroll_sprite(5,0,0x78);
	if (keys & J_B){
		scroll_sprite(6,0,0x70);
		scroll_sprite(7,0,0x70);
		scroll_sprite(8,0,0x77);
		scroll_sprite(9,0,0x77);
		}
	if (keys & J_A){
		scroll_sprite(10,0,0x66);
		scroll_sprite(11,0,0x66);
		scroll_sprite(12,0,0x6e);
		scroll_sprite(13,0,0x6e);
		}

	wait_vbl_done();	

	for (UINT8 i=0; i<=maxSpriteID; i++){
		hide_sprite(i);
	}
}

}
