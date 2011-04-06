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
 * @header      XSApplication.h
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    ...
 */

#ifndef _XS_APPLICATION_H_
#define _XS_APPLICATION_H_
#pragma once

#include "XSMacros.h"

XS_EXTERN_C_BEGIN

#include "XSArray.h"
#include "XSString.h"
#include "XSApplicationArgument.h"

/*!
 * @typedef     XSApplicationRef
 * @abstract    Opaque type for the XSApplication objects
 */
typedef struct XSApplication * XSApplicationRef;

/*!
 * @function    XSApplication_Exit
 * @abstract    XSFoundation start routine
 * @description You must call this function before using any other XSFoundation
 *              function or object. Note that an auto-release pool is
 *              automatically created, so the auto-release features are
 *              enabled by default.
 * @param       argc    The number of CLI arguments
 * @param       argv    The CLI arguments array
 * @result      The application object
 */
XSApplicationRef XSApplication_Start( int argc, const char ** argv );

/*!
 * @function    XSApplication_Exit
 * @abstract    Application termination
 * @description You must call this function when exiting your application,
 *              instead of the classic 'exit()' function, so the auto-released
 *              memory is reclaimed, and the threads are terminated properly.
 * @result      void
 */
void XSApplication_Exit( void );

/*!
 * @function    XSApplication_SharedApplication
 * @abstract    Gets the application object
 * @result      The application object
 */
XSApplicationRef XSApplication_SharedApplication( void );

/*!
 * @function    XSApplication_PrintHelp
 * @abstract    Prints the application help dialog
 * @param       app     The application object
 * @result      void
 */
void XSApplication_PrintHelp( XSApplicationRef app, const char * description );

/*!
 * @function    XSApplication_RegisterArgument
 * @abstract    
 * @param       app     The application object
 * @result      
 */
void XSApplication_RegisterArgument( XSApplicationRef app, const char * name, XSApplicationArgumentType type, ... );

/*!
 * @function    XSApplication_GetArgument
 * @abstract    
 * @param       app     The application object
 * @result      
 */
XSApplicationArgumentRef XSApplication_GetArgument( XSApplicationRef app, const char * name );

/*!
 * @function    XSApplication_HasArgument
 * @abstract    
 * @param       app     The application object
 * @result      
 */
BOOL XSApplication_HasArgument( XSApplicationRef app, const char * name );

/*!
 * @function    XSApplication_GetFlag
 * @abstract    
 * @param       app     The application object
 * @result      
 */
BOOL XSApplication_GetFlag( XSApplicationRef app, const char * name );

/*!
 * @function    XSApplication_GetInteger
 * @abstract    
 * @param       app     The application object
 * @result      
 */
XSInteger XSApplication_GetInteger( XSApplicationRef app, const char * name );

/*!
 * @function    XSApplication_GetUnsignedInteger
 * @abstract    
 * @param       app     The application object
 * @result      
 */
XSUInteger XSApplication_GetUnsignedInteger( XSApplicationRef app, const char * name );

/*!
 * @function    XSApplication_GetString
 * @abstract    
 * @param       app     The application object
 * @result      
 */
XSStringRef XSApplication_GetString( XSApplicationRef app, const char * name );

/*!
 * @function    XSApplication_GetUnnamedArguments
 * @abstract    
 * @param       app     The application object
 * @result      
 */
XSArrayRef XSApplication_GetUnnamedArguments( XSApplicationRef app );

XS_EXTERN_C_END

#endif /* _XS_APPLICATION_H_ */
