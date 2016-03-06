//****************************************************************************
// FILE NAME:    usecases.c
//****************************************************************************
//
//   Revision History
//   Version      Author         yyyy/mm/dd      Description
//     0.1      Eric Luong       2010/01/22     File creation
// 
//****************************************************************************

// Standard library include files
#include <stdio.h>
#include <stdlib.h>
#include "inc/TIBLT.h"
#include "inc/usecases.h"

// This function allocate the memory basic on the file size and read the file contain to memory and return ptr
int readInputFile(char *input_file, long file_size, char * ptr)
{
    FILE * src_file      = NULL;

    src_file             = fopen (input_file, "r");
    if (src_file == NULL )
    {
        printf ("readInputFile: FILE Open Error: Can't open %s Abort testing !!!\n", input_file);
	return -1;
    }
    printf("readInputFile: Reading input file %s to memory location... \n",input_file);
    fread (ptr, 1, file_size, src_file);
    fclose (src_file);
    return 0;

}

// This function will write the memory contain pass in ptr the file
int saveOutputFile(char *output_file, long file_size, char * ptr)
{
    FILE * dest_file      = NULL;

    dest_file = fopen (output_file, "w");
    if (dest_file == NULL)
    {
	printf ("saveOutputFile: FILE Open Error: Can't open %s for writing. Free the input pointer\n", output_file);
	return -1;
    }
    printf ("saveOutputFile: Saving resulting frame to output file %s\n",output_file);
    fwrite (ptr, 1, file_size, dest_file);
    printf ("saveOutputFile: Write Successful. free input pointer... \n");
    fclose (dest_file);
    return 0;
}

//
//   Usecase TIBLT001050 Solid Fill BGRA32 with 0xFFFF0000
//
extern int UC001050(unsigned int solidcolor, 
		    unsigned short dstwidth, 
		    unsigned short dstheight, 
		    unsigned short dststride, 
		    char * dstptr);
int TIBLT001050()
{
  unsigned int solidcolor    = 0xFFFF0000;
  unsigned short dstwidth    = 864;
  unsigned short dstheight   = 480;
  unsigned short dststride   = 4*dstwidth;
  char * input_file          = "./images/TIBLT001050_input.rgb";
  char * output_file         = "./images/TIBLT001050_output.rgb";
  char * dstptr              = NULL;
  TIBLTERROR ret             = TIBLT_ERR_NONE ;
  long file_size              = dstheight*dststride;

  printf("####################################################################################\n");
  printf("TIBLT001050: Running TIBLT001050 usecase %s \n",TIBLT001050_DESC);
  printf("TIBLT001050: input file size is %d \n",file_size);
  /* Allocation memory */
  dstptr    = malloc (file_size);
  if (!dstptr)
  {
    printf ("TIBLT001050: Out of memory\n");
    return -1;
  }

  if ((readInputFile(input_file, file_size,dstptr)) == -1)
  {
    free(dstptr);
    return -1;
  }

  ret = UC001050(solidcolor, dstwidth, dstheight, dststride, dstptr);
  if (ret == TIBLT_ERR_NONE )
    saveOutputFile(output_file, file_size, dstptr);
  else
    printf ("TIBLT001050 false error code %d \n",ret);

  free(dstptr);
  printf("####################################################################################\n");
  return 0;
}

//
//   Usecase TIBLT002300 convert BGR24 to BGRx32
//
extern TIBLTERROR UC002300(unsigned short srcwidth,
			   unsigned short srcheight,
			   unsigned short dstwidth,
			   unsigned short dstheight,
			   unsigned short srcstride, 
			   unsigned short dststride, 
			   unsigned char * srcptr,
			   unsigned char * dstptr);

