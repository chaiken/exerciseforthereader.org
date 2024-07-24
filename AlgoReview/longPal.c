/******************************************************************************
*									      *
*	File:     longPal.c						      *
*	Author:   Alison Chaiken <alison@bonnet.exerciseforthereader.org>     *
*	Created:  Tue Mar 29 16:15:21 PDT 2011				      *
*	Contents: STRING QUESTION							      *
*	Write code to find the longest palindrome in a string. e.g. For	      *
*	ABACDDCQR the longest palindrom is CDDC.			      *
*									      *
*	Tricky aspects: 						      *
*	1. Longest palindrome may not be symmetrically in center of string.   *
*	It could be the first or last n chars.				      *
*	2. The char in the center need not be duplicated.  It (alone) can be a*
*	singleton.   Let's call these "odd" palindromes, as opposed to "even" *
*	palindromes that have a pair of duplicates in the center.	      *
*	3. If the center char is a singleton, then the chars which are	      *
*	duplicates are not consecutive.   Thus we must check two chars ahead  *
*	for palindromes, not just one.					      *
*	4. A sequential duplicate pair ("DD") need not be at the center of a  *
*	palindrome.							      *
*									      *
*									      *
*	Comments:							      *
*	1. Recursion makes no sense here.  We are not sorting or counting random*
*	input but sequentially processing ("walking") a structure that is     *
*	already ordered.						      *
*	2. If we walk the string from start to finish and we have already found a*
*	palindrome of length k, we need not proceed past element n - k.	      *
*	3. For char i of an n-char string, the longest possible palindrome    *
*	centered at i is (for odd case) = (2*i) - 1.    		      *
*	4. Sparse case: for a given input string, the maximum possible length of*
*	a palindrome = (total number of duplicate chars in the string) + 1.   *
*	For an 80-character string then, if there is only one char that is    *
*	ever repeated, we need not search for palindromes longer than 3 chars.*
*	So we could use a pre-count of duplicates as a condition to terminate *
*	a search.							      *
*	5. Since we don't want to modify the elements of the string, we can store it*
*	either in a pointer or an array.				      *
*									      *
*	Pseudocode:							      *
*	1. Presume we are presented with the whole string at once, and that it is*
*	not part of a stream.						      *
*	2. Read the string into a char array, get totalchars.  		      *
*	3. Handle special cases: If there are no chars, exit.  If there is 1  *
*	char, print it and exit. If the string is 2 chars, check whether chars*
*	are equal and print result.  Otherwise, proceed.		      *
*	4. Initialization: maxlength = currlength = 0.  Palcenter pointer to start of*
*	longest palindrome is NULL.					      *
*	5. While charsleft is >= totalchars - maxlength, compare current char i*
*	with next char i++, and, if they are equal, look for an even	      *
*	palindrome centered here.					      *
*									      *
*		   j = i						      *
*		   while (char[(j-1)--] = char[(j+2)++]) increment currlength *
*		   if currlength > maxlength, maxlength = currlength	      *
*		   palcenter = i					      *
*		   							      *
*	6. Now, irrespective of even results, Look for odd palindrome with    *
*	same center by considering whether char (i-1) and (i+1) are equal.    *
*									      *
*		   j = i						      *
*		   while (char[(j-1)--] = char[(j+1)++]) increment currlength *
*		   if currlength > maxlength, maxlength = currlength	      *
*		   palcenter = i					      *
*									      *
*	7. Done processing char i; continue with next.			      *
*									      *
*	8. Print longest palindrome with its length.			      *
*									      *
*	Strategy questions:						      *
*	1. Does it make sense to start in the middle, or is starting in the ends*
*	just as good?							      *
*	2. We could consider each char as a potential palindrome center, and  *
*	evaluate in either direction from it.  Would that involve unnecessary *
*	duplication?							      *
*	3. Is there a more efficient number-theoretic method  based on turning*
*	the chars into their ASCII codes and doing math on the value?	      *
*	4. Put '\0' at start of string, so a test for null is the termination *
*	check we have to do in either direction.   Increment totalchars.      *
*									      *
*	Slowly typed by Alison Chaiken. Offered under GPLv3 or even better.   *
*									      *
******************************************************************************/

