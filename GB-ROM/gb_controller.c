#include <gb/gb.h>
#include <stdint.h>
#include <stdio.h>


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

  puts("gb_controller v0.1");

  CRITICAL {
        add_SIO(serial_interrupt);    // disable waiting VRAM state before return
        set_interrupts(VBL_IFLAG | SIO_IFLAG);      // disable other interrupts
      }

}


