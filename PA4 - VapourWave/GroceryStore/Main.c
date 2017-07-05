/*
* =====================================================================================
*
*       Filename:  Main.c
*
*    Description:  This is the driver file for the program.
*
*        Version:  1.0
*        Created:  2/16/2017 10:04:34 PM
*       Revision:  none
*       Compiler:  msft c
*
*         Author:  Edgar Perez (eap), edgar.a.perez@wsu.edu
*   Organization:  Washington State University
*
* =====================================================================================
*/

#include	"Groceries.h"

int main(void) {
	srand((unsigned int)(time(NULL)));
	runApp();
	return 0;
}