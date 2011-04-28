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
 * @file        XSRuntime.c
 * @brief       Implementation of the runtime functions
 * @author      Jean-David Gadina <macmade@eosgarden.com>
 */

#include "XS.h"
#include "__XSRuntime.h"
#include "__XSMemory.h"
#include "__XSMemoryDebug.h"

/*!
 * define       __XS_RUNTIME_CLASS_TABLE_SIZE
 * @brief       Default allocation size for the runtime class table
 */
#define __XS_RUNTIME_CLASS_TABLE_SIZE   1024

/*!
 * define       __XS___XS_RUNTIME_INIT_CHECK_INIT_CHECK
 * @brief       Checks if the runtime has been initialized
 * @details     This macro will produce a fatal error if the runtime has not been initialized.
 */
#define __XS___XS_RUNTIME_INIT_CHECK_INIT_CHECK         if( __inited == NO ) { XSFatalError( "Error: the runtime has not been initialized\n" ) }

/*!
 * @var         __inited
 * @brief       Whether the XSFoundation runtime has been initialized
 */
static BOOL __inited = NO;

/*!
 * @var         __class_table
 * @brief       The runtime class table
 */
static XSRuntimeClass * __class_table;

/*!
 * @var         __class_size
 * @brief       The allocated size of the runtime class table
 */
static size_t __class_size;

/*!
 * @var         __class_count
 * @brief       The number of registered classes in the runtime class table
 */
static size_t __class_count;

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

