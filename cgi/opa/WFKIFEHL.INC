000010 REM WFKIFEHL
000020 REM Includemodul Fehlerroutine
000030 DEF FN.WFKIFEHL$(MODUL$,ERR.NR,ERR.LI,CRC$,FL%)
000040 
000050      FEHLER.MERKER% = 2
000060      ERR.MSG$(1) = "Im Programmmodul - <strong>"&MODUL$&"</strong> - ist Fehler - <strong>"&STR$(ERR.NR)&"</strong> - aufgetreten, Dateinummer "&STR$(FL%)&"! <br /><br/>"
000070      SELECT ERR.NR
000080           CASE 27
000090                ERR.MSG$(2) = "Eine Datei wurde nicht ge&ouml;ffnet"
000100           CASE 28
000110                ERR.MSG$(2) = "Eine Datei mehrfach ge&ouml;ffnet"
000120           CASE 30
000130                ERR.MSG$(2) = "Eine Datei wurde nicht gefunden"
000140           CASE 31 OR 32
000150                ERR.MSG$(2) = "Verzeichnis/Festplatte voll"
000160           CASE 33 OR 49
000170                ERR.MSG$(2) = "Eine Datei ist schreibgesch&uuml;tzt"
000180           CASE 34
000190                ERR.MSG$(2) = "falscher Dateischl&uuml;ssel"
000200           CASE 35
000210                ERR.MSG$(2) = "falsche Zugriffsmethode"
000220           CASE 40
000230                ERR.MSG$(2) = "Kommando nicht gefunden"
000240           CASE 46
000250                ERR.MSG$(2) = "Ger&auml;t nicht gefunden"
000260           CASE 47
000270                ERR.MSG$(2) = "Datensatz fehlerhaft"
000280           CASE 48
000290                ERR.MSG$(2) = "Datensatz gesperrt"
000300           CASE 51
000310                ERR.MSG$(2) = "Speicher&uuml;berlauf einer Variable"
000320           OTHERWISE 
000330                ERR.MSG$(2) = "unbestimmter Fehler"
000340           CEND 
000350      IF CRC$<>"" ! Theos Toolkit meldet Fehler
000360           FEHLER.MERKER% = 3
000370           ERR.MSG$(2) = "Systemmeldung: "&TRIM$(CRC$)&"<br />"
000380           IFEND 
000390      OPEN #80:"/WWWROOT/OPA/FEHLLOG.OPA", OUTPUT INDEXED 
000400      KY80$ = "1"&STR$(DAY(DATE$(0)))&STR$(SECOND(TIME$(0)))
000410      WRITE #80,KY80$:FKDNR$,MODUL$,ERR.NR,ERR.LI,CRC$,FL%,DATE$(0),TIME$(0)
000420      CLOSE #80
000430 
000440 FN.ENDE: ! Ausgang
000450      FOR I% = 1 TO FEHLER.MERKER%
000460           CALL CGI.TEMPLATE.VAR("msg"&STR$((I%)),ERR.MSG$(I%))
000470           NEXT I%
000480      CALL CGI.TEMPLATE("/wwwroot/opa/error.asp")
000490      END \ QUIT 
000500      FNEND 
000510 REM ---------------------------------------------------
000520 REM modul$ = name des programms
000530 REM err.nr = fehlernummer
000540 REM err.li = fehler in zeile x
000550 REM crc$   = fehler aus einem theos modul z.b email,bserver,des56,cgi
000560 REM fl%    = dateinummer
