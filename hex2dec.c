/******************************************************************************
*									      *
*	File:     hex2dec.c						      *
*	Author:   Alison Chaiken <alchaiken@gmail.com>          	      *
*	Created:  Wed Jul 14 18:40:04 PDT 2010				      *
*	Contents: Convert hex-formatted numbers to decimal format and         *
*       and print the results.	Accepts input on command-line or from         *
*       stdin.                                                                *
*									      *
*       Distributed under version 3 of the GNU General Public License,        *
*       see http://www.gnu.org/licenses/gpl.html for more info.               *
*									      *
******************************************************************************/

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXSTRING 100
/* #define DEBUGMODE */

void process_token (char *);
void process_line (char *);

int
main(int argc, char *argv[])
{

    int i;
    
    char            instring[MAXSTRING], *stringp;

    if (argc > 1){ /* args to be converted on command line */
	strcpy(instring,argv[1]);
	for (i=2;i<argc;i++){
	    strcat(instring," ");
	    strcat(instring,argv[i]);
	}	
        #ifdef DEBUGMODE
	printf("instring is %s.\n", instring);
        #endif

	process_line(instring);

    }

    else {
	/* args from stdin */
	while (fgets(instring,MAXSTRING,stdin) != NULL){
	    stringp = instring;
	    /* line from stdin ends in '\n' */
	    /*	    while ((*stringp++ = getchar())!= '\n') */
    	    while (*stringp++ != '\n') 
		;
	    /* make last character a null instead of '\n' */
	    *--stringp='\0';

        #ifdef DEBUGMODE
	printf("instring is %s.\n", instring);
        #endif

	process_line(instring);
	}
    }

    printf("\n");
    
    exit(0);

}

void process_line(char *thisline)
{
    char *next_token;
    
    next_token = strtok(thisline," ");
    do {
	process_token(next_token);
    } while ((next_token = strtok(NULL," ")) != NULL) ;
    
}

void process_token (char *str_token)
{
    int outnum = 0,  digits = 0, startdigit = 0, coeff  = 0, thisdigit = 0, i;

	digits = strlen(str_token);
	if ((str_token[0] == 48) && (str_token[1] == 120)) {
	    startdigit = 2;		/* skip over 0x prefix */
	}
	else {
	    startdigit = 0;	
	}
	for (i = startdigit; i < digits; i++) {
	    thisdigit = str_token[i];

	    if ((thisdigit >= 48) && (thisdigit <= 57)) {
		/*
		 * in ASCII, zero is 48, nine is 57 
		 */
		coeff = thisdigit - 48;
	    } else if ((thisdigit >= 65) && (thisdigit <= 70)) {
		/*
		 * A is 65, F is 70
		 */
		coeff = thisdigit - 55;
	    } else if ((thisdigit >= 97) && (thisdigit <= 102)) {
		/*
		 * a is 97, f is 102 
		 */
		coeff = thisdigit - 87;
	    } else {
		printf
		    ("Illegal digit %c: use A-F, a-f and 0-9 with optional leading 'Ox'.\n", thisdigit);
		exit(1);
	    }
	    outnum += coeff * pow(16, (digits - i - 1));
	}
	if (startdigit == 0) {
	        #ifdef DEBUGMODE
		printf("Ox%s = %d.\n", str_token, outnum);
		#else
	        printf("%d ", outnum);
		#endif
	    }
	else {
	        #ifdef DEBUGMODE
	        printf("%s = %d.\n", str_token, outnum);
		#else
	        printf("%d ", outnum);
		#endif
	}
	return;
}
