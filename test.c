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
 * @header      test.c
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    ...
 */

#include <stdlib.h>
#include <stdio.h>
#include "XS.h"

int main( void )
{
    unsigned int         i;
    char              ** test;
    XSAutoreleasePoolRef ap1;
    XSAutoreleasePoolRef ap2;
    XSStringRef          str1;
    XSStringRef          str2;
    XSStringRef          str3;
    
    XSRuntime_Initialize();
    
    ap1   = XSAutoreleasePool_Create();
    test  = XSAutoAlloc( 5 * sizeof( char * ) );
    ap2   = XSAutoreleasePool_Create();
    
    for( i = 0; i < 5; i++ )
    {
        test[ i ] = XSAutoAlloc( 2 );
    }
    
    str1 = XSString_CreateWithCString( "hello, world" );
    str2 = XSString_SubstringFromIndex( str1, 5 );
    str3 = XSCopy( str2 );
    
    printf( "%s%s%s\n", XSString_CString( str1 ), XSString_CString( str2 ), XSString_CString( str3 ) );
    
    XSLog( "hello, universe: %i %@ %i %@ %i", 42, str1, 43, ap1, 44 );
    
    XSRelease( str1 );
    XSRelease( str2 );
    XSRelease( str3 );
    
    XSAutoreleasePool_Drain();
    XSRelease( ap2 );
    XSRelease( ap1 );
    
    return EXIT_SUCCESS;
}
