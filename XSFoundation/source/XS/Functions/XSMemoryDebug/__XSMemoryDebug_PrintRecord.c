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
 * @file        __XSMemoryDebug_PrintRecord.c
 * @copyright   (c) 2010-2014 - Jean-David Gadina - www.xs-labs.com
 * @author      Jean-David Gadina - www.xs-labs.com
 * @abstract    Definition for __XSMemoryDebug_PrintRecord
 */

#include <XS/XS.h>
#include <XS/__private/Functions/XSMemoryDebug.h>

void __XSMemoryDebug_PrintRecord( __XSMemoryDebug_Record * record )
{
    const char * allocFile;
    const char * allocFunc;
    const char * freeFile;
    const char * freeFunc;
    const char * pos1;
    const char * pos2;
    const char * classname;
    
    #ifndef DEBUG
    
    ( void )record;
    ( void )allocFile;
    ( void )allocFunc;
    ( void )freeFile;
    ( void )freeFunc;
    ( void )pos1;
    ( void )pos2;
    ( void )classname;
    
    return;
    
    #endif
    
    if( record == NULL || record->object == NULL )
    {
        return;
    }
    
    allocFile = record->allocFile;
    allocFunc = record->allocFunc;
    freeFile  = record->freeFile;
    freeFunc  = record->freeFunc;
    classname = XSRuntime_GetClassName( record->classID );
    
    #ifdef _WIN32
    pos1 = ( allocFile != NULL ) ? strrchr( allocFile, '\\' ) : NULL;
    pos2 = ( freeFile  != NULL ) ? strrchr( freeFile,  '\\' ) : NULL;
    #else
    pos1 = ( allocFile != NULL ) ? strrchr( allocFile, '/' ) : NULL;
    pos2 = ( freeFile  != NULL ) ? strrchr( freeFile, '/' )  : NULL;
    #endif
    
    if( pos1 != NULL ) { allocFile = pos1 + 1; }
    if( pos2 != NULL ) { freeFile  = pos2 + 1; }
    
    fprintf
    (
        stderr,
        "\n"
        "#-------------------------------------------------------------------------------\n"
        "# Memory object ID:      %lu\n"
        "# Class ID:              %lu - %s\n"
        "# Allocation size:       %lu bytes\n"
        "# Data pointer:          %p\n",
        ( unsigned long )( record->allocID ),
        ( unsigned long )( record->classID ),
        ( classname == NULL ) ? "N/A" : classname,
        ( unsigned long )( record->size ),
        record->data
    );
    
    if( allocFile != NULL )
    {
        fprintf
        (
            stderr,
            "# Allocated in file:     %s:%i\n",
            allocFile,
            record->allocLine
        );
    }
    else
    {
        fprintf
        (
            stderr,
            "# Allocated in file:     N/A\n"
        );
    }
    
    fprintf
    (
        stderr,
        "# Allocated in function: %s\n"
        "# Allocated in thread:   %lX\n",
        ( allocFunc == NULL ) ? "N/A" : allocFunc,
        ( unsigned long )( record->allocThreadID )
    );
    
    if( record->freed )
    {
        fprintf
        (
            stderr,
            "# Freed in file:         %s:%i\n"
            "# Freed in function:     %s\n"
            "# Freed in thread:       %lX\n",
            freeFile,
            record->freeLine,
            freeFunc,
            ( unsigned long )( record->freeThreadID )
        );
    }
    else
    {
        fprintf
        (
            stderr,
            "# Freed in file:         N/A\n"
            "# Freed in function:     N/A\n"
            "# Freed in thread:       N/A\n"
        );
    }
    
    fprintf
    (
        stderr,
        "#-------------------------------------------------------------------------------\n"
        "\n"
    );
}
