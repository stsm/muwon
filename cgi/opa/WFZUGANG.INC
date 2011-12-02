000010 REM WFZUGANG.INC
000020 REM Zugangskontrolle der einzelen Bereiche die in 30/5 (ver)(ge)währt wurden
000030 REM 05.03.08 Schmidt - Programmerstellung
000040 
000050 DEF FN.WFZUGANG$(PRG$,FKDNR$)
000060      LOCAL XFKDNR$,PW$,BST%,BAR%,BAN%,BLI%,BAE%,GESPERRT%,BLA%
000070      FL% = 1 \ OPEN #1:"/WWWROOT/OPA/PARAMET.OPA", INPUT INDEXED \ CLEAR FL%
000080      KY1$ = "1"&FKDNR$
000090      GOSUB L1 \ UNLOCK #1
000100      CLOSE #1
000110      SELECT PRG$ ! Prüfen ob Programm freigeschaltet
000120           CASE "bewo_st" ! Bewohnerstammdaten
000130                IF BST%=1 THEN GOTO FN.ENDE
000140                IF BST%=0 THEN GESPERRT% = 1 \ GOTO FN.ENDE
000150           CASE "bewo_ar" ! Bewohnerartikel
000160                IF BAR%=1 THEN GOTO FN.ENDE
000170                IF BAR%=0 THEN GESPERRT% = 1 \ GOTO FN.ENDE
000180           CASE "bewo_an" ! Bewohner anlegen
000190                IF BAN%=1 THEN GOTO FN.ENDE
000200                IF BAN%=0 THEN GESPERRT% = 1 \ GOTO FN.ENDE
000210           CASE "bewo_li" ! Bewohnerlisten
000220                IF BLI%=1 THEN GOTO FN.ENDE
000230                IF BLI%=0 THEN GESPERRT% = 1 \ GOTO FN.ENDE
000240           CASE "bewo_ae" ! Bewohner ändern
000250                IF BAE%=1 THEN GOTO FN.ENDE
000260                IF BAE%=0 THEN GESPERRT% = 1 \ GOTO FN.ENDE
000270           CASE "bewo_la" ! Eingang der letzten Artikel
000280                IF BLA%=1 THEN GOTO FN.ENDE
000290                IF BLA%=0 THEN GESPERRT% = 1 \ GOTO FN.ENDE
000300           OTHERWISE 
000310                GOTO FN.ENDE
000320           CEND 
000330 REM --------------------------------------------------------
000340 L1: ! PARAMET.OPA lesen
000350      READ #1,KY1$:XFKDNR$,PW$,BST%,BAR%,BAN%,BLI%,BSP%,BAE%,BARV%,EMAIL%,BGAR%,BAOA%,BLA%,BTA%
000370      RETURN 
000380 REM --------------------------------------------------------
000390 FN.ENDE: ! Ausgang
000400      IF GESPERRT%=1 ! Zugangsmerker "gesperrt" gesetzt
000410           MSG$(1) = "Dieser Bereich ist f&uuml;r Sie <strong>nicht</strong> freigeschaltet!"
000420           NAVIGATION$ = "<a href=""javascript:history.back();""><img src=""../global/pics/back.png"" border=""0""><font face=""verdana"" size=""2""> Zur&uuml;ck&nbsp;</font></a>"
000430           CALL CGI.TEMPLATE.VAR("msg1",MSG$(1))
000440           CALL CGI.TEMPLATE.VAR("navigation",NAVIGATION$)
000450           CALL CGI.TEMPLATE("/wwwroot/opa/tpl/hinweis.tpl")
000460           END \ QUIT 
000470           IFEND 
000480      FNEND 
000490 REM --------------------------------------------------------
000500 REM PRG$ = Programmname
000510 REM bewo_st = Bewohnerstammdaten / BST%
000520 REM bewo_ar = Bewohnerartikel / BAR%
000530 REM bewo_an = Bewohner anlegen / BAN%
000540 REM bewo_li = Bewohnerlisten / BLI%
000550 REM bewo_ae = Bewohner ändern / BAE%
000560 REM bewo_la = Eingang der letzten Artikel / BLA%
000570 REM --------------------------------------------------------
