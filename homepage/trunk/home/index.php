<?php

function ShowTD()
{
	print("background=\"home/prost.gif\"");
}


function ShowPage()
{
	global $BERLIOS_GROUP_ID;


	// link to the news headers (including some lines)
	$newsfile = sprintf("projnews.php\?group_id=%d\&limit=10\&flat=0\&show_summaries=1", $BERLIOS_GROUP_ID);

	print("<p><br><center><h2>Welcome to the home of the Retro Replay Tools!</h2></center><br><br>\n");
	print("You'll find the latest versions of our projects and some related files here.\n");
	print("<p><br>\n");


	print("<h3>CBMImager</h3>\n");
	print("CBMImager is a tool to create and edit disk images for the Commodore C64 and compatible computers.\n");
	print("It supports full read/write access to D64 and DFI and read-only access to images of a CMD HD.<br>\n");
	print("<a href=\"index.php?area=cbmimager\">[More...]</a>\n");
	print("<p><br>\n");

	print("<h3>DLoad</h3>\n");
	print("DreamLoad (or short DLoad) is a 2 bit IRQ fastloader for many different drives like 1541 and compatible,\n");
	print("1570/71, 1581 and the CMD devices. The latest version also supports the MMC64.\n");
	print("DLoad works works on pal and ntsc machines and can easily be combined with crunchers and levelpackers.<br>\n");
	print("<a href=\"index.php?area=dload\">[More...]</a>\n");
	print("<p><br>\n");

	print("<h3>DreamAss</h3>\n");
	print("DreamAss is a crossassembler. It produces binaries for 6510, 65816 and compatible CPUs.\n");
	print("The 'illegal' opcodes of the 6510 are also supported.<br>\n");
	print("<a href=\"index.php?area=dreamass\">[More...]</a>\n");
	print("<p><br>\n");

	print("<h3>DreaMon</h3>\n");
	print("DreaMon is an assembly language monitor for the SCPU. It requires a Super Ram Card. It supports Freezepoints and\n");
	print("has a very comfortable and intuitive scroll mode for debugging. DreaMon can use the normal Vic display or on a C128\n");
	print("the 80 columns screen with up to 50 lines (depends on the monitor)<br>\n");
	print("<a href=\"index.php?area=dreamon\">[More...]</a>\n");
	print("<p><br>\n");

	print("<h3>DreaMon_crt</h3>\n");
	print("DreaMon_crt is a port of the DreaMon project to the Retro Replay cart.<br>\n");
	print("<a href=\"index.php?area=dreamon_crt\">[More...]</a>\n");
	print("<p><br>\n");

	print("<h3>MMC64 Plugin</h3>\n");
	print("This project provides a framework for MMC64 plugins. It contains several examples like a D64 and Lynx extractor and the DFI plugin.<br>\n");
	print("<a href=\"index.php?area=mmc64_plugin\">[More...]</a>\n");
	print("<p><br>\n");

	print("<h3>Mylene</h3>\n");
	print("Mylene is a file browser library for the C64. It can be configured to display various information and supports caching.\n");
	print("Mylene is used in the dfi and lnx plugins for the MMC64.<br>\n");
	print("<a href=\"index.php?area=mylene\">[More...]</a>\n");
	print("<p><br>\n");

	print("This page is best viewed with <a href=\"http://elinks.cz\">links</a> in 80x50. But then you would miss Uncle Tom and TWOO in the background (I guess everything has it's ups and downs).\n");
	print("<br>IIRC Tom was yelling 'Beeer!'. Or was it 'Dreeeams!' ? Hum, nevermind... almost the same anyway. ;)\n");
	print("<p><br>\n");
	print("Crappy page design by <a href=\"mailto:baccy_drm@berlios.de\">Doc Bacardi</a>/The Dreams\n");
	print("<p><br>\n");
}

?>