int TIBLT002300()
{
  unsigned short srcwidth    = 864;
  unsigned short srcheight   = 480;
  unsigned short dstwidth    = 864;
  unsigned short dstheight   = 480;
  unsigned short srcstride   = 3*srcwidth;
  unsigned short dststride   = 4*dstwidth;
  char * input_file          = "./images/TIBLT002300_input.rgb";
  char * output_file         = "./images/TIBLT002300_output.rgba";
  char * srcptr              = NULL;
  char * dstptr              = NULL;
  TIBLTERROR ret             = TIBLT_ERR_NONE ;
  long input_file_size       = srcheight*srcstride;
  long output_file_size      = dstheight*dststride;

  printf("####################################################################################\n");
  printf("TIBLT002300: Running TIBLT002300 usecase %s \n", TIBLT002300_DESC);
  printf("TIBLT002300: input file size  is %d \n",input_file_size);
  printf("TIBLT002300: output file size is %d \n",output_file_size);
  srcptr    = malloc (input_file_size);
  if (!srcptr)
  {
    printf ("TIBLT002300: Out of memory\n");
    return -1;
  }

  if ((readInputFile(input_file, input_file_size,srcptr)) == -1)
  {
    free(srcptr);
    return -1;
  }

  dstptr = malloc (output_file_size);
  if (!dstptr)
  {
    printf ("TIBLT002300: Out of memory\n");
    free(srcptr);
    return -1;
  }

  ret = UC002300(srcwidth,srcheight,dstwidth, dstheight, srcstride, dststride, srcptr, dstptr);
  if (ret == TIBLT_ERR_NONE )
    saveOutputFile(output_file, output_file_size, dstptr);
  else
    printf ("TIBLT002300 false error code %d \n",ret);
  free(srcptr);
  free(dstptr);
  printf("####################################################################################\n");
  return 0;
}

//
//   Usecase TIBLT003010 RGB16 90 degree rotation
//
extern TIBLTERROR UC003010(unsigned short srcwidth,
		    unsigned short srcheight,
		    unsigned short dstwidth,
		    unsigned short dstheight,
		    unsigned short srcstride, 
		    unsigned short dststride, 
		    unsigned char * srcptr,
		    unsigned char * dstptr);
int TIBLT003010()
{
  unsigned short srcwidth    = 864;
  unsigned short srcheight   = 480;
  unsigned short dstwidth    = 480;
  unsigned short dstheight   = 864;
  unsigned short srcstride   = 2*srcwidth;
  unsigned short dststride   = 2*dstwidth;
  char * input_file          = "./images/TIBLT003010_input.rgb";
  char * output_file         = "./images/TIBLT003010_output.rgb";
  char * srcptr              = NULL;
  char * dstptr              = NULL;
  TIBLTERROR ret             = TIBLT_ERR_NONE ;
  long input_file_size       = srcheight*srcstride;
  long output_file_size      = dstheight*dststride;

  printf("####################################################################################\n");
  printf("TIBLT003010: Running TIBLT003010 usecase %s \n",TIBLT003010_DESC);
  printf("TIBLT003010: input file size  is %d \n",input_file_size);
  printf("TIBLT003010: output file size is %d \n",output_file_size);
  srcptr    = malloc (input_file_size);
  if (!srcptr)
  {
    printf ("TIBLT003010: Out of memory\n");
    return -1;
  }

  if ((readInputFile(input_file, input_file_size,srcptr)) == -1)
  {
    free(srcptr);
    return -1;
  }

  dstptr = malloc (output_file_size);
  if (!dstptr)
  {
    printf ("TIBLT003010: Out of memory\n");
    free(srcptr);
    return -1;
  }

  ret = UC003010(srcwidth, srcheight, dstwidth, dstheight, srcstride, dststride, srcptr, dstptr);
  if (ret == TIBLT_ERR_NONE )
    saveOutputFile(output_file, output_file_size, dstptr);
  else
    printf ("TIBLT003010 false error code %d \n",ret);
  free(srcptr);
  free(dstptr);
  printf("####################################################################################\n");
  return 0;
}

//
//   Usecase TIBLT003011 RGB16 180 degree rotation
//
extern TIBLTERROR UC003011(unsigned short srcwidth,
		    unsigned short srcheight,
		    unsigned short dstwidth,
		    unsigned short dstheight,
		    unsigned short srcstride, 
		    unsigned short dststride, 
		    unsigned char * srcptr,
		    unsigned char * dstptr);
