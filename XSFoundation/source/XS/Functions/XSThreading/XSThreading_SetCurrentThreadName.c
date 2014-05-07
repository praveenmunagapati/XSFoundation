/*******************************************************************************
 * XSFoundation - XEOS C Foundation Library
 * 
 * Copyright (c) 2010-2014, Jean-David Gadina - www.xs-labs.com
 * All rights reserved.
 * 
 * XEOS Software License - Version 1.0 - December 21, 2012
 * 
 * Permission is hereby granted, free of charge, to any person or organisation
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to deal in the Software, with or without
 * modification, without restriction, including without limitation the rights
 * to use, execute, display, copy, reproduce, transmit, publish, distribute,
 * modify, merge, prepare derivative works of the Software, and to permit
 * third-parties to whom the Software is furnished to do so, all subject to the
 * following conditions:
 * 
 *      1.  Redistributions of source code, in whole or in part, must retain the
 *          above copyright notice and this entire statement, including the
 *          above license grant, this restriction and the following disclaimer.
 * 
 *      2.  Redistributions in binary form must reproduce the above copyright
 *          notice and this entire statement, including the above license grant,
 *          this restriction and the following disclaimer in the documentation
 *          and/or other materials provided with the distribution, unless the
 *          Software is distributed by the copyright owner as a library.
 *          A "library" means a collection of software functions and/or data
 *          prepared so as to be conveniently linked with application programs
 *          (which use some of those functions and data) to form executables.
 * 
 *      3.  The Software, or any substancial portion of the Software shall not
 *          be combined, included, derived, or linked (statically or
 *          dynamically) with software or libraries licensed under the terms
 *          of any GNU software license, including, but not limited to, the GNU
 *          General Public License (GNU/GPL) or the GNU Lesser General Public
 *          License (GNU/LGPL).
 * 
 *      4.  All advertising materials mentioning features or use of this
 *          software must display an acknowledgement stating that the product
 *          includes software developed by the copyright owner.
 * 
 *      5.  Neither the name of the copyright owner nor the names of its
 *          contributors may be used to endorse or promote products derived from
 *          this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT OWNER AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE, TITLE AND NON-INFRINGEMENT ARE DISCLAIMED.
 * 
 * IN NO EVENT SHALL THE COPYRIGHT OWNER, CONTRIBUTORS OR ANYONE DISTRIBUTING
 * THE SOFTWARE BE LIABLE FOR ANY CLAIM, DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN ACTION OF CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF OR IN CONNECTION WITH
 * THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

/* $Id$ */

/*!
 * @file        XSThreading_SetCurrentThreadName.c
 * @copyright   (c) 2010-2014 - Jean-David Gadina - www.xs-labs.com
 * @author      Jean-David Gadina - www.xs-labs.com
 * @abstract    Definition for XSThreading_SetCurrentThreadName
 */

#include <XS/XS.h>
#include <XS/__private/Functions/XSThreading.h>

#ifdef _WIN32

/*!
 * @define      __MS_VC_EXCEPTION
 * @abstract    Exception number to set the thread name
 */
#define __MS_VC_EXCEPTION   0x406D1388

#pragma pack( push, 8 )

/*!
 * @typedef     THREADNAME_INFO
 * @abstract    Thread name info structure
 */
typedef struct tagTHREADNAME_INFO
{
   DWORD  dwType;       /*! Must be 0x1000 */
   LPCSTR szName;       /*! Pointer to name (in user addr space) */
   DWORD  dwThreadID;   /*! Thread ID (-1=caller thread) */
   DWORD  dwFlags;      /*! Reserved for future use, must be zero */
}
THREADNAME_INFO;

#pragma pack( pop )

#endif

void XSThreading_SetCurrentThreadName( const char * name )
{
    #if defined( _WIN32 )
    
    THREADNAME_INFO info;
    
    info.dwType     = ( DWORD )0x1000;
    info.szName     = ( LPCSTR )name;
    info.dwThreadID = ( DWORD )-1;
    info.dwFlags    = ( DWORD )0;
    
    /* See: http://msdn.microsoft.com/en-us/library/xcb2z8hs.aspx */
    __try
    {
        RaiseException( __MS_VC_EXCEPTION, 0, sizeof( info ) / sizeof( ULONG_PTR ), ( ULONG_PTR * )&info );
    }
    __except( EXCEPTION_EXECUTE_HANDLER )
    {}
    
    #elif defined( __APPLE__ )
    
    pthread_setname_np( name );
    
    #elif defined( __linux )
    
    pthread_setname_np( pthread_self(), name );
    
    #elif defined( __unix__ )
    
    pthread_set_name_np( pthread_self(), name );
    
    #elif defined( __XEOS__ )
    
    ( void )name;
    
    #else
    
    ( void )name;
    
    #endif
}
