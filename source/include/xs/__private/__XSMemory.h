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
 * @header      __XSMemory management
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    Private memory functions and private XSAutoreleasePool class definitions
 */

#ifndef ___XS_MEMORY_H_
#define ___XS_MEMORY_H_
#pragma once

#include "../XSMacros.h"

XS_EXTERN_C_BEGIN

#include "XS.h"

/* Maximum number of auto-release pools */
#define XS_MEMORY_MAX_AR_POOLS  256

/* Initial capacity of the auto-release pools */
#define XS_MEMORY_NUM_OBJECTS   256

/*!
 * @typdef      __XSAutoreleasePool
 * @abstract    XSAutoreleasePool class
 * @field       __class     Runtime class
 */
typedef struct __XSAutoreleasePool_Struct
{
    XSRuntimeClass __class;
    size_t         size;
    size_t         numObjects;
    void        ** objects;
}
__XSAutoreleasePool;

/*!
 * @typdef      __XSMemoryObject
 * @abstract    Allocated memeory object
 * @field       retain_count    The object's retain count
 * @field       size            The allocated data size
 * @field       typeID          The typeID (only for allocated objects)
 * @field       f1              Memory fence to prevent overflows
 * @field       data            A pointer to the allocated data
 * @field       f2              Memory fence to prevent overflows
 */
typedef struct ___XSMemoryObject_Struct
{
    XSUInteger    retainCount;
    size_t        size;
    size_t        allocID;
    XSClassID     classID;
    Str255        hash;
    void        * data;
    unsigned char fence[ 12 ];
}
__XSMemoryObject;

/*!
 * @function    __XSAutoreleasePool_Initialize
 * @abstract    Runtime initialization
 * @result      void
 */
void __XSAutoreleasePool_Initialize( void );

/*!
 * @function    __XSAutoreleasePool_Destruct
 * @abstract    Destructor
 * @abstract    A pointer to the object to be destructed
 * @param       object  The object that will be destructed
 * @result      void
 */
void __XSAutoreleasePool_Destruct( XSObject object );

/*!
 * @function    __XSAutoreleasePool_Copy
 * @abstract    Object copy
 * @param       object  A pointer to the object
 * @result      void
 */
void __XSAutoreleasePool_Copy( XSObject source, XSObject destination );

/*!
 * @function    __XSMemory_GetCurrentAutoreleasePool
 * @abstract    Gets a pointer to a memory records object from a pointer returned by the XS allocation functions.
 * @result      The auto-release pool object or NULL if no aut-release pool were created
 */
__XSAutoreleasePool * __XSMemory_GetCurrentAutoreleasePool( void );

/*!
 * @function    __XSMemory_AutoreleasePoolDrain
 * @abstract    Releases all objects placed in the auto-release pool.
 * @result      void
 */
void __XSMemory_AutoreleasePoolDrain( __XSAutoreleasePool * ap );

/*!
 * @function    __XSMemory_GetMemoryObject
 * @abstract    Gets the current (top-level) auto-release pool
 * @result      A pointer to the memory record object
 */
__XSMemoryObject * __XSMemory_GetMemoryObject( void * ptr );

/* Storage for the auto-release pools */
extern __XSAutoreleasePool * __xsmemory_ar_pools[];

/* NUmber of active auto-release pools */
extern XSUInteger __xsmemory_ar_pools_num;

XS_EXTERN_C_END

#endif /* ___XS_MEMORY_H_ */