int TIBLT003011()
{
  unsigned short srcwidth    = 864;
  unsigned short srcheight   = 480;
  unsigned short dstwidth    = 864;
  unsigned short dstheight   = 480;
  unsigned short srcstride   = 2*srcwidth;
  unsigned short dststride   = 2*dstwidth;
  char * input_file          = "./images/TIBLT003010_input.rgb";
  char * output_file         = "./images/TIBLT003011_output.rgb";
  char * srcptr              = NULL;
  char * dstptr              = NULL;
  TIBLTERROR ret             = TIBLT_ERR_NONE ;
  long input_file_size       = srcheight*srcstride;
  long output_file_size      = dstheight*dststride;

  printf("####################################################################################\n");
  printf("TIBLT003011: Running TIBLT003011 usecase %s \n",TIBLT003011_DESC);
  printf("TIBLT003011: input file size  is %d \n",input_file_size);
  printf("TIBLT003011: output file size is %d \n",output_file_size);
  srcptr    = malloc (input_file_size);
  if (!srcptr)
  {
    printf ("TIBLT003011: Out of memory\n");
    return -1;
  }

  if ((readInputFile(input_file, input_file_size,srcptr)) == -1)
  {
    free(srcptr);
    return -1;
  }

  dstptr = malloc (output_file_size);
  if (!dstptr)
  {
    printf ("TIBLT003011: Out of memory\n");
    free(srcptr);
    return -1;
  }

  ret = UC003011(srcwidth, srcheight, dstwidth, dstheight, srcstride, dststride, srcptr, dstptr);
  if (ret == TIBLT_ERR_NONE )
    saveOutputFile(output_file, output_file_size, dstptr);
  else
    printf ("TIBLT003011 false error code %d \n",ret);
  free(srcptr);
  free(dstptr);
  printf("####################################################################################\n");
  return 0;
}

//
//   Usecase TIBLT003012 RGB16 270 degree rotation
//
extern TIBLTERROR UC003012(unsigned short srcwidth,
		    unsigned short srcheight,
		    unsigned short dstwidth,
		    unsigned short dstheight,
		    unsigned short srcstride, 
		    unsigned short dststride, 
		    unsigned char * srcptr,
		    unsigned char * dstptr);
int TIBLT003012()
{
  unsigned short srcwidth    = 864;
  unsigned short srcheight   = 480;
  unsigned short dstwidth    = 480;
  unsigned short dstheight   = 864;
  unsigned short srcstride   = 2*srcwidth;
  unsigned short dststride   = 2*dstwidth;
  char * input_file          = "./images/TIBLT003010_input.rgb";
  char * output_file         = "./images/TIBLT003012_output.rgb";
  char * srcptr              = NULL;
  char * dstptr              = NULL;
  TIBLTERROR ret             = TIBLT_ERR_NONE ;
  long input_file_size       = srcheight*srcstride;
  long output_file_size      = dstheight*dststride;

  printf("####################################################################################\n");
  printf("TIBLT003012: Running TIBLT003012 usecase %s \n",TIBLT003012_DESC);
  printf("TIBLT003012: input file size  is %d \n",input_file_size);
  printf("TIBLT003012: output file size is %d \n",output_file_size);
  srcptr    = malloc (input_file_size);
  if (!srcptr)
  {
    printf ("TIBLT003012: Out of memory\n");
    return -1;
  }

  if ((readInputFile(input_file, input_file_size,srcptr)) == -1)
  {
    free(srcptr);
    return -1;
  }

  dstptr = malloc (output_file_size);
  if (!dstptr)
  {
    printf ("TIBLT003012: Out of memory\n");
    free(srcptr);
    return -1;
  }

  ret = UC003012(srcwidth, srcheight, dstwidth, dstheight, srcstride, dststride, srcptr, dstptr);
  if (ret == TIBLT_ERR_NONE )
    saveOutputFile(output_file, output_file_size, dstptr);
  else
    printf ("TIBLT003012 false error code %d \n",ret);
  free(srcptr);
  free(dstptr);
  printf("####################################################################################\n");
  return 0;
}

