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
 * @file        __XSException.c
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    Private implementation for the XSException class
 */

#include "XS.h"
#include "__XSException.h"

/*!
 * @var         __XSExceptionClass
 * @abstract    Runtime class definition
 */
static const XSClassInfos __XSExceptionClass =
{
    "XSException",              /* Class name */
    sizeof( __XSException ),    /* Object size */
    NULL,                       /* Constructor */
    __XSException_Destruct,     /* Destructor */
    NULL,                       /* Default initializer */
    __XSException_Copy,         /* Object copy */
    __XSException_ToString,     /* Object description */
    NULL                        /* Object comparison */
};

/*!
 * @var         __XSExceptionClassID
 * @abstract    Type ID for the runtime class
 */
XSClassID __XSExceptionClassID;

void __XSException_Initialize( void )
{
    __XSExceptionClassID = XSRuntime_RegisterClass( &__XSExceptionClass );
}

void __XSException_Destruct( XSObject object )
{
    __XSException * e;
    
    e = ( __XSException * )object;
    
    XSRelease( e->reason );
}

XSString __XSException_ToString( XSObject object )
{
    XSString description;
    
    description = XSString_Init( XSString_Alloc() );
    
    XSString_AppendFormat
    (
        description,
        ( char * )"%i: %s",
        ( ( __XSException * )object )->code,
        XSString_CString( ( ( __XSException * )object )->reason )
    );
    
    return XSAutorelease( description );
}

void __XSException_Copy( XSObject source, XSObject destination )
{
    __XSException * e1;
    __XSException * e2;
    
    e1 = ( __XSException * )source;
    e2 = ( __XSException * )destination;
    
    e2->reason = XSCopy( e1->reason );
}