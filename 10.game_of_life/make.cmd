c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o game_of_life.o game_of_life.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wl-yt2 -Wl-yo4 -Wl-ya4 -o game_of_life.gb game_of_life.o
MOVE game_of_life.gb ..\00.ROMs\10.game_of_life.gb
DEL game_of_life.lst game_of_life.map game_of_life.o game_of_life.sym