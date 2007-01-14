<?php

function ShowPage()
{
	global $ARGV;

	print("<P><center><h1>Das Tier = 666</h1></center><BR><BR>\n");

	if( isset($ARGV["idx"]) && $ARGV["idx"]>0 && $ARGV["idx"]<19 )
	{
		$idx = $ARGV["idx"];
		if( $idx>1 )
			$link = sprintf("<a href=\"index.php?area=sodom&idx=%d\">Vorige Seite</a>", $idx-1);
		else
			$link = "Vorige Seite";
		$link .= " - <a href=\"index.php?area=sodom\">Zur&uuml;ck</a> - ";
		if( $idx<18 )
			$link .= sprintf("<a href=\"index.php?area=sodom&idx=%d\">N&auml;chste Seite</a>", $idx+1);
		else
			$link .= "N&auml;chste Seite";

		printf("<center>%s<hr>", $link);
		if( $idx<17 )
		{
			$name = "Seite " . $idx;
			printf("%s<br><br>", $name);
			printf("<img src=\"sodom/Sodom_%02d.jpg\" alt=\"%s\" title=\"%s\"><p>\n", $idx, $name, $name);
		}
		else
		{
			$name = "Postkarte " . (($idx==17)?"Vorderseite":"Hinterseite");
			printf("%s<br><br>", $name);
			printf("<img src=\"sodom/Sodom_Post%d.jpg\" alt=\"%s\" title=\"%s\"><p>\n", $idx-16, $name, $name);
		}
		printf("<hr>%s</center>\n", $link);
	}
	else
	{
		print "<p>Leider verh&auml;lt sich ein Rechner nicht immer so logisch, klar und nachvollziehbar, wie man es von einem\n";
		print "elektronischen Ger&auml;et erwartet. Oft vertst&ouml;sst er sogar gegen s&auml;mtliche Gesetze der menschlichen Logik,\n";
		print "sodass man glauben mag, nicht vor einer Maschiene, sondern einem kleinen Kobold zu sitzen.</p>\n";

		print "<p>&Uuml;ber dieses Thema scheinen sich auch Kirchenm&auml;nner Gedanken zu machen, besonders aber solche,\n";
		print "die es gerne w&auml;ren. Das wurde mir klar, als meine Oma an einem stinknormalen deutschen Wallfahrtsort\n";
		print "folgendes in die Hand gedr&uuml;ckt bekam.</p>\n";

		print "<p>Nun habe ich durch Fr. Meinrad Mitra von der Benediktinerabtei Stift G&ouml;ttweig erfahren, dass die\n";
		print "Marienkinder nicht mehr von der katholischen Kirche geduldet werden. Vielen Dank f&uuml;r diese guten Nachrichten,\n";
		print "das gibt mir ein St&uuml;ck des Vertrauens zur&uuml;ck, das ich mal in die Kirche hatte. Mir macht jedoch noch grosse Sorge,\n";
		print "dass diese Jungs mal anerkannt waren. Andererseits hatten sie eine Erkl&auml;rung f&uuml;r all diese Abst&uuml;rze...\n";
		print "Naja, man kann in dieser Welt wohl nicht alles haben.</p>\n";

		print '<P><BR><BR><center><table><tr>';
		for($cnt=1; $cnt<17; $cnt++)
		{
			printf("<td><a href=\"index.php?area=sodom&idx=%d\"><img src=\"sodom/Sodom_t%02d.jpg\" alt=\"Seite %d\" title=\"Seite %d\"></a></td>\n",$cnt,$cnt,$cnt,$cnt);
			if( $cnt%4==0 && $cnt<16)
				print("</tr><tr>\n");
		}
		print("</tr></table></center><P>\n");
		print("Jau, so stehts also um den Computer. Wer nach diesen ersch&uuml;tternden Erkenntnissen ein auf Papier gedrucktes Exemplar vorzieht, fordere dieses bitte mit der unten abgebildeten Postkarte kostenlos an.\n");
		print("Ich kann Euch auch die angebotene wundert&auml;tige Medallie sehr empfehlen! (kleiner Nachteil: seitdem sie an meinem PC h&auml;ngt, l&auml;sst sich Windows nicht mehr starten)\n");
		print("Und seid vorsichtig, wenn Ihr das n&auml;chste mal Euren Rechner aufschraubt. Wer wei&szlig;, wer darin auf Euch wartet....\n");
		print("<P><BR><center>\n");
		print("<a href=\"index.php?area=sodom&idx=17\"><img src=\"sodom/Sodom_tPost1.jpg\" alt=\"Postkarte Vorderseite\"></a>\n");
		print("<a href=\"index.php?area=sodom&idx=18\"><img src=\"sodom/Sodom_tPost2.jpg\" alt=\"Postkarte R&uuml;ckseite\"></a>\n");
		print("</center><P><BR><BR>\n");
	}
}

?>
