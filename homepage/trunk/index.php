<?php

// Global Vars
$ARGV = array();
$BERLIOS_GROUP_ID = 7602;

// merge all vars
$ARGV = array_merge($HTTP_POST_VARS, $HTTP_GET_VARS);

ShowPageMain();
exit;


function ShowPageMain()
{
	global $ARGV;
	global $BERLIOS_GROUP_ID;

	$subpages = array(
				// area name	, page path
				'home'		=> 'home/index.php',
				'cbmimager'	=> 'cbmimager/index.php',
				'dload'		=> 'dload/index.php',
				'dreamass'	=> 'dreamass/index.php',
				'dreamon'	=> 'dreamon/index.php',
				'dreamon_crt'	=> 'dreamon_crt/index.php',
				'mmc64_plugin'	=> 'mmc64_plugin/index.php',
				'mylene'	=> 'mylene/index.php'
			);


	// set default page if the frontpage does not exist
	if( isset($ARGV['area']) )
	{
		$area = $ARGV['area'];
	}
	else
	{
		$area = 'home';
	}

	// get page for area
	if( isset($subpages[$area]) )
	{
		$file = $subpages[$area];
	}

	// include page file
	if( isset($file) && is_file($file) )
	{
		include $file;
	}

	print("<html><head>");
	print("<meta name=\"Keywords\" content=\"rrtools,c64,retro replay,mmc64,rrnet\">");
	print("<meta name=\"Description\" content=\"Retro Replay Tools Homepage\">");
	print("<title>Retro Replay Tools</title>");
	print("</head>");
	print("<body bgcolor=\"#000000\" text=\"#eeeeee\" alink=\"#33ccff\" vlink=\"#3366ff\" link=\"#3333ff\">");
	print("<font face=\"Arial,Helvetica\">\n");
	print("<table border=0 cellpadding=0 cellspacing=0 width=100%><tbody>\n");
	print("<tr><td><img src=\"br0.gif\"></td><td background=\"br1.gif\"><img src=\"br1.gif\"></td><td><img src=\"br2.gif\"></td><td width=2><img src=\"blk2x2.gif\"></td><td width=6000><img src=\"blk2x2.gif\"></td></tr>\n");
	print("<tr><td background=\"br3.gif\" width=8><img src=\"br3.gif\"></td><td bgcolor=\"#222222\" valign=top>\n");

	print("<strong>Menu<strong><font size=-1><br>\n");
	print("&nbsp;&nbsp;&nbsp;<a href=\"index.php?area=home\">Home</a><br>\n");
	print("&nbsp;&nbsp;&nbsp;<a href=\"http://developer.berlios.de/projects/rrtools\">Project&nbsp;Page</a><br>\n");
	printf("&nbsp;&nbsp;&nbsp;<a href=\"http://developer.berlios.de/project/showfiles.php?group_id=%d\">All&nbsp;Downloads</a><br>\n", $BERLIOS_GROUP_ID);
	printf("&nbsp;&nbsp;&nbsp;<a href=\"http://developer.berlios.de/mail/?group_id=%d\">All&nbsp;Mailinglists</a><br>\n", $BERLIOS_GROUP_ID);
	print("</font><p>");

	print("<strong>Projects<strong><font size=-1><br>\n");
	print("&nbsp;&nbsp;&nbsp;<a href=\"index.php?area=cbmimager\">CBMImager</a><br>\n");
	print("&nbsp;&nbsp;&nbsp;<a href=\"index.php?area=dload\">DLoad</a><br>\n");
	print("&nbsp;&nbsp;&nbsp;<a href=\"index.php?area=dreamass\">DreaMon</a><br>\n");
	print("&nbsp;&nbsp;&nbsp;<a href=\"index.php?area=dreamon\">DreaMon</a><br>\n");
	print("&nbsp;&nbsp;&nbsp;<a href=\"index.php?area=dreamon_crt\">DreaMon_CRT</a><br>\n");
	print("&nbsp;&nbsp;&nbsp;<a href=\"index.php?area=mmc64_plugin\">MMC64 Plugin</a><br>\n");
	print("&nbsp;&nbsp;&nbsp;<a href=\"index.php?area=mylene\">Mylene</a><br>\n");
	print("</font><p>");

	print("<strong>Links<strong><font size=-1><br>\n");
	print("&nbsp;&nbsp;&nbsp;<a href=\"http://retrohackers.org\">Retrohackers</a><br>\n");
	print("&nbsp;&nbsp;&nbsp;<a href=\"http://www.c64.sk/\">C64.sk</a><br>\n");
	print("&nbsp;&nbsp;&nbsp;<a href=\"http://noname.c64.org/csdb/\">CSDB</a><br>\n");
	print("&nbsp;&nbsp;&nbsp;<a href=\"http://www.the-dreams.de/\">The&nbsp;Dreams</a><br>\n");
	print("</font><p>");

	// show berlios logo
	ShowBerliOsLogo();

	print("</td><td background=\"br4.gif\" width=8><img src=\"br4.gif\"></td><td width=2><img src=\"blk2x2.gif\"></td>\n");
	print("<td valign=top width=6000 ");
	if( function_exists("ShowTD") )
	{
		// insert table cell attributes like background etc.
		ShowTD();
	}
	print(">\n");

	if( function_exists("ShowPage") )
	{
		ShowPage();
	}
	else
	{
		printf("Page %s does not exist yet.", $ARGV["area"]);
	}

	print("</td></tr><tr><td><img src=\"br5.gif\"></td><td background=\"br6.gif\"><img src=\"br6.gif\"></td><td><img src=\"br7.gif\"></td><td width=2><img src=\"blk2x2.gif\"></td><td width=6000><img src=\"blk2x2.gif\"></td></tr></tbody></table></font></body></html>");
}


function ShowBerliOsLogo()
{
	global $BERLIOS_GROUP_ID;


	print("<center><font size=-2>Thanks to<br>\n");
	printf("<a href=\"http://developer.berlios.de\"><img src=\"http://developer.berlios.de/bslogo.php?group_id=%d\" width=\"124\" height=\"32\" border=\"0\" alt=\"BerliOS Logo\"/></a><br>\n", $BERLIOS_GROUP_ID);
	print("for hosting us!</font></center>\n");
}

?>
