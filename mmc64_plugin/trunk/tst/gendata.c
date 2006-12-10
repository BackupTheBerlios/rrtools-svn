
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	FILE *f_out;
	int iCnt, iErr;


	if(argc!=2) {
		fprintf(stderr, "Usage:\n%s <outputfile>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/* open output file */
	f_out = fopen(argv[1], "wb");
	if( f_out==NULL ) {
		fprintf(stderr, "%s: Error: failed to open output file '%s': %s\n", argv[0], argv[1], strerror(errno));
		exit(EXIT_FAILURE);
	}

	/* write data to output file */
	for(iCnt=0; iCnt<512; ++iCnt) {
		iErr = fputc( (iCnt&0xff), f_out );
		if( iErr==EOF ) {
			fprintf(stderr, "%s: Error: failed to write to output file '%s': %s\n", argv[0], argv[1], strerror(errno));
			fclose(f_out);
			exit(EXIT_FAILURE);
		}
	}

	/* close output file */
	iErr = fclose(f_out);
	if(iErr!=0) {
		fprintf(stderr, "%s: Error: failed to close output file '%s': %s\n", argv[0], argv[1], strerror(errno));
		exit(EXIT_FAILURE);	
	}

	exit(EXIT_SUCCESS);
}

