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
 * @file        __XSRuntime.c
 * @brief       Implementation of the private runtime functions
 * @author      Jean-David Gadina <macmade@eosgarden.com>
 */

#include "XS.h"
#include "__XSRuntime.h"
#include "__XSMemoryDebug.h"

/*!
 * @var         __xsruntime_inited
 * @brief       Whether the XSFoundation runtime has been initialized
 */
BOOL __xsruntime_inited = NO;

/*!
 * @var         __class_table
 * @brief       The runtime class table
 */
XSRuntimeClass * __xsruntime_class_table;

/*!
 * @var         __class_size
 * @brief       The allocated size of the runtime class table
 */
size_t __xsruntime_class_size;

/*!
 * @var         __class_count
 * @brief       The number of registered classes in the runtime class table
 */
size_t __xsruntime_class_count;

/* Prototypes for the initialization of the core runtime classes */
void __XSMemoryObject_Initialize( void );
void __XSApplication_Initialize( void );
void __XSApplicationArgument_Initialize( void );
void __XSArray_Initialize( void );
void __XSBag_Initialize( void );
void __XSBool_Initialize( void );
void __XSBTree_Initialize( void );
void __XSColor_Initialize( void );
void __XSData_Initialize( void );
void __XSDictionary_Initialize( void );
void __XSError_Initialize( void );
void __XSException_Initialize( void );
void __XSFile_Initialize( void );
void __XSHost_Initialize( void );
void __XSLock_Initialize( void );
void __XSNull_Initialize( void );
void __XSNotification_Initialize( void );
void __XSNotificationCenter_Initialize( void );
void __XSNumber_Initialize( void );
void __XSSet_Initialize( void );
void __XSString_Initialize( void );
void __XSThread_Initialize( void );
void __XSTimer_Initialize( void );
void __XSURL_Initialize( void );
void __XSURLRequest_Initialize( void );

void __XSRuntime_Initialize( void )
{
    XSDebugLog( XSDebugLogLevelDebug, "Initializing the XSFoundation runtime" );
    
    __xsruntime_inited = YES;
    
    atexit( __XSRuntime_Finalize );
    atexit( __XSMemoryDebug_Finalize );
    atexit( XSApplication_Exit );
    
    __XSMemoryDebug_InstallSignalHandlers();
    
    __XSAutoreleasePool_Initialize();
    __XSArray_Initialize();
    __XSApplication_Initialize();
    __XSApplicationArgument_Initialize();
    __XSBag_Initialize();
    __XSBool_Initialize();
    __XSBTree_Initialize();
    __XSColor_Initialize();
    __XSData_Initialize();
    __XSDictionary_Initialize();
    __XSError_Initialize();
    __XSException_Initialize();
    __XSFile_Initialize();
    __XSHost_Initialize();
    __XSLock_Initialize();
    __XSNotification_Initialize();
    __XSNotificationCenter_Initialize();
    __XSNull_Initialize();
    __XSNumber_Initialize();
    __XSSet_Initialize();
    __XSString_Initialize();
    __XSThread_Initialize();
    __XSTimer_Initialize();
    __XSURL_Initialize();
    __XSURLRequest_Initialize();
}

void __XSRuntime_Finalize( void )
{
    __xsruntime_inited = NO;
    
    XSDebugLog( XSDebugLogLevelDebug, "Finalizing the XSFoundation runtime" );
    
    free( __xsruntime_class_table );
}