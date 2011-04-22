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
 * @header      XSMacros.h
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    General macros
 */

#ifndef _XS_MACROS_H_
#define _XS_MACROS_H_
#pragma once

#ifdef _WIN32
    
    #define XSMain( argc, argv )    int _tmain( int argc, _TCHAR * argv[] )
    
#else
    
    #define XSMain( argc, argv )    int main( int argc, char * argv[] )
    
#endif

#define XSMainStart( argc, argv )                                               \
    XSMain( argc, argv )                                                        \
    {                                                                           \
        XSApplication_Start( argc, ( const char ** )argv );                     \
        XSFunctionStart()

#define XSMainEnd( returnValue )                                                \
        XSFunctionEnd( returnValue )                                            \
    }

#define XSFunctionStart()                                                       \
    {                                                                           \
        {                                                                       \
            XSUInteger  e;                                                      \
            XSException __xs_exception;                                         \
                                                                                \
            XSTry                                                               \
            {

#define XSFunctionEnd( returnValue )                                            \
            }                                                                   \
            XSCatch( e )                                                        \
            {                                                                   \
                    __xs_exception = XSExceptionCenter_GetException             \
                    (                                                           \
                        XSExceptionCenter_DefaultCenter(),                      \
                        e                                                       \
                    );                                                          \
                                                                                \
                    XSMemoryDebug_Disable();                                    \
                                                                                \
                    XSLog                                                       \
                    (                                                           \
                        "FATAL ERROR: uncaught exception: $@\n",                \
                        __xs_exception                                          \
                    );                                                          \
                    exit( EXIT_FAILURE );                                       \
            }                                                                   \
        }                                                                       \
        return returnValue;                                                     \
    }

#define XSThrow   for( ; ; longjmp( *( XSExceptionContext->e_env ), 1 ) ) XSExceptionContext->e = 

#define XSTry                                                   \
    {                                                           \
        jmp_buf * e_prev;                                       \
        jmp_buf   e_cur;                                        \
                                                                \
        e_prev                    = XSExceptionContext->e_env;  \
        XSExceptionContext->e_env = &e_cur;                     \
                                                                \
        if( setjmp( e_cur ) == 0 )                              \
        {                                                       \
            do

#define __XSCatch( action )                                                         \
            while( XSExceptionContext->caught = 0, XSExceptionContext->caught );    \
        }                                                                           \
        else                                                                        \
        {                                                                           \
            XSExceptionContext->caught = 1;                                         \
        }                                                                           \
                                                                                    \
        XSExceptionContext->e_env = e_prev;                                         \
    }                                                                               \
    if( !XSExceptionContext->caught || action )                                     \
    {}                                                                              \
    else

#define XSCatch( e ) __XSCatch( ( ( e ) = XSExceptionContext->e, 0 ) )

#if !defined( XS_EXTERN_C_BEGIN )
    #if defined( __cplusplus )
        
        /*!
         * @define      XS_EXTERN_C_BEGIN
         * @abstract    Substitution for 'extern "C" {' start
         */
        #define XS_EXTERN_C_BEGIN extern "C" {
        
        /*!
         * @define      XS_EXTERN_C_END
         * @abstract    Substitution for 'extern "C" {' end
         */
        #define XS_EXTERN_C_END              }
        
    #else
        #define XS_EXTERN_C_BEGIN
        #define XS_EXTERN_C_END
    #endif
#endif

XS_EXTERN_C_BEGIN

#include "XSMacrosTarget.h"

/*!
 * @define      XSSTR
 * @abstract    Creates an XSString instance from a C string
 * @param       s   A C string (char *)
 */
#define XSSTR( s ) XSAutorelease( XSString_InitWithCString( XSString_Alloc(), s ) )

/*!
 * @define      __XSFatalError
 * @abstract    Issues a fatal error message and aborts the program
 * @description Never call this macro directly. Use XSFatalError instead.
 * @param       FILE    The file name in which the error occured
 * @param       LINE    The line number in which the error occured
 * @param       ...     Message and format arguments
 */
#define __XSFatalError( FILE, LINE, ... )                                       \
    fprintf( stderr, "Fatal error: %s:%i\n", strrchr( FILE, '/' ) + 1, LINE );  \
    fprintf( stderr, __VA_ARGS__ );                                             \
    fprintf( stderr, "\n" );                                                    \
    pthread_exit( NULL );                                               \
    exit( EXIT_FAILURE );

