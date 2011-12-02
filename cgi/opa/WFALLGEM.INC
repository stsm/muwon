000010 REM wfallgem.inc
000020 
000030 REM Include für allgemeine subroutinen
000040 REM 20.05.2009 - Schmidt (Programmerstellung)
000050 
000060 
000070 REM *** Windows Character Set zu Theos Character Set ***
000080 REM *** wenn die Daten über den HTTP Server kommen ***
000090 
000100 
000110 DEF FN.UMLAUTE.ZU.THEOS$(STRING$)
000120 
000130      LOCAL UML$(7),TUML$(7)
000140      LOCAL CU$,SUCH%,POS%
000150 
000160 ! Ä,ä - Ö,ö - Ü,ü - ß
000170      UML$(1) = CHR$(196) \ UML$(2) = CHR$(228) \ UML$(3) = CHR$(214) \ UML$(4) = CHR$(246) \ UML$(5) = CHR$(220) \ UML$(6) = CHR$(252) \ UML$(7) = CHR$(223)
000180      TUML$(1) = CHR$(192) \ TUML$(2) = CHR$(193) \ TUML$(3) = CHR$(206) \ TUML$(4) = CHR$(207) \ TUML$(5) = CHR$(211) \ TUML$(6) = CHR$(212) \ TUML$(7) = CHR$(224)
000190 
000200      FOR SUCH% = 1 TO 7
000210           CU$ = UML$(SUCH%)
000220           POS% = SCH(1,STRING$,CU$)
000230           WHILE POS%>0
000240 ! Stelle des falschen Characters mit 'richtigem' ersetzen
000250                STRING$ = OVR$(STRING$,POS%,1,TUML$(SUCH%))
000260                POS% = SCH(1,STRING$,CU$)
000270                WEND 
000280           NEXT SUCH%
000290      FN.UMLAUTE.ZU.THEOS$ = STRING$
000300      FNEND 
000310 
000320 REM *******************************************************
000330 
000340 DEF FN.UMLAUTE.ZU.WINDOWS$(STRING$)
000350 
000360      LOCAL UML$(7),TUML$(7)
000370      LOCAL CU$,SUCH%,POS%
000380 
000390 ! Ä,ä - Ö,ö - Ü,ü - ß
000400      TUML$(1) = CHR$(196) \ UML$(2) = CHR$(228) \ UML$(3) = CHR$(214) \ UML$(4) = CHR$(246) \ UML$(5) = CHR$(220) \ UML$(6) = CHR$(252) \ UML$(7) = CHR$(223)
000410      UML$(1) = CHR$(192) \ TUML$(2) = CHR$(193) \ TUML$(3) = CHR$(206) \ TUML$(4) = CHR$(207) \ TUML$(5) = CHR$(211) \ TUML$(6) = CHR$(212) \ TUML$(7) = CHR$(224)
000420 
000430      FOR SUCH% = 1 TO 7
000440           CU$ = TUML$(SUCH%)
000450           POS% = SCH(1,STRING$,CU$)
000460           WHILE POS%>0
000470 ! Stelle des falschen Characters mit 'richtigem' ersetzen
000480                STRING$ = OVR$(STRING$,POS%,1,UML$(SUCH%))
000490                POS% = SCH(1,STRING$,CU$)
000500                WEND 
000510           NEXT SUCH%
000520      FN.UMLAUTE.ZU.WINDOWS$ = STRING$
000530      FNEND 
