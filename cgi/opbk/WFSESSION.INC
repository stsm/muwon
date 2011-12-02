000010 REM WFSESSION.INC
000020 REM Sessionmanagement
000030 REM 16.04.2009 Schmidt - Programmerstellung
000060 
000070 
000080      INCLUDE "encrypt"
000090 
000100 DEF FN.WFSESSION$(AKTION$,SID$,FKDNR$)
000110      LOCAL SESSION.ID$,JETZT,ABLAUF
000120      SELECT TRIM$(AKTION$)
000130           CASE "session.generate" ! Session ID generieren und speichern
000140                SYSTEM "sh ospl > syspl.txt:m"
000150                OPEN #1:"/syspl.txt:m", INPUT SEQUENTIAL 
000160                LINPUT #1:ZEILE$
000170                CLOSE #1
000180                TRENNER% = SCH(1,ZEILE$,"=")
000190                VER$ = ZEILE$[TRENNER%+1:LEN(ZEILE$)]
000200                RANDOMIZE 
000210                DIM SID.PART$(2)
000220                SID.PART$(1) = STR$(RND) ! Zufallszahl Teil1
000230                SID.PART$(2) = STR$(RND) ! Zufallszahl Teil2
000240                SID.PART$(1) = SID.PART$(1)[2:11]
000250                SID.PART$(2) = SID.PART$(2)[2:11]
000260                SESSION.ID$ = SID.PART$(1)&SID.PART$(2)
000270                IF VAL(VER$)>50181.0 ! MD5 Hash erst ab 50182
000280                     CALL MD5.ENCODE(SESSION.ID$,ADDROF(SID.HASH$))
000290                     FOR I% = 1 TO LEN(SID.HASH$)
000300                          C% = ASC(SID.HASH$[I%:I%])
000310                          MD5.SID$ = MD5.SID$&HEXOF$(C%)[3:4]
000320                          NEXT I%
000330                     CLEAR SESSION.ID$
000340                     SESSION.ID$ = LCASE$(MD5.SID$)
000350                     IFEND 
000360                FL% = 1 \ OPEN #1:"/WWWROOT/SESSION.ALLE", OUTPUT INDEXED \ CLEAR FL%
000370                JETZT = SECOND(TIME$(0))
000380                ABLAUF = JETZT+900 ! 15 Minuten
000390                ZEIT.JETZT$ = TIME$(JETZT) ! lesbare Zeit HH.MM.SS
000400                ZEIT.ABLAUF$ = TIME$(ABLAUF) ! lesbare Zeit HH.MM.SS
000410                KY1$ = "1"&FKDNR$&SESSION.ID$
000420                GOSUB S1 ! Session schreiben
000430                FN.WFSESSION$ = SESSION.ID$
000440                GOTO FN.ENDE
000450           CASE "session.update" ! Session prüfen & Sessionlänge erneuern
000460                FL% = 1 \ OPEN #1:"/WWWROOT/SESSION.ALLE", UPDATE INDEXED \ CLEAR FL%
000470                KY1$ = "1"&FKDNR$&SID$
000480                GOSUB L1 \ UNLOCK #1 ! Sessiondatei lesen
000490                IF EOF(1) ! Session abgelaufen oder Hijacking
000500                     MSG$(1) = "Sie haben l&auml;ngere Zeit keine Eingaben gemacht oder durch eine Fehleingabe einen Fehler hervorgerufen.<br /> Aus Sicherheitsgr&uuml;nden wurde daher die aktuelle Sitzung abgebrochen.<br />Bitte melden Sie sich erneut an."
000510                     IMG$ = "<img src=""../global/pics/error.png"">"
000520                     CALL CGI.TEMPLATE.VAR("img",IMG$)
000530                     CALL CGI.TEMPLATE.VAR("msg1",MSG$(1))
000540                     CALL CGI.TEMPLATE("/wwwroot/opbk/error.asp")
000550                     END \ QUIT 
000560                     IFEND 
000570                JETZT = SECOND(TIME$(0))
000580                ABLAUF = JETZT+900 ! 15 Minuten
000590                ZEIT.JETZT$ = TIME$(JETZT) ! lesbare Zeit HH.MM.SS
000600                ZEIT.ABLAUF$ = TIME$(ABLAUF) ! lesbare Zeit HH.MM.SS
000610                KY1$ = "1"&FKDNR$&SID$
000620                GOSUB S1 ! Sessioneintrag erneuern (ABLAUF)
000630                CALL CGI.TEMPLATE.VAR("sid",SID$)
000640                GOTO FN.ENDE
000650           CASE "session.destroy" ! Session löschen, Sitzung normal beendet
000660                FL% = 1 \ OPEN #1:"/WWWROOT/SESSION.ALLE", OUTPUT INDEXED \ CLEAR FL%
000670                JETZT = SECOND(TIME$(0))
000680                ABLAUF = 0
000690                SESSION.ID$ = SID$
000700                KY1$ = "1"&FKDNR$&SID$
000710                GOSUB S1 ! Ablauf auf 0 setzen damit der Daemon sie lö.
000720                GOTO FN.ENDE
000730           OTHERWISE 
000740                PRINT "Hacking attempt!"
000750                STOP 
000760           CEND 
000770 REM --------------------------------------------------------
000780 L1: ! Sessiondatei lesen
000790      READ #1,KY1$:GKDNR$,SESSION.ID$,JETZT,ABLAUF,TEMP$,TEMP$,TEMP$
000800      RETURN 
000810 S1: ! Sessiondatei schreiben
000820      WRITE #1,KY1$:FKDNR$,SESSION.ID$,JETZT,ABLAUF,ZEIT.JETZT$,ZEIT.ABLAUF$,DATE$(0)
000830      RETURN 
000840 REM --------------------------------------------------------
000850 FN.ENDE: ! Ausgang
000860      CLOSE #1 ! Sessiondatei schliessen
000870      FNEND 
000880 
