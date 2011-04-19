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
 * @header      XSThread.c
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    Implementation for the XSThread class
 */

#include "XS.h"
#include "__XSThread.h"

extern XSClassID __XSThreadClassID;

XSStatic XSObject XSThread_Alloc( void )
{
    return ( XSObject )XSRuntime_CreateInstance( __XSThreadClassID );
}

XSObject XSThread_Init( XSObject xsThis )
{
    return xsThis;
}

XSStatic XSThread XSThread_Detach( void ( * func )( XSThread thread, XSObject arg ), void * arg )
{
    pthread_t     t;
    XSUInteger    tid;
    __XSThread  * thread;

    #ifdef _WIN32
    HANDLE        handle;
    #endif

    thread = ( __XSThread * )XSThread_Init( XSThread_Alloc() );
    thread->func = func;
    thread->arg  = arg;

    XSRetain( arg );
    
    #ifdef _WIN32
    
    ( void )tid;
    ( void )t;

    handle = CreateThread( NULL, 0, ( LPTHREAD_START_ROUTINE )&__XSThread_Run, ( LPVOID )thread, 0, NULL );

    if( handle == NULL )
    {
        return NULL;
    }

    CloseHandle( handle );

    #else

    tid = pthread_create( &t, NULL, __XSThread_Run, ( void * )thread );
    
    if( tid )
    {
        XSRelease( thread );
        
        return NULL;
    }

    #endif

    return ( XSThread )thread;
}

XSUInteger XSThread_GetID( XSThread xsThis )
{
    return ( ( __XSThread * )xsThis )->tid;
}
