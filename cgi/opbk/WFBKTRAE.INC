000010 REM WFKIBEWA
000020 REM Includemodul zum auswählen von Trägern
000030 DEF FNWFBKTRAE$(FKDNR$) ! formatierte Kd.-nr ("999999") an INC übegeben
000040      DIM TRAESU$(1000),TRAENA$(1000),TRAENR$(1000),SELECT.INHALT.NAMEN$(1000),SELECT.INHALT.NUMMER$(1000),SELECT.INHALT.SUCHNA$(1000)
000050      SUCHBOX$ = FN.FORM.CHECKBOX$("suchbox",0,"aktiv","Artikelsuche :")
000060      SUCHFELD$ = FN.FORM.INPUT$("suchfeld",25,30,"")
000070      ARTIKELBOX$ = FN.FORM.CHECKBOX$("artikelbox",0,"aktiv","nach Status :")
000080      ARTIKEL.AUSWAHL$(1) = FN.FORM.SELECT.OPTION$("99",1,"jeder Status")
000090      ARTIKEL.AUSWAHL$(2) = FN.FORM.SELECT.OPTION$("0",0,"beim Kunden")
000100      ARTIKEL.AUSWAHL$(3) = FN.FORM.SELECT.OPTION$("1",0,"beim W&auml;scher")
000110      SYSTEM "cr ALSUCH."&FKDNR$&":m (indexed file 2000 recl 100 keyl 50"
000120      SYSTEM "cr SUCHNA."&FKDNR$&":m (indexed file 2000 recl 100 keyl 50"
000130      FL% = 10 \ OPEN #10:"ALSUCH."&FKDNR$&":m", UPDATE INDEXED \ CLEAR FL%
000140      FL% = 11 \ OPEN #11:"/TRAE10.REI", INPUT INDEXED \ CLEAR FL% ! Trae.-stammdaten
000150      FL% = 12 \ OPEN #12:"SUCHNA."&FKDNR$&":m", UPDATE INDEXED \ CLEAR FL%
000210      KY11$ = "1"&FKDNR$
000220      GOSUB L11 \ UNLOCK #11 ! Trägerstamm lesen
000230      GOSUB L111 \ UNLOCK #11 ! Trägerstamm lesen
000240      IF EOF(11) THEN CLOSE #11 \ GOTO 380
000250      IF KY11$[2:7]<>FKDNR$ THEN GOTO 230 ! nächsten Satz BEWOH1
000260      I% = I%+1
000270      TRAENA$(I%) = TRASBE$
000280      TRAENR$(I%) = STR$(TRASNR)
000290      TRAESU$(I%) = TRASSW$
000300      IF TRIM$(TRAESU$(I%))="" THEN TRAESU$(I%) = "X"
000310      GOSUB S10 ! Sortierung schreiben (Bewohnernummer)
000320      GOSUB S12 ! Sortierung schreiben (Suchname)
000330      FOR Y% = I% TO I% ! nach Namen sortieren
000340           SELECT.INHALT.NUMMER$(Y%) = FN.FORM.SELECT.OPTION$(TRAENR$(Y%),0,FORMAT$(VAL(TRAENR$(Y%)),"9999")&" - "&TRAENA$(Y%))
000350           CALL CGI.TEMPLATE.VAR("selbox.nummer"&STR$(Y%),SELECT.INHALT.NUMMER$(Y%)) ! Inhalt des Nummernauswahlfeldes generieren
000360           NEXT Y%
000361      GOTO 230 ! nächsten Satz BEWOH1
000380      KY10$ = "1"
000390      GOSUB L10 \ UNLOCK #10
000400      FOR X% = 1 TO I% ! nach Bewohnernummer sortieren
000410           GOSUB L101 \ UNLOCK #10
000420           SELECT.INHALT.NAMEN$(X%) = FN.FORM.SELECT.OPTION$(ALKDNR$,0,KY10$) ! Inhalt des Namenauswahlfeldesgenerieren
000430           CALL CGI.TEMPLATE.VAR("selbox.namen"&STR$(X%),SELECT.INHALT.NAMEN$(X%))
000440           NEXT X%
000450 !     IF BARV%=1 ! Bew.-art.-liste vollständig/unvollst. darf nach St. suchen
000460 !          CALL CGI.TEMPLATE.VAR("artikelbox",ARTIKELBOX$)
000470 !          CALL CGI.TEMPLATE.VAR("selbox.artikel1",ARTIKEL.AUSWAHL$(1))
000480 !          CALL CGI.TEMPLATE.VAR("selbox.artikel2",ARTIKEL.AUSWAHL$(2))
000490 !          CALL CGI.TEMPLATE.VAR("selbox.artikel3",ARTIKEL.AUSWAHL$(3))
000500 !          IFEND
000510      GOTO FN.ENDE
000520 REM **********************************************************
000530 L10:      ! Alphabetische Sortierung Bewohner
000540      READ #10,KY10$:ALKDNR$ \ 
000550      RETURN 
000560 L101:      ! Alphabetische Sortierung Bewohner
000570      READNEXT #10,KY10$:ALKDNR$
000580      RETURN 
000590 S10:      ! Alphabetische Sortierung schreiben
000600      WRITE #10,TRAENA$(I%):TRAENR$(I%)
000610      RETURN 
000620 L11: ! Bewohnerstamm lesen
000630      READ #11,KY11$:TRAS1%,TRAS2%,TRASFR%,TRKNR,TRASNR,TRASBE$,TRASSW$,TRASP1$,TRASP2$
000640      RETURN 
000650 L111: ! Trägerstamm lesen - nächsten Satz
000660      READNEXT #11,KY11$:TRAS1%,TRAS2%,TRASFR%,TRKNR,TRASNR,TRASBE$,TRASSW$,TRASP1$,TRASP2$
000670      RETURN 
000680 L12:      ! Sortierung der Bewohner nach Suchnamen
000690      READ #12,KY12$:SUCH.BEWNA$,SUCH.BEWNR$
000700      RETURN 
000710 L121:      ! Sortierung der Bewohner nach Suchname
000720      READNEXT #12,KY12$:SUCH.BEWNA$,SUCH.BEWNR$
000730      RETURN 
000740 S12:      ! Sortierung nach Suchname schreiben
000750      WRITE #12,"1"&TRAESU$(I%)&TRAENR$(I%):TRAENA$(I%),TRAENR$(I%)
000760      RETURN 
000770 REM **********************************************************
000780 FN.ENDE:      ! Ausgang
000790      CLOSE #10 \ CLOSE #11 \ CLOSE #12
000800      SYSTEM "er ALSUCH."&FKDNR$&":m ( not noq"
000810      SYSTEM "er SUCHNA."&FKDNR$&":m ( not noq"
000820      FNEND 
