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
 * @header      XSDictionary.c
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    Implementation for the XSDictionary class
 */

#include "XS.h"
#include "__XSDictionary.h"

extern XSClassID __XSDictionaryClassID;

XSStatic XSObject XSDictionary_Alloc( void )
{
    return ( XSObject )XSRuntime_CreateInstance( __XSDictionaryClassID );
}

XSObject XSDictionary_Init( XSObject xsThis )
{
    return XSDictionary_InitWithCapacity( xsThis, ( XSUInteger )XSDICTIONARY_DEFAULT_CAPACITY );
}

XSDictionary XSDictionary_InitWithCapacity( XSDictionary xsThis, XSUInteger capacity )
{
    XSObject       * store;
    XSString       * keys;
    __XSDictionary * dict;
    
    if( NULL == ( store = ( XSObject * )XSAlloc( capacity * sizeof( XSObject ) ) ) )
    {
        return NULL;
    }
    
    if( NULL == ( keys = ( XSString * )XSAlloc( capacity * sizeof( XSString ) ) ) )
    {
        XSRelease( store );
        return NULL;
    }
    
    dict                  = ( __XSDictionary * )xsThis;
    dict->values          = store;
    dict->keys            = keys;
    dict->capacity        = capacity;
    dict->initialCapacity = capacity;
    dict->count    = 0;
    
    return ( XSDictionary )dict;
}

XSDictionary XSDictionary_InitWithKeysAndValues( XSDictionary xsThis, XSString key1, XSObject value1, ... )
{
    XSString key;
    XSObject value;
    va_list  args;
    
    if( value1 == NULL || key1 == NULL )
    {
        return xsThis;
    }
    
    XSDictionary_Init( xsThis );
    XSDictionary_SetValueForKey( xsThis, value1, key1 );
    va_start( args, value1 );
    
    while( NULL != ( key = va_arg( args, XSString ) ) )
    {
        value = va_arg( args, void * );
        
        if( value == NULL )
        {
            return xsThis;
        }
        
        XSDictionary_SetValueForKey( xsThis, value, key );
    }
    
    va_end( args );
    
    return xsThis;
}

XSUInteger XSDictionary_Count( XSDictionary xsThis )
{
    return ( ( __XSDictionary * )xsThis )->count;
}

XSAutoreleased XSArray XSDictionary_Keys( XSDictionary xsThis )
{
    __XSDictionary * _dict;
    XSArray          array;
    XSUInteger       i;
    
    _dict = ( __XSDictionary * )xsThis;
    array = XSArray_InitWithCapacity( XSArray_Alloc(), _dict->count );
    
    for( i = 0; i < _dict->count; i++ )
    {
        XSArray_AppendValue( array, _dict->keys[ i ] );
    }
    
    return XSAutorelease( array );
}

XSAutoreleased XSArray XSDictionary_Values( XSDictionary xsThis )
{
    __XSDictionary * _dict;
    XSArray          array;
    XSUInteger       i;
    
    _dict = ( __XSDictionary * )xsThis;
    array = XSArray_InitWithCapacity( XSArray_Alloc(), _dict->count );
    
    for( i = 0; i < _dict->count; i++ )
    {
        XSArray_AppendValue( array, _dict->values[ i ] );
    }
    
    return XSAutorelease( array );
}

XSObject XSDictionary_ValueForKey( XSDictionary xsThis, XSString key )
{
    __XSDictionary * _dict;
    XSUInteger       i;
    
    _dict = ( __XSDictionary * )xsThis;
    
    for( i = 0; i < _dict->count; i++ )
    {
        if( XSString_IsEqualToString( key, _dict->keys[ i ] ) )
        {
            return _dict->values[ i ];
        }
    }
    
    return NULL;
}

void XSDictionary_SetValueForKey( XSDictionary xsThis, XSObject value, XSString key )
{
    XSString       * keys;
    XSObject       * values;
    __XSDictionary * dict;
    XSUInteger       i;
    
    dict = ( __XSDictionary * )xsThis;
    
    for( i = 0; i < dict->count; i++ )
    {
        if( XSEquals( dict->keys[ i ], key ) )
        {
            XSRelease( dict->values[ i ] );
            
            dict->values[ i ] = XSRetain( value );
            
            return;
        }
    }
    
    if( dict->count == dict->capacity )
    {
        if( NULL == ( keys = ( XSString * )XSRealloc( dict->keys, sizeof( XSString * ) * ( dict->count + dict->initialCapacity ) ) ) )
        {
            return;
        }
        
        if( NULL == ( values = ( XSObject * )XSRealloc( dict->values, sizeof( XSObject ) * ( dict->count + dict->initialCapacity ) ) ) )
        {
            return;
        }
        
        dict->keys   = keys;
        dict->values = values;
    }
    
    dict->keys[ dict->count ]     = XSRetain( key );
    dict->values[ dict->count++ ] = XSRetain( value );
}

void XSDictionary_RemoveValueForKey( XSDictionary xsThis, XSString key )
{
    BOOL             found;
    __XSDictionary * dict;
    XSUInteger       i;
    
    dict  = ( __XSDictionary * )xsThis;
    found = NO;
    
    for( i = 0; i < dict->count; i++ )
    {
        if( found == YES )
        {
            dict->keys[ i - 1 ]   = dict->keys[ i ];
            dict->values[ i - 1 ] = dict->values[ i ];
            dict->keys[ i ]       = NULL;
            dict->values[ i ]     = NULL;
            
            continue;
        }
        
        if( XSEquals( dict->keys[ i ], key ) )
        {
            XSRelease( dict->keys[ i ] );
            XSRelease( dict->values[ i ] );
            
            found = YES;
        }
    }
}

BOOL XSDictionary_KeyExists( XSDictionary xsThis, XSString key )
{
    __XSDictionary * dict;
    XSUInteger       i;
    
    dict = ( __XSDictionary * )xsThis;
    
    for( i = 0; i < dict->count; i++ )
    {
        if( XSEquals( dict->keys[ i ], key ) )
        {
            return YES;
        }
    }
    
    return NO;
}

BOOL XSDictionary_ContainsValue( XSDictionary xsThis, XSObject value )
{
    __XSDictionary * dict;
    XSUInteger       i;
    
    dict = ( __XSDictionary * )xsThis;
    
    for( i = 0; i < dict->count; i++ )
    {
        if( XSEquals( dict->values[ i ], value ) )
        {
            return YES;
        }
    }
    
    return NO;
}
