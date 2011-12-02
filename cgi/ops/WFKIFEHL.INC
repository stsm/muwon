000010 REM WFKIFEHL
000020 REM Includemodul Fehlerroutine
000030 DEF FN.WFKIFEHL$(MODUL$,ERR.NR,ERR.LI,CRC$,FL%)
000040 
000050      FEHLER.MERKER% = 2
000060      ERR.MSG$(1) = "Im Programmmodul - <strong>"&MODUL$&"</strong> - ist Fehler - <strong>"&STR$(ERR.NR)&"</strong> - aufgetreten, Dateinummer "&STR$(FL%)&"! <br /><br/>"
000070      SELECT ERR.NR
000080           CASE 1
000090                ERR.MSG$(2) = "Programmabbruch!"
000100           CASE 27
000110                ERR.MSG$(2) = "Eine Datei wurde nicht ge&ouml;ffnet"
000120           CASE 28
000130                ERR.MSG$(2) = "Eine Datei mehrfach ge&ouml;ffnet"
000140           CASE 30
000150                ERR.MSG$(2) = "Eine Datei wurde nicht gefunden"
000160           CASE 31 OR 32
000170                ERR.MSG$(2) = "Verzeichnis/Festplatte voll"
000180           CASE 33 OR 49
000190                ERR.MSG$(2) = "Eine Datei ist schreibgesch&uuml;tzt"
000200           CASE 34
000210                ERR.MSG$(2) = "falscher Dateischl&uuml;ssel"
000220           CASE 35
000230                ERR.MSG$(2) = "falsche Zugriffsmethode"
000240           CASE 36
000250                ERR.MSG$(2) = "keine Daten vorhanden"
000260           CASE 38
000270                ERR.MSG$(2) = "falscher Dateikanal"
000280           CASE 40
000290                ERR.MSG$(2) = "Befehl nicht gefunden"
000300           CASE 46
000310                ERR.MSG$(2) = "Ger&auml;t nicht gefunden"
000320           CASE 47
000330                ERR.MSG$(2) = "Datensatz fehlerhaft"
000340           CASE 48
000350                ERR.MSG$(2) = "Datensatz gesperrt"
000360           CASE 49
000370                ERR.MSG$(2) = "Datei gesperrt"
000380           CASE 50
000390                ERR.MSG$(2) = "Divisor durch 0"
000400           CASE 51
000410                ERR.MSG$(2) = "Speicher&uuml;berlauf einer Variable"
000420           CASE 52
000430                ERR.MSG$(2) = "&Ouml;ffentlicher Varibale steht kein Speicher zur Verf&uuml;gung"
000440           CASE 68
000450                ERR.MSG$(2) = "&Ouml;ffentlicher Varibale wurde nicht gefunden"
000460           CASE 124
000470                ERR.MSG$(2) = "Nicht zugewiesene Variable in der IOLIST"
000480           OTHERWISE 
000490                ERR.MSG$(2) = "unbestimmter Fehler"
000500           CEND 
000510      IF CRC$<>"" ! Theos Toolkit meldet Fehler
000520           FEHLER.MERKER% = 3
000530           ERR.MSG$(2) = "Systemmeldung: "&TRIM$(CRC$)&"<br />"
000540           IFEND 
000550      OPEN #80:"/WWWROOT/OPS/FEHLLOG.OPS", OUTPUT INDEXED 
000560      KY80$ = "1"&STR$(DAY(DATE$(0)))&STR$(SECOND(TIME$(0)))
000570      WRITE #80,KY80$:FKDNR$,MITA$,MODUL$,ERR.NR,ERR.LI,CRC$,FL%,DATE$(0),TIME$(0)
000580      CLOSE #80
000590 
000600 FN.ENDE: ! Ausgang
000610      FOR I% = 1 TO FEHLER.MERKER%
000620           CALL CGI.TEMPLATE.VAR("msg"&STR$((I%)),ERR.MSG$(I%))
000630           NEXT I%
000640      CALL CGI.TEMPLATE("/wwwroot/ops/error.asp")
000650      END 
000660      FNEND 
000670 REM ---------------------------------------------------
000680 REM modul$ = name des programms
000690 REM err.nr = fehlernummer
000700 REM err.li = fehler in zeile x
000710 REM crc$   = fehler aus einem theos modul z.b email,bserver,des56,cgi
000720 REM fl%    = dateinummer
