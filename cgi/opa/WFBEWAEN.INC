000010 REM WFBEWAEN
000020 REM Includemodul für Bewohneränderungsmerker
000030 REM 15.10.2008 - Schmidt (Programmerstellung)
000040 
000050 SUB WFBEWAEN(WKISS$,WSTAM$)
000060      SHARED AEM$
000070      IF TRIM$(WKISS$)<>TRIM$(WSTAM$) THEN AEM$ = " [x]" ELSE AEM$ = ""
000080      END SUB 