void XSRuntime_Initialize( void )
{
    XSDebugLog( XSDebugLogLevelDebug, "Initializing the XSFoundation runtime" );
    
    __inited = YES;
    
    atexit( XSRuntime_Finalize );
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

void XSRuntime_Finalize( void )
{
    __inited = NO;
    
    XSDebugLog( XSDebugLogLevelDebug, "Finalizing the XSFoundation runtime" );
    
    XSRelease( __class_table );
}

XSClassID XSRuntime_NewClass( const XSClassInfos * const cls )
{
    __XS___XS_RUNTIME_INIT_CHECK_INIT_CHECK
    
    if( __class_size == 0 )
    {
        XSDebugLog( XSDebugLogLevelDebug, "Allocating space for the class table" );
        
        if( NULL == ( __class_table = ( XSRuntimeClass * )XSAlloc( sizeof( XSRuntimeClass ) * __XS_RUNTIME_CLASS_TABLE_SIZE ) ) )
        {
            fprintf( stderr, "Error: unable to allocate the runtime class table!\n" );
            exit( EXIT_FAILURE );
        }
        
        __class_size += __XS_RUNTIME_CLASS_TABLE_SIZE;
    }
    
    if( __class_count == __class_size )
    {
        XSDebugLog( XSDebugLogLevelDebug, "Reallocating space for the class table" );
        
        if( NULL == ( __class_table = ( XSRuntimeClass * )XSRealloc( __class_table, sizeof( XSRuntimeClass ) * ( __XS_RUNTIME_CLASS_TABLE_SIZE + __class_size ) ) ) )
        {
            fprintf( stderr, "Error: unable to re-allocate the runtime class table!\n" );
            exit( EXIT_FAILURE );
        }
        
        __class_size += __XS_RUNTIME_CLASS_TABLE_SIZE;
    }
    
    XSDebugLog( XSDebugLogLevelDebug, "Registering class: %s", cls->className );
    
    __class_table[ __class_count ].classInfos = ( XSClassInfos * )cls;
    
    return ++__class_count;
}

XSObject XSRuntime_CreateInstance( XSClassID typeID )
{
    XSRuntimeClass * cls;
    size_t           size;
    XSInstance       o;
    
    __XS___XS_RUNTIME_INIT_CHECK_INIT_CHECK
    
    if( typeID > __class_count || typeID == 0 )
    {
        return NULL;
    }
    
    cls           = &( __class_table[ typeID - 1 ] );
    size          = cls->classInfos->instanceSize;
    o             = XSAlloc( size, typeID );
    
    if( o != NULL )
    {
        o->__class = cls;
    }
    
    return ( XSObject )o;
}

XSObject XSRuntime_CreateInstanceOfClass( XSClass cls )
{
    XSClassID classID;
    
    if( cls == NULL )
    {
        return NULL;
    }
    
    classID = XSRuntime_GetClassIDForClass( ( XSClass )cls );
    
    if( classID == 0 )
    {
        return NULL;
    }
    
    return XSRuntime_CreateInstance( classID );
}

XSObject XSRuntime_CreateInstanceOfClassWithName( const char * name )
{
    size_t           i;
    XSObject         o;
    XSRuntimeClass * cls;
    
    if( name == NULL )
    {
        return NULL;
    }
    
    for( i = 0; i < __class_count; i++ )
    {
        cls = &( __class_table[ i ] );
        
        if( strcmp( cls->classInfos->className, name ) == 0 )
        {
            o = XSRuntime_CreateInstance( i + 1 );
            
            if( cls->classInfos->init != NULL )
            {
                return cls->classInfos->init( o );
            }
        }
    }
    
    return NULL;
}

const char * XSRuntime_ObjectDescription( void * ptr )
{
    XSString           description;
    XSString           str;
    __XSMemoryObject * o;
    XSClass            cls;
    
    if( ptr == NULL )
    {
        return "<XSObject: nil>";
    }
    
    if( XSRuntime_IsInstance( ptr ) == NO )
    {
        return "<XSNotAnObject>";
    }
    
    o   = __XSMemory_GetMemoryObject( ptr );
    cls = XSRuntime_GetClassForClassID( o->classID );
    str = XSAutorelease( XSString_Init( XSString_Alloc() ) );
    
    XSString_AppendFormat( str, ( char * )"<%s: %p>", cls->classInfos->className, ptr );
    
    if( cls->classInfos->toString != NULL )
    {
        description = cls->classInfos->toString( ptr );
        XSString_AppendFormat( str, ( char * )" [ %s ]", XSString_CString( description ) );
    }
    
    return XSString_CString( str );
}

BOOL XSRuntime_IsInstance( void * ptr )
{
    __XSMemoryObject * o;
    
    if( ptr == NULL )
    {
        return NO;
    }
    
    o = __XSMemory_GetMemoryObject( ptr );
    
    if( o->classID > 0 && XSRuntime_GetClassForClassID( o->classID ) != NULL )
    {
        return YES;
    }
    
    return NO;
}

XSClass XSRuntime_GetClassForClassID( XSClassID classID )
{
    if( classID == 0 )
    {
        return NULL;
    }
    
    if( classID > __class_count )
    {
        return NULL;
    }
    
    return ( XSClass )&( __class_table[ classID - 1 ] );
}

XSClassID XSRuntime_GetClassIDForClass( XSClass cls )
{
    XSUInteger       i;
    
    if( cls == NULL )
    {
        return 0;
    }
    
    for( i = 0; i < __class_count; i++ )
    {
        if( &( __class_table[ i ] ) == cls )
        {
            return i + 1;
        }
    }
    
    return 0;
}

XSClass XSRuntime_GetClassForObject( XSObject object )
{
    if( object == NULL )
    {
        return NULL;
    }
    
    if( XSRuntime_IsInstance( object ) == NO )
    {
        return NULL;
    }
    
    return ( ( XSInstance )object )->__class;
}

XSClassID XSRuntime_GetTypeIDForObject( XSObject object )
{
    if( object == NULL )
    {
        return 0;
    }
    
    if( XSRuntime_IsInstance( object ) == NO )
    {
        return 0;
    }
    
    return XSRuntime_GetClassIDForClass( XSRuntime_GetClassForObject( object ) );
}

const char * XSRuntime_GetClassNameForClassID( XSClassID classID )
{
    if( classID == 0 || classID > __class_count )
    {
        return "N/A";
    }
    
    return __class_table[ classID - 1 ].classInfos->className;
}

const char * XSRuntime_GetClassNameForClass( XSClass cls )
{
    if( cls == NULL )
    {
        return NULL;
    }
    
    return cls->classInfos->className;
}

const char * XSRuntime_GetClassNameForObject( XSObject object )
{
    if( object == NULL )
    {
        return NULL;
    }
    
    if( XSRuntime_IsInstance( object ) == NO )
    {
        return NULL;
    }
    
    return ( ( XSInstance )object )->__class->classInfos->className;
}

BOOL XSRuntime_IsInstanceOfClass( XSObject object, XSClass cls )
{
    if( object == NULL || cls == NULL )
    {
        return NO;
    }
    
    if( XSRuntime_IsInstance( object ) == NO )
    {
        return NO;
    }
    
    if( ( ( XSInstance )object )->__class == cls )
    {
        return YES;
    }
    
    return NO;
}

BOOL XSRuntime_IsInstanceOfClassName( XSObject object, const char * name )
{
    if( object == NULL || name == NULL )
    {
        return NO;
    }
    
    if( XSRuntime_IsInstance( object ) == NO )
    {
        return NO;
    }
    
    if( strcmp( ( ( XSRuntimeClass * )object )->classInfos->className, name ) == 0 )
    {
        return YES;
    }
    
    return NO;
}