//****************************************************************************
// FILE NAME:    tibltMenu.c
//****************************************************************************
//
//   Revision History
//   Version      Author         yyyy/mm/dd      Description
//     0.1      Eric Luong       2010/01/22     File creation
//     0.2      Eric Luong       2010/04/12     Modified for Android environment
// 
//****************************************************************************

/* Standard library include files */
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include "inc/TIBLT.h"
#include "inc/usecases.h"
//#include "inc/utils.h"

/* "Local standard" include files ("compiler.h") */

/* Program-specific include files (#defines,typedef,struct,union)*/
#define  MAXLINE   1024
#define  UC_WIDTH  11
int      g_count=0;

// usecases mapping table structure
typedef struct
{
  char *      usecase;
  int    (*ptr2Usecase)();
  char *      description;
} tiblt_usecase_t;

// usecases mapping table 
tiblt_usecase_t usecase_tbl[] =
{
  { "TIBLT001050",  &TIBLT001050, "Solid Fill BGRA32" },
  { "TIBLT002300",  &TIBLT002300, "Convert BGR24 to BGRx32 " },
  { "TIBLT003010",  &TIBLT003010, "RGB16 90 degree rotation " },
  { "TIBLT003011",  &TIBLT003011, "RGB16 180 degree rotation " },
  { "TIBLT003012",  &TIBLT003012, "RGB16 270 degree rotation " },
  { "TIBLT003020",  &TIBLT003020, "UYVY 90 degree rotation " },
  { "TIBLT003021",  &TIBLT003021, "UYVY 180 degree rotation " },
  { "TIBLT003022",  &TIBLT003022, "UYVY 270 degree rotation " },
  { "TIBLT002401",  &TIBLT002401, "Convert BGRx32 to RGB16 " },
  { "TIBLT002203",  &TIBLT002203, "Convert RGB16 to BGRx32 " },
  { "TIBLT004010",  &TIBLT004010, "RGB16 Global Alpha Blend " },
  { "TIBLT002700",  &TIBLT002700, "Convert UYVY to BGR132 " },
  { "",  NULL , ""}, // end of table marker
};

/****************************************************************************

 FUNCTION NAME:   tiblt_get_input

 DESCRIPTION:     Get user input line into *s 

 CAUTIONS:

*****************************************************************************
*/
int tiblt_get_input(char *s, int lim)
{
  char c='\0';
  int  i;
  for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
    s[i]=c;
  if (c == '\n')
  {
     s[i] = c;
     ++i;
  }
  s[i] = '\0';
  return i;
}

/****************************************************************************

 FUNCTION NAME:   tiblt_print_help

 DESCRIPTION:     display the help menu

 CAUTIONS:

*****************************************************************************
*/
int tiblt_print_input_file_format(void)
{
  int			rtn_val=0;
  printf( "\n" );
  printf( "\n" );
  printf( " #\n" );
  printf( " # This is 2D TIBLT library use case descriptions file\n" );
  printf( " # tibltTest will parse this file and run all the use case\n" );
  printf( " # defined in this file\n" );
  printf( " # File format\n" );
  printf( " # '#' at the begining of the line is treat at comment (The parser will ignore the entire line)\n" );
  printf( " # ':' field deliminter\n" );
  printf( " #\n" );
  printf( " # usecase #        description              input image           output image\n" );
  printf( " # ----------- ---------------------- ------------------------ ----------------------\n" );
  printf( " # TIBLTxxxxxx:test case  descriptions:TIBLTxxxxxxxxx_input.zzz:TIBLTxxxxxx_output.yyy\n" );
  printf( " #\n" );
  printf( " # TIBLT001000 - TIBLT001999  Solid Fill Operations\n" );
  printf( " #\n" );
  printf( " # TIBLT002000 - TIBLT002999  Copy Operation\n" );
  printf( " #\n" );
  printf( " # TIBLT003000 - TIBLT003999  Rotation Operations\n" );
  printf( " #\n" );
  printf( " # TIBLT004000 - TIBLT004999  Global Alpha Blend Operations\n" );
  printf( " #\n" );
  printf( " # TIBLT005000 - TIBLT005999  Local (Per-Pixel) Blend Operations\n" );
  printf( " #\n" );
  printf( " #\n" );
  printf( " TIBLT001050:Solid Fill BGRA32:TIBLT001050_input.rgb:TIBLT001050_output.rgb\n" );
  printf( " TIBLT002300:Convert BGR24 to BGRx32:TIBLT002300_input.bgr:TIBLT002300_output.bgra\n" );
  printf( " TIBLT003010:RGB16 90 degree rotation \n" );
  printf( "\n" );
  return(rtn_val);
}
/****************************************************************************

 FUNCTION NAME:   tiblt_print_help

 DESCRIPTION:     display the help menu

 CAUTIONS:

*****************************************************************************
*/
int tiblt_print_help(void)
{
  int			rtn_val=0;
  printf( "\n" );
  printf( "        TIBLT unit test menu \n" );
  printf( "        Date build 04/20/2010\n" );
  printf( "\n" );
  printf( "a     - Run all available usecases.\n" );
  printf( "s     - Show all available usecases.\n" );
  printf( "      - Enter usecases ID to run the usecase.\n" );
  printf( "?     - help.\n" );
  printf( "w     - Who Rocks !!!.\n" );
  printf( "q     - Quit.\n" );
  printf( "\n" );
  return(rtn_val);
}

