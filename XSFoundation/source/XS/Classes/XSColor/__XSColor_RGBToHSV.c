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
 * @file        __XSColor_RGBToHSV.c
 * @copyright   (c) 2010-2014 - Jean-David Gadina - www.xs-labs.com
 * @author      Jean-David Gadina - www.xs-labs.com
 * @abstract    Definition for __XSColor_RGBToHSV
 */

#include <XS/XS.h>
#include <XS/__private/Classes/XSColorRef.h>

void __XSColor_RGBToHSV( XSColorRef object )
{
    XSFloat h;
    XSFloat s;
    XSFloat v;
    XSFloat r;
    XSFloat g;
    XSFloat b;
    XSFloat max;
    XSFloat min;
    XSFloat delta;
    XSFloat r_delta;
    XSFloat g_delta;
    XSFloat b_delta;
    
    if( object == NULL )
    {
        return;
    }
    
    XSRecursiveLock_Lock( object->lock );
    
    h = 0;
    r = object->r;
    g = object->g;
    b = object->b;
    
    max = XS_MAX( r, XS_MAX( g, b ) );
    min = XS_MIN( r, XS_MIN( g, b ) );
    
    delta = max - min;
    v     = max;
    
    if( XSFloat_IsZero( delta ) )
    {
        h = 0;
        s = 0;
    }
    else
    {
        s = delta / max;
        
        r_delta = ( ( ( max - r ) / 6 ) + ( delta / 2 ) ) / delta;
        g_delta = ( ( ( max - g ) / 6 ) + ( delta / 2 ) ) / delta;
        b_delta = ( ( ( max - b ) / 6 ) + ( delta / 2 ) ) / delta;
        
        if( XSFloat_IsEqualToFloat( r, max ) )
        {
            h = b_delta - g_delta;
        }
        else if( XSFloat_IsEqualToFloat( g, max ) )
        {
            h = ( 1 / 3 ) + r_delta - b_delta;
        }
        else if( XSFloat_IsEqualToFloat( b, max ) )
        {
            h = ( 2 / 3 ) + g_delta - r_delta;
        }
        
        if( h < 0 )
        {
            h += 1;
        }
        else if( h > 1 )
        {
            h -= 1;
        }
    }
    
    object->h = h;
    object->s = s;
    object->v = v;
    
    XSRecursiveLock_Unlock( object->lock );
}
