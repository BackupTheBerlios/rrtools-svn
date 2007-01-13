<?php

// this is the configuration


// area name, page path and page description
// NOTE: the first entry in this array must be the main page. it is omitted in the projects listing
$subpages = array(
	'home'		=> array(name=>'Home', 'path'=>'home/index.php', 'dsc'=>
''),

	'cbmimager'	=> array(name=>'CBMImager', 'path'=>'cbmimager/index.php', 'dsc'=>
'CBMImager is a tool to create and edit disk images for the Commodore C64 and compatible computers.
It supports full read/write access to D64 and DFI and read-only access to images of a CMD HD.'),

	'dload'		=> array(name=>'DLoad', 'path'=>'dload/index.php', 'dsc'=>
'DreamLoad (or short DLoad) is a 2 bit IRQ fastloader for many different drives like 1541 and compatible,
1570/71, 1581 and the CMD devices. The latest version also supports the MMC64.
DLoad works works on pal and ntsc machines and can easily be combined with crunchers and levelpackers.'),

	'dreamass'	=> array(name=>'DreamAss', 'path'=>'dreamass/index.php', 'dsc'=>
'DreamAss is a crossassembler. It produces binaries for 6510, 65816 and compatible CPUs.
The \'illegal\' opcodes of the 6510 are also supported.'),

	'dreamon'	=> array(name=>'DreaMon', 'path'=>'dreamon/index.php', 'dsc'=>
'DreaMon is an assembly language monitor for the SCPU. It requires a Super Ram Card. It supports Freezepoints and
has a very comfortable and intuitive scroll mode for debugging. DreaMon can use the normal Vic display or on a C128
the 80 columns screen with up to 50 lines (depends on the monitor)'),

	'dreamon_crt'	=> array(name=>'DreaMon_crt', 'path'=>'dreamon_crt/index.php', 'dsc'=>
'DreaMon_crt is a port of the DreaMon project to the Retro Replay cart.'),

	'mmc64_plugin'	=> array(name=>'MMC64 Plugin', 'path'=>'mmc64_plugin/index.php', 'dsc'=>
'This project provides a framework for MMC64 plugins. It contains several examples like a D64 and Lynx extractor and the DFI plugin.'),

	'mylene'	=> array(name=>'Mylene', 'path'=>'mylene/index.php', 'dsc'=>
'Mylene is a file browser library for the C64. It can be configured to display various information and supports caching.
Mylene is used in the dfi and lnx plugins for the MMC64.')
);


$links = array(
	'Retrohackers'	=> 'http://retrohackers.org',
	'C64.sk'	=> 'http://www.c64.sk',
	'CSDB'		=> 'http://noname.c64.org/csdb',
	'The Dreams'	=> 'http://www.the-dreams.de'
);


// Copy all banner codes into this array, quoted with single ticks (').
// Don't forget to escape any ticks in the banner code itself. :)
$banners = array(

	// Small "Defective By Design" badge from http://www.defectivebydesign.org/promo/button
'<a href="http://www.defectivebydesign.org/join/button">
<img src="banner/dbd_sm_btn.png"
alt="DRM is DefectiveByDesign"
width="88" height="30" border="0" align="middle" /><br />
<small>Protect your freedom!</small></a>',

	// BadVista logo from http://badvista.fsf.org/logos/BadVista_no_littering.png/view
'<a href="http://www.badvista.org" target="new">
<img src="banner/BadVista_no_littering.png" border="0"
alt="BadVista.org: Stopping Vista adoption by promoting free software"></a>'
);



$ARGV = array();
$BERLIOS_GROUP_ID = 7602;

if( isset($_SERVER['HTTPS']) )
{
	$PROTO = 'https';
}
else
{
	$PROTO = 'http';
}

// merge all vars
$ARGV = array_merge($HTTP_POST_VARS, $HTTP_GET_VARS);

ShowPageMain();
exit;


function ShowPageMain()
{
	global $ARGV;
	global $BERLIOS_GROUP_ID;
	global $PROTO;
	global $banners;
	global $subpages;


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
		$ar_attr = $subpages[$area];
	}

	// include page file
	if( isset($ar_attr) && isset($ar_attr['path']) )
	{
		$file = $ar_attr['path'];
		if( is_file($file) )
		{
			include $file;
		}
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

	print "<strong>Menu<strong><font size=-1><br>\n";
	if( isset($subpages['home']) )
	{
		$home_attr = $subpages['home'];
		print '&nbsp;&nbsp;&nbsp;<a href="index.php?area=home">';
		print str_replace(' ', '&nbsp;', $home_attr['name']);
		print "</a><br>\n";
	}
	print "&nbsp;&nbsp;&nbsp;<a href=\"http://developer.berlios.de/projects/rrtools\">Project&nbsp;Page</a><br>\n";
	print "&nbsp;&nbsp;&nbsp;<a href=\"http://developer.berlios.de/project/showfiles.php?group_id=$BERLIOS_GROUP_ID\">All&nbsp;Downloads</a><br>\n";
	print "&nbsp;&nbsp;&nbsp;<a href=\"http://developer.berlios.de/mail/?group_id=$BERLIOS_GROUP_ID\">All&nbsp;Mailinglists</a><br>\n";
	print "</font><p>\n";

	print("<strong>Projects<strong><font size=-1><br>\n");
	foreach($subpages as $section=>$ar_attr)
	{
		// is this the 'home' page?
		if( $section!='home' )
		{
			print '&nbsp;&nbsp;&nbsp;<a href="index.php?area=';
			print $section;
			print '">';
			print str_replace(' ', '&nbsp;', $ar_attr['name']);
			print "</a><br>\n";
		}
	}
	print("</font><p>");

	print("<strong>Links<strong><font size=-1><br>\n");
	ShowLinks('&nbsp;&nbsp;&nbsp;', "<br>\n");
	print '</font><p><br>';

	// show some banners
	print '<center><font size=-2>';
	foreach($banners as $code)
	{
		print $code;
		print '<p>';
	}
	print '</font></center><p><br>';

	// show berlios logo
	print "<center><font size=-2>Thanks to<br>\n";
	print "<a href=\"$PROTO://developer.berlios.de\"><img src=\"$PROTO://developer.berlios.de/bslogo.php?group_id=$BERLIOS_GROUP_ID\" width=\"124\" height=\"32\" border=\"0\" alt=\"BerliOS Logo\"/></a><br>\n";
	print("for hosting us!</font></center>\n");

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


function ShowLinks($strPre, $strPost)
{
	global $links;


	// show all links in
	foreach($links as $link_name=>$link_url)
	{
		print $strPre;
		print '<a href="';
		print $link_url;
		print '">';
		print str_replace(' ', '&nbsp;', $link_name);
		print '</a>';
		print $strPost;
	}
}
?>
