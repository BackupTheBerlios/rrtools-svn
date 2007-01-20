<?php


function ShowPage()
{
	global $links;


	print "<p><br><center><h2>Links</h2></center><br><br>\n";
	print "On this page you'll find some links (more or less) related to the RRTools project.<br>\n";
	print "Of course we are not responsible for all the disgusting things you'll find there. ;)\n";
	print '<p><br>';

	foreach($links as $link_name=>$link_attr)
	{
		print '<h3>';
		print $link_name;
		print "</h3>\n";
		print $link_attr['dsc'];
		print '<br><a href="';
		print $link_attr['link'];
		print '">';
		print $link_attr['link'];
		print "</a>\n<p><br>\n";
	}
}

?>
