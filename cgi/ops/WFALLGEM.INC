000010 REM wfallgem.inc
000020 REM Include f¸r allgemeine subroutinen
000030 REM 08.01.2009 - Schmidt (Programmerstellung)
000040 
000050      INCLUDE "filesys" ! Theos Filesystem toolkit
000060 
000070 REM *** Umlaute in HTML Code wandeln ***
000080 REM *** Anfang ***
000090 SUB UMLAUTE.ZU.HTML(WERT$)
000100 
000110      LOCAL UML$(7),HTML$(7),CU$,SUCH%,UML%,POS%
000120      SHARED HTML.CODE$
000130 
000140      UML$(1) = "ƒ" \ UML$(2) = "‰" \ UML$(3) = "÷" \ UML$(4) = "ˆ" \ UML$(5) = "‹" \ UML$(6) = "¸" \ UML$(7) = "ﬂ"
000150      HTML$(1) = "&Auml;" \ HTML$(2) = "&auml;" \ HTML$(3) = "&Ouml;" \ HTML$(4) = "&ouml;" \ HTML$(5) = "&Uuml;" \ HTML$(6) = "&uuml;" \ HTML$(7) = "&szlig;"
000160 
000170      FOR SUCH% = 1 TO 7
000180           CU$ = UML$(SUCH%)
000190           POS% = SCH(1,WERT$,CU$)
000200           IF POS%>0
000210                WERT$ = WERT$[1:POS%-1]&HTML$(SUCH%)&WERT$[POS%+1:LEN(WERT$)]
000220                IFEND 
000230           NEXT SUCH%
000240      HTML.CODE$ = TRIM$(WERT$)
000250      END SUB 
000260 REM *** Ende ***
000270 
000280 REM *** Download von Dateien auﬂerhalb des HTTP Servers ***
000290 REM ***                  Anfang                         ***
000300 SUB DATEI.DOWNLOAD(DATEI.PFAD$,DATEI.NAME$,TYP$)
000310      CALL FILE.LOAD(DATEI.PFAD$&DATEI.NAME$,ADDROF(DATEI.INHALT$))
000320      DATEI.LAENGE$ = STR$(LEN(DATEI.INHALT$)+6)
000330      PRINT "Content-Type: Application/octet-stream"
000340      PRINT "Content-Disposition: Attachment; Filename=""test.zip"" "
000350      PRINT "Content-Length:0" !&DATEI.LAENGE$
000360      PRINT DATEI.INHALT$
000370 !     PRINT DATEI.INHALT$
000380      END SUB 
000390 SUB GET.FILE
000400      CALL CGI.INIT
000410      CALL CGI.GET("pfad",ADDROF(PFAD$))
000420      CALL CGI.GET("datei",ADDROF(DATEI$))
000430      CALL CGI.GET("typ",ADDROF(TYP$))
000440      CALL CGI.GET("aktion",ADDROF(AKTION$))
000450      SELECT AKTION$
000460           CASE LCASE$("get")
000470                CALL FILE.LOAD(PFAD$&DATEI$,ADDROF(DATEI.INHALT$))
000480                DATEI.LAENGE$ = STR$(LEN(DATEI.INHALT$))
000500                PRINT "Content-Type: Application/octetstream"
000510                PRINT "Content-Disposition: Attachment; Filename="" "&DATEI$&""
000511                PRINT "Content-Length:"&DATEI.LAENGE$
000520                PRINT DATEI.INHALT$
000540      PRINT DATEI.INHALT$
000550           CASE LCASE$("len")
000560                CALL FILE.LOAD(PFAD$&DATEI$,ADDROF(DATEI.INHALT$))
000570                DATEI.LAENGE$ = TRIM$(STR$(LEN(DATEI.INHALT$)))
000580                PRINT DATEI.LAENGE$
000590           OTHERWISE 
000600                PRINT "geht net"
000610           CEND 
000620      END SUB 
