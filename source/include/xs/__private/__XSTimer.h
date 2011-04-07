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
 * @header      __XSTimer.h
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    ...
 */

#ifndef ___XSTIMER_H_
#define ___XSTIMER_H_
#pragma once

#include "../XSMacros.h"

XS_EXTERN_C_BEGIN

#include "XS.h"

/*!
 * @typdef      XSTimer
 * @abastract   XSTimer class
 * @field       _xsbase     Runtime class
 */
typedef struct _XSTimer
{
    XSRuntimeClass __class;
    BOOL           valid;
    XSUInteger     msecs;
    void ( * func )( XSTimerRef timer );
    
}
XSTimer;

/*!
 * @function    __XSTimer_Initialize
 * @abstract    Runtime initialization
 * @result      void
 */
void __XSTimer_Initialize( void );

/*!
 * @function    __XSTimer_Alloc
 * @abstract    Object allocator
 * @result      A pointer to the allocated object
 */
XSTimer * __XSTimer_Alloc( void );

/*!
 * @function    __XSTimer_RunOnce
 * @abstract    Runs a timer object after its time interval
 * @param       object  The thread object
 * @param       object  The timer object
 * @return      void
 */
void __XSTimer_RunOnce( XSThreadRef thread, void * object );

/*!
 * @function    __XSTimer_RunAndRepeat
 * @abstract    Runs a timer object after its time interval, and repeats untile the timer is invalidated
 * @param       object  The thread object
 * @param       object  The timer object
 * @return      void
 */
void __XSTimer_RunAndRepeat( XSThreadRef thread, void * object );

XS_EXTERN_C_END

#endif /* ___XSTIMER_H_ */