//
//   Usecase TIBLT003020 UYVY 90 degree rotation
//
extern TIBLTERROR UC003020(unsigned short srcwidth,
		    unsigned short srcheight,
		    unsigned short dstwidth,
		    unsigned short dstheight,
		    unsigned short srcstride, 
		    unsigned short dststride, 
		    unsigned char * srcptr,
		    unsigned char * dstptr);
int TIBLT003020()
{
  unsigned short srcwidth    = 864;
  unsigned short srcheight   = 480;
  unsigned short dstwidth    = 480;
  unsigned short dstheight   = 864;
  unsigned short srcstride   = 2*srcwidth;
  unsigned short dststride   = 2*dstwidth;
  char * input_file          = "./images/TIBLT003020_input.uyvy";
  char * output_file         = "./images/TIBLT003020_output.uyvy";
  char * srcptr              = NULL;
  char * dstptr              = NULL;
  TIBLTERROR ret             = TIBLT_ERR_NONE ;
  long input_file_size       = srcheight*srcstride;
  long output_file_size      = dstheight*dststride;

  printf("####################################################################################\n");
  printf("TIBLT003020: Running TIBLT003020 usecase %s \n",TIBLT003020_DESC);
  printf("TIBLT003020: input file size  is %d \n",input_file_size);
  printf("TIBLT003020: output file size is %d \n",output_file_size);
  srcptr    = malloc (input_file_size);
  if (!srcptr)
  {
    printf ("TIBLT003020: Out of memory\n");
    return -1;
  }

  if ((readInputFile(input_file, input_file_size,srcptr)) == -1)
  {
    free(srcptr);
    return -1;
  }

  dstptr = malloc (output_file_size);
  if (!dstptr)
  {
    printf ("TIBLT003020: Out of memory\n");
    free(srcptr);
    return -1;
  }

  ret = UC003020(srcwidth, srcheight, dstwidth, dstheight, srcstride, dststride, srcptr, dstptr);
  if (ret == TIBLT_ERR_NONE )
    saveOutputFile(output_file, output_file_size, dstptr);
  else
    printf ("TIBLT003020 false error code %d \n",ret);
  free(srcptr);
  free(dstptr);
  printf("####################################################################################\n");
  return 0;
}

//
//   Usecase TIBLT003021 UYVY 180 degree rotation
//
extern TIBLTERROR UC003021(unsigned short srcwidth,
		    unsigned short srcheight,
		    unsigned short dstwidth,
		    unsigned short dstheight,
		    unsigned short srcstride, 
		    unsigned short dststride, 
		    unsigned char * srcptr,
		    unsigned char * dstptr);
int TIBLT003021()
{
  unsigned short srcwidth    = 864;
  unsigned short srcheight   = 480;
  unsigned short dstwidth    = 864;
  unsigned short dstheight   = 480;
  unsigned short srcstride   = 2*srcwidth;
  unsigned short dststride   = 2*dstwidth;
  char * input_file          = "./images/TIBLT003020_input.uyvy";
  char * output_file         = "./images/TIBLT003021_output.uyvy";
  char * srcptr              = NULL;
  char * dstptr              = NULL;
  TIBLTERROR ret             = TIBLT_ERR_NONE ;
  long input_file_size       = srcheight*srcstride;
  long output_file_size      = dstheight*dststride;

  printf("####################################################################################\n");
  printf("TIBLT003021: Running TIBLT003021 usecase %s \n",TIBLT003021_DESC);
  printf("TIBLT003021: input file size  is %d \n",input_file_size);
  printf("TIBLT003021: output file size is %d \n",output_file_size);
  srcptr    = malloc (input_file_size);
  if (!srcptr)
  {
    printf ("TIBLT003021: Out of memory\n");
    return -1;
  }

  if ((readInputFile(input_file, input_file_size,srcptr)) == -1)
  {
    free(srcptr);
    return -1;
  }

  dstptr = malloc (output_file_size);
  if (!dstptr)
  {
    printf ("TIBLT003021: Out of memory\n");
    free(srcptr);
    return -1;
  }

  ret = UC003021(srcwidth, srcheight, dstwidth, dstheight, srcstride, dststride, srcptr, dstptr);
  if (ret == TIBLT_ERR_NONE )
    saveOutputFile(output_file, output_file_size, dstptr);
  else
    printf ("TIBLT003021 false error code %d \n",ret);
  free(srcptr);
  free(dstptr);
  printf("####################################################################################\n");
  return 0;
}

