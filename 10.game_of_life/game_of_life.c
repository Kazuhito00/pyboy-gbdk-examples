#include <stdio.h>
#include <string.h>
#include <rand.h>
#include <gb/gb.h>
#include <gb/drawing.h>
#include <gb/console.h>

// 盤面描画用定数
#define SQUARE_SIDE_LEN (10)    // マス目の１辺のピクセル数
#define X_MAX (160)             // GBの画面横幅：最大ピクセル数
#define X_POINT_MAX (X_MAX-1)
#define X_SQUARE_NUM ((UBYTE)((X_MAX / SQUARE_SIDE_LEN) - 1))  // マス目の横最大数
#define Y_MAX (144)             // GBの画面縦幅：最大ピクセル数
#define Y_POINT_MAX (Y_MAX-1)
#define Y_SQUARE_NUM ((UBYTE)((Y_MAX / SQUARE_SIDE_LEN) - 1))  // マス目の縦最大数
#define SQUARE_OFFSET_X (4)
#define SQUARE_OFFSET_Y (6)

// ゲーム状態
typedef enum {
    SETTING_MODE,
    GAME_MODE,
    NONE
} GameState;
// キー押下状態
typedef enum {
    KEY_UP,
    KEY_DOWN
} KeyState;
// マス目状態
typedef enum {
    ALIVE,
    DEAD,
    CURSOR,
    DEBUG
} SquareType;

// 状態遷移テーブル
#define GAME_STATE_NUM (2)
#define KEY_NUM (8 + 1)
UBYTE g_game_state_transition[GAME_STATE_NUM][KEY_NUM] = {
//                  NONE,     RIGHT     LEFT      UP        DOWN      A         B         SELECT        START
/* SETTING_MODE */ {NONE,     NONE,     NONE,     NONE,     NONE,     NONE,     NONE,     NONE,         GAME_MODE},
/* GAME_MODE    */ {NONE,     NONE,     NONE,     NONE,     NONE,     NONE,     NONE,     SETTING_MODE, NONE}
};

// 盤面状態保持用変数
UBYTE preboard[Y_SQUARE_NUM][X_SQUARE_NUM];
UBYTE board[Y_SQUARE_NUM][X_SQUARE_NUM];

// プロトタイプ宣言
void init(UBYTE*, UBYTE*);
void reset_board(UBYTE*);
UBYTE draw_square(UBYTE, UBYTE, SquareType);
UBYTE draw_board(UBYTE*, UBYTE*, BYTE, BYTE, BYTE, BYTE);
void setting_mode(UBYTE, UBYTE*, BYTE*, BYTE*, BYTE*, BYTE*);
void game_mode(UBYTE*, UBYTE*);
UBYTE count_neighbors(UBYTE*, UBYTE, UBYTE);
UBYTE get_bit_position(UBYTE);

// ゲーム初期化
void init(UBYTE* p_board, UBYTE* p_preboard)
{
    UBYTE index;
    volatile UBYTE x, y;
    volatile UBYTE box_x1, box_y1, box_x2, box_y2;

    index = 0;
    x = 0;
    y = 0;
    box_x1 = 0;
    box_y1 = 0;
    box_x2 = 0;
    box_y2 = 0;

    // スプラッシュスクリーン
    printf(" ");
    gotoxy(0, 8);
    printf("Conway's GameOfLife\n");
    printf(" made by K.TAKAHASHI\n");

    delay(1000);

    // 盤面初期描画
    color(BLACK, BLACK, SOLID);
    box(0, 0, X_POINT_MAX, Y_POINT_MAX, M_NOFILL);
    for (y = 0; y < Y_SQUARE_NUM; y += 1) {
        for (x = 0; x < X_SQUARE_NUM; x += 1) {
            index = x + (y * X_SQUARE_NUM);
            p_board[index] = DEAD;
            p_preboard[index] = DEAD;

            box_x1 = (x * SQUARE_SIDE_LEN);
            box_x1 += SQUARE_OFFSET_X;
            box_y1 = (y * SQUARE_SIDE_LEN);
            box_y1 += SQUARE_OFFSET_Y;
            box_x2 = box_x1 + SQUARE_SIDE_LEN;
            box_y2 = box_y1 + SQUARE_SIDE_LEN;
            
            box(box_x1, box_y1, box_x2, box_y2, M_NOFILL);
        }
    }
    draw_square(0, 0, CURSOR);
}

