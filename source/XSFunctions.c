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
#include "__XSFunctions.h"

/*!
 * @function    XSMakePoint
 * @abstract    Creates an XSPoint structure
 * @param       x   The X coordinate
 * @param       y   The Y coordinate
 * @result      An XSPoint structure
 */
XSPoint XSMakePoint( XSFloat x, XSFloat y )
{
    XSPoint p;
    
    p.x = x;
    p.y = y;
    
    return p;
}

/*!
 * @function    XSMakeSize
 * @abstract    Creates an XSSize structure
 * @param       width   The width
 * @param       height  The height
 * @result      An XSSize structure
 */
XSSize XSMakeSize( XSFloat width, XSFloat height )
{
    XSSize s;
    
    s.width  = width;
    s.height = height;
    
    return s;
}

/*!
 * @function    XSMakeRect
 * @abstract    Creates an XSRect structure
 * @param       x       The X coordinate
 * @param       y       The Y coordinate
 * @param       width   The width
 * @param       height  The height
 * @result      An XSRect structure
 */
XSRect XSMakeRect( XSFloat x, XSFloat y, XSFloat width, XSFloat height )
{
    XSRect r;
    
    r.origin.x    = x;
    r.origin.y    = y;
    r.size.width  = width;
    r.size.height = height;
    
    return r;
}

/*!
 * @function    XSRectZero
 * @abstract    Creates an XSRect structure with 0 origin and size
 * @result      An XSRect structure
 */
XSRect XSRectZero( void )
{
    return XSMakeRect( 0, 0, 0, 0 );
}

/*!
 * @function    XSMakeRange
 * @abstract    Creates an XSRange structure
 * @param       location    The range location
 * @param       length      The range length
 * @result      An XSRange structure
 */
XSRange XSMakeRange( XSUInteger location, XSUInteger length )
{
    XSRange r;
    
    r.location = location;
    r.length   = length;
    
    return r;
}

/*!
 * @function    XSLog
 * @abstract    Outputs a log message to stdout
 * @description The log message will be prefixed by the date/time, process
 *              name, ID, and thread ID (or MACH port if available).
 * @param       fmt     The message format
 * @param       ...     Arguments for the format
 * @result      void
 */
void XSLog( const char * fmt, ... )
{
    va_list args;
    
    va_start( args, fmt );
    
    XSVLog( fmt, args );
    
    va_end( args );
}

/*!
 * @function    XSVLog
 * @abstract    Outputs a log message to stdout
 * @description The log message will be prefixed by the date/time, process
 *              name, ID, and thread ID (or MACH port if available).
 * @param       fmt     The message format
 * @param       args    Arguments for the format
 * @result      void
 */
void XSVLog( const char * fmt, va_list args )
{
    __XSVLog( fmt, args );
}
