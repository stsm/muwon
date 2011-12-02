000010 REM WFKIBEWA
000020 REM Includemodul zum Auswählen der Bewohner
000030 DEF FNWFKIBEWA$(FKDNR$) ! formatierte Kd.-nr ("999999") an INC übegeben
000040      DIM BEWOSU$(1000),BEWONA$(1000),BEWONR$(1000),SELECT.INHALT.NAMEN$(1000),SELECT.INHALT.NUMMER$(1000),SELECT.INHALT.SUCHNA$(1000)
000050      SUCHBOX$ = FN.FORM.CHECKBOX$("suchbox",0,"aktiv","Artikelsuche :")
000060      SUCHFELD$ = FN.FORM.INPUT$("suchfeld",25,30,"")
000070      ARTIKELBOX$ = FN.FORM.CHECKBOX$("artikelbox",0,"aktiv","nach Status :")
000080      ARTIKEL.AUSWAHL$(1) = FN.FORM.SELECT.OPTION$("99",1,"jeder Status")
000090      ARTIKEL.AUSWAHL$(2) = FN.FORM.SELECT.OPTION$("0",0,"beim Kunden")
000100      ARTIKEL.AUSWAHL$(3) = FN.FORM.SELECT.OPTION$("1",0,"beim W&auml;scher")
000110      SYSTEM "cr ALSUCH."&FKDNR$&":m (indexed file 2000 recl 100 keyl 50"
000120      SYSTEM "cr SUCHNA."&FKDNR$&":m (indexed file 2000 recl 100 keyl 50"
000130      FL% = 10 \ OPEN #10:"ALSUCH."&FKDNR$&":m", UPDATE INDEXED \ CLEAR FL%
000140      FL% = 11 \ OPEN #11:"/BEWOH1.REI", INPUT INDEXED \ CLEAR FL% ! Bewo.-stammdaten
000150      FL% = 12 \ OPEN #12:"SUCHNA."&FKDNR$&":m", UPDATE INDEXED \ CLEAR FL%
000160      FL% = 13 \ OPEN #13:"/BEWOH2.REI", INPUT INDEXED \ CLEAR FL% ! Bewo.-stammdaten
000170      KY11$ = "1"&FKDNR$
000180      GOSUB L11 \ UNLOCK #11 ! Bewohnerstamm lesen
000190      GOSUB L111 \ UNLOCK #11 ! Bewohnerstamm lesen nächst
000200      IF EOF(11) THEN CLOSE #11 \ GOTO 340
000210      IF KY11$[2:7]<>FKDNR$ THEN GOTO 190 ! nächsten Satz BEWOH1
000220      I% = I%+1
000230      BEWONA$(I%) = ASBE$
000240      BEWONR$(I%) = STR$(ASNR)
000250      BEWOSU$(I%) = ASSW$
000260      IF TRIM$(BEWOSU$(I%))="" THEN BEWOSU$(I%) = "X"
000270      GOSUB S10 ! Sortierung schreiben (Bewohnernummer)
000280      GOSUB S12 ! Sortierung schreiben (Suchname)
000290      FOR Y% = I% TO I% ! nach Namen sortieren
000300           SELECT.INHALT.NUMMER$(Y%) = FN.FORM.SELECT.OPTION$(BEWONR$(Y%),0,FORMAT$(VAL(BEWONR$(Y%)),"9999")&" - "&BEWONA$(Y%))
000310           CALL CGI.TEMPLATE.VAR("selbox.nummer"&STR$(Y%),SELECT.INHALT.NUMMER$(Y%)) ! Inhalt des Nummernauswahlfeldes generieren
000320           NEXT Y%
000330      GOTO 190 ! nächsten Satz BEWOH1
000340      KY10$ = "1"
000350      GOSUB L10 \ UNLOCK #10
000360      FOR X% = 1 TO I% ! nach Bewohnernummer sortieren
000370           GOSUB L101 \ UNLOCK #10
000380           SELECT.INHALT.NAMEN$(X%) = FN.FORM.SELECT.OPTION$(ALKDNR$,0,KY10$) ! Inhalt des Namenauswahlfeldesgenerieren
000390           CALL CGI.TEMPLATE.VAR("selbox.namen"&STR$(X%),SELECT.INHALT.NAMEN$(X%))
000400           NEXT X%
000410      KY12$ = "1"
000420      GOSUB L12 \ UNLOCK #12
000430      FOR Z% = 1 TO I% ! nach Bewohnersuchname sortieren
000440           GOSUB L121 \ UNLOCK #12
000450           SELECT.INHALT.SUCHNA$(Z%) = FN.FORM.SELECT.OPTION$(SUCH.BEWNR$,0,KY12$[2:2]&" - "&SUCH.BEWNA$) ! Inhalt des Namenauswahlfeldesgenerieren
000460           CALL CGI.TEMPLATE.VAR("selbox.suchna"&STR$(Z%),SELECT.INHALT.SUCHNA$(Z%))
000470           NEXT Z%
000480      CALL CGI.TEMPLATE.VAR("suchbox",SUCHBOX$)
000490      CALL CGI.TEMPLATE.VAR("suchfeld",SUCHFELD$)
000500      IF BARV%=1 ! Bew.-art.-liste vollständig/unvollst. darf nach St. suchen
000510           CALL CGI.TEMPLATE.VAR("artikelbox",ARTIKELBOX$)
000520           CALL CGI.TEMPLATE.VAR("selbox.artikel1",ARTIKEL.AUSWAHL$(1))
000530           CALL CGI.TEMPLATE.VAR("selbox.artikel2",ARTIKEL.AUSWAHL$(2))
000540           CALL CGI.TEMPLATE.VAR("selbox.artikel3",ARTIKEL.AUSWAHL$(3))
000550           IFEND 
000560      GOTO FN.ENDE
000570 REM **********************************************************
000580 L10:      ! Alphabetische Sortierung Bewohner
000590      READ #10,KY10$:ALKDNR$ \ 
000600      RETURN 
000610 L101:      ! Alphabetische Sortierung Bewohner
000620      READNEXT #10,KY10$:ALKDNR$
000630      RETURN 
000640 S10:      ! Alphabetische Sortierung schreiben
000650      WRITE #10,BEWONA$(I%):BEWONR$(I%)
000660      RETURN 
000670 L11:      ! Bewohnerstamm lesen
000680      READ #11,KY11$:AS1%,AS2%,ZNR%,KNR,ASNR,ASBE$,ASSW$,ASP1$,ASP2$,ASP3$,ASP4$,ASP5,ASP6,ASP7%,ASP8%,XX1$,XX2$
000690      RETURN 
000700 L111:      ! Bewohnerstamm lesen - nächsten Satz
000710      READNEXT #11,KY11$:AS1%,AS2%,ZNR%,KNR,ASNR,ASBE$,ASSW$,ASP1$,ASP2$,ASP3$,ASP4$,ASP5,ASP6,ASP7%,ASP8%,XX1$,XX2$
000720      RETURN 
000730 L12:      ! Sortierung der Bewohner nach Suchnamen
000740      READ #12,KY12$:SUCH.BEWNA$,SUCH.BEWNR$
000750      RETURN 
000760 L121:      ! Sortierung der Bewohner nach Suchname
000770      READNEXT #12,KY12$:SUCH.BEWNA$,SUCH.BEWNR$
000780      RETURN 
000790 S12:      ! Sortierung nach Suchname schreiben
000800      WRITE #12,"1"&BEWOSU$(I%)&BEWONR$(I%):BEWONA$(I%),BEWONR$(I%)
000810      RETURN 
000820 L13: ! Bewohnersuchnamen lesen
000830      READ #13,KY13$:ASSW$,LSUKNR,LSUBNR
000840      RETURN 
000850 L131: ! Bewohnersuchnamen lesen - nächsten Satz
000860      READNEXT #13,KY13$:ASSW$,LSUKNR,LSUBNR
000870      RETURN 
000880 REM **********************************************************
000890 FN.ENDE:      ! Ausgang
000900      CLOSE #10 \ CLOSE #11 \ CLOSE #12
000910      SYSTEM "er ALSUCH."&FKDNR$&":m ( not noq"
000920      SYSTEM "er SUCHNA."&FKDNR$&":m ( not noq"
000930      FNEND 
