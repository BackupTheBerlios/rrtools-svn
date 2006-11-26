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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef bool
#define bool int
#define true 1
#define false 0
#endif

int dumpBuf(unsigned char *buf, int len, FILE *outFile);


int main(int argc, char * argv[])
{
	char *scrName,      *outName;
	FILE *scrFile=NULL, *outFile=NULL;
	bool block_ok;
	unsigned char scrBuf[0x0400];
	unsigned char colBuf[0x0400];
	unsigned int scrComI[0x0100];
	unsigned char scrCom[0x0100];
	unsigned char colCom[0x0400];
	unsigned char ebc;
	int cnt0;
	int xpos, ypos=0;
	int x1, y1, x2, y2;
	int color, col[2];
	int scrComLen, scrComILen, colComLen;
	int swap0, swap1;


	printf("DreaMon menu compressor V1.0 by Doc Bacardi/DRM.\n");
	
	if(argc!=7)
	{
		printf("Syntax: %s <screenFile> <x1> <y1> <x2> <y2> <outfile>\n\n",argv[0]);
		exit(1);
	}
	scrName=argv[1];
	if( sscanf(argv[2], "%d", &x1)!=1 )
	{
		printf("Argument 2 is not a number: '%s'!\n", argv[2]);
		goto err_exit;
	}
	if( sscanf(argv[3], "%d", &y1)!=1 )
	{
		printf("Argument 3 is not a number: '%s'!\n", argv[3]);
		goto err_exit;
	}
	if( sscanf(argv[4], "%d", &x2)!=1 )
	{
		printf("Argument 4 is not a number: '%s'!\n", argv[4]);
		goto err_exit;
	}
	if( sscanf(argv[5], "%d", &y2)!=1 )
	{
		printf("Argument 5 is not a number: '%s'!\n", argv[5]);
		goto err_exit;
	}
	if( x1<0 || x1>39 || x2<0 || x2>39 || y1<0 || y1>25 || y2<0 || y2>25 || x1>=x2 || y1>=y2 )
	{
		printf("Coodrinates describe no valid rectangle!\n");
		goto err_exit;
	}

	outName=argv[6];

	if( !(scrFile=fopen(scrName,"rb")) )
	{
		printf("Unable to open screen File!\n");
		goto err_exit;
	}

//Ok, all files are open. Read in data now.
//but first skip the load adress
	if( fread(scrBuf, 1, 2, scrFile)!=2 )
	{
		printf("Read Error!\n");
		goto err_exit;
	}
	if( fread(scrBuf, 1, 0x400, scrFile)!=0x400 )
	{
		printf("Read Error!\n");
		goto err_exit;
	}
	if( fread(colBuf, 1, 0x400, scrFile)!=0x400 )
	{
		printf("Read Error!\n");
		goto err_exit;
	}

	fclose(scrFile);
	scrFile=NULL;

//Test selected Block for one Extended Background color
	ebc = scrBuf[x1 + 40*y1] & 0xc0;
	block_ok = true;
	for(ypos=y1; ypos<=y2; ypos++)
	{
		for(xpos=x1; xpos<=x2; xpos++)
		{
//			printf(" $%02X", (scrBuf[xpos + 40*ypos] & 0xc0));
			block_ok &=  ((scrBuf[xpos + 40*ypos] & 0xc0) == ebc);
		}
//		printf("\n");
	}
	if( !block_ok )
	{
		printf("The selected block has more than one extended background color!\n");
		goto err_exit;
	}

//Test selected Block for two D8 colors
	col[0]=col[1]=-1;
	for(ypos=y1; ypos<=y2; ypos++)
		for(xpos=x1; xpos<=x2; xpos++)
		{
			color = colBuf[xpos + 40*ypos] & 0x0f;
			for(cnt0=0; cnt0<2; cnt0++)
			{
				if( col[cnt0]==-1 || col[cnt0]==color)
				{
					col[cnt0]=color;
					break;
				}
			}
			if( cnt0==2 )
			{
				printf("The selected block has more than two D8 colors!\n");
				goto err_exit;
			}
		}

//Compress the screencodes with 4in3
	memset(scrComI,0,sizeof(scrComI));
	for(ypos=y1, scrComILen=0; ypos<=y2; ypos++)
	{
		for(xpos=x1; xpos<=x2; xpos++)
		{
			swap0=scrBuf[xpos + 40*ypos] & 0x3f;
			for(cnt0=swap1=0; cnt0<6; cnt0++)
			{
				swap1 <<= 1;
				swap1  |= (swap0 & 1);
				swap0 >>= 1;
			}
			scrComI[scrComILen>>2] >>=6;
			scrComI[scrComILen>>2] |= (swap1)<<18;
			scrComILen++;
		}
	}

//Convert the int to a byte array
	memset(scrCom,0,sizeof(scrCom));
	for(cnt0=scrComLen=0; cnt0<(scrComILen>>2); cnt0++)
	{
		scrCom[scrComLen++] =  scrComI[cnt0]      & 0xff;
		scrCom[scrComLen++] = (scrComI[cnt0]>> 8) & 0xff;
		scrCom[scrComLen++] = (scrComI[cnt0]>>16) & 0xff;
	}

//Compress the colors with a 1-bit-field
	memset(colCom,0,sizeof(colCom));
	for(ypos=y1, colComLen=0; ypos<=y2; ypos++)
		for(xpos=x1; xpos<=x2; xpos++)
		{
			colCom[colComLen>>3] >>=1;
			colCom[colComLen>>3] |= (colBuf[xpos + 40*ypos])<<7;
			colComLen++;
		}


	if( !(outFile=fopen(outName,"w")) )
	{
		printf("Unable to open output File!\n");
		goto err_exit;
	}

	fprintf(outFile,";---------------------------------------\n");
	fprintf(outFile,"; Compressed Menu\n");
	fprintf(outFile,";---------------------------------------\n");

	fprintf(outFile,"\nMenu_Col:\n");
	dumpBuf(colCom, colComLen>>3, outFile);

	fprintf(outFile,"\nMenu_Scr:\n");
	dumpBuf(scrCom, scrComLen, outFile);

	fclose(outFile);

	exit(0);

err_exit:
	if( scrFile )
		fclose(scrFile);
	if( outFile )
		fclose(outFile);
	exit(1);
}


int dumpBuf(unsigned char *buf, int len, FILE *outFile)
{
	int cnt0;


	for(cnt0=0; cnt0<len; cnt0++)
	{
		if( (cnt0&7)==0 )
			fprintf(outFile,"\t.DB ");
		fprintf(outFile,"$%02X%c",buf[cnt0],((cnt0&7)!=7 && cnt0!=len-1 ? ',' : '\n'));
	}
	return 0;
}

