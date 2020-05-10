#include <stdio.h>
#include <rand.h>
#include <gb/gb.h>
#include <gb/console.h>

// メイン処理
int main(void)
{
    UBYTE index;
    UBYTE random_value;

    index = 0;
    random_value = 0;

    // Hello World
    gotoxy(0, 0);
    printf("Hello World\n");
    
    // コード指定での表示
    gotoxy(0, 1);
    for(index = 1; index < 0xFF; index++){
        printf("%c", index);
    }

    // 数値表示
    initarand(42);  // 乱数シード初期化
    random_value = rand();

    gotoxy(0, 15);
    printf("%u\n", random_value);
}
