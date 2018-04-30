/*
 * =====================================================================================
 *
 *       Filename:  sender.h
 *
 *    Description:  Header fuer sender von Nachrichten aus /dev/shm 
 *
 *        Version:  1.0.0
 *        Created:  04/30/2018 10:20:05 AM
 *       Revision:  none
 *       Compiler:  gcc52
 *
 *         Author:  Ovidiu - Dan Bogat [ic17b501], ic17b501@technikum-wien.at
 * =====================================================================================
 */
#ifndef __sender_h
#define __sender_h

const char *help_message =
  "       <<< sender help >>>       \n"
  "---------------------------------\n"
  "-h           Gibt diese Hilfe aus\n"
  "---------------------------------\n";

void print_help(void);

#endif /* sender.h */