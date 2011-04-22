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
 * @header      XSException.c
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    Implementation for the XSException class
 */

#include "XS.h"
#include "__XSException.h"

extern XSClassID __XSExceptionClassID;

XSStatic XSObject XSException_Alloc( void )
{
    return ( XSObject )XSRuntime_CreateInstance( __XSExceptionClassID );
}

XSStatic XSAutoreleased XSException XSException_New( XSInteger code, XSString reason )
{
    return XSAutorelease( XSException_Init( XSException_Alloc(), code, reason ) );
}

XSException XSException_Init( XSException xsThis, XSInteger code, XSString reason )
{
    __XSException * e;
    
    if( xsThis == NULL )
    {
        return NULL;
    }
    
    e = ( __XSException * )xsThis;
    
    e->code   = code;
    e->reason = reason;
    
    XSRetain( e->reason );
    
    return ( XSException )e;
}

XSInteger XSException_GetCode( XSException xsThis )
{
    if( xsThis == NULL )
    {
        return 0;
    }
    
    return ( ( __XSException * )xsThis )->code;
}

XSAutoreleased XSString XSException_GetReason( XSException xsThis )
{
    if( xsThis == NULL )
    {
        return NULL;
    }
    
    return XSAutorelease( XSCopy( ( ( __XSException * )xsThis )->reason ) );
}