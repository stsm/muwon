000010 REM WFKIFEHL
000020 REM Includemodul Fuﬂzeile
000030 REM 03.08.2008 - Schmidt (Programmerstellung)
000040 DEF FN.WFFOOTER$(NIX$)
000050 
000100      FOOTER$ = "<font face=""verdana"" size=""1"">&#171; Angemeldet als: "&MITA$&" &#187; || &#171; Copyright &copy; 2007 - "&DATE$(0)[7:10]&"<a href=""http://muwasch.m-u.de"" target=""_blank"">&nbsp;Mittermeier &amp; Ungelenk GmbH</a> &#187;</font>"
000110 
000120 FN.ENDE: ! Ausgang
000130      CALL CGI.TEMPLATE.VAR("footer",FOOTER$)
000140      FNEND 
