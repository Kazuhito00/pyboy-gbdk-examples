#include <stdio.h>
#include <string.h>
#include <gb/gb.h>
#include <gb/drawing.h>
#include <gb/console.h>

// メイン処理
int main(void)
{
    UBYTE x1, y1;
    UBYTE x2, y2;
    UBYTE radius;

    // 円描画
    x1 = 10;
    y1 = 10;
    radius = 10;
    color(BLACK, WHITE, SOLID);
    circle(x1, y1, radius, M_FILL);
    
    x1 = 30;
    y1 = 10;
    radius = 10;
    color(DKGREY, WHITE, SOLID);
    circle(x1, y1, radius, M_FILL);
    
    x1 = 50;
    y1 = 10;
    radius = 10;
    color(LTGREY, WHITE, SOLID);
    circle(x1, y1, radius, M_FILL);
    
    x1 = 70;
    y1 = 10;
    radius = 10;
    color(BLACK, WHITE, SOLID);
    circle(x1, y1, radius, M_NOFILL);
    
    x1 = 10;
    y1 = 30;
    radius = 10;
    color(BLACK, WHITE, SOLID);
    circle(x1, y1, radius, M_FILL);

    x1 = 20;
    y1 = 30;
    radius = 10;
    color(BLACK, WHITE, OR);
    circle(x1, y1, radius, M_FILL);
    
    x1 = 40;
    y1 = 30;
    radius = 10;
    color(BLACK, WHITE, SOLID);
    circle(x1, y1, radius, M_FILL);

    x1 = 50;
    y1 = 30;
    radius = 10;
    color(BLACK, WHITE, XOR);
    circle(x1, y1, radius, M_FILL);

    // 線描画
    x1 = 5;
    y1 = 50;
    x2 = 155;
    y2 = 50;
    color(BLACK, WHITE, SOLID);
    line(x1, y1, x2, y2);
    
    x1 = 5;
    y1 = 55;
    x2 = 155;
    y2 = 55;
    color(DKGREY, WHITE, SOLID);
    line(x1, y1, x2, y2);
    
    x1 = 5;
    y1 = 60;
    x2 = 155;
    y2 = 60;
    color(LTGREY, WHITE, SOLID);
    line(x1, y1, x2, y2);

    x1 = 5;
    y1 = 45;
    x2 = 155;
    y2 = 65;
    color(DKGREY, WHITE, SOLID);
    line(x1, y1, x2, y2);

    // 矩形描画
    x1 = 5;
    y1 = 70;
    x2 = 155;
    y2 = 90;
    color(BLACK, BLACK, SOLID);
    box(x1, y1, x2, y2, M_FILL);

    x1 = 5;
    y1 = 95;
    x2 = 155;
    y2 = 115;
    color(BLACK, DKGREY, SOLID);
    box(x1, y1, x2, y2, M_FILL);

    x1 = 5;
    y1 = 120;
    x2 = 155;
    y2 = 140;
    color(LTGREY, WHITE, SOLID);
    box(x1, y1, x2, y2, M_NOFILL);
}