/* test odd case:
   [alison@bonnet AlgorithmsReview]$ clear; echo "123123123he12345llffflloacaworld" | ./longPal
   llfffll

   test even case:
   [alison@bonnet AlgorithmsReview]$ clear; echo "123123123he12345lllloacaworld" | ./longPal
   llll

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHARS 256

struct pal {
    char * palstart;
    int pallen;  
};

// test whether current position is center char of a palindrome
struct pal *testmirror(char *teststart, int currpos, struct pal *currmax)
{
    int offset  = 1;
    char firstchar = '\0', secondchar = '\0';
    struct pal currpal;
    struct pal besteven;
    currpal.pallen = 0;
    currpal.palstart = teststart + currpos;
    besteven.pallen = 0;
    besteven.palstart = '\0';

    /*
      Check for even palindromes.
      +1 because we start comparison with current char
    */
    sscanf((currpal.palstart),"%c",&firstchar);
    sscanf((currpal.palstart + 1),"%c",&secondchar);
    while (firstchar == secondchar)
	{
	    besteven.pallen += 2;
	    offset++;
	    sscanf(((currpal.palstart + 1) - offset),"%c",&firstchar);
	    sscanf((currpal.palstart +  offset),"%c",&secondchar);
	}
    /* note that the axis, which is what we are finding, is ((besteven.pallen/2)-1)
       chars advanced from the start of the palindrome */
    if (besteven.pallen)
	besteven.palstart = currpal.palstart - ((besteven.pallen/2) - 1);
    
    /*
      odd palindrome
      compare chars on either side of current char
    */
    offset = 1;
    sscanf((currpal.palstart - 1),"%c",&firstchar);
    sscanf((currpal.palstart + 1),"%c",&secondchar);
    while (firstchar == secondchar)
	{
	    currpal.pallen = (2*offset) + 1;
	    offset++;
    	    sscanf((currpal.palstart - offset),"%c",&firstchar);
	    sscanf((currpal.palstart + offset),"%c",&secondchar);
	}
    if (currpal.pallen)
	currpal.palstart -= currpal.pallen/2;
    
    // choose longest odd palindrome unless longest even is better
    if (besteven.pallen > currpal.pallen)
		currpal = besteven;
    if (currpal.pallen > currmax->pallen)
	{
	    currmax->palstart = currpal.palstart;
	    currmax->pallen = currpal.pallen;
	}

    return(currmax);
}

int main()
{
    int numchars = 0, pos = 0;
    char * instring = (char *) malloc(sizeof(char)*MAXCHARS);
    char * outstring = (char *) malloc(sizeof(char)*MAXCHARS);
    struct pal maxpal;
    maxpal.palstart = '\0';
    maxpal.pallen = 0;
    
    
    /* I/O preliminaries */
    if (!scanf("%s",instring)) 
	{
	    fprintf(stderr, "No input.\n");
	    exit(EXIT_FAILURE);
	}
    numchars = strlen(instring);
    //printf("Input is %s\n",instring);
    
    // take care of corner cases
    if (numchars == 1)
	{
	    printf("%c\n",*instring);
	    exit(EXIT_SUCCESS);
	}
    if (numchars == 2)
	{
	    if (*instring == *(instring+1))
		printf("%s\n",instring);
	    else printf("No palindromes.\n");
    	    exit(EXIT_SUCCESS);
	}

    /*
      Main Work Loop

      Note if pos > (numchars - maxpal.pallen) then we are too close to
      the end to find a longer palindrome than the best one we already have
    */
    while (pos <= (numchars - maxpal.pallen))
	{
	    maxpal = *testmirror(instring,pos,&maxpal);
	    pos++;
	}
    

    /*
      Output Result

      need to make sure that the string is null-terminated
    */
    if (maxpal.pallen)
	{
	    //  +1 since snprintf counts terminating null it adds
	    snprintf(outstring,maxpal.pallen+1,"%s",maxpal.palstart);
	    printf("%s\n",outstring);
	}
    else printf("No palindromes.\n");

    free(instring);
    free(outstring);
    exit(EXIT_SUCCESS);
}
