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


int dumpBuf(unsigned char *buf, int len, FILE *outFile);

int main(int argc, char * argv[])
{
	char *scrName,      *colName,      *outName;
	FILE *scrFile=NULL, *colFile=NULL, *outFile=NULL;
	unsigned char scrBuf[0x118], colBuf[0x118];
	unsigned char scrCom[0x64],  colCom[0x19], tiles[0x10];
	int cnt0, cnt1, tile_cnt;


	printf("DreaMon logo compressor V1.0 by Doc Bacardi/DRM.\n");
	
	if(argc!=4)
	{
		printf("Syntax: %s <scrFile> <colFile> <outFile>\n\n",argv[0]);
		exit(1);
	}
	scrName=argv[1];
	colName=argv[2];
	outName=argv[3];

	if( !(scrFile=fopen(scrName,"rb")) )
	{
		printf("Unable to open screencode File!\n");
		goto err_exit;
	}

	if( !(colFile=fopen(colName,"rb")) )
	{
		printf("Unable to open color File!\n");
		goto err_exit;
	}

	if( !(outFile=fopen(outName,"w")) )
	{
		printf("Unable to open output File!\n");
		goto err_exit;
	}

//Ok, all files are open. Read in data now.
	if( fread(scrBuf, 1, 0x118, scrFile)!=0x118 )
	{
		printf("Read Error!\n");
		goto err_exit;
	}
	if( fread(colBuf, 1, 0x118, colFile)!=0x118 )
	{
		printf("Read Error!\n");
		goto err_exit;
	}

	fclose(scrFile);
	fclose(colFile);
	scrFile=NULL;
	colFile=NULL;

//Check for empty blue lines at top and bottom
	for(cnt0=0; cnt0<40; cnt0++)
	{
		if( scrBuf[cnt0]!=0xA0 || scrBuf[cnt0+6*40]!=0xA0 || colBuf[cnt0]!=6 || colBuf[cnt0+6*40]!=6 )
		{
			printf("Logo Error: Missing blue bars at top and bottom!");
			goto err_exit;
		}
	}

	tile_cnt=0;
	for(cnt0=0; cnt0<0xc8; cnt0++)
	{
		for(cnt1=0; cnt1<tile_cnt && scrBuf[cnt0+0x28]!=tiles[cnt1]; cnt1++);
		if( cnt1==tile_cnt )
		{
			if( tile_cnt==0x10 )
			{
				printf("More than 16 tiles in screenfile!\n");
				goto err_exit;
			}
			tiles[tile_cnt++]=scrBuf[cnt0+0x28];
		}
		scrCom[cnt0>>1] <<= 4;
		scrCom[cnt0>>1]  |= cnt1;
	}

	memset(colCom, 0, 0x19);
	for(cnt0=0; cnt0<0xc8; cnt0++)
	{
		colCom[cnt0>>3] <<= 1;
		colCom[cnt0>>3]  |= (colBuf[cnt0+0x28]==6 ? 0 : 1);
	}

	fprintf(outFile,";---------------------------------------\n");
	fprintf(outFile,"; Compressed Logo\n");
	fprintf(outFile,";---------------------------------------\n");

	fprintf(outFile,"\nLogo_Col:\n");
	dumpBuf(colCom, 0x19, outFile);

	fprintf(outFile,"\nLogo_Scr:\n");
	dumpBuf(scrCom, 0x64, outFile);

	fprintf(outFile,"\nLogo_Tiles:\n");
	dumpBuf(tiles, tile_cnt, outFile);

	fclose(outFile);

	exit(0);

err_exit:
	if( scrFile )
		fclose(scrFile);
	if( colFile )
		fclose(colFile);
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