// メイン処理
int main(void)
{
    volatile UBYTE key, current_key;
    UBYTE key_number;

    volatile BYTE cursor_x, cursor_y;
    volatile BYTE pre_cursor_x, pre_cursor_y;

    volatile KeyState key_state;
    volatile GameState game_state;
    volatile GameState next_transition;

    key = 0, current_key = 0;
    key_number = 0;

    cursor_x = 0, cursor_y = 0;
    pre_cursor_x = 0, pre_cursor_y = 0;

    key_state = KEY_UP;
    game_state = SETTING_MODE;
    next_transition = NONE;

    init(board, preboard);

    while (1) {
        // キー入力確認
        current_key = joypad();
        if((current_key != 0) && (key_state == KEY_UP)){
            key = current_key;
            key_state = KEY_DOWN;
        }

        // キー入力とゲーム状態による状態遷移
        key_number = get_bit_position(key);
        next_transition = g_game_state_transition[game_state][key_number];
        if(next_transition != NONE){
            if ((game_state == GAME_MODE) && (next_transition == SETTING_MODE)) {
                reset_board(board);
            }
            if ((game_state == SETTING_MODE) && (next_transition == GAME_MODE)) {
                draw_square((UBYTE)cursor_x, (UBYTE)cursor_y, (SquareType)board[cursor_y][cursor_x]);
                pre_cursor_x = cursor_x;
                pre_cursor_y = cursor_y;
            }
            game_state = next_transition;
        }

        // 各状態での処理と描画
        switch (game_state) {
            case SETTING_MODE:
                setting_mode(key, board, &cursor_x, &cursor_y, &pre_cursor_x, &pre_cursor_y);
                break;
            case GAME_MODE:
                game_mode(board, preboard);
                break;
            default:
                break;
        }
        draw_board(board, preboard, cursor_x, cursor_y, pre_cursor_x, pre_cursor_y);
        
        key = 0;
        if((current_key == 0) && (key_state == KEY_DOWN)){
            key_state = KEY_UP;
        }
    }
}

// 盤面のカーソル操作による初期状態設定
void setting_mode(UBYTE key, UBYTE* p_board, BYTE* p_cursor_x, BYTE* p_cursor_y, BYTE* p_pre_cursor_x, BYTE* p_pre_cursor_y)
{    
    UBYTE index;    
    UBYTE directional_key_bit;
    
    index = 0;    
    directional_key_bit = (J_RIGHT | J_LEFT | J_DOWN | J_UP);

    if (p_board == NULL) {
        return;
    }

    if (key & directional_key_bit) {
        *p_pre_cursor_x = *p_cursor_x;
        *p_pre_cursor_y = *p_cursor_y;

        if (key & J_RIGHT) {
            *p_cursor_x = (*p_cursor_x) + 1;
        }
        if (key & J_LEFT) {
            *p_cursor_x = (*p_cursor_x) - 1;
        }
        if (key & J_DOWN) {
            *p_cursor_y = (*p_cursor_y) + 1;
        }
        if (key & J_UP) {
            *p_cursor_y = (*p_cursor_y) - 1;
        }
        
        if ((*p_cursor_x) < 0) {
            *p_cursor_x = 0;
        }
        if ((*p_cursor_x) >= (X_SQUARE_NUM - 1)) {
            *p_cursor_x = (X_SQUARE_NUM - 1);
        }
        if ((*p_cursor_y) < 0) {
            *p_cursor_y = 0;
        }
        if ((*p_cursor_y) >= (Y_SQUARE_NUM - 1)) {
            *p_cursor_y = (Y_SQUARE_NUM - 1);
        }
    }
    if (key & J_A) {
        index = (*p_cursor_x) + ((*p_cursor_y) * X_SQUARE_NUM);
        p_board[index] = p_board[index] == ALIVE ? DEAD : ALIVE;
    }
}

// ライフゲームの生存死亡判定
void game_mode(UBYTE* p_board, UBYTE* p_preboard)
{
    UBYTE index;
    UBYTE x, y;
    UBYTE count;
    
    index = 0;
    x = 0;
    y = 0;
    count = 0;

    for (y = 0; y < Y_SQUARE_NUM; y += 1) {
        for (x = 0; x < X_SQUARE_NUM; x += 1) {
            count = count_neighbors(p_preboard, x, y);
            index = x + (y * X_SQUARE_NUM);

            if (p_preboard[index] == DEAD) {
                if (count == 3) {
                    p_board[index] = ALIVE;
                } 
            }
            if (p_preboard[index] == ALIVE) {
                if ((count <= 1) || (count >= 4)) {
                    p_board[index] = DEAD;
                }
                if ((count == 2) || (count == 3)) {
                    p_board[index] = ALIVE;
                } 
            }
        }
    }
}

// 盤面初期化
void reset_board(UBYTE* p_board)
{
    UBYTE index;
    volatile UBYTE x, y;

    index = 0;
    x = 0;
    y = 0;

    for (y = 0; y < Y_SQUARE_NUM; y += 1) {
        for (x = 0; x < X_SQUARE_NUM; x += 1) {
            index = x + (y * X_SQUARE_NUM);
            p_board[index] = DEAD;
        }
    }
}

