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
 * @file        
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    
 */

#include "XS.h"
#include "private/__XSMemory.h"

XSAutoreleasePool * __xs_ar_pools[ XS_MEMORY_MAX_AR_POOLS ];
XSUInteger          __xs_ar_pools_num;

static const XSRuntimeClass __XSAutoreleasePoolClass =
{
    "XSAutoreleasePool"
};

static XSTypeID __XSAutoreleasePoolTypeID;

void __XSAutoreleasePool_Initialize( void )
{
    __XSAutoreleasePoolTypeID = XSRuntime_RegisterClass( &__XSAutoreleasePoolClass );
}

XSAutoreleasePool * __XSAutoreleasePool_Alloc( void )
{
    return ( XSAutoreleasePool * )XSRuntime_CreateInstance( __XSAutoreleasePoolTypeID, sizeof( XSAutoreleasePool ) );
}

XSAutoreleasePool * __XSMemory_GetCurrentAutoreleasePool( void )
{
    return __xsmemory_ar_pools[ __xs_ar_pools_num - 1 ];
}

void __XSMemory_AutoreleasePoolDrain( XSAutoreleasePool * ap )
{
    size_t i;
    
    for( i = 0; i < ap->num_objects; i++ )
    {
        XSRelease( ap->objects[ i ] );
    }
    
    ap->num_objects = 0;
}

__XSMemoryObject * __XSMemory_GetMemoryObject( void * ptr )
{
    __XSMemoryObject * o;
    char           * c;
    
    c  = ( char * )ptr;
    c -= sizeof( __XSMemoryObject * );
    c -= sizeof( void * );
    o  = ( __XSMemoryObject * )c;
    
    return o;
}
