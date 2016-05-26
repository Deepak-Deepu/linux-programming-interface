#ifndef TLPI_HDR_H
#define TLPI_HDR_H

#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>

#include<unistd.h>
#include<errno.h>
#include<string.h>

#include "get_num.h"

#include "error_functions.h"
typedef enum { FALSE, TRUE } Boolean;

#define min(m,n) ((m) < (n) ? (m) : (n))
#define max(m,n) ((m) > (n) ? (m) : (n))

#endif

#ifndef ERROR_FUNCTIONS_H
#define ERROR_FUNCTIONS_H

void errMsg(const char *format, ...);

#ifdef __GNU__

#define NORETURN __attribute__ ((__noreturn__))
#else
#define NORETURN
#endif


void errExit(const char *format, ...) NORETURN;
void err_exit(const char *format, ...) NORETURN;
void errExitEN(int errnum,const char *format, ...) NORETURN;
void fatal(const char *format, ...) NORETURN;
void usageErr(const char *format, ...) NORETURN;
void cmdLineErr(const char *format, ...) NORETURN;

#endif

#include<stdarg.h>
#include "error_functions.h"
#include "tlpi_hdr.h"
#include "ename.c.inc"

#ifdef __GNUC__
__attribute__ ((__noreturn__))
#endif

static void terminate(Boolean useExit3)
{
        char *s;
        /* Dump core if EF_DUMPCORE environment variable is defined and
        is a nonempty string; otherwise call exit(3) or _exit(2),
        depending on the value of 'useExit3'. */

        s = getenv("EF_DUMPCORE");

        if(s != NULL && *s != '\0')
                abort();
        else if(useEXIT3)
                exit(EXIT_FAILURE);
        else
                _exit(EXIT_FAILURE);
}

static void outputError(Boolean useErr, int err,
Boolean flushStdout,const char *format, va_list ap)

{
	#define BUF_SIZE 500
        char buf[BUF_SIZE], userMsg[BUF_SIZE], errText[BUF_SIZE];

        vsnprintf(userMsg, BUF_SIZE, format, ap);

        if(useErr)
                snprintf(errText, BUF_SIZE, "[%s %s]",
                 (err > 0 && err <= MAX_ENAME) ?
                ename[err] : "?UNKNOWN?", strerror(err));
        else
                snprintf(errText, BUF_SIZE, ":");

        snprintf(buf, BUF_SIZE, "ERROR %s %s\n", errText, userMsg);

        if(flushStdout)
                fflush(stdout);
        fputs(buf, stderr);
                fflush(stderr);
}


void errMsg(const char *format, ...)
{
        va_list argList;
        int savedErrno;

        savedErrno = errno;

        va_start(argList, format);
        outputError(TRUE, errno, TRUE, format, argList);
        va_end(argList);

        errno = savedErrno;
}

void errExit(const char *format, ...)
{
        va_list argList;

        va_start(argList, format);
        outputError(TRUE, errno, TRUE, format, argList);
        va_end(argList);

        terminate(TRUE);
}

void err_exit(const char *format, ...)
{
        va_list argList;

        va_start(argList, format);
        outputError(TRUE, errno, FALSE, format, argList);
        va_end(argList);

        terminate(FALSE);
}

void errExitEN(int errnum, const char *format, ...)
{
        va_list argList;

        va_start(argList, format);
        output(TRUE, errnum, TRUE, format, argList);
        va_end(argList);

        terminate(TRUE);
}

void fatal(const char *format, ...)
{
	va_list argList;

	va_start(argList, format);
	outputError(FALSE, 0 , TRUE, format, argList);
	va_end(argList);

	terminate(TRUE);
}

void usageErr(const char *format, ...)
{
	va_list argList;
	
	fflush(stdout);

	fprintf(stderr, "usage: ");
	va_start(argList, format);
	vfprintf(stderr, format, argList);
	va_end(argList);

	fflush(stderr);
	exit(EXIT_FAILURE);
}

void cmdLineErr(const char *format, ...)
{
	va_list argList;

	fflush(stdout);

	fprintf(stderr, "Command-line usage error: ");
	va_start(argList, format);
	vfprintf(stderr,format, argList);
	va_end(argList);

	fflush(stderr);
	exit(EXIT_FAILURE);
}                                                          
                                                          
                                                          
