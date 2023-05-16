/*
   The operating system, must be one of: (ZH_x)

     MACX	- Mac OS X
     MAC9	- Mac OS 9
     MSDOS	- MS-DOS and Windows
     OS2	- OS/2
     OS2EMX	- XFree86 on OS/2 (not PM)
     WIN32	- Win32 (Windows 95/98/ME and Windows NT/2000/XP)
     CYGWIN	- Cygwin
     SOLARIS	- Sun Solaris
     HPUX	- HP-UX
     ULTRIX	- DEC Ultrix
     LINUX	- Linux
     FREEBSD	- FreeBSD
     NETBSD	- NetBSD
     OPENBSD	- OpenBSD
     BSDI	- BSD/OS
     IRIX	- SGI Irix
     OSF	- HP Tru64 UNIX
     SCO	- SCO OpenServer 5
     UNIXWARE	- UnixWare 7, Open UNIX 8
     AIX	- AIX
     HURD	- GNU Hurd
     DGUX	- DG/UX
     RELIANT	- Reliant UNIX
     DYNIX	- DYNIX/ptx
     QNX	- QNX
     QNX6	- QNX RTP 6.1
     LYNX	- LynxOS
     BSD4	- Any BSD 4.4 system
     UNIX	- Any UNIX BSD/SYSV system
*/

#if defined(__APPLE__) && defined(__GNUC__)
#  define ZH_MACX
#elif defined(__MACOSX__)
#  define ZH_MACX
#elif defined(macintosh)
#  define ZH_MAC9
#elif defined(__CYGWIN__)
#  define ZH_CYGWIN
#elif defined(MSDOS) || defined(_MSDOS)
#  define ZH_MSDOS
#elif defined(__OS2__)
#  if defined(__EMX__)
#    define ZH_OS2EMX
#  else
#    define ZH_OS2
#  endif
#elif !defined(SAG_COM) && (defined(WIN64) || defined(_WIN64) || defined(__WIN64__))
#  define ZH_WIN32
#  define ZH_WIN64
#elif !defined(SAG_COM) && (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
#  define ZH_WIN32
#elif defined(__MWERKS__) && defined(__INTEL__)
#  define ZH_WIN32
#elif defined(__sun) || defined(sun)
#  define ZH_SOLARIS
#elif defined(hpux) || defined(__hpux)
#  define ZH_HPUX
#elif defined(__ultrix) || defined(ultrix)
#  define ZH_ULTRIX
#elif defined(sinix)
#  define ZH_RELIANT
#elif defined(__linux__) || defined(__linux)
#  define ZH_LINUX
#elif defined(__FreeBSD__)
#  define ZH_FREEBSD
#  define ZH_BSD4
#elif defined(__NetBSD__)
#  define ZH_NETBSD
#  define ZH_BSD4
#elif defined(__OpenBSD__)
#  define ZH_OPENBSD
#  define ZH_BSD4
#elif defined(__bsdi__)
#  define ZH_BSDI
#  define ZH_BSD4
#elif defined(__sgi)
#  define ZH_IRIX
#elif defined(__osf__)
#  define ZH_OSF
#elif defined(_AIX)
#  define ZH_AIX
#elif defined(__Lynx__)
#  define ZH_LYNX
#elif defined(__GNU_HURD__)
#  define ZH_HURD
#elif defined(__DGUX__)
#  define ZH_DGUX
#elif defined(__QNXNTO__)
#  define ZH_QNX6
#elif defined(__QNX__)
#  define ZH_QNX
#elif defined(_SEQUENT_)
#  define ZH_DYNIX
#elif defined(_SCO_DS)                   /* SCO OpenServer 5 + GCC */
#  define ZH_SCO
#elif defined(__USLC__)                  /* all SCO platforms + UDK or OUDK */
#  define ZH_UNIXWARE
#  define ZH_UNIXWARE7
#elif defined(__svr4__) && defined(i386) /* Open UNIX 8 + GCC */
#  define ZH_UNIXWARE
#  define ZH_UNIXWARE7
#else
#  error "Qt has not been ported to this OS - talk to qt-bugs@trolltech.com"
#endif

#if defined(ZH_MAC9) || defined(ZH_MACX)
#  define ZH_MAC
#endif

#if defined(ZH_MAC9) || defined(ZH_MSDOS) || defined(ZH_OS2) || defined(ZH_WIN32) || defined(ZH_WIN64)
#  undef ZH_UNIX
#elif !defined(ZH_UNIX)
#  define ZH_UNIX
#endif