//
//   Usecase TIBLT003022 UYVY 270 degree rotation
//
extern TIBLTERROR UC003022(unsigned short srcwidth,
		    unsigned short srcheight,
		    unsigned short dstwidth,
		    unsigned short dstheight,
		    unsigned short srcstride, 
		    unsigned short dststride, 
		    unsigned char * srcptr,
		    unsigned char * dstptr);
int TIBLT003022()
{
  unsigned short srcwidth    = 864;
  unsigned short srcheight   = 480;
  unsigned short dstwidth    = 480;
  unsigned short dstheight   = 864;
  unsigned short srcstride   = 2*srcwidth;
  unsigned short dststride   = 2*dstwidth;
  char * input_file          = "./images/TIBLT003020_input.uyvy";
  char * output_file         = "./images/TIBLT003022_output.uyvy";
  char * srcptr              = NULL;
  char * dstptr              = NULL;
  TIBLTERROR ret             = TIBLT_ERR_NONE ;
  long input_file_size       = srcheight*srcstride;
  long output_file_size      = dstheight*dststride;

  printf("####################################################################################\n");
  printf("TIBLT003022: Running TIBLT003022 usecase %s \n",TIBLT003022_DESC);
  printf("TIBLT003022: input file size  is %d \n",input_file_size);
  printf("TIBLT003022: output file size is %d \n",output_file_size);
  srcptr    = malloc (input_file_size);
  if (!srcptr)
  {
    printf ("TIBLT003022: Out of memory\n");
    return -1;
  }

  if ((readInputFile(input_file, input_file_size,srcptr)) == -1)
  {
    free(srcptr);
    return -1;
  }

  dstptr = malloc (output_file_size);
  if (!dstptr)
  {
    printf ("TIBLT003022: Out of memory\n");
    free(srcptr);
    return -1;
  }

  ret = UC003022(srcwidth, srcheight, dstwidth, dstheight, srcstride, dststride, srcptr, dstptr);
  if (ret == TIBLT_ERR_NONE )
    saveOutputFile(output_file, output_file_size, dstptr);
  else
    printf ("TIBLT003022 false error code %d \n",ret);
  free(srcptr);
  free(dstptr);
  printf("####################################################################################\n");
  return 0;
}

//
//   Usecase TIBLT002401 convert BGR24 to BGRx32 to RGB16
//
extern TIBLTERROR UC002401(unsigned short srcwidth,
		    unsigned short srcheight,
		    unsigned short dstwidth,
		    unsigned short dstheight,
		    unsigned short srcstride, 
		    unsigned short dststride, 
		    unsigned char * srcptr,
		    unsigned char * dstptr);
