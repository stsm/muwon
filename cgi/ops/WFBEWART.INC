000010 REM WFBEWART
000020 REM Includemodul zum auswählen von Bewohnerartikeln
000030      INCLUDE "FILESYS" ! Dateisystem Toolkit
000040 DEF FNWFBEWART$(FKDNR$)
000050      DIM BA.NAME$(10000),BA.NR$(10000),SELECT.INHALT.BEWART$(10000)
000060      CALL FILE.ACCESS("/BEUM"&STR$(VAL(DATE$(0)[7:10])-1),"IR")
000070      IF CALL.RETURN.VALUE=0 THEN VORJAHR% = 1
000080      FL% = 14 \ OPEN #14:"/BEUM"&DATE$(0)[7:10]&".REI", INPUT INDEXED \ CLEAR FL% ! Bewohnerartikelumsätze
000090      FL% = 15 \ OPEN #15:"/ARSTEU.REI", INPUT INDEXED \ CLEAR FL% ! Artikelstamm
000100 
000110      KY14$ = "1"&FKDNR$
000120      GOSUB L14 ! ersten Satz BEUMnnnn.REI lesen
000130      GOSUB L14.1 ! nächsten Satz BEUMnnnn.REI
000140      IF EOF(14) OR KY14$[2:7]<>FKDNR$ THEN GOTO AUSGABE
000150      IF STR$(VAL(KY14$[14:19]))=BA.NR$(WFBA.I%) THEN GOTO 130
000160      WFBA.I% = WFBA.I%+1
000170      BA.NR$(WFBA.I%) = STR$(VAL(KY14$[14:19])) ! Artikelnummer ablegen
000180      KY15$ = "1000000"&KY14$[14:19] ! Artikelstamm lesen
000190      GOSUB L15
000200      BA.NAME$(WFBA.I%) = TRIM$(ASBE$)
000210      GOTO 130
000220 AUSGABE:
000230      IF WFBA.I%>=1
000240           REDIM BA.NR$(WFBA.I%),SELECT.INHALT.BEWART$(WFBA.I%)
000250           IFEND 
000260      FOR WFBA.X% = 1 TO WFBA.I%
000270           SELECT.INHALT.BEWART$(WFBA.X%) = FN.FORM.SELECT.OPTION$(BA.NR$(WFBA.X%),0,BA.NR$(WFBA.X%)&" - "&BA.NAME$(WFBA.X%)&"&nbsp;")
000280           CALL CGI.TEMPLATE.VAR("selbox.bewart"&STR$(WFBA.X%),SELECT.INHALT.BEWART$(WFBA.X%))
000290           NEXT WFBA.X%
000300      CALL CGI.TEMPLATE.VAR("selbox.jahr1",DATE$(0)[7:10])
000310      IF VORJAHR%=1 ! Vorjahresdatei vorhanden
000320           CALL CGI.TEMPLATE.VAR("selbox.jahr2",STR$(VAL(DATE$(0)[7:10])-1))
000330           IFEND 
000340      GOTO FN.ENDE
000350 REM **********************************************************
000360 L14: ! Bewohnerartikelumsatz /-mengen
000370      FL% = 14 \ READ #14,KY14$:XX$ \ CLEAR FL%
000380      RETURN 
000390 REM **********************************************************
000400 L14.1: ! Bewohnerartikelumsatz /-mengen
000410      FL% = 14 \ READNEXT #14,KY14$:XX$ \ CLEAR FL%
000420      RETURN 
000430 REM **********************************************************
000440 L15: ! Artikelstamm lesen
000450      FL% = 15 \ READ #15,KY15$:AS1%,AS2%,ASFR%,KNR,ASNR,ASBE$ \ CLEAR FL%
000460      RETURN 
000470 REM **********************************************************
000480 FN.ENDE:      ! Ausgang
000490      IF I%=0 THEN STOP 
000500      CLOSE #14 \ CLOSE #15
000510      FNEND 
