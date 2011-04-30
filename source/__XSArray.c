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
 * @file        __XSArray.c
 * @brief       Private implementation for the XSArray class
 * @author      Jean-David Gadina <macmade@eosgarden.com>
 */

#include "XS.h"
#include "__XSArray.h"

/*!
 * @var         __XSArrayClass
 * @brief       Runtime class definition
 */
static const XSClassInfos __XSArrayClass =
{
    "XSArray",              /* Class name */
    sizeof( __XSArray ),    /* Object size */
    NULL,                   /* Constructor */
    __XSArray_Destruct,     /* Destructor */
    XSArray_Init,           /* Default initializer */
    __XSArray_Copy,         /* Object copy */
    __XSArray_ToString,     /* Object description */
    NULL                    /* Object comparison */
};

/*!
 * @var         __XSArrayClassID
 * @brief       Type ID for the runtime class
 */
XSClassID __XSArrayClassID;

void __XSArray_Initialize( void )
{
    __XSArrayClassID = XSRuntime_RegisterClass( &__XSArrayClass );
}

void __XSArray_Destruct( XSObject object )
{
    __XSArray  * array;
    XSUInteger  i;
    
    array = ( __XSArray * )object;
    
    if( array->values != NULL )
    {
        for( i = 0; i < array->count; i++ )
        {
            if( array->values[ i ] != NULL )
            {
                XSRelease( array->values[ i ] );
            }
        }
        
        XSRelease( array->values );
    }
}

XSString __XSArray_ToString( XSObject object )
{
    XSUInteger  i;
    __XSArray * array;
    XSString    description;
    
    description = XSString_Init( XSString_Alloc() );
    array       = ( __XSArray * )object;
    
    XSString_AppendFormat( description, ( char * )"%lu items: {\n", array->count );
    
    for( i = 0; i < array->count; i++ )
    {
        if( array->values[ i ] == NULL )
        {
            XSString_AppendFormat( description, ( char * )"    %lu => (null),\n" );
        }
        else if( XSRuntime_IsInstance( array->values[ i ] ) )
        {
            XSString_AppendFormat( description, ( char * )"    %lu => %s,\n", i, ( char * )XSRuntime_ObjectDescription( array->values[ i ] ) );
        }
        else
        {
            XSString_AppendFormat( description, ( char * )"    %lu => %p,\n", i, array->values[ i ] );
        }
    }
    
    XSString_AppendCString( description, ( char * )"}" );
    
    return XSAutorelease( description );
}

void __XSArray_Copy( XSObject source, XSObject destination )
{
    __XSArray * a1;
    __XSArray * a2;
    XSUInteger  i;
    
    a1 = ( __XSArray * )source;
    a2 = ( __XSArray * )destination;
    
    a2->values = XSCopy( a1->values );
    
    for( i = 0; i < a1->count; i++ )
    {
        XSRetain( a2->values[ i ] );
    }
}
