c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o draw_figure.o draw_figure.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wl-yt2 -Wl-yo4 -Wl-ya4 -o draw_figure.gb draw_figure.o
MOVE draw_figure.gb ..\00.ROMs\02.draw_figure.gb
DEL draw_figure.lst draw_figure.map draw_figure.o draw_figure.sym