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
 * @header      XSNumber.h
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    ...
 */

#ifndef _XS_NUMBER_H_
#define _XS_NUMBER_H_
#pragma once

#include "XSMacros.h"

XS_EXTERN_C_BEGIN

/*!
 * @typedef     XSNumberRef
 * @abstract    Opaque type for the XSNumber objects
 */
typedef struct XSNumber * XSNumberRef;

/*!
 * @function    XSNumber_CreateWithBool
 * @abstract    Creates a number with a BOOL value
 * @param       The BOOL value
 * @result      The number object
 */
XSNumberRef XSNumber_CreateWithBool( BOOL value );

/*!
 * @function    XSNumber_CreateWithChar
 * @abstract    Creates a number with a char value
 * @param       The char value
 * @result      The number object
 */
XSNumberRef XSNumber_CreateWithChar( char value );

/*!
 * @function    XSNumber_CreateWithDouble
 * @abstract    Creates a number with a double value
 * @param       The double value
 * @result      The number object
 */
XSNumberRef XSNumber_CreateWithDouble( double value );

/*!
 * @function    XSNumber_CreateWithFloat
 * @abstract    Creates a number with a float value
 * @param       The float value
 * @result      The number object
 */
XSNumberRef XSNumber_CreateWithFloat( float value );

/*!
 * @function    XSNumber_CreateWithInt
 * @abstract    Creates a number with an int value
 * @param       The int value
 * @result      The number object
 */
XSNumberRef XSNumber_CreateWithInt( int value );

/*!
 * @function    XSNumber_CreateWithInteger
 * @abstract    Creates a number with an integer value
 * @param       The integer value
 * @result      The number object
 */
XSNumberRef XSNumber_CreateWithInteger( XSInteger value );

/*!
 * @function    XSNumber_CreateWithLong
 * @abstract    Creates a number with a long value
 * @param       The long value
 * @result      The number object
 */
XSNumberRef XSNumber_CreateWithLong( long value );

/*!
 * @function    XSNumber_CreateWithLongLong
 * @abstract    Creates a number with a long long value
 * @param       The long long value
 * @result      The number object
 */
XSNumberRef XSNumber_CreateWithLongLong( long long value );

/*!
 * @function    XSNumber_CreateWithShort
 * @abstract    Creates a number with a short value
 * @param       The short value
 * @result      The number object
 */
XSNumberRef XSNumber_CreateWithShort( short value );

/*!
 * @function    XSNumber_CreateWithUnsignedChar
 * @abstract    Creates a number with an unsigned char value
 * @param       The unsigned char value
 * @result      The number object
 */
XSNumberRef XSNumber_CreateWithUnsignedChar( unsigned char value );

/*!
 * @function    XSNumber_CreateWithUnsignedInt
 * @abstract    Creates a number with an unsigned int value
 * @param       The unsigned int value
 * @result      The number object
 */
XSNumberRef XSNumber_CreateWithUnsignedInt( unsigned int value );

/*!
 * @function    XSNumber_CreateWithUnsignedInteger
 * @abstract    Creates a number with an unsigned integer value
 * @param       The unsigned integer value
 * @result      The number object
 */
XSNumberRef XSNumber_CreateWithUnsignedInteger( XSUInteger value );

/*!
 * @function    XSNumber_CreateWithUnsignedLong
 * @abstract    Creates a number with an unsigned long value
 * @param       The unsigned long value
 * @result      The number object
 */
XSNumberRef XSNumber_CreateWithUnsignedLong( unsigned long value );

/*!
 * @function    XSNumber_CreateWithUnsignedLongLong
 * @abstract    Creates a number with an unsigned long long value
 * @param       The unsigned long long value
 * @result      The number object
 */
XSNumberRef XSNumber_CreateWithUnsignedLongLong( unsigned long long value );

/*!
 * @function    XSNumber_CreateWithUnsignedShort
 * @abstract    Creates a number with an unsigned short value
 * @param       The unsigned short value
 * @result      The number object
 */
XSNumberRef XSNumber_CreateWithUnsignedShort( unsigned short value );

XS_EXTERN_C_END

#endif /* _XS_NUMBER_H_ */
