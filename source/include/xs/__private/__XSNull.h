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
 * @header      __XSNULL.h
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    Private XSNull class definitions
 */

#ifndef ___XS_NULL_H_
#define ___XS_NULL_H_
#pragma once

#include "../XSMacros.h"

XS_EXTERN_C_BEGIN

#include "XS.h"

/*!
 * @typdef      __XSNull
 * @abstract    XSNull class
 * @field       _xsbase     Runtime class
 */
typedef struct __XSNull_Struct
{
    XSRuntimeClass __class;
}
__XSNull;

/*!
 * @function    __XSNull_Initialize
 * @abstract    Runtime initialization
 * @result      void
 */
void __XSNull_Initialize( void );

/*!
 * @function    __XSString_Equals
 * @abstract    Object comparison
 * @param       object1 The first object to compare
 * @param       object1 The second object to compare
 * @result      YES if both objects are equals, otherwise NO
 */
BOOL __XSNull_Equals( XSObject object1, XSObject object2 );

XS_EXTERN_C_END

#endif /* ___XS_NULL_H_ */
