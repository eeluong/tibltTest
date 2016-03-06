//****************************************************************************
// FILE NAME:    001050.c
//****************************************************************************
//
//   Revision History
//   Version      Author         yyyy/mm/dd      Description
//     0.1      Eric Luong       2010/01/28     File creation
// 
//   Description
//   Solid Fill BGRA32
//****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inc/TIBLT.h"
#include "inc/usecases.h"

TIBLTERROR UC001050(unsigned int solidcolor, 
		  unsigned short dstwidth,
		  unsigned short dstheight, 
		  unsigned short dststride, 
		  unsigned char * dstptr)
{
    printf ("UC001050: Setting up blit parameters\n");
    TIBLTPARAMS parms;
    memset(&parms, 0, sizeof(parms));
    parms.structsize = sizeof(parms);
    parms.flags = TIBLT_FLAG_ROP;
    parms.ROP = 0xF0F0; // PATCOPY

    TIBLTSURF dst;
    memset(&dst, 0, sizeof(dst));
    dst.structsize = sizeof(dst);
    dst.format = TIBLT_FMT_BGRA32;
    dst.width = dstwidth;
    dst.height = dstheight;
    dst.orientation = 0;
    dst.virtptr = dstptr;
    dst.virtstride = dststride;
    parms.pdst = &dst;
    parms.dstrect.left = 0;
    parms.dstrect.top = 0;
    parms.dstrect.width = dstwidth;
    parms.dstrect.height = dstheight;
    parms.dithertype = TIBLT_DT_NONE;

    TIBLTSURF brush;
    memset(&brush, 0, sizeof(brush));
    brush.structsize = sizeof(brush);
    brush.format =  TIBLT_FMT_BGRA32; //does not need to match destination format
    brush.width = 1;
    brush.height = 1;
    brush.orientation = 0;
    brush.virtptr = &solidcolor;
    brush.virtstride = 4; // not actually used, but set to size of one pixel container
    parms.pbrush = &brush;
    parms.brushrect.left = 0;
    parms.brushrect.top = 0;
    parms.brushrect.width = 1;
    parms.brushrect.height = 1;

    printf ("UC001050: Performing %s \n",TIBLT001050_DESC);
    return TIBLT(&parms);
}

