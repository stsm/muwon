000010 REM WFZUGANG.INC
000020 REM Zugangskontrolle der einzelen Bereiche die in 30/5/2 (ver)(ge)währt wurden
000030 REM 05.05.08 Schmidt - Programmerstellung
000040 
000050 DEF FN.WFZUGANG$(PRG$,FKDNR$)
000060      LOCAL XFKDNR$,PW$,TRAEST%,TRAEAR%,TRAEAN%,TRAELI%,TRAEBE%,TRAEEI%
000070      FL% = 1 \ OPEN #1:"/WWWROOT/OPBK/PARAMET.OPBK", INPUT INDEXED \ CLEAR FL%
000080      KY1$ = "1"&FKDNR$
000090      GOSUB L1 \ UNLOCK #1
000100      CLOSE #1
000110      SELECT PRG$ ! Prüfen ob Programm freigeschaltet
000120           CASE "bk_st" ! Trägerstamm
000130                IF TRAEST%=1 THEN GOTO FN.ENDE
000140                IF TRAEST%=0 THEN GESPERRT% = 1 \ GOTO FN.ENDE
000150           CASE "bk_ar" ! Trägerartikel
000160                IF TRAEAR%=1 THEN GOTO FN.ENDE
000170                IF TRAEAR%=0 THEN GESPERRT% = 1 \ GOTO FN.ENDE
000180           CASE "bk_an" ! Träger anlegen
000190                IF TRAEAN%=1 THEN GOTO FN.ENDE
000200                IF TRAEAN%=0 THEN GESPERRT% = 1 \ GOTO FN.ENDE
000210           CASE "bk_li" ! Trägerlisten
000220                IF TRAELI%=1 THEN GOTO FN.ENDE
000230                IF TRAELI%=0 THEN GESPERRT% = 1 \ GOTO FN.ENDE
000240           CASE "bk_be" ! Bestellung
000250                IF TRAEBE%=1 THEN GOTO FN.ENDE
000260                IF TRAEBE%=0 THEN GESPERRT% = 1 \ GOTO FN.ENDE
000270           CASE "einst" ! Einstellungen
000280                IF TRAEEI%=1 THEN GOTO FN.ENDE
000290                IF TRAEEI%=0 THEN GESPERRT% = 1 \ GOTO FN.ENDE
000300           OTHERWISE 
000310                GOTO FN.ENDE
000320           CEND 
000330 REM --------------------------------------------------------
000340 L1: ! PARAMET.OPBK lesen
000350      READ #1,KY1$:XFKDNR$,PW$,TRAEST%,TRAEAR%,TRAEAN%,TRAELI%,TRAEBE%,TRAEEI%
000360      RETURN 
000370 REM --------------------------------------------------------
000380 FN.ENDE: ! Ausgang
000390      IF GESPERRT%=1 ! Zugangsmerker "gesperrt" gesetzt
000400           MSG$(1) = "<img src=/global/pics/error.png border=""0""> Dieser Bereich ist f&uuml;r Sie <strong>nicht</strong> freigeschaltet!"
000410           NAVIGATION$ = "<a href=""javascript:history.back();""><img src=""../global/pics/back.png"" border=""0""><font face=""verdana"" size=""2""> Zur&uuml;ck&nbsp;</font></a>"
000420           CALL CGI.TEMPLATE.VAR("msg1",MSG$(1))
000430           CALL CGI.TEMPLATE.VAR("navigation",NAVIGATION$)
000440           CALL CGI.TEMPLATE("/wwwroot/opbk/tpl/hinweis.tpl")
000450           END \ QUIT 
000460           IFEND 
000470      FNEND 
000480 REM --------------------------------------------------------
