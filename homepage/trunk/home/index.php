<?php


function ShowTD()
{
	print("style=\"background-image: url(home/prost.png)\"");
}


function ShowPage()
{
	global $subpages;


	print("<p><br><h2 style=\"text-align: center\">Welcome to the home of the Retro Replay Tools!</h2><br><br>\n");
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
