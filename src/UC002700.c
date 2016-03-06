//****************************************************************************
// FILE NAME:    UC002700.c
//****************************************************************************
//
//   Revision History
//   Version      Author         yyyy/mm/dd      Description
//     0.1      Eric Luong       2010/04/26     File creation
// 
//   Description
//   UYVY 90 degree rotation
//****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inc/TIBLT.h"
#include "inc/usecases.h"

TIBLTERROR UC002700(unsigned short srcwidth,
		    unsigned short srcheight,
		    unsigned short dstwidth,
		    unsigned short dstheight,
		    unsigned short srcstride, 
		    unsigned short dststride, 
		    unsigned char * srcptr,
		    unsigned char * dstptr)
{
    printf ("UC002700: Setting up blit parameters\n");

    /////////////////////////////////////////////////////////////////////////////////////////////

    TIBLTPARAMS parms;
    memset(&parms, 0, sizeof(parms));
    parms.structsize = sizeof(parms);
    parms.flags = TIBLT_FLAG_ROP;
    parms.ROP = 0xCCCC; // SRCCOPY

    TIBLTSURF dst;
    memset(&dst, 0, sizeof(dst));
    dst.structsize = sizeof(dst);
    dst.format = TIBLT_FMT_BGR132;
    dst.width = dstwidth;
    dst.height = dstheight;
    dst.virtptr = dstptr;
    dst.virtstride = dststride;
    parms.pdst = &dst;
    parms.dstrect.left = 0;
    parms.dstrect.top = 0;
    parms.dstrect.width = dstwidth;
    parms.dstrect.height = dstheight;
    parms.dithertype = TIBLT_DT_NONE;

   TIBLTSURF src;
    memset(&src, 0, sizeof(src));
    src.structsize = sizeof(src);
    src.format = TIBLT_FMT_UYVY;
    src.width = srcwidth;
    src.height = srcheight;
    src.virtptr = srcptr;
    src.virtstride = srcstride;
    parms.psrc = &src;
    parms.srcrect.left = 0;
    parms.srcrect.top = 0;
    parms.srcrect.width = srcwidth;
    parms.srcrect.height = srcheight;
 
    printf ("UC002700: Performing %s \n",TIBLT002700_DESC);
    return TIBLT(&parms);
}

