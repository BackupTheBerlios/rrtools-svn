<?php


function ShowTD()
{
	print("background=\"home/prost.png\"");
}


function ShowPage()
{
	global $BERLIOS_GROUP_ID;
	global $subpages;


	// link to the news headers (including some lines)
	$newsfile = sprintf("projnews.php\?group_id=%d\&limit=10\&flat=0\&show_summaries=1", $BERLIOS_GROUP_ID);

	print("<p><br><center><h2>Welcome to the home of the Retro Replay Tools!</h2></center><br><br>\n");
	print("You'll find the latest versions of our projects and some related files here.\n");
	print("<p><br>\n");


	foreach($subpages as $section=>$ar_attr)
	{
		// show the section?
		if( isset($ar_attr['dsc']) )
		{
			print '<h3>';
			print $ar_attr['name'];
			print "</h3>\n";
			print $ar_attr['dsc'];
			print "<br><a href=\"index.php?area=$section\">[More...]</a>\n";
			print "<p><br>\n";
		}
	}

	print("This page is best viewed with <a href=\"http://elinks.cz\">links</a> in 80x50. But then you would miss Uncle Tom and TWOO in the background (I guess everything has it's ups and downs).\n");
	print("<br>IIRC Tom was yelling 'Beeer!'. Or was it 'Dreeeams!' ? Hum, nevermind... almost the same anyway. ;)\n");
	print("<p><br>\n");
	print("Crappy page design by Doc Bacardi/The Dreams\n");
	print("<p><br>\n");
}

?>