/*!
 * @define      XSFatalError
 * @abstract    Issues a fatal error message and aborts the program
 * @param       ...     Message and format arguments
 */
#define XSFatalError( ... ) __XSFatalError( __FILE__, __LINE__, __VA_ARGS__ )

/*!
 * @define      XSEndian16_Swap
 * @abstract    Swap endiannes of a 16 bits value
 * @param       value   The value to swap
 */
#define XSEndian16_Swap( value )                        \
    (                                                   \
        ( ( ( UInt16 )( ( value ) & 0x00FF ) ) << 8 ) | \
        ( ( ( UInt16 )( ( value ) & 0xFF00 ) ) >> 8 )   \
    )

/*!
 * @define      XSEndian32_Swap
 * @abstract    Swap endiannes of a 32 bits value
 * @param       value   The value to swap
 */
#define XSEndian32_Swap( value )                                \
    (                                                           \
        ( ( ( UInt32 )( ( value ) & 0x000000FF ) ) << 24 ) |    \
        ( ( ( UInt32 )( ( value ) & 0x0000FF00 ) ) <<  8 ) |    \
        ( ( ( UInt32 )( ( value ) & 0x00FF0000 ) ) >>  8 ) |    \
        ( ( ( UInt32 )( ( value ) & 0xFF000000 ) ) >> 24 )      \
    )

/*!
 * @define      XSEndian64_Swap
 * @abstract    Swap endiannes of a 64 bits value
 * @param       value   The value to swap
 */
#define XSEndian64_Swap(value)                                          \
    (                                                                   \
        ( ( ( ( UInt64 )value ) << 56 ) & 0xFF00000000000000ULL )  |    \
        ( ( ( ( UInt64 )value ) << 40 ) & 0x00FF000000000000ULL )  |    \
        ( ( ( ( UInt64 )value ) << 24 ) & 0x0000FF0000000000ULL )  |    \
        ( ( ( ( UInt64 )value ) <<  8 ) & 0x000000FF00000000ULL )  |    \
        ( ( ( ( UInt64 )value ) >>  8 ) & 0x00000000FF000000ULL )  |    \
        ( ( ( ( UInt64 )value ) >> 24 ) & 0x0000000000FF0000ULL )  |    \
        ( ( ( ( UInt64 )value ) >> 40 ) & 0x000000000000FF00ULL )  |    \
        ( ( ( ( UInt64 )value ) >> 56 ) & 0x00000000000000FFULL )       \
    )

/*!
 * @define      WEAK_ATTRIBUTE
 * @abstract    Standardization of the weak compiler attribute
 * @description Not all compiler support this attribute, so it may be defined
 *              to nothing.
 */
#if defined( __GNUC__ ) && ( ( __GNUC__ >= 4 ) || ( ( __GNUC__ == 3 ) && ( __GNUC_MINOR__ >= 1 ) ) )
    #define WEAK_ATTRIBUTE __attribute__( ( weak ) )
#else
    #define WEAK_ATTRIBUTE
#endif

/*!
 * @define      WEAK_IMPORT_ATTRIBUTE
 * @abstract    Standardization of the weak import compiler attribute
 * @description Not all compiler support this attribute, so it may be defined
 *              to nothing.
 */
#if defined( __GNUC__ ) && ( ( __GNUC__ >= 4 ) || ( ( __GNUC__ == 3 ) && ( __GNUC_MINOR__ >= 1 ) ) )
    #define WEAK_IMPORT_ATTRIBUTE __attribute__( ( weak_import ) )
#elif defined(__MWERKS__) && ( __MWERKS__ >= 0x3205 )
    #define WEAK_IMPORT_ATTRIBUTE __attribute__( ( weak_import ) )
#else
    #define WEAK_IMPORT_ATTRIBUTE
#endif

/*!
 * @define      DEPRECATED_ATTRIBUTE
 * @abstract    Standardization of the deprecated compiler attribute
 * @description Not all compiler support this attribute, so it may be defined
 *              to nothing.
 */
