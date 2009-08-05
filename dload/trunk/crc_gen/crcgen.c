/***************************************************************************
 *                                                                         *
 *               DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE               *
 *                      Version 2, December 2004                           *
 *                                                                         *
 *   Copyright (C) 2004 Sam Hocevar                                        *
 *    14 rue de Plaisance, 75014 Paris, France                             *
 *   Everyone is permitted to copy and distribute verbatim or modified     *
 *   copies of this license document, and changing it is allowed as long   *
 *   as the name is changed.                                               *
 *                                                                         *
 *              DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE                *
 *     TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION     *
 *                                                                         *
 *   0. You just DO WHAT THE FUCK YOU WANT TO.                             *
 *                                                                         *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void showHelp(void);
unsigned char generateData(void);
void generateFile(FILE *outputFile, unsigned short startadr, unsigned short endadr);
unsigned short updateCrc16(unsigned short crc, unsigned char data);


int main(int argc, char *argv[])
{
	int cnt;
	const char *fileName;
        int startadr;
        int endadr;
        FILE *outputFile;


        // default/initial options
        fileName = NULL;
        startadr = -1;
        endadr = -1;

	for(cnt=1; cnt<argc; cnt++)
	{
		if( !strcmp(argv[cnt],"-o") )
		{
			if(++cnt>=argc)
			{
				fprintf( stderr, "No Arg for '-o'!\n");
				exit(1);
			}
			fileName=argv[cnt];

		} else if( !strcmp(argv[cnt],"-s") )
		{
			if(++cnt>=argc)
			{
				fprintf( stderr, "No Arg for '-s'!\n");
				exit(1);
			}
			if ( sscanf(argv[cnt],"%i",&startadr)!=1 )
			{
				fprintf( stderr, "Funny Arg for '-s'\n");
				exit(1);
			}
                        if( startadr<0 || startadr>=0x010000 )
                        {
				fprintf( stderr, "Startaddress must be >=0x0000 and <=0xffff ! Startaddress is: 0x%04x\n", startadr);
				exit(1);
                        }
		} else if( !strcmp(argv[cnt],"-e") )
		{
			if(++cnt>=argc)
			{
				fprintf( stderr, "No Arg for '-e'!\n");
				exit(1);
			}
			if ( sscanf(argv[cnt],"%i",&endadr)!=1 )
			{
				fprintf( stderr, "Funny Arg for '-e'\n");
				exit(1);
			}
                        if( endadr<0 || endadr>=0x010000 )
                        {
				fprintf( stderr, "Endaddress must be >=0x0000 and <=0xffff ! Endaddress is: 0x%04x\n", endadr);
				exit(1);
                        }
		} else if( !strcmp(argv[cnt],"--help") )
                {
			showHelp();
                        exit(0);
                } else
                {
			showHelp();
                        exit(1);
                }
	}

        if( startadr==-1 )
        {
		fprintf( stderr, "No startaddress provided!\n");
                exit(1);
        }
        if( endadr==-1 )
        {
		fprintf( stderr, "No endaddress provided!\n");
                exit(1);
        }
	if( startadr>=endadr )
	{
		fprintf( stderr, "Startaddress must be smaller than endaddress! Startaddress is: 0x%04x. Endaddress is: 0x%04x\n", startadr, endadr);
		exit(1);
	}

	if( fileName==NULL )
        {
                outputFile = stdout;
        } else if( (outputFile=fopen(fileName,"wb"))==NULL )
        {
		fprintf( stderr, "Error opening output file \"%s\"!\n", fileName);
                exit(1);
        }

	generateFile(outputFile, startadr, endadr);

        if( fileName!=NULL )
        {
		fclose( outputFile );
        }
	exit(0);
}


void initGenerateData(void)
{
        time_t t;
//        struct timespec ts;
        unsigned int seed;

/*
	if( clock_gettime(CLOCK_REALTIME, &ts)==0 )
        {
		seed = (unsigned int)ts.tv_nsec;
        } else if( clock_gettime(CLOCK_MONOTONIC, &ts)==0 )
        {
		seed = (unsigned int)ts.tv_nsec;
        } else
        {
*/
		t = time(NULL);
	        seed = (unsigned int)t;
//	}
//        printf("Seed: %d\n", seed);
	srand(seed);
}


unsigned char generateData(void)
{
	unsigned char c;


        c = (rand()/((double)RAND_MAX))*255;
//        printf("Rand: %d\n", c);
	return c;
}


void generateFile(FILE *outputFile, unsigned short startadr, unsigned short endadr)
{
	unsigned short crc;
        unsigned char data;


	// write startadr
	fputc(startadr&0xff, outputFile);
	fputc(startadr>>8,   outputFile);

	initGenerateData();
	crc = 0;
	do
	{
		data = generateData();
		fputc(data, outputFile);
		crc = updateCrc16(crc, data);
	} while( ++startadr<endadr );

	fputc(crc>>8,   outputFile);
	fputc(crc&0xff, outputFile);
}


void showHelp(void)
{
	fprintf(stderr, "Syntax: crcgen [-o <OutFile>] -s startaddress -e endaddress\n\n");
}

unsigned short updateCrc16(unsigned short crc, unsigned char data)
{
	crc  = (unsigned char)(crc >> 8) | (crc << 8);
	crc ^= data;
	crc ^= (unsigned char)(crc & 0xff) >> 4;
	crc ^= (crc << 8) << 4;
	crc ^= ((crc & 0xff) << 4) << 1;

	return crc;
}


