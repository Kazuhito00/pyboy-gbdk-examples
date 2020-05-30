#include <stdio.h>
#include <string.h>
#include <gb/gb.h>
#include <gb/drawing.h>
#include <gb/console.h>

// メイン処理
int main(void)
{
    /* ボタン種類 | ボタン定数 | 値    */
    /*------------|------------|-------*/
    /* START      | J_START    | 0x80U */
    /* SELECT     | J_SELECT   | 0x40U */
    /* B          | J_B        | 0x20U */
    /* A          | J_A        | 0x10U */
    /* 下         | J_DOWN     | 0x08U */
    /* 上         | J_UP       | 0x04U */
    /* 左         | J_LEFT     | 0x02U */
    /* 右         | J_RIGHT    | 0x01U */

    UBYTE key;

    while(1) {
        waitpad(0xFF);                /* ボタンが押されるまで待つ */
        key = joypad();               /* 押下ボタンを取得する     */
        waitpadup();                  /* ボタンが放されるまで待つ */

        gotoxy(0, 0);

        if (key & J_START) {
            printf("KEY:START ");
        }
        if (key & J_SELECT) {
            printf("KEY:SELECT");
        }
        if (key & J_UP) {
            printf("KEY:UP    ");
        }
        if (key & J_DOWN) {
            printf("KEY:DOWN  ");
        }
        if (key & J_LEFT) {
            printf("KEY:LEFT  ");
        }
        if (key & J_RIGHT) {
            printf("KEY:RIGHT ");
        }
        if (key & J_A) {
            printf("KEY:A     ");
        }
        if (key & J_B) {
            printf("KEY:B     ");
        }

        delay(10);
    }
}
