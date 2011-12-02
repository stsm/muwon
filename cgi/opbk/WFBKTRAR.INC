000010 REM WFBKTRAR
000020 REM Includemodul zum auswählen von Trägerartikelvorschlägen
000030 DEF FNWFBKTRAR$(FKDNR$) ! formatierte Kd.-nr ("999999") an INC übegeben
000040      CLEAR I%
000050      DIM TRAEASBE$(1000),TRAEARNR$(1000),SELECT.INHALT.ARTIKEL$(1000)
000060      FL% = 11 \ OPEN #11:"/TRAE02.REI", INPUT INDEXED \ CLEAR FL% ! Trae.-artikelvorschlag
000070      FL% = 12 \ OPEN #12:"/ARSTEU.REI", INPUT INDEXED \ CLEAR FL% ! Artikelstamm
000080      KY11$ = "1"&FKDNR$
000090      GOSUB L11 \ UNLOCK #11 ! Vorschläge lesen
000100      GOSUB L111 \ UNLOCK #11 ! nächsten lesen
000110      IF EOF(11) THEN CLOSE #11 \ GOTO 210
000120      IF KY11$[2:7]<>FKDNR$ THEN GOTO 210
000130      KY12$ = "1000000"&KY11$[8:13]
000140      GOSUB L12 ! Artikelstamm lesen
000150      I% = I%+1
000160      TRAEARNR$(I%) = STR$(ZTRAR)
000170      TRAEASBE$(I%) = ASBE$ ! Artikelbezeichnung
000180      SELECT.INHALT.ARTIKEL$(I%) = FN.FORM.SELECT.OPTION$(TRAEARNR$(I%),0,TRAEASBE$(I%))
000190      CALL CGI.TEMPLATE.VAR("selbox.artikel"&STR$(I%),SELECT.INHALT.ARTIKEL$(I%))
000200      GOTO 100 ! nächsten Satz
000210      GOTO FN.ENDE
000220 REM **********************************************************
000230 L11: ! Vorschläge lesen
000240      FL% = 11 \ READ #11,KY11$:AKY11$,ZTRKD,ZTRAR \ UNLOCK #11 \ CLEAR FL%
000250      RETURN 
000260 L111: ! Vorschläge nächster Satz
000270      FL% = 11 \ READNEXT #11,KY11$:AKY11$,ZTRKD,ZTRAR \ UNLOCK #11 \ CLEAR FL%
000280      RETURN 
000290 L12: ! Artikelstamm lesen
000300      FL% = 12 \ READ #12,KY12$:AS1%,AS2%,ASFR%,KNR,ASNR,ASBE$ \ UNLOCK #12 \ CLEAR FL%
000310      RETURN 
000320 REM **********************************************************
000330 FN.ENDE:      ! Ausgang
000340      CLOSE #11 \ CLOSE #12
000350      FNWFBKTRAR$ = STR$(I%) ! Rückgabewert
000360      FNEND 
