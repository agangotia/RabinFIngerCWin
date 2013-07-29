// RabinWin.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>	// for 'open'
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>	// for 'isprint'

#include "rabinpoly.h"

#define FINGERPRINT_PT 0xbfe6b8a5bf378d83LL
// value take from LBFS fingerprint.h. For detail on this,
// refer to the original rabin fingerprint paper.
#define BUFSIZE	1024

char* progname;

void usage() {
	fprintf(stderr, "Usage: %s <file-to-read> <sliding-window-size>\n", progname);
	fprintf(stderr, "\tExample) %s testfile 16\n", progname);

}
using namespace std;

int run_task(char* filename, int windowsize) {

	size_t count;
	FILE* rFile;

	u_int64_t rabinf;
	char buf[BUFSIZE];// buffer to read data in

	// INITIALIZE RABINPOLY CLASS
	window myRabin(FINGERPRINT_PT, windowsize);

	// RESET if you want to clear up the buffer in the RABINPOLY CLASS
	myRabin.reset();

	// OPEN THE FILE
	rFile = fopen(filename, "r");
	if(rFile!=NULL){

		while( (count = fread(buf,1, BUFSIZE,rFile)) > 0 ) {

			// FEED RABINPOLY CLASS BYTE-BY-BYTE
			for (int i=0; i<count; i++) {
				rabinf = myRabin.slide8(buf[i]);

				/*if (isprint((int)buf[i])) {
					printf("%c\t", buf[i]);
				} else {
					printf("0x%x\t", buf[i]);
				}*/
				printf("==>\t%lu\n", rabinf);
			}

		}
	}

	fclose(rFile);
	return 1;
}

int main() {

	int   ret;
	char* filename;
	int   windowsize;

	try{
		   printf("Lets See");
	// READ ARGUMENTS
	filename = "Time2.mp3";
	//filename = "ReadMe.txt";


	windowsize = 48;
	// READ THE FILE AND COMPUTE RABIN FINGERPRINT
	ret = run_task(filename, windowsize);
	printf("Lets See what is returned::%d",ret);

	  }catch(...)
	  {
		  fwprintf(stdout,L"Something Bad happen");
		  return 0;
	  }
	

	return ret;

}