c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o hello_world.o hello_world.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wl-yt2 -Wl-yo4 -Wl-ya4 -o hello_world.gb hello_world.o
MOVE hello_world.gb ..\00.ROMs\01.hello_world.gb
DEL hello_world.lst hello_world.map hello_world.o hello_world.sym