// 盤面描画
UBYTE draw_board(
    UBYTE* p_board, 
    UBYTE* p_preboard,
    BYTE cursor_x, 
    BYTE cursor_y, 
    BYTE pre_cursor_x, 
    BYTE pre_cursor_y
)
{
    UBYTE index;
    UBYTE x, y;
    
    index = 0;
    x = 0;
    y = 0;

    if ((p_board == NULL) || (p_preboard == NULL)) {
        return -1;
    }
    if ((cursor_x >= X_SQUARE_NUM) || (cursor_y >= Y_SQUARE_NUM)) {
        return -1;
    }
    if ((pre_cursor_x >= X_SQUARE_NUM) || (pre_cursor_y >= Y_SQUARE_NUM)) {
        return -1;
    }

    if ((cursor_x != pre_cursor_x) || (cursor_y != pre_cursor_y)) {
        index = pre_cursor_x + (pre_cursor_y * X_SQUARE_NUM);
        draw_square(pre_cursor_x, pre_cursor_y, p_board[index]);
        draw_square(cursor_x, cursor_y, CURSOR);
    }

    for (y = 0; y < Y_SQUARE_NUM; y += 1) {
        for (x = 0; x < X_SQUARE_NUM; x += 1) {
            index = x + (y * X_SQUARE_NUM);
            if (p_board[index] != p_preboard[index]) {
                p_preboard[index] = p_board[index];
                draw_square(x, y, p_board[index]);
            }
        }
    }
}

// マス目描画
UBYTE draw_square(UBYTE x, UBYTE y, SquareType square_type)
{
    UBYTE box_x1, box_y1, box_x2, box_y2;

    box_x1 = 0;
    box_y1 = 0;
    box_x2 = 0;
    box_y2 = 0;

    if ((x >= X_SQUARE_NUM) || (y >= Y_SQUARE_NUM)) {
        return -1;
    }

    box_x1 = (x * SQUARE_SIDE_LEN);
    box_x1 += (int)(SQUARE_SIDE_LEN/5);
    box_x1 += SQUARE_OFFSET_X;
    box_y1 = (y * SQUARE_SIDE_LEN);
    box_y1 += (int)(SQUARE_SIDE_LEN/5);
    box_y1 += SQUARE_OFFSET_Y;
    box_x2 = box_x1 + SQUARE_SIDE_LEN;
    box_x2 -= (int)((SQUARE_SIDE_LEN * 2)/5);
    box_y2 = box_y1 + SQUARE_SIDE_LEN;
    box_y2 -= (int)((SQUARE_SIDE_LEN * 2)/5);

    switch (square_type) {
    case ALIVE:
        color(BLACK, BLACK, SOLID);
        box(box_x1, box_y1, box_x2, box_y2, M_FILL);
        break;
    case DEAD:
        color(WHITE, WHITE, SOLID);
        box(box_x1, box_y1, box_x2, box_y2, M_FILL);
        break;
    case CURSOR:
        color(BLACK, BLACK, SOLID);
        box(box_x1, box_y1, box_x2, box_y2, M_NOFILL);
        break;
    case DEBUG:
        color(LTGREY, LTGREY, SOLID);
        box(box_x1, box_y1, box_x2, box_y2, M_FILL);
        break;
    default:
        color(WHITE, WHITE, SOLID);
        box(box_x1, box_y1, box_x2, box_y2, M_FILL);
    }

    return 0;
}

// 隣接マス(８方向)の生存マスをカウント
UBYTE count_neighbors(UBYTE* p_board, UBYTE x, UBYTE y)
{
    UBYTE temp_x, temp_y;
    UBYTE index;
    UBYTE count;

    count = 0;

    for (temp_y = 0; temp_y <= 2; temp_y++) {
        for (temp_x = 0; temp_x <= 2; temp_x++) {
            if ((temp_x == 1) && (temp_y == 1)) {
                continue;
            }
            if ((x == 0) && (temp_x == 0)) {
                continue;
            }
            if ((y == 0) && (temp_y == 0)) {
                continue;
            }
            if ((x == (X_SQUARE_NUM - 1)) && (temp_x == 2)) {
                continue;
            }
            if ((y == (Y_SQUARE_NUM - 1)) && (temp_y == 2)) {
                continue;
            }
            
            index = (x + (temp_x - 1)) + ((y + (temp_y - 1)) * X_SQUARE_NUM);
            count = p_board[index] == ALIVE ? count + 1 : count;
        }
    }

    return count;
}

// ビット位置算出
UBYTE get_bit_position(UBYTE value)
{
    UBYTE count;
    UBYTE index;

    count = 0;
    index = 0;

    for (index = 1; index <= 8; index++) {
        if (value & 0x01) {
            count = index;
            break;
        }
        value = value >> 1;
    }
    return count;
}
