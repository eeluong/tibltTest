//****************************************************************************
// FILE NAME:    usecases.h
//****************************************************************************
//
//   Revision History
//   Version      Author         yyyy/mm/dd      Description
//     0.1      Eric Luong       2010/01/22     File creation
// 
//****************************************************************************

/* Standard library include files */
#include <stdio.h>
#include <stdlib.h>
#include "TIBLT.h"

#define TIBLT001050_DESC      "Solid Fill BGRA32 size 864x480 "
#define TIBLT002300_DESC      "Convert BGR24 to BGRx32 size 864x480 "
#define TIBLT003010_DESC      "RGB16 90 degree rotation size 864x480 "
#define TIBLT003011_DESC      "RGB16 180 degree rotation size 864x480 "
#define TIBLT003012_DESC      "RGB16 270 degree rotation size 864x480 "
#define TIBLT003020_DESC      "UYVY 90 degree rotation size 864x480 "
#define TIBLT003021_DESC      "UYVY 180 degree rotation size 864x480 "
#define TIBLT003022_DESC      "UYVY 270 degree rotation size 864x480 "
#define TIBLT002401_DESC      "Convert BGRx32 to RGB16 size 864x480 "
#define TIBLT002203_DESC      "Convert RGB16 to BGRx32 size 480x864 "
#define TIBLT004010_DESC      "RGB16 Global Alpha Blend"
#define TIBLT002700_DESC      "Convert UYVY to BGR132 size 480x864"

extern int TIBLT001050(); // Solid Fill BGRA32
extern int TIBLT002300(); // convert BGR24 to BGRx32
extern int TIBLT003010(); // RGB16 90 degree rotation
extern int TIBLT003011(); // RGB16 180 degree rotation
extern int TIBLT003012(); // RGB16 270 degree rotation
extern int TIBLT003020(); // UYVY 90 degree rotation
extern int TIBLT003021(); // UYVY 180 degree rotation
extern int TIBLT003022(); // UYVY 270 degree rotation
extern int TIBLT002401(); // Convert BGRx32 to RGB16 size 864x480
extern int TIBLT002203(); // Convert RGB16 to BGRx32 size 480x864
extern int TIBLT004010(); // RGB16 Global Alpha Blend
extern int TIBLT002700(); // Convert UYVY to BGR132 size 480x864
