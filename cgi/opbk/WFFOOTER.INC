000010 REM WFKIFEHL
000020 REM Includemodul Fuﬂzeile
000030 REM 03.08.2008 - Schmidt (Programmerstellung)
000040 DEF FN.WFFOOTER$(NIX$)
000050 
000060      FL% = 90 \ OPEN #90:"/KUSTWA.REI", INPUT INDEXED 
000070      KY90$ = "1"&FORMAT$(VAL(KDNR$),"999999")
000080      READ #90,KY90$:K8%,K9%,KF%,KNR,KA1$,KA2$,KST$,KPL,KOR$,KL$,KSW$,KI$,KUG$,KDB,K1%,K2%,KRB$,KFA%,KTU%,KGR%,KBK%,KAN%,KMG%,KBZ%,KLB$,K3%,KPO%,KOP%,KT$,K4%,K5%,XX1$,XX2$,FK1% \ UNLOCK #10 \ CLEAR FL%
000090      CLOSE #90
000100      FOOTER$ = "<font face=""verdana"" size=""1"">&#171; Angemeldet als: "&FORMAT$(VAL(KDNR$),"######")&" - "&TRIM$(KA1$)&", "&TRIM$(KA2$)&" &#187; || &#171; Copyright &copy; 2007 - "&DATE$(0)[7:10]&"<a href=""http://muwasch.m-u.de"" target=""_blank"">&nbsp;Mittermeier &amp; Ungelenk GmbH</a> &#187;</font>"
000110 
000120 FN.ENDE: ! Ausgang
000130      CALL CGI.TEMPLATE.VAR("footer",FOOTER$)
000140      FNEND 
