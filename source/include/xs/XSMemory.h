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
 * @header      
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    
 */

#ifndef _XS_MEMORY_H_
#define _XS_MEMORY_H_
#pragma once

#include "XSMacros.h"

XS_EXTERN_C_BEGIN

#include "XSTypes.h"

/*!
 * @typedef     XSAutoreleasePoolRef
 * @abstract    Opaque type for the XSAutoreleasePool objects
 */
typedef struct XSAutoreleasePool * XSAutoreleasePoolRef;

/*!
 * @function    XSAutoreleasePool_Create
 * @abstract    Creates a new auto-release pool
 * @description The newly created pool will be set as the active one, meaning
 *              objects auto-released after the pool creation will be placed
 *              inside it.
 * @result      The new auto-release pool object
 */
XSAutoreleasePoolRef XSAutoreleasePool_Create( void );

/*!
 * @function    XSAutoreleasePool_Drain
 * @abstract    Removes objects from the current auto-release pool, sending the a release message.
 * @result      void
 */
void XSAutoreleasePool_Drain( void );

/*!
 * @function    XSAlloc
 * @abstract    Allocates memory
 * descriton    Returned pointer will have to be passed to the XSRelease
 *              function in order to be free.
 * @param       size    The number of bytes to allocate
 * @param       ...     Reserved for internal runtime use
 * @result      A pointer to the allocated memory
 */
void * XSAlloc( size_t size, ... );

/*!
 * @function    XSRealloc
 * @abstract    Reallocates memory
 * @param       ptr     The pointer to reallocate
 * @param       size    The new size in bytes
 * @result      The new pointer to the reallocated memory
 */
void * XSRealloc( void * ptr, size_t size );

/*!
 * @function    XSRetain
 * @abstract    Retains a memory pointer, preventing it to be freed
 * @description When retaining an object, the internal retain count is
 *              incremented. It means you own an object that you retain, and
 *              that you are responsible to release it using XSRelease.
 * @param       ptr     The pointer to retain
 * @result      void
 */
void XSRetain( void * ptr );

/*!
 * @function    XSRelease
 * @abstract    Releases a memory pointer
 * @description When releasing an object, the internal retain count is
 *              decremented. When it reaches 0, the pointer will be
 *              automatically freed.
 * @param       ptr     The pointer to release
 * @result      void
 */
void XSRelease( void * ptr );

/*!
 * @function    XSAutorelease
 * @abstract    Marks a memory pointer as auto-releasable
 * @description The pointer will be placed in the instance of the current
 *              auto-release pool, and will receive a release message the next
 *              the auto-release pool is drained.
 * @param       The memory pointer to mark as auto-releasable
 * @result      void
 */
void XSAutorelease( void * ptr );

/*!
 * @function    XSAutoAlloc
 * @abstract    Allocates auto-releasable memory
 * @description When using this function, the object will automatically receive
 *              a release message the next time the current auto-release pool
 *              is drained. It means you don't own it, and that you are not
 *              responsible to release it explicitely.
 * @param       size    The size to allocate in bytes
 * @result      A pointer to the allocated memory,
 */
void * XSAutoAlloc( size_t size );

/*!
 * @function    XSCopy
 * @abstract    Copies a pointer
 * @description This function executes a soft-copy. When using a structure with
 *              pointers, only the first level is copied.
 *              Note that you are responsible to release the copied pointer
 *              by using the XSRelease function.
 * @param       ptr     The pointer to copy
 * @result      The copy of the new pointer
 */
void * XSCopy( void * ptr );

/*!
 * @function    XSGetRetainCount
 * @abstract    Gets the retain count for a pointer
 * @param       ptr     The pointer
 * @result      The retain count
 */
XSUInteger XSGetRetainCount( void * ptr );

XS_EXTERN_C_END

#endif /* _XS_MEMORY_H_ */
