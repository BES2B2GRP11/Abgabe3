/*
 * =====================================================================================
 *
 *       Filename:  error_handling.c
 *
 *    Description:  Main file for error handling
 *
 *        Version:  1.0
 *        Created:  26.02.2018 18:15:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ovidiu - Dan Bogat [ic17b501], ic17b501@technikum-wien.at
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include "error_handling.h"

/* /\*  */
/*  * ===  FUNCTION  ====================================================================== */
/*  *         Name:  print_usage */
/*  *  Description:  Prints the synopsis for this prorgram */
/*  * ===================================================================================== */
/*  * */
/*  *\//\*! */
/*     * @author Ovidiu - Dan Bogat */
/*     *	@brief Prints the usage for the programm  */
/*     *	@version 1.0.0 */
/*     *	@date 2018/03/01 */
/*     * ===================================================================================== */
/*     *\/ */
/* void print_usage() */
/* { */
/*   fprintf(stdout, "Usage: myfind <path> <action> [paramters]\n"); */
/*   fprintf(stdout, "  Try: myfind -help\n"); */
/* }		/\* -----  end of function print_help_message  ----- *\/ */


/* /\*  */
/*  * ===  FUNCTION  ====================================================================== */
/*  *         Name:  print_help */
/*  *  Description:  prints the help for myfind */
/*  * ===================================================================================== */
/*  * */
/*  *\//\*! */
/*     * @author Ovidiu - Dan Bogat */
/*     *	@brief Prints correct help and usage for the programm with additional information */
/*     *	@version 1.0.0 */
/*     *	@date 2018/03/01 */
/*     * ===================================================================================== */
/*     *\/ */
/* void print_help ( ) */
/* { */
/*   fprintf(stdout,"<<myfind v1.0 - help>>\n"); */
/*   fprintf(stdout, "Usage: myfind <path> <action> [paramters]\n"); */
/*   fprintf(stdout," %10s | %-15s %-50s\n", "----------", "---------------","---------------------------------------"); */
/*   fprintf(stdout," %10s | %-15s %-50s\n", "<action>", "[parameters]","Description"); */
/*   fprintf(stdout," %10s | %-15s %-50s\n", "----------", "---------------","---------------------------------------"); */
/*   fprintf(stdout," %10s | %-15s %-50s\n", "-user", "<name>/<uid>","finde Directoryeinträge eines Users"); */
/*   fprintf(stdout," %10s | %-15s %-50s\n", "-name", "<pattern>", "finde Directoryeinträge mit passendem Namen"); */
/*   fprintf(stdout," %10s | %-15s %-50s\n", "-type", "[bcdpfls]", "finde Directoryeinträge mit passendem Typ"); */
/*   fprintf(stdout," %10s | %-15s %-50s\n", "-print", "", "gibt den Namen und Informationen des Directoryeintrags aus"); */
/*   fprintf(stdout," %10s   %-15s %-50s\n", "", "", "analog zu {3}find -ls"); */
/*   fprintf(stdout," %10s | %-15s %-50s\n", "-nouser", "", "finde Directoryeinträge ohne User"); */
/*   fprintf(stdout," %10s | %-15s %-50s\n", "-path", "<pattern>", "finde Directoryeinträge mit passendem Pfad (inkl. Namen)"); */
/*   fprintf(stdout," %10s | %-15s %-50s\n", "-group", "<name>/<gid>", "finde Directoryeinträge einer bestimmten Gruppe");	 */
/*   fprintf(stdout," %10s | %-15s %-50s\n", "-nogroup", "", "finde Directoryeinträge ohne Gruppe"); */
/*   fprintf(stdout," %10s | %-15s %-50s\n", "-version", "", "gibt die Version des Programmes aus"); */
/*   fprintf(stdout," %10s   %-15s %-50s\n", "", "", "myfind -version"); */
/*   fprintf(stdout," %10s | %-15s %-50s\n", "-help", "", "gibt diese Hilfe aus"); */
/*   fprintf(stdout," %10s   %-15s %-50s\n", "", "", "myfind -help"); */
/* }		/\* -----  end of function print_help  ----- *\/ */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  print_error
 *  Description:  Print the error string to stderr
 * =====================================================================================
 *
 *//*!
    * @author Ovidiu - Dan Bogat
    * @brief Actually prints the error mesage
    * @details
    * Print the actual error message, along with the strerror of errno if sys_meld > 0
    * @param sys_meld indicates whether strerror is called or not (int)
    * @param fmt format for error string (const char*)
    * @param az - given parameters to function (va_list)
    * @version 1.0.0
    * @date 2018/03/01
    * =====================================================================================
    */
static void print_error(int sys_meld, const char *fmt, va_list az)
{
  char buffer[4096];
  sys_meld=sys_meld;
  vsprintf(buffer, fmt, az);
  //  if(sys_meld && errno != 0)
  sprintf(buffer+strlen(buffer), ": %s\n", strerror(errno));
  fflush(NULL);
  return;

}		/* -----  end of function print_error  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  handle_error
 *  Description:  Handle a given error (FATAL or WARN) witrh strerror on errno
 * =====================================================================================
 *
 *//*!
    * @author Ovidiu - Dan Bogat
    * @brief Handles errros according to errno and the defined ERRORTYPE
    * @param error_type (enum ERRORTYPE)
    * @version 1.0.0
    * @date 2018/03/01
    * =====================================================================================
    */
void handle_error (enum ERRORTYPE error_type, const char* fmt, ...)
{
  va_list az;
  
  va_start(az,fmt);

  switch(error_type)
    {
    case INFO:
    case DBUG:
    case WARN:
      print_error(1,fmt,az);
      break;
    case FATAL:
      print_error(1,fmt,az);
      break;
    default:
      break;
    }

  va_end(az);

  if(error_type==FATAL)
    {
      if(errno == EINVAL)
	{
	  exit(errno);
	}
    }
}		/* -----  end of function handle_error  ----- */


void DBG(const char* fmt, ...)
{
  char buffer[4096];
  va_list az;
  va_start(az,fmt);
  sprintf(buffer, "[DEBUG] ");
  vsprintf(buffer+8, fmt, az);
  fprintf(stderr,"%s\n",buffer);
  fflush(NULL);
  va_end(az);
}		/* -----  end of function DBG  ----- */
