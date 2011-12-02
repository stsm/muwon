000010 REM WFKIHEIM
000020 REM Includemodul zum Auswählen des Heims
000030 DEF FNWFKIHEIM$(NIX$)
000040      DIM KDNA1$(500),KDNA2$(500),KDNR$(500),KDSW$(500),SELECT.INHALT.NUMMER$(500)
000050      FL% = 11 \ OPEN #11:"/KUSTWA.REI", INPUT INDEXED \ CLEAR FL% ! Bewo.-stammdaten
000060      KY11$ = "1"
000070      GOSUB L11 \ UNLOCK #11 ! Kundenstamm lesen
000080      GOSUB L111 \ UNLOCK #11 ! nächsten Satz lesen
000090      IF EOF(11) THEN CLOSE #11 \ GOTO 350
000100      IF KT$[160:162]<>"009" THEN GOTO 80 ! nächsten Satz Kd.-stamm
000110      I% = I%+1
000120      KDNA1$(I%) = KA1$
000130      KDNA2$(I%) = KA2$
000140      KDNR$(I%) = FORMAT$(KNR,"999999")
000150      KDSW$(I%) = KSW$
000160      IF TRIM$(KDSW$(I%))="" THEN KDSW$(I%) = "X"
000170      FOR Y% = I% TO I% ! nach Namen sortieren
000180           IF TRIM$(KDNA2$(Y%))<>""
000190                SELECT.INHALT.NUMMER$(Y%) = FN.FORM.SELECT.OPTION$(KDNR$(Y%),0,KDNR$(Y%)&" - "&KDNA1$(Y%)&" ; "&KDNA2$(Y%)&" ")
000200           ELSE 
000210                SELECT.INHALT.NUMMER$(Y%) = FN.FORM.SELECT.OPTION$(KDNR$(Y%),0,KDNR$(Y%)&" - "&KDNA1$(Y%)&" ")
000220                IFEND 
000230           CALL CGI.TEMPLATE.VAR("selbox.nummer"&STR$(Y%),SELECT.INHALT.NUMMER$(Y%)) ! Inhalt des Nummernauswahlfeldes generieren
000240           NEXT Y%
000250      GOTO 80  ! nächsten Satz KUSTWA
000260      GOTO FN.ENDE
000270 REM **********************************************************
000280 L11:      ! Kundenstamm lesen
000290      READ #11,KY11$:K8%,K9%,KF%,KNR,KA1$,KA2$,KST$,KPL,KOR$,KL$,KSW$,KI$,KUG%,KDB,K1%,K2%,KRB%,KFA%,KTU%,KGR%,KBK%,KAN%,KMG%,KBZ%,KLB$,K3%,KPO%,KOP%,KT$,K4%,K5%,XX$,XX$,FK1%
000300      RETURN 
000310 L111:      ! nächsten Satz Kundenstamm lesen
000320      READNEXT #11,KY11$:K8%,K9%,KF%,KNR,KA1$,KA2$,KST$,KPL,KOR$,KL$,KSW$,KI$,KUG%,KDB,K1%,K2%,KRB%,KFA%,KTU%,KGR%,KBK%,KAN%,KMG%,KBZ%,KLB$,K3%,KPO%,KOP%,KT$,K4%,K5%,XX$,XX$,FK1%
000330      RETURN 
000340 REM **********************************************************
000350 FN.ENDE:      ! Ausgang
000360      CLOSE #11
000370      FNEND 
