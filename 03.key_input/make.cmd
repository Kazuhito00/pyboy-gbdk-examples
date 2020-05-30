c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o key_input.o key_input.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wl-yt2 -Wl-yo4 -Wl-ya4 -o key_input.gb key_input.o
MOVE key_input.gb ..\00.ROMs\03.key_input.gb
DEL key_input.lst key_input.map key_input.o key_input.sym