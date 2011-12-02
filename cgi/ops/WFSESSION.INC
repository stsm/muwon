000010 REM WFSESSION.INC
000020 REM Sessionmanagement
000030 REM 25.01.08 Schmidt - Programmerstellung
000040 REM 01.02.08 Schmidt - Einbau der Session ID prüfung
000050 REM 13.02.08 Schmidt - Fehlertexte geändernt
000060 REM 04.02.09 Schmidt - MD5 Hash als Session-ID
000070 
000080      INCLUDE "encrypt"
000090 
000100 
000110 DEF FN.WFSESSION$(AKTION$,SID$,MITA$)
000120      LOCAL SESSION.ID$,JETZT,ABLAUF
000130      SELECT TRIM$(AKTION$)
000140           CASE "session.generate" ! Session ID generieren und speichern
000150                SYSTEM "sh ospl > syspl.txt:m"
000160                OPEN #1:"/syspl.txt:m", INPUT SEQUENTIAL 
000170                LINPUT #1:ZEILE$
000180                CLOSE #1
000190                TRENNER% = SCH(1,ZEILE$,"=")
000200                VER$ = ZEILE$[TRENNER%+1:LEN(ZEILE$)]
000210                RANDOMIZE 
000220                DIM SID.PART$(2)
000230                SID.PART$(1) = STR$(RND)      ! Zufallszahl Teil1
000240                SID.PART$(2) = STR$(RND)      ! Zufallszahl Teil2
000250                SID.PART$(1) = SID.PART$(1)[2:11]
000260                SID.PART$(2) = SID.PART$(2)[2:11]
000270                SESSION.ID$ = SID.PART$(1)&SID.PART$(2)
000280                IF VAL(VER$)>50181.0 ! MD5 Hash erst ab 50182
000290                     CALL MD5.ENCODE(SESSION.ID$,ADDROF(SID.HASH$))
000300                     FOR I% = 1 TO LEN(SID.HASH$)
000310                          C% = ASC(SID.HASH$[I%:I%])
000320                          MD5.SID$ = MD5.SID$&HEXOF$(C%)[3:4]
000330                          NEXT I%
000340                     CLEAR SESSION.ID$
000350                     SESSION.ID$ = LCASE$(MD5.SID$)
000360                     IFEND 
000370                FL% = 1 \ OPEN #1:"/WWWROOT/SESSION.ALLE", OUTPUT INDEXED \ CLEAR FL%
000380                JETZT = SECOND(TIME$(0))
000390                ABLAUF = JETZT+900      ! 15 Minuten
000400                ZEIT.JETZT$ = TIME$(JETZT)      ! lesbare Zeit HH.MM.SS
000410                ZEIT.ABLAUF$ = TIME$(ABLAUF)      ! lesbare Zeit HH.MM.SS
000420                KY1$ = "1"&MITA$&SESSION.ID$
000430                GOSUB S1      ! Session schreiben
000440                FN.WFSESSION$ = SESSION.ID$
000450                GOTO FN.ENDE
000460           CASE "session.update"      ! Session prüfen & Sessionlänge erneuern
000470                FL% = 1 \ OPEN #1:"/WWWROOT/SESSION.ALLE", UPDATE INDEXED \ CLEAR FL%
000480                KY1$ = "1"&MITA$&SID$
000490                GOSUB L1 \ UNLOCK #1 ! Sessiondatei lesen
000500                IF EOF(1)      ! Session abgelaufen oder Hijacking
000510                     MSG$(1) = "Sie haben l&auml;ngere Zeit keine Eingaben gemacht oder durch eine Fehleingabe einen Fehler hervorgerufen.<br /> Aus Sicherheitsgr&uuml;nden wurde daher die aktuelle Sitzung abgebrochen.<br />Bitte melden Sie sich erneut an."
000520                     IMG$ = "<img src=""../global/pics/error.png"">"
000530                     CALL CGI.TEMPLATE.VAR("img",IMG$)
000540                     CALL CGI.TEMPLATE.VAR("msg1",MSG$(1))
000550                     CALL CGI.TEMPLATE("/wwwroot/ops/error.asp")
000560                     END \ QUIT 
000570                     IFEND 
000580                JETZT = SECOND(TIME$(0))
000590                ABLAUF = JETZT+900      ! 15 Minuten
000600                ZEIT.JETZT$ = TIME$(JETZT)      ! lesbare Zeit HH.MM.SS
000610                ZEIT.ABLAUF$ = TIME$(ABLAUF)      ! lesbare Zeit HH.MM.SS
000620                KY1$ = "1"&MITA$&SID$
000630                GOSUB S1      ! Sessioneintrag erneuern (ABLAUF)
000640                CALL CGI.TEMPLATE.VAR("sid",SID$)
000650                GOTO FN.ENDE
000660           CASE "session.destroy"      ! Session löschen, Sitzung normal beendet
000670                FL% = 1 \ OPEN #1:"/WWWROOT/SESSION.ALLE", OUTPUT INDEXED \ CLEAR FL%
000680                JETZT = SECOND(TIME$(0))
000690                ABLAUF = 0
000700                SESSION.ID$ = SID$
000710                KY1$ = "1"&MITA$&SID$
000720                GOSUB S1      ! Ablauf auf 0 setzen damit der Daemon sie lö.
000730                GOTO FN.ENDE
000740           OTHERWISE 
000750                PRINT "Hacking attempt!"
000760                STOP 
000770           CEND 
000780 REM --------------------------------------------------------
000790 L1:      ! Sessiondatei lesen
000800      READ #1,KY1$:XMITA$,SESSION.ID$,JETZT,ABLAUF,TEMP$,TEMP$,TEMP$
000810      RETURN 
000820 S1:      ! Sessiondatei schreiben
000830      WRITE #1,KY1$:MITA$,SESSION.ID$,JETZT,ABLAUF,ZEIT.JETZT$,ZEIT.ABLAUF$,DATE$(0)
000840      RETURN 
000850 REM --------------------------------------------------------
000860 FN.ENDE:      ! Ausgang
000870      CLOSE #1      ! Sessiondatei schliessen
000880      FNEND 
000890 
