/* Demonstrates breaking up a string in much the same manner as is done by 
 * the standard library function strtok.  It's also an actually practical 
 * occurrence of a triple pointer (char ***).
 * 
 * Prepared for tutorial purposes by David Warde-Farley, CSC209H Winter 2008
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 100

/*
 * This function takes a source string as it's first argument, a one 
 * character separator, and a pointer to an external char ** used for
 * returning the substrings. 
 * 
 * The return value of the function is the number of tokens found delimited 
 * by sep. The function allocates space for that many (char *) pointers, 
 * and fills it with pointers to the beginnings of the various substrings. 
 * 
 * It stores a pointer to this array of (char *) pointers in *output so
 * in a sense it is "returning" more than one thing. This is a common idiom
 * in C programming.
 * 
 * NOTE that this function MODIFIES the memory pointed to by srcstr, much 
 * in the same way as the standard library's strtok() function. If you want
 * to preserve the original string in either case, you'd want to first
 * make a copy of it and call str_separate() on the copy (same goes if 
 * you're using strtok).
 */
int 
str_separate(char *srcstr, char sep, char ***output)
{
	/* Assume we have a properly NULL-terminated string. */
	int len = strlen(srcstr);

	/* Initialize the number of tokens to 0. */ 
	int numparts = 0;

	/* A temporary pointer to a char pointer we'll use later. */
	char **currentpart;
	
	/* 
	 * Replace every instance of sep with a NULL character. 
	 * This has the effect of turning one string into many; you can
	 * think of the first string beginning where the original string
	 * did, and ending at the first NULL, then the second string
	 * beginning at the character right after that NULL.
	 */
	int i;
	for (i = 0; i < len; i++)
	{
		if (srcstr[i] == sep)
		{
			srcstr[i] = '\0';	
			numparts++;
		}
	}

	/* 
	 * Increment numparts one more time, for the last substring. 
	 * i.e. if we found N separators we have N+1 parts. If two
	 * separator characters appear together, or there is a 
	 * separator at the end, then some of these become the empty
	 * string "".
	 */
	numparts++;
	
	/* Allocate space for our pointers to the various substrings
	 * Note that here we dereference output once, to assign to the
	 * char ** we declared in the calling function (i.e. main())
	 */
	*output = malloc(numparts * sizeof(char *));

	/* You should always check the return value of malloc! */
	if (*output == NULL)
	{
		perror("malloc() call in str_separate");
		exit(1);
	}
	
	/* Start with currentpart pointing to the first allocated pointer.
	 * We'll use this to step through the array of char * pointers.
	 */
	currentpart = *output;

	/*
	 * The first char * pointer should point to the beginning of the 
	 * original string, as that is necessarily the first token.
	 */
	*currentpart = srcstr;
	
	/* 
	 * We've placed \0's in the place of every occurrence of sep; so
	 * a new token/substring begins at the character AFTER a \0
	 * (excluding the very last \0, which we will never hit with this
	 * loop).
	 * 
	 * This loop finds all the NULLs we placed in the string, and stores
	 * a pointer to the character after each NULL in *currentpart, after
	 * incrementing currentpart to move to the next char * slot.
	 */
	
	for (i = 0; i < len; i++) /* < len: we never get to the last '\0', 
							   * since strlen gives us the length of
							   * the string, not including the NULL */
	{
		if (srcstr[i] == '\0') {
			currentpart++;
			*currentpart = &(srcstr[i+1]);
		}
	}
	
	/* 
	 * We only return the integer numparts, but in fact we are 
	 * "implicitly returning" the contents of *output, since this
	 * was declared outside str_separate but modified by it.
	 */
	return numparts; 
}




int
main(int argc, char **argv)
{
	char buf[BUFSIZE];
	char **mystrptrs;
	char sep = ' ';
	int numparts;
	int j;
	strncpy(buf, "CSC209 Winter 2008 taught by Karen Reid", 100);

	/* Just to prove to ourselves that the string is really in there... */
	printf("Contents of buf: %s\n", buf);
	printf("Address of buf: %p\n", buf);

	numparts = str_separate(buf, ' ', &mystrptrs);
	

	/* Print out the number of tokens we found */
	printf("Tokens found with delimiter '%c': %d\n\n", sep, numparts);
	
	/* Header for our printout */
	printf("Token                        ");
	printf("Word                     Starting address\n");
	printf("-----------------------------");
	printf("-----------------------------------------\n");
	for (j = 0; j < numparts; j++)
	{
		printf("%5d\t%30s\t%30p\n",j+1,mystrptrs[j],mystrptrs[j]);
	}

	/* We'll print this again just to show that buf was modified */
	printf("\nContents of buf: %s\n", buf);
	printf("(will only display until the first NULL character)\n");
	
	/* 
	 * str_separate made a call to malloc(); you should make it a 
	 * practice to always make sure you free() what you malloc()
	 * when you're done with it, even though it strictly doesn't
	 * matter in this case since we're just exiting.
	 *	 
	 * DON'T:
	 *   - try to free() memory you didn't allocate.
	 *   - try to free() things that have already been free()'d.
	 *   - try to dereference a pointer to memory you've free()'d
	 */	
	
	free(mystrptrs);
	return 0;
}
