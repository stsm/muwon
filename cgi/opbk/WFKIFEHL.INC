000010 REM WFKIFEHL
000020 REM Includemodul Fehlerroutine
000030 DEF FN.WFKIFEHL$(MODUL$,ERR.NR,ERR.LI,CRC$,FL%)
000040 
000050      FEHLER.MERKER% = 2
000060      ERR.MSG$(1) = "Im Programmmodul - <strong>"&MODUL$&"</strong> - ist Fehler - <strong>"&STR$(ERR.NR)&"</strong> - aufgetreten, Dateinummer "&STR$(FL%)&"! <br /><br/>"
000070      SELECT ERR.NR
000080           CASE 1
000090                ERR.MSG$(2) = "Programm wurde abgebrochen"
000100           CASE 27
000110                ERR.MSG$(2) = "Eine Datei wurde nicht ge&ouml;ffnet"
000120           CASE 28
000130                ERR.MSG$(2) = "Eine Datei mehrfach ge&ouml;ffnet"
000140           CASE 29
000150                ERR.MSG$(2) = "Array unzureichend dimensioniert"
000160           CASE 30
000170                ERR.MSG$(2) = "Eine Datei wurde nicht gefunden"
000180           CASE 31 OR 32
000190                ERR.MSG$(2) = "Verzeichnis/Festplatte voll"
000200           CASE 33 OR 49
000210                ERR.MSG$(2) = "Eine Datei ist schreibgesch&uuml;tzt"
000220           CASE 34
000230                ERR.MSG$(2) = "falscher Dateischl&uuml;ssel"
000240           CASE 35
000250                ERR.MSG$(2) = "falsche Zugriffsmethode"
000260           CASE 36
000270                ERR.MSG$(2) = "unerwartetes Dateiende"
000280           CASE 38
000290                ERR.MSG$(2) = "falscher Dateikanal"
000300           CASE 40
000310                ERR.MSG$(2) = "Programm/Kommando nicht gefunden"
000320           CASE 46
000330                ERR.MSG$(2) = "Ger&auml;t nicht gefunden"
000340           CASE 47
000350                ERR.MSG$(2) = "Datensatz fehlerhaft"
000360           CASE 48
000370                ERR.MSG$(2) = "Datensatz gesperrt"
000380           CASE 50
000390                ERR.MSG$(2) = "Divisor durch 0"
000400           CASE 51
000410                ERR.MSG$(2) = "Speicher&uuml;berlauf einer Variable"
000420           CASE 62
000430                ERR.MSG$(2) = "Haupttask hat unzureichenden Speicher"
000440           OTHERWISE 
000450                ERR.MSG$(2) = "unbestimmter Fehler"
000460           CEND 
000470      IF CRC$<>"" ! Theos Toolkit meldet Fehler
000480           FEHLER.MERKER% = 3
000490           ERR.MSG$(2) = "Systemmeldung: "&TRIM$(CRC$)&"<br />"
000500           IFEND 
000510      OPEN #80:"/WWWROOT/OPBK/FEHLLOG.OPBK", OUTPUT INDEXED 
000520      KY80$ = "1"&STR$(DAY(DATE$(0)))&STR$(SECOND(TIME$(0)))
000530      WRITE #80,KY80$:FKDNR$,MODUL$,ERR.NR,ERR.LI,CRC$,FL%,DATE$(0),TIME$(0)
000540      CLOSE #80
000550 
000560 FN.ENDE: ! Ausgang
000570      FOR I% = 1 TO FEHLER.MERKER%
000580           CALL CGI.TEMPLATE.VAR("msg"&STR$((I%)),ERR.MSG$(I%))
000590           NEXT I%
000600      CALL CGI.TEMPLATE("/wwwroot/opbk/error.asp")
000610      END \ QUIT 
000620      FNEND 
000630 REM ---------------------------------------------------
000640 REM modul$ = name des programms
000650 REM err.nr = fehlernummer
000660 REM err.li = fehler in zeile x
000670 REM crc$   = fehler aus einem theos modul z.b email,bserver,des56,cgi
000680 REM fl%    = dateinummer
