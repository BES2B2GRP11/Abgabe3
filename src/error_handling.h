/*
 * =====================================================================================
 *
 *       Filename:  error_handling.h
 *
 *    Description:  Handles errors 
 *
 *        Version:  1.0.0
 *        Created:  26.02.2018 18:15:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ovidiu - Dan Bogat [ic17b501], ic17b501@technikum-wien.at
 *
 * =====================================================================================
 */
#ifndef __error_handling_h
#define __error_handling_h

enum ERRORTYPE { INFO, DBUG, WARN, FATAL };

//void print_usage(void);
//void print_help(void);
void handle_error(enum ERRORTYPE, const char*,...);
void DBG(const char*,...);

#endif /* error_handling.h */
