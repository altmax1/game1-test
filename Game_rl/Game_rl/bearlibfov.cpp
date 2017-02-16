// BeaRLibFOV.cpp : Defines the exported functions for the DLL application.
//
#include <math.h>
#include <stdio.h>

#include "bearlibfov.h"

inline int max( int a, int b ) { return a > b ? a : b; }

inline int min( int a, int b ) { return a < b ? a : b; }

struct shadow_t
{
    double start;
    double end;

    shadow_t() { start = 0.0; end = 0.0; }
    shadow_t( double start_, double end_ ) { start = start_; end = end_; }
};

shadow_t* shadows = NULL;
int shadows_count = 0;
int shadows_allocated = 0;

inline void AddShadow( shadow_t shadow )
{
    if ( shadows_count == shadows_allocated )
    {
        shadows_allocated *= 2;
        delete[] shadows;
        shadows = new shadow_t[shadows_allocated];
    }

    shadows[shadows_count++] = shadow;
}

inline bool CellOpaque( FOV_MAP *map, int x, int y )
{
    if ( x < 0 || y < 0 || x >= map->Width || y >= map->Height ) return false;
    return (map->Cells[y*map->Width+x].Flags & FOV_CELL_OPAQUE) > 0;
}

inline bool CellVisible( FOV_MAP *map, int x, int y )
{
    if ( x < 0 || y < 0 || x >= map->Width || y >= map->Height ) return false;
    return (map->Cells[y*map->Width+x].Flags & FOV_CELL_VISIBLE) > 0;
}

inline void SetFlag( FOV_MAP *map, int x, int y, unsigned char flag )
{
    if ( x < 0 || y < 0 || x >= map->Width || y >= map->Height ) return;
    map->Cells[y*map->Width+x].Flags |= flag;
}

inline void ClearFlag( FOV_MAP *map, int x, int y, unsigned char flag )
{
    if ( x < 0 || y < 0 || x >= map->Width || y >= map->Height ) return;
    map->Cells[y*map->Width+x].Flags &= (0xFF ^ flag);
}

void CalcFOVQuadrant3( FOV_MAP *map, int px, int py, int radius, int xy, int dx, int dy )
{
    int iteration = 1; // iteration step (distance from (px,py) by main direction)
    
    int shadows_before = 0;
	double min_angle = 0.0f;

	int x, y, dv, dw, pv, pw, maxv;
    int tx, ty;

    // xy: 0 = vertical (y) edge, 1 = horisontal (x) edge

    int& v = xy ? x : y;
    int& w = xy ? y : x;

    if ( xy == 0 )
    {
        // Vertical edge
        pv = py; pw = px;
        dv = dy; dw = dx;
        tx = 0; ty = dy;
        maxv = map->Height;
    }
    else
    {
        // Horisontal edge
        pv = px; pw = py;
        dv = dx; dw = dy;
        tx = dx; ty = 0;
        maxv = map->Width;
    }

    // Reset shadow counter
    shadows_count = 0;

    // Do while there are unblocked slopes left and the algo is within the map's boundaries
    // Scan progressive lines/columns from the PC outwards

    v = pv + dv; // The outer slope's coordinates (first processed line)

    bool done = false;
    if ( v < 0 || v >= maxv ) done = true;
    
	while( !done )
    {
        // Process cells in the line

		double slopesPerCell = 1.0 / (double)(iteration + 1);
		double halfSlopes = slopesPerCell * 0.5;
		int processedCell = (int)floor(min_angle / slopesPerCell);
        
        int minw = max( 0, pw-iteration );
        int maxw = min( (xy ? map->Height : map->Width)-1, pw+iteration );
        
        done = true; // If there will be any visible cells in current line, this flag will be cleared back to false
        
        for ( w = pw + (processedCell * dw); w >= minw && w <= maxw; w += dw )
        {
            bool visible = true;

            double startSlope = (double)processedCell*slopesPerCell;
            double centreSlope = startSlope+halfSlopes;
            double endSlope = startSlope+slopesPerCell;

            if ( shadows_before > 0 && !CellVisible( map, x, y ) )
            {
                for ( int i = 0; i < shadows_count; i++ ) // For each shadow
                {
                    if ( !CellOpaque( map, x, y ) ) // Can see throug this cell?
                    {
                        if (centreSlope > shadows[i].start && centreSlope < shadows[i].end)
                        {
                            visible = false;
                        }
                    }
                    else
                    {
                        if (startSlope >= shadows[i].start && endSlope <= shadows[i].end)
                        {
                            visible = false;
                        }
                    }

                    // If cell is still marked as visible it can be a glitch
                    // To make sure, check if two nearby cells in previous line are blocked from sight or not

                    bool c1blocked = !CellVisible( map, x-tx, y-ty ) || CellOpaque( map, x-tx, y-ty );
                    bool c2blocked = !CellVisible( map, x-dx, y-dy ) || CellOpaque( map, x-dx, y-dy );

                    // If there are no close and visible cells in previous line, then it's a glitch

                    if ( visible && c1blocked && c2blocked) visible = false;
                }
            }

            if ( visible )
            {
                if ( (x-px)*(x-px) + (y-py)*(y-py) <= radius*radius )
                {
                    SetFlag( map, x, y, FOV_CELL_VISIBLE );
                    SetFlag( map, x, y, FOV_CELL_VISITED );
                }
                    
                done = false; // Visible cell means there can be more visible cells further, so we're not done

                // If the cell is opaque, block the adjacent slopes
                if ( CellOpaque( map, x, y ) )
                {
                    if (min_angle >= startSlope)
                    {
                        min_angle = endSlope;
                    }
                    else
                    {
                        // TODO: Shadow optimization is not implemented yet
                        // CombineShadows( shadow_t( startSlope, endSlope ) );

                        AddShadow( shadow_t( startSlope, endSlope ) );
                    }
                }
            }

            processedCell++;
        }

        if ( iteration == radius ) done = true;
        iteration++;

        shadows_before = shadows_count;
        
        v += dv;
        
        if ( v < 0 || v >= maxv ) done = true;
		if ( min_angle >= 1.0f ) done=true;
    }
}

int __stdcall CalcFOVC( FOV_MAP *map, int px, int py, int radius )
{
    if ( map == NULL || map->Cells == NULL ) return -1;

    // Clear all cells' visiblity flags but leave 'visited' flag intact
    for ( int i=0; i<map->Width * map->Height; i++ )
    {
        map->Cells[i].Flags &= (0xFF ^ FOV_CELL_VISIBLE);
    }

    SetFlag( map, px, py, FOV_CELL_VISIBLE );

    shadows_allocated = radius;
    shadows = new shadow_t[shadows_allocated];

    const int vectors[4][2] =
    {
        { +1, +1 },
        { +1, -1 },
        { -1, +1 },
        { -1, -1 }
    };

    for ( int i=0; i<4; i++ )
    {
        CalcFOVQuadrant3( map, px, py, radius, 0, vectors[i][0], vectors[i][1] );
        CalcFOVQuadrant3( map, px, py, radius, 1, vectors[i][0], vectors[i][1] );
    }

    delete[] shadows;

    return 0;
}
