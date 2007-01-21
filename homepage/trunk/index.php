<?php

// this is the configuration


// area name, page path and page description
// NOTE: if the description is not set, the entry is not shown in the projects list
$subpages = array(
	// 'home' and 'links' are special, they should only appear in the main menu
	'home'		=> array(name=>'Home', 'path'=>'home/index.php'),
	'links'		=> array(name=>'Links', 'path'=>'links/index.php'),

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
Mylene is used in the dfi and lnx plugins for the MMC64.'),

	// next are the hidden entries (the fun stuff)
	'bughunt'	=> array(name=>'Baccy\'s Big Bughunt', 'path'=>'bughunt/index.php'),

	'sodom'		=> array(name=>'Das Tier = 666', 'path'=>'sodom/index.php')
);


$links = array(
	'Retrohackers'		=> array(link=>'http://retrohackers.org', 'dsc'=>
'Meet the developers: Retrohackers is the community for Retro Replay, RR-Net and equivalents where we discuss our projects.'),

	'Individual Computers'	=> array(link=>'http://ami.ga', 'dsc'=>
'Producer of the Retro Replay and other cool hardware for your C64 and Amiga.'),

	'C64.sk'		=> array(link=>'http://www.c64.sk', 'dsc'=>
'Open C64 scene news: new software, demos, games and parties.'),

	'CSDB'			=> array(link=>'http://noname.c64.org/csdb', 'dsc'=>
'The C64 Scene Database, a site dedicated to gathering as much information as possible about the productions, the groups, the sceners and the events in the Commodore 64 scene.'),

	'The Dreams'		=> array(link=>'http://www.the-dreams.de', 'dsc'=>
'Weird guys...')
);