#if defined( __GNUC__ ) && ( ( __GNUC__ >= 4 ) || ( ( __GNUC__ == 3 ) && ( __GNUC_MINOR__ >= 1 ) ) )
    #define DEPRECATED_ATTRIBUTE __attribute__( ( deprecated ) )
#else
    #define DEPRECATED_ATTRIBUTE
#endif

/*!
 * @define      UNAVAILABLE_ATTRIBUTE
 * @abstract    Standardization of the unavailable compiler attribute
 * @description Not all compiler support this attribute, so it may be defined
 *              to nothing.
 */
#if defined( __GNUC__ ) && ( ( __GNUC__ >= 4 ) || ( ( __GNUC__ == 3 ) && ( __GNUC_MINOR__ >= 1 ) ) )
    #define UNAVAILABLE_ATTRIBUTE __attribute__( ( unavailable ) )
#else
    #define UNAVAILABLE_ATTRIBUTE
#endif

/*!
 * @define      FORMAT_ATTRIBUTE
 * @abstract    Standardization of the format compiler attribute
 * @description Not all compiler support this attribute, so it may be defined
 *              to nothing.
 */
#if defined( __GNUC__ ) && ( ( __GNUC__ >= 4 ) || ( ( __GNUC__ == 3 ) && ( __GNUC_MINOR__ >= 1 ) ) )
    #define FORMAT_ATTRIBUTE( f, s, v ) __attribute__( ( format( f, s, v ) ) )
#else
    #define FORMAT_ATTRIBUTE( f, s, v )
#endif

/*!
 * @define      CONST_ATTRIBUTE
 * @abstract    Standardization of the const compiler attribute
 * @description Not all compiler support this attribute, so it may be defined
 *              to nothing.
 */
#if defined( __GNUC__ ) && ( ( __GNUC__ >= 4 ) || ( ( __GNUC__ == 3 ) && ( __GNUC_MINOR__ >= 1 ) ) )
    #define CONST_ATTRIBUTE __attribute__( ( const ) )
#else
    #define CONST_ATTRIBUTE
#endif

/*!
 * @define      NORETURN_ATTRIBUTE
 * @abstract    Standardization of the noreturn compiler attribute
 * @description Not all compiler support this attribute, so it may be defined
 *              to nothing.
 */
#if defined( __GNUC__ ) && ( ( __GNUC__ >= 4 ) || ( ( __GNUC__ == 3 ) && ( __GNUC_MINOR__ >= 1 ) ) )
    #define NORETURN_ATTRIBUTE __attribute__( ( noreturn ) )
#else
    #define NORETURN_ATTRIBUTE
#endif

/*!
 * @define      XS_INLINE
 * @abstract    Standardization of the inline compiler keywork
 */
#if !defined( XS_INLINE )
    #if defined( __GNUC__ ) && ( __GNUC__ == 4 ) && !defined( DEBUG )
        #define XS_INLINE static __inline__ __attribute__( ( always_inline ) )
    #elif defined( __GNUC__ )
        #define XS_INLINE static __inline__
    #elif defined( __MWERKS__ ) || defined( __cplusplus )
        #define XS_INLINE static inline
    #elif defined(_MSC_VER)
        #define XS_INLINE static __inline
    #endif
#endif

/*******************************************************************************
 * Standardization macros for different compilers
 ******************************************************************************/

#if !defined( NULL )
    #if defined( __GNUG__ )
        #define NULL __null
    #elif defined( __cplusplus )
        #define NULL 0
    #else
        #define NULL ( ( void * )0 )
    #endif
#endif

#if !defined( TRUE )
    #define TRUE    1
#endif

#if !defined( FALSE )
    #define FALSE	0
#endif

#ifndef __func__
    #ifdef _WIN32
        #if defined( __FUNCTION__ )
            #define __func__ __FUNCTION__
        #elif defined( __FUNCSIG__ )
            #define __func__ __FUNCSIG__
        #elif defined( __FUNCDNAME__ )
            #define __func__ __FUNCDNAME__
        #endif
    #elif __STDC_VERSION__ < 199901L
        #ifdef __GNUC__
            #if __GNUC__ >= 2
                #define __func__ __FUNCTION__
            #else
                #define __func__ "<unknown function>"
            #endif
        #else
            #define __func__ "<unknown function>"
        #endif
    #endif
#endif

XS_EXTERN_C_END

#endif /* _XS_MACROS_H_ */
