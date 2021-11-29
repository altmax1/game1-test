

#ifndef BEARLIB_FOV_H_
#define BEARLIB_FOV_H_

extern "C"
{
    typedef struct
    {
        unsigned char Flags;
        void* Reserved;
    }
    FOV_CELL;

    typedef struct
    {
        int Width;
        int Height;
        FOV_CELL* Cells;
    }
    FOV_MAP;

    #define FOV_CELL_VISIBLE    1
    #define FOV_CELL_OPAQUE     2
    #define FOV_CELL_VISITED    4

    int __declspec(dllexport) __stdcall CalcFOVC( FOV_MAP *map, int px, int py, int radius );
}

#endif