/****************************************************************************

 FUNCTION NAME:   tiblt_show_all_usecases

 DESCRIPTION:     show all usecase

 CAUTIONS:

*****************************************************************************
*/
void tiblt_show_all_usecases(void)
{
  int                   i=0;
  i=0;

  while (strcmp(usecase_tbl[i].usecase,"") != 0)
  {
      printf("%s  %s\n",usecase_tbl[i].usecase,usecase_tbl[i].description);
      i++;
  }

  printf("\n");
  printf( "-----------  Enter usecases ID to run the usecase.\n" );
  printf("\n");
}

/****************************************************************************

 FUNCTION NAME:   tiblt_run_all_usecases

 DESCRIPTION:     run all usecase

 CAUTIONS:

*****************************************************************************
*/
void tiblt_run_all_usecases(void)
{
  int                   i=0;
  i=0;
  while (strcmp(usecase_tbl[i].usecase,"") != 0)
  {
      printf("Running usecase %s \n",usecase_tbl[i].usecase);
      usecase_tbl[i].ptr2Usecase();
      g_count++;
       i++;
  }
}


/****************************************************************************

 FUNCTION NAME:   tiblt_run_usecase

 DESCRIPTION:     run one usecase 

 CAUTIONS:

*****************************************************************************
*/
int tiblt_run_usecase(char * uc)
{
  int   i=0;
  int   j=0;
  int   found;
  i=0;

  while (strcmp(usecase_tbl[i].usecase,"") != 0)
  {
      /*printf("compare usecase pass in %s with %s in table \n",uc,usecase_tbl[i].usecase);*/
      found = 1;
      for (j=0; j<UC_WIDTH ; j++)
        if (uc[j] != usecase_tbl[i].usecase[j])
          found =0;
        if (found == 1)
        {
           printf("Found usecase %s \n",usecase_tbl[i].usecase);
           usecase_tbl[i].ptr2Usecase();
           g_count++;
           return 0;
        }
        i++;
  }
  return -1;
}

/****************************************************************************

 FUNCTION NAME:   tiblt_menu

 DESCRIPTION:     

 CAUTIONS:

*****************************************************************************
*/
int main(int argc, char *argv[])
{
  int			fd;
  fd_set		read_fd_set;
  fd_set		copy_fd_set;
  int			rtn_val=0;
  char                  line[MAXLINE];
  int                   i=0;
  char *                uc;


  // check to see the user pass in any usecase for arguments
  // if so check to see if the input usecase valid and run the usecase
  if ( argc > 1)
  {
    // parse the input argv and find the usecase in usecase table
    // if it matches run the usecase
      while(argc--)
      {
        i=0;
        while (strcmp(usecase_tbl[i].usecase,"") != 0)
        {
          if (strcmp(*argv,usecase_tbl[i].usecase) == 0)
          {
             printf("Running usecase %s \n",usecase_tbl[i].usecase);
             usecase_tbl[i].ptr2Usecase();
  	     g_count++;
          }
  	  i++;
        }
        *argv++;
      }
  }

  // menu driven mode
  // print tiblt prompt 
  printf("tiblt, %d> ",g_count);

  for(;;)
    {
	  /* get input line */
	  tiblt_get_input(line,MAXLINE);
	  /* parse input command */
	  switch (line[0])
	  {
	    case 'h':
	    case '?':
	      tiblt_print_help();
	      break;
	    case 'p':
	      tiblt_print_input_file_format();
	      break;
	    case 'a':
	      printf( "a     - Run all available test.\n" );
	      tiblt_run_all_usecases();
	      break;
	    case 's':
	      printf("\n");
	      printf( "-----------  Available usecases.\n\n" );
	      tiblt_show_all_usecases();
	      break;
	    case 'w':
	      printf( "\n");
	      printf( "*************  Eric!!!  *************\n");
	      printf( "\n");
	      break;
	    case 'q':
	      fflush(stdout);
	      return(rtn_val);
	      break;
	    case ' ':
	    case '\n':
	      break;
	    default:
	      if (tiblt_run_usecase(line) == -1)
		printf("tiblt: command not found: %s",line);
	      break;
	  }
	  printf("tiblt, %d> ",g_count);
    }
  return(rtn_val);
}
