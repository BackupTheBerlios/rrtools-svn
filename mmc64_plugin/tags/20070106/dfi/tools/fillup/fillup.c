
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


/* some prototypes */
void showHelp(const char *pcArgv0);
int parseArgs(int argc, char **argv);


/* the config */
static char *gpc_cfg_input_filename = NULL;		/* input filename, NULL means not set */
static char *gpc_cfg_output_filename = NULL;		/* output filename, NULL means not set */
static int gf_cfg_verbose = -1;				/* verbose mode active, -1 means not set */
static int gf_cfg_showHelp = -1;			/* help requested, -1 means not set */
static off_t goff_cfg_paddedsize = -1;			/* force padded size, -1 means not set */

/* some locals */
static off_t goff_valid_filesizes[] =
{
	0x00020000,		/*   128kb */
	0x00040000,		/*   256kb */
	0x00080000,		/*   512kb */
	0x00100000,		/*  1024kb */
	0x00200000,		/*  2048kb */
	0x00400000,		/*  4096kb */
	0x00800000,		/*  8192kb */
	0x01000000		/* 16384kb */
};

#define COPY_BUFFER_SIZE 4096
static unsigned char ab_copy_buffer[COPY_BUFFER_SIZE];

int main(int argc, char **argv)
{
	int iRet;
	int iCnt;
	struct stat finfo;
	FILE *fInputFile;
	FILE *fOutputFile;
	off_t off_input_filesize;
	off_t off_output_filesize;
	off_t off_cnt;
	off_t off_copy_segment;


	iRet = parseArgs(argc, argv);
	if( iRet!=1 )
	{
		showHelp(*argv);
		exit(EXIT_FAILURE);
	}

	/* set some defaults */
	if( gf_cfg_verbose==-1 )
	{
		/* don't be verbose by default */
		gf_cfg_verbose = 0;
	}

	/* help requested? */
	if( gf_cfg_showHelp!=-1 )
	{
		showHelp(*argv);
		exit(EXIT_SUCCESS);
	}

	/* all necessary parameters set? */
	if( gpc_cfg_input_filename==NULL )
	{
		fprintf(stderr, "error: no input file specified!\n");
		exit(EXIT_FAILURE);
	}
	if( gpc_cfg_output_filename==NULL )
	{
		fprintf(stderr, "error: no output file specified!\n");
		exit(EXIT_FAILURE);
	}

	/* get input filesize */
	iRet = stat(gpc_cfg_input_filename, &finfo);
	if( iRet!=0 )
	{
		fprintf(stderr, "error: failed to stat input file: '%s'\n", gpc_cfg_input_filename);
		exit(EXIT_FAILURE);
	}
	off_input_filesize = finfo.st_size;

	/* check size */
	if( goff_cfg_paddedsize==-1 )
	{
		/* autodetect filesize */
		for(iCnt=0; iCnt<(sizeof(goff_valid_filesizes)/sizeof(goff_valid_filesizes[0])); ++iCnt)
		{
			off_output_filesize = goff_valid_filesizes[iCnt];
			if( off_input_filesize<=off_output_filesize )
			{
				break;
			}
		}
		if( iCnt>=(sizeof(goff_valid_filesizes)/sizeof(goff_valid_filesizes[0])) )
		{
			fprintf(stderr, "error: filesize exceeds REU limit!\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* check forced filesize */
		for(iCnt=0; iCnt<(sizeof(goff_valid_filesizes)/sizeof(goff_valid_filesizes[0])); ++iCnt)
		{
			if( goff_cfg_paddedsize==goff_valid_filesizes[iCnt] )
			{
				break;
			}
		}
		if( iCnt>=(sizeof(goff_valid_filesizes)/sizeof(goff_valid_filesizes[0])) )
		{
			fprintf(stderr, "error: illegal size: %ld!\n", goff_cfg_paddedsize);
			fprintf(stderr, "valid filesizes are:\n");
			for(iCnt=0; iCnt<(sizeof(goff_valid_filesizes)/sizeof(goff_valid_filesizes[0])); ++iCnt)
			{
				fprintf(stderr, "%ld\n", goff_valid_filesizes[iCnt]);
			}
			fprintf(stderr, "\n");
			exit(EXIT_FAILURE);
		}

		/* padded filesize must be greater or equal than the input filesize */
		if( goff_cfg_paddedsize<off_input_filesize )
		{
			fprintf(stderr, "error: forced size is smaller than filesize!\n");
			exit(EXIT_FAILURE);
		}

		/* accept output file size */
		off_output_filesize = goff_cfg_paddedsize;
	}

	if( gf_cfg_verbose )
	{
		printf("input file has %ld bytes, output file will have %ld bytes.\n", off_input_filesize, off_output_filesize);
	}

	if( gf_cfg_verbose )
	{
		printf("opening input file '%s'...\n", gpc_cfg_input_filename);
	}
	fInputFile = fopen(gpc_cfg_input_filename, "rb");
	if( fInputFile==NULL )
	{
		fprintf(stderr, "error: failed to open input file: '%s'\n", gpc_cfg_input_filename);
		exit(EXIT_FAILURE);
	}

	/* open output file */
	if( gf_cfg_verbose )
	{
		printf("opening output file '%s'...\n", gpc_cfg_output_filename);
	}
	fOutputFile = fopen(gpc_cfg_output_filename, "wb");
	if( fOutputFile==NULL )
	{
		fclose(fInputFile);
		fprintf(stderr, "error: failed to open output file: '%s'\n", gpc_cfg_output_filename);
		exit(EXIT_FAILURE);
	}

	if( gf_cfg_verbose )
	{
		printf("copy input file...\n");
	}
	off_cnt = 0;
	while( off_cnt<off_input_filesize )
	{
		off_copy_segment = off_input_filesize - off_cnt;
		if( off_copy_segment>COPY_BUFFER_SIZE )
		{
			off_copy_segment = COPY_BUFFER_SIZE;
		}
		if( fread(ab_copy_buffer, off_copy_segment, 1, fInputFile)!=1 )
		{
			/* file is smaller than fstat reported */
			fclose(fInputFile);
			fclose(fOutputFile);
			fprintf(stderr, "error: failed to read from input file: '%s'\n", gpc_cfg_input_filename);
			exit(EXIT_FAILURE);
		}
		if( fwrite(ab_copy_buffer, off_copy_segment, 1, fOutputFile)!=1 )
		{
			/* file is smaller than fstat reported */
			fclose(fInputFile);
			fclose(fOutputFile);
			fprintf(stderr, "error: failed to write to output file: '%s'\n", gpc_cfg_output_filename);
			exit(EXIT_FAILURE);
		}
		off_cnt += off_copy_segment;
	}

	if( gf_cfg_verbose )
	{
		printf("pad output file...\n");
	}

	memset(ab_copy_buffer, 0, COPY_BUFFER_SIZE);

	while( off_cnt<off_output_filesize )
	{
		off_copy_segment = off_output_filesize - off_cnt;
		if( off_copy_segment>COPY_BUFFER_SIZE )
		{
			off_copy_segment = COPY_BUFFER_SIZE;
		}
		if( fwrite(ab_copy_buffer, off_copy_segment, 1, fOutputFile)!=1 )
		{
			/* file is smaller than fstat reported */
			fclose(fInputFile);
			fclose(fOutputFile);
			fprintf(stderr, "error: failed to write to output file: '%s'\n", gpc_cfg_output_filename);
			exit(EXIT_FAILURE);
		}
		off_cnt += off_copy_segment;
	}

	if( gf_cfg_verbose )
	{
		printf("ok!\n");
	}

	fclose(fInputFile);
	fclose(fOutputFile);

	exit(EXIT_SUCCESS);
}




void showHelp(const char *pcArgv0)
{
	int iCnt;


	printf(
		"Usage: %s [-s padded_size] [-v] input_file output_file\n"
		"Fillup image to match a vaild reu size for vice.\n"
		"\n"
		"Options:\n"
		"  -h,  --help               show this help text.\n"
		"  -s,  --size <NUMBER>      pad the image to this size, -1 is autodetect.\n"
		"                            default is autodetect.\n"
		"  -v,  --verbose            be verbose.\n"
		"\n"
		"Please note: This tool will only pad the file to match the valid reu sizes.\n"
		"It does not increase the number of free blocks. Use a tool like cbmimager or\n"
		"cbmconvert for this purpose.\n"
		"\n"
		"Valid sizes are:\n", pcArgv0);

	iCnt=0;
	do
	{
		printf("%ld", goff_valid_filesizes[iCnt]);
		++iCnt;
		if( iCnt<(sizeof(goff_valid_filesizes)/sizeof(goff_valid_filesizes[0])) )
		{
			printf(", ");
		}
		else
		{
			break;
		}
	} while(1);

	printf(
		"\n"
		"\n"
		"Examples:\n"
		"  %s pubgames.dfi paddedpubgames.dfi            convert with autodetect\n"
		"\n"
		"Email bug reports to baccy_drm@berlios.de .\n"
		"DreamAss home page: http://rrtools.berlios.de\n", pcArgv0 );
}


int parseArgs(int argc, char **argv)
{
	int fVerboseMoan;
	char **argp, **arge;
	long int num;
	char *epos;
	int iState;


	/* init local vars */
	fVerboseMoan = 0;
	iState = 0;

	/*
	 * Read in Args
	 */
	argp=argv;
	arge=argv+argc;

	while( ++argp<arge )
	{
		if( !strcmp(*argp, "-v") || !strcmp(*argp, "--verbose") )
		{
			if( gf_cfg_verbose!=-1 && fVerboseMoan==0 )
			{
				fprintf(stderr, "warning: multiple verbose options, ignoring previous ones\n");
				fVerboseMoan = 1;
			}
			gf_cfg_verbose = 1;
		}
		else if( !strcmp(*argp, "-h") || !strcmp(*argp, "--help") )
		{
			gf_cfg_showHelp = 1;
		}
		else if( !strcmp(*argp, "-s") || !strcmp(*argp, "--size") )
		{
			if( ++argp>=arge )
			{
				fprintf(stderr, "Missing Argument for parameter '%s'\n", *(argp-1) );
				return 0;
			}
			else if( goff_cfg_paddedsize!=-1 )
			{
				fprintf(stderr, "error: multiple sizes specified!\n");
				return 0;
			}
			else
			{
				num = strtol(*argp,&epos,10);
				if( *epos!=0 )
				{
					fprintf(stderr, "Non-numeric Argument for parameter '%s'\n", *(argp-1) );
					return 0;
				}
				goff_cfg_paddedsize = (int)num;
			}
		}
		else if( iState==0 )
		{
			gpc_cfg_input_filename = *argp;
			++iState;
		}
		else if( iState==1 )
		{
			gpc_cfg_output_filename = *argp;
			++iState;
		}
	}

	return 1;
}


