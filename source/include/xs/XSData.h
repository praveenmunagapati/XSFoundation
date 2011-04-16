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
 * @header      XSData.h
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    XSData class functions
 */

#ifndef _XS_DATA_H_
#define _XS_DATA_H_
#pragma once

#include "XSMacros.h"

XS_EXTERN_C_BEGIN

/*!
 * @typedef     XSData
 * @abstract    Opaque type for the XSData objects
 */
typedef struct XSData * XSData;

/*!
 * @function    __XSData_Alloc
 * @abstract    Object allocator
 * @result      The allocated object
 */
XSStatic XSObject XSData_Alloc( void );

/*!
 * @function    XSData_Init
 * @abstract    Creates a data object
 * @param       xsThis  The data object
 * @result      The data object
 */
XSObject XSData_Init( XSObject xsThis );

/*!
 * @function    XSData_InitWithCapacity
 * @abstract    Creates a data object with an initial capacity
 * @param       xsThis      The data object
 * @param       capacity    The initial capacity
 * @result      The data object
 */
XSData XSData_InitWithCapacity( XSData xsThis, XSUInteger capacity );

/*!
 * @function    XSData_InitWithBytes
 * @abstract    Creates a data object with bytes
 * @param       xsThis      The data object
 * @param       bytes       The data to copy
 * @param       capacity    The length of the data
 * @result      The data object
 */
XSData XSData_InitWithBytes( XSData xsThis, UInt8 * bytes, XSUInteger length );

/*!
 * @function    XSData_GetLength
 * @abstract    Gets the data length
 * @result      The data length
 */
XSUInteger XSData_GetLength( XSData xsThis );

/*!
 * @function    XSData_GetBytes
 * @abstract    Get bytes from the data object
 * @param       xsThis      The data object
 * @param       range       The range of the data to get
 * @result      The data bytes
 */
XSAutoreleased UInt8 * XSData_GetBytes( XSData xsThis, XSRange range );

/*!
 * @function    XSData_AppendBytes
 * @abstract    Appends bytes to the data object
 * @param       xsThis      The data object
 * @param       bytes       The bytes to append
 * @param       length      The length of the data to append
 * @result      The data bytes
 */
void XSData_AppendBytes( XSData xsThis, UInt8 * bytes, XSUInteger length );

/*!
 * @function    XSData_GetBytesPointer
 * @abstract    Gets a pointer to the bytes
 * @param       xsThis      The data object
 * @result      A pointer to the bytes data
 */
UInt8 * XSData_GetBytesPointer( XSData xsThis );

XS_EXTERN_C_END

#endif /* _XS_DATA_H_ */
