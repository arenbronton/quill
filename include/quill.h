#pragma once

typedef enum
{
    NORMAL,
    INSERT,
    VISUAL
} Mode;

typedef struct
{
    Mode mode;
    int cursor_x;
    int cursor_y;
} EditorMode;