int TIBLT002401()
{
  unsigned short srcwidth    = 864;
  unsigned short srcheight   = 480;
  unsigned short dstwidth    = 864;
  unsigned short dstheight   = 480;
  unsigned short srcstride   = 4*srcwidth;
  unsigned short dststride   = 2*dstwidth;
  char * input_file          = "./images/TIBLT002401_input.rgbx";
  char * output_file         = "./images/TIBLT002401_output.rgb";
  char * srcptr              = NULL;
  char * dstptr              = NULL;
  TIBLTERROR ret             = TIBLT_ERR_NONE ;
  long input_file_size       = srcheight*srcstride;
  long output_file_size      = dstheight*dststride;

  printf("####################################################################################\n");
  printf("TIBLT002401: Running TIBLT002401 usecase %s \n",TIBLT002401_DESC);
  printf("TIBLT002401: input file size  is %d \n",input_file_size);
  printf("TIBLT002401: output file size is %d \n",output_file_size);
  srcptr    = malloc (input_file_size);
  if (!srcptr)
  {
    printf ("TIBLT002401: Out of memory\n");
    return -1;
  }

  if ((readInputFile(input_file, input_file_size,srcptr)) == -1)
  {
    free(srcptr);
    return -1;
  }

  dstptr = malloc (output_file_size);
  if (!dstptr)
  {
    printf ("TIBLT002401: Out of memory\n");
    free(srcptr);
    return -1;
  }

  ret = UC002401(srcwidth, srcheight, dstwidth, dstheight, srcstride, dststride, srcptr, dstptr);
  if (ret == TIBLT_ERR_NONE )
    saveOutputFile(output_file, output_file_size, dstptr);
  else
    printf ("TIBLT002401 false error code %d \n",ret);
  free(srcptr);
  free(dstptr);
  printf("####################################################################################\n");
  return 0;
}


//
//   Usecase TIBLT002203 convert BGR16 to BGRx32 size 480x864
//
extern TIBLTERROR UC002203(unsigned short srcwidth,
			   unsigned short srcheight,
			   unsigned short dstwidth,
			   unsigned short dstheight,
			   unsigned short srcstride, 
			   unsigned short dststride, 
			   unsigned char * srcptr,
			   unsigned char * dstptr);

int TIBLT002203()
{
  unsigned short srcwidth    = 864;
  unsigned short srcheight   = 480;
  unsigned short dstwidth    = 864;
  unsigned short dstheight   = 480;
  unsigned short srcstride   = 2*srcwidth;
  unsigned short dststride   = 4*dstwidth;
  char * input_file          = "./images/TIBLT002203_input.rgb";
  char * output_file         = "./images/TIBLT002203_output.rgba";
  char * srcptr              = NULL;
  char * dstptr              = NULL;
  TIBLTERROR ret             = TIBLT_ERR_NONE ;
  long input_file_size       = srcheight*srcstride;
  long output_file_size      = dstheight*dststride;

  printf("####################################################################################\n");
  printf("TIBLT002203: Running TIBLT002203 usecase %s \n", TIBLT002203_DESC);
  printf("TIBLT002203: input file size  is %d \n",input_file_size);
  printf("TIBLT002203: output file size is %d \n",output_file_size);
  srcptr    = malloc (input_file_size);
  if (!srcptr)
  {
    printf ("TIBLT002203: Out of memory\n");
    return -1;
  }

  if ((readInputFile(input_file, input_file_size,srcptr)) == -1)
  {
    free(srcptr);
    return -1;
  }

  dstptr = malloc (output_file_size);
  if (!dstptr)
  {
    printf ("TIBLT002203: Out of memory\n");
    free(srcptr);
    return -1;
  }

  ret = UC002203(srcwidth,srcheight,dstwidth, dstheight, srcstride, dststride, srcptr, dstptr);
  if (ret == TIBLT_ERR_NONE )
    saveOutputFile(output_file, output_file_size, dstptr);
  else
    printf ("TIBLT002203 false error code %d \n",ret);
  free(srcptr);
  free(dstptr);
  printf("####################################################################################\n");
  return 0;
}

//
//   Usecase TIBLT004010 RGB16 Global Alpha Blend
//
extern TIBLTERROR UC004010(unsigned short srcwidth,
		    unsigned short srcheight,
		    unsigned short dstwidth,
		    unsigned short dstheight,
		    unsigned short srcstride, 
		    unsigned short dststride, 
		    unsigned char * srcptr,
		    unsigned char * dstptr);
