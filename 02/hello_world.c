#include <stdio.h>
#include <string.h>
#include <gb/gb.h>
#include <gb/drawing.h>
#include <gb/console.h>

// メイン処理
int main(void)
{
    UBYTE index;

    // Hello World
    gotoxy(0, 0);
    printf("Hello World\n");
    
    // コード指定での表示
    gotoxy(0, 2);
    for(index = 1; index < 0xFF; index++){
        printf("%c", index);
    }
}