// Copy all banner codes into this array, quoted with single ticks (').
// Don't forget to escape any ticks in the banner code itself. :)
$banners = array(
	// c64.sk
'<a href="http://www.c64.sk"><img class=banner src="banner/c64sk90x30.gif" alt="C64.sk Logo"><br><small>C64 News</small></a>',

	// Small "Defective By Design" badge from http://www.defectivebydesign.org/promo/button
'<a href="http://www.defectivebydesign.org/join/button">
<img class=banner src="banner/dbd_sm_btn.png" alt="DRM is DefectiveByDesign"/><br />
<small>Protect your freedom!</small></a>',

	// BadVista logo from http://badvista.fsf.org/logos/BadVista_no_littering.png/view
'<a href="http://www.badvista.org">
<img class=banner src="banner/BadVista_no_littering.png" alt="BadVista.org: Stopping Vista adoption by promoting free software"></a>'
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

	print '<?xml version="1.0" encoding="ISO-8859-1"?>';
	print '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">';
	print '<html><head>';
	print '<link rel=StyleSheet href="dreams.css" type="text/css">';
	print '<meta name="Keywords" content="rrtools,c64,retro replay,mmc64,rrnet">';
	print '<meta name="Description" content="Retro Replay Tools Homepage">';
	print '<title>Retro Replay Tools';
	if( isset($ar_attr) && isset($ar_attr['name']) )
	{
		print ' - ';
		print $ar_attr['name'];
	}
	print '</title>';
	print '</head>';
	print '<body>';

	print "<table border=0 cellpadding=0 cellspacing=0 width=\"100%\"><tbody>\n";

	print '<tr><td class=menu_ul><img src="blk1x1.gif" alt=""></td><td class=menu_u><img src="blk1x1.gif" alt=""></td><td class=menu_ur><img src="blk1x1.gif" alt=""></td><td class=menu_g><img src="blk2x2.gif" alt=""></td><td class=parea_u><img src="blk1x1.gif" alt=""></td></tr>';
	print "\n";

	print "<tr><td class=menu_l><img src=\"blk8x8.gif\" alt=\"\"></td><td class=menu_cu>\n";

	print "<strong>Menu</strong><br>\n";
	if( isset($subpages['home']) )
	{
		$attr = $subpages['home'];
		print '&nbsp;&nbsp;&nbsp;<a class=menuitem href="index.php?area=home">';
		print str_replace(' ', '&nbsp;', $attr['name']);
		print "</a><br>\n";
	}
	print "&nbsp;&nbsp;&nbsp;<a class=menuitem href=\"$PROTO://developer.berlios.de/projects/rrtools\">Project&nbsp;Page</a><br>\n";
	print "&nbsp;&nbsp;&nbsp;<a class=menuitem href=\"$PROTO://developer.berlios.de/project/showfiles.php?group_id=$BERLIOS_GROUP_ID\">All&nbsp;Downloads</a><br>\n";
	print "&nbsp;&nbsp;&nbsp;<a class=menuitem href=\"$PROTO://developer.berlios.de/mail/?group_id=$BERLIOS_GROUP_ID\">All&nbsp;Mailinglists</a><br>\n";
	if( isset($subpages['links']) )
	{
		$attr = $subpages['links'];
		print '&nbsp;&nbsp;&nbsp;<a class=menuitem href="index.php?area=links">';
		print str_replace(' ', '&nbsp;', $attr['name']);
		print "</a><br>\n";
	}
	print "<p>\n";

	print("<strong>Projects</strong><br>\n");
	foreach($subpages as $section=>$prj_attr)
	{
		// is the description set?
		if( isset($prj_attr['dsc']) )
		{
			print '&nbsp;&nbsp;&nbsp;<a class=menuitem href="index.php?area=';
			print $section;
			print '">';
			print str_replace(' ', '&nbsp;', $prj_attr['name']);
			print "</a><br>\n";
		}
	}
	print("<p>");

	print '<strong>Quick Links</strong><br>';
	ShowLinks('&nbsp;&nbsp;&nbsp;', "<br>\n");
	print '<p><br>';

	print "</td><td class=menu_r><img src=\"blk8x8.gif\" alt=\"\"></td><td class=menu_g><img src=\"blk2x2.gif\" alt=\"\"></td>\n";
	print '<td valign=top rowspan=2 ';
	if( function_exists("ShowTD") )
	{
		// insert table cell attributes like background etc.
		ShowTD();
	}
	print ">\n";

	if( function_exists('ShowPage') )
	{
		ShowPage();
	}
	else
	{
		print "Page $area does not exist yet.";
	}

	print '</td></tr>';

	print "<tr><td class=menu_l><img src=\"blk8x8.gif\" alt=\"\"></td><td class=menu_cb>\n";
	// show some banners
	foreach($banners as $code)
	{
		print "<p class=banner>$code</p>\n";
	}
	print '<p><br>';

	// show berlios logo, but not for local development
	print "<p class=banner>Thanks to<br>\n";
	if( isset($_SERVER['SERVER_ADDR']) && $_SERVER['SERVER_ADDR']=="127.0.0.1" )
	{
		print 'BerliOS<br>';
	}
	else
	{
		print "<a href=\"$PROTO://developer.berlios.de\"><img src=\"$PROTO://developer.berlios.de/bslogo.php?group_id=$BERLIOS_GROUP_ID\" width=\"124\" height=\"32\" border=\"0\" alt=\"BerliOS Logo\"/></a><br>\n";
	}
	print "for hosting us!</p>\n";
	print '<p><br>';

	// show contact info
	print '<p class=contact>Contact: <img src="contact.png" alt="baccy_drm*berlios.de"></p><br>';

	print "</td><td class=menu_r><img src=\"blk8x8.gif\" alt=\"\"></td><td class=menu_g><img src=\"blk2x2.gif\" alt=\"\"></td>\n";

	print "<tr><td class=menu_bl><img src=\"blk8x8.gif\" alt=\"\"></td><td class=menu_b><img src=\"blk8x8.gif\" alt=\"\"></td><td class=menu_br><img src=\"blk8x8.gif\" alt=\"\"></td><td class=menu_g><img src=\"blk2x2.gif\" alt=\"\"></td><td><img src=\"blk2x2.gif\" alt=\"\"></td></tr></tbody></table></body></html>";
}


function ShowLinks($strPre, $strPost)
{
	global $links;


	// show all links in
	foreach($links as $link_name=>$link_attr)
	{
		print $strPre;
		print '<a class=menuitem href="';
		print $link_attr['link'];
		print '">';
		print str_replace(' ', '&nbsp;', $link_name);
		print '</a>';
		print $strPost;
	}
}
?>