int TIBLT004010()
{
  unsigned short srcwidth    = 864;
  unsigned short srcheight   = 480;
  unsigned short dstwidth    = 864;
  unsigned short dstheight   = 480;
  unsigned short srcstride   = 2*srcwidth;
  unsigned short dststride   = 2*dstwidth;
  char * input_file_a        = "./images/TIBLT004010a_input.rgb";
  char * input_file_b        = "./images/TIBLT004010b_input.rgb";
  char * output_file         = "./images/TIBLT004010_output.rgb";
  char * srcptr              = NULL;
  char * dstptr              = NULL;
  TIBLTERROR ret             = TIBLT_ERR_NONE ;
  long input_file_size_a     = srcheight*srcstride;
  long input_file_size_b     = srcheight*srcstride;
  long output_file_size      = dstheight*dststride;

  printf("####################################################################################\n");
  printf("TIBLT004010: Running TIBLT004010 usecase %s \n",TIBLT004010_DESC);
  printf("TIBLT004010: input file size a is %d \n",input_file_size_a);
  printf("TIBLT004010: input file size b is %d \n",input_file_size_b);
  printf("TIBLT004010: output file size is %d \n",output_file_size);
  srcptr    = malloc (input_file_size_a);
  if (!srcptr)
  {
    printf ("TIBLT004010: Out of memory\n");
    return -1;
  }

  if ((readInputFile(input_file_a, input_file_size_a,srcptr)) == -1)
  {
    free(srcptr);
    return -1;
  }

  dstptr = malloc (output_file_size);
  if (!dstptr)
  {
    printf ("TIBLT004010: Out of memory\n");
    free(srcptr);
    return -1;
  }

  // read the second file into dstptr for blending
  if ((readInputFile(input_file_b, input_file_size_b,dstptr)) == -1)
  {
    free(srcptr);
    free(dstptr);
    return -1;
  }

  ret = UC004010(srcwidth, srcheight, dstwidth, dstheight, srcstride, dststride, srcptr, dstptr);
  if (ret == TIBLT_ERR_NONE )
    saveOutputFile(output_file, output_file_size, dstptr);
  else
    printf ("TIBLT004010 false error code %d \n",ret);
  free(srcptr);
  free(dstptr);
  printf("####################################################################################\n");
  return 0;
}

//
//   Usecase TIBLT002700 convert UYVY to BGR132
//
extern TIBLTERROR UC002700(unsigned short srcwidth,
			   unsigned short srcheight,
			   unsigned short dstwidth,
			   unsigned short dstheight,
			   unsigned short srcstride, 
			   unsigned short dststride, 
			   unsigned char * srcptr,
			   unsigned char * dstptr);

int TIBLT002700()
{
  unsigned short srcwidth    = 864;
  unsigned short srcheight   = 480;
  unsigned short dstwidth    = 864;
  unsigned short dstheight   = 480;
  unsigned short srcstride   = 2*srcwidth;
  unsigned short dststride   = 4*dstwidth;
  char * input_file          = "./images/TIBLT002700_input.uyvy";
  char * output_file         = "./images/TIBLT002700_output.rgba";
  char * srcptr              = NULL;
  char * dstptr              = NULL;
  TIBLTERROR ret             = TIBLT_ERR_NONE ;
  long input_file_size       = srcheight*srcstride;
  long output_file_size      = dstheight*dststride;

  printf("####################################################################################\n");
  printf("TIBLT002700: Running TIBLT002700 usecase %s \n", TIBLT002700_DESC);
  printf("TIBLT002700: input file size  is %d \n",input_file_size);
  printf("TIBLT002700: output file size is %d \n",output_file_size);
  srcptr    = malloc (input_file_size);
  if (!srcptr)
  {
    printf ("TIBLT002700: Out of memory\n");
    return -1;
  }

  if ((readInputFile(input_file, input_file_size,srcptr)) == -1)
  {
    free(srcptr);
    return -1;
  }

  dstptr = malloc (output_file_size);
  if (!dstptr)
  {
    printf ("TIBLT002700: Out of memory\n");
    free(srcptr);
    return -1;
  }

  ret = UC002700(srcwidth,srcheight,dstwidth, dstheight, srcstride, dststride, srcptr, dstptr);
  if (ret == TIBLT_ERR_NONE )
    saveOutputFile(output_file, output_file_size, dstptr);
  else
    printf ("TIBLT002700 false error code %d \n",ret);
  free(srcptr);
  free(dstptr);
  printf("####################################################################################\n");
  return 0;
}
