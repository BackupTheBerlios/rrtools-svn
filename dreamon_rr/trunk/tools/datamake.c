/***************************************************************************
 *   Copyright (C) 2000 - 2006 by Christoph Thelen                         *
 *   DocBacardi@the-dreams.de                                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


/*--------------------------------------

DataMaker V1

--------------------------------------*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	FILE *RawFile, *TextFile;
	char *RawFileName=NULL, *TextFileName=NULL;
	int cnt, FreeMe=0, BytesPerLine=16;
	int ByteCnt, Byte;
	long Skip=0;
	long Counter=0,MaxLen=0;

	if (argc==1)
	{
		fprintf(stderr, "Syntax: DataMaker [-o <OutFile>] [-n Num] [-s Skip] [-m MaxLen] <RawFile>\n\n"
		       "Num is the number of Bytes per Line, default is 16.\n"
		       "Skip is the number of bytes to skip at the beginning of the file, default is 0\n"
		       "MaxLen is the maximum number of bytes to output, 0 means no limit. Default is 0\n\n");
		exit(1);
	}

	for(cnt=1; cnt<argc; cnt++)
	{
		if( !strcmp(argv[cnt],"-o") )
		{
			if(++cnt>=argc)
			{
				fprintf( stderr, "No Arg for '-o'!\n");
				exit(1);
			}
			TextFileName=argv[cnt];

		} else if( !strcmp(argv[cnt],"-n") )
		{
			if(++cnt>=argc)
			{
				fprintf( stderr, "No Arg for '-n'!\n");
				exit(1);
			}
			if ( sscanf(argv[cnt],"%d",&BytesPerLine)!=1 )
			{
				fprintf( stderr, "Funny Arg for '-n'\n");
				exit(1);
			}
		} else if( !strcmp(argv[cnt],"-s") )
		{
			if(++cnt>=argc)
			{
				fprintf( stderr, "No Arg for '-s'!\n");
				exit(1);
			}
			if ( sscanf(argv[cnt],"%ld",&Skip)!=1 )
			{
				fprintf( stderr, "Funny Arg for '-s'\n");
				exit(1);
			}
		} else if( !strcmp(argv[cnt],"-m") )
		{
			if(++cnt>=argc)
			{
				fprintf( stderr, "No Arg for '-m'!\n");
				exit(1);
			}
			if ( sscanf(argv[cnt],"%ld",&MaxLen)!=1 )
			{
				fprintf( stderr, "Funny Arg for '-m'\n");
				exit(1);
			}
		} else if( RawFileName )
		{
			fprintf(stderr, "Unknown option: '%s'!\n", argv[cnt]);
			exit(1);
		} else RawFileName=argv[cnt];
	}

	if(!TextFileName)
	{
		if ( !(TextFileName=(char*) malloc(strlen(argv[1])+5)) )	/* 4 Chars fuer .src und null */
 		{
			fprintf( stderr, "No Memory!\n");
			exit(1);
		}
		FreeMe=1;
		strcpy(TextFileName, argv[1]);
		strcat(TextFileName, ".src");
	}


	if ( !(RawFile=fopen(RawFileName,"rb")) )
	{
		fprintf( stderr, "Unable to open file: '%s'!\n", RawFileName);
		exit(1);
	}

	if( fseek(RawFile, Skip, SEEK_SET) )
	{
		fprintf( stderr, "Unable to skip %ld bytes. File too short or read error!\n", Skip);
		exit(1);
	}

	if ( !(TextFile=fopen(TextFileName,"w")) )
	{
		fprintf( stderr, "Unable to open file: '%s'!\n", TextFileName);
		exit(1);
	}

	fprintf(TextFile,"/*--------------------------------------\n");
	fprintf(TextFile,"  Datafile for '%s'\n", RawFileName);
	fprintf(TextFile,"--------------------------------------*/\n");

	ByteCnt=BytesPerLine;
	while( !feof(RawFile) && (!MaxLen || Counter<MaxLen) )
	{
		Byte=getc(RawFile);
		if( feof(RawFile) ) break;

		Counter++;
		if(++ByteCnt >= BytesPerLine)
		{
			fprintf(TextFile,"\n\t.DB $%02x", Byte);
			ByteCnt=0;
		} else fprintf(TextFile,",$%02x", Byte);
	}
	fprintf(TextFile,"\n\n");

	fclose(RawFile);
	fclose(TextFile);

	if(FreeMe) free(TextFileName);

	return 0;
}


