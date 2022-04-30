#CC	= ../../../bin/lcc -Wa-l -Wl-m -Wl-j
CC	= /opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j

BINS	= gb_controller.gb

all:	#$(BINS)
	$(CC) -o $(BINS) gb_controller.c tilemap.c tileset.c buttons.c

make.bat: Makefile
	@echo "REM Automatically generated from Makefile" > make.bat
	@make -sn | sed y/\\//\\\\/ | grep -v make >> make.bat

# Compile and link single file in one pass
%.gb:	%.c
	$(CC) -o $@ $<

clean:
	rm -f *.o *.lst *.map *.gb *~ *.rel *.cdb *.ihx *.lnk *.sym *.asm *.noi

