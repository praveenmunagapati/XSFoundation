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
 * @file        __XSThread.c
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    Private implementation for the XSThread class
 */

#include "XS.h"
#include "__XSThread.h"

/*!
 * @var         __XSThreadClass
 * @abstract    Runtime class definition
 */
static const XSClassInfos __XSThreadClass =
{
    "XSThread",             /* Class name */
    sizeof( __XSThread ),   /* Object size */
    NULL,                   /* Constructor */
    NULL,                   /* Destructor */
    XSThread_Init,          /* Default initializer */
    NULL,                   /* Object copy */
    NULL,                   /* Object description */
    NULL                    /* Object comparison */
};

/*!
 * @var         __XSThreadClassID
 * @abstract    Type ID for the runtine class
 */
XSClassID __XSThreadClassID;

void __XSThread_Initialize( void )
{
    __XSThreadClassID = XSRuntime_RegisterClass( &__XSThreadClass );
}

BOOL __XSThread_Equals( void * object1, void * object2 )
{
    __XSThread * t1;
    __XSThread * t2;
    
    t1 = ( __XSThread * )object1;
    t2 = ( __XSThread * )object2;
    
    if( t1->tid == t2->tid )
    {
        return YES;
    }
    
    return NO;
}

#ifdef _WIN32
DWORD __XSThread_Run( LPVOID thread )
#else
void * __XSThread_Run( void * thread )
#endif
{
    pthread_t         tid;
    __XSThread      * _thread;
    XSAutoreleasePool ap;
    
    #ifdef __MACH__
    mach_port_t mid;
    #endif
    
    _thread = ( __XSThread * )thread;
    tid     = pthread_self();
    ap      = XSAutoreleasePool_Init( XSAutoreleasePool_Alloc() );

    #ifdef __MACH__
    mid          = pthread_mach_thread_np( tid );
    _thread->tid = mid;
    #else
    _thread->tid = tid;
    #endif

    _thread->func( ( XSThread )thread, _thread->arg );
    
    XSRelease( _thread->arg );
    XSRelease( thread );
    XSRelease( ap );
    
    pthread_exit( NULL );

    #ifdef _WIN32
    return 0;
    #endif
}
