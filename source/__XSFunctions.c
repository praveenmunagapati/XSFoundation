/*******************************************************************************
 * Copyright (c) 2011, Jean-David Gadina <macmade@eosgarden.com>
 * Distributed under the Boost Software License, Version 1.0.
 * 
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ******************************************************************************/
 
/* $Id$ */

/*!
 * @header      __XSFunctions.c
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    ...
 */

#include "XS.h"
#include "private/__XSFunctions.h"

char * __progname                    = NULL;
char * program_invocation_short_name = NULL;

extern char * __progname                    __attribute__( ( weak ) );
extern char * program_invocation_short_name __attribute__( ( weak ) );

void __XSVLog( const char * fmt, va_list args )
{
    pid_t            pid;
    pthread_t        tid;
    time_t           t;
    struct tm      * now;
    struct timeval   tv;
    char             date[ 255 ];
    char           * exec;
    unsigned int     count;
    int              va_int;
    unsigned int     va_uint;
    int            * va_int_ptr;
    const char     * va_char_ptr;
    void           * va_ptr;
    char           * num_ptr;
    char             num_buf[ 50 ];
    XSRuntimeBase  * b;
    XSRuntimeClass * cls;
    
    #ifdef __MACH__
    mach_port_t    mid;
    #endif
    
    count = 0;
    
    pid = getpid();
    tid = pthread_self();
    
    t   = time( NULL );
    now = localtime( &t );
    gettimeofday( &tv, NULL );
    
    #ifdef __MACH__
    mid = pthread_mach_thread_np( tid );
    #endif
    
    memset( ( void * )date, 0, 255 );
    strftime( ( char * )date, 255, "%Y-%m-%d %H:%M:%S", now );
    
    if( __progname != NULL )
    {
        exec = __progname;
    }
    else if( program_invocation_short_name != NULL )
    {
        exec = program_invocation_short_name;
    }
    else
    {
        exec = "unknown";
    }
    
    #ifdef __MACH__
    printf( "%s.%06lu %s[%i:%X] ", date, ( unsigned long )tv.tv_usec, exec, pid, mid );
    #else
    printf( "%s.%06lu %s[%i:%lu] ", date, ( unsigned long )tv.tv_usec, exec, pid, ( unsigned long )tid );
    #endif
    
    while( 1 )
    {
        if( *( fmt ) == '\0' )
        {
            break;
        }
        
        if( *( fmt ) == '%' )
        {
            fmt++;
            
            if( *( fmt ) == 'n' )
            {
                va_int_ptr      = va_arg( args, int * );
                *( va_int_ptr ) = count;
            }
            else if( *( fmt ) == '%' )
            {
                putc( '%', stdout );
                count++;
            }
            else if( *( fmt ) == 'c' )
            {
                va_int = va_arg( args, int );
                
                putc( va_int, stdout );
                
                count++;
            }
            else if( *( fmt ) == 's' )
            {
                va_char_ptr = va_arg( args, const char * );
                
                if( va_char_ptr == NULL )
                {
                    va_char_ptr = "(NULL)";
                }
                
                fputs( va_char_ptr, stdout );
                
                count += strlen( va_char_ptr );
            }
            else if( *( fmt ) == 'd' )
            {
                va_int = va_arg( args, int );
                
                if( va_int < 0 )
                {
                    va_uint = -va_int;
                }
                else
                {
                    va_uint = va_int;
                }
                
                num_ptr = num_buf;
                
                do
                {
                    *( num_ptr++ ) = ( char )( '0' + va_uint % 10 );
                    va_uint       /= 10;
                }
                while( va_uint > 0 );
                
                if( va_int < 0 )
                {
                    *( num_ptr++ ) = '-';
                }
                
                do
                {
                    num_ptr--;
                    putc( *( num_ptr ), stdout );
                    count++;
                    
                }
                while( num_ptr != num_buf );
            }
            else if( *( fmt ) == '@' )
            {
                va_ptr = va_arg( args, void * );
                b      = ( XSRuntimeBase * )va_ptr;
                cls    = b->isa;
                
                printf( "<%s: %p>", cls->className, va_ptr );
                
                if( cls->description != NULL )
                {
                    printf( " %s", cls->description( va_ptr ) );
                }
            }
            else if( *( fmt ) == 'p' )
            {
                /* Pointer support */
            }
            else if( strchr( "eEgGfF", *( fmt ) ) != NULL && *( fmt ) != 0 )
            {
                /* Floating point support */
            }
            else
            {
                /* Extras support */
            }
        }
        else
        {
            putc( *( fmt ), stdout );
            
            count++;
        }
        
        fmt++;
    }
    
    putc( '\n', stdout );
}