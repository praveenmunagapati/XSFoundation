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
 * @header      XSColorRef.h
 * @copyright   (c) 2010-2014 - Jean-David Gadina - www.xs-labs.com
 * @author      Jean-David Gadina - www.xs-labs.com
 * @abstract    Private definitions for XSColorRef.h
 * @discussion  ...
 */

#ifndef __XS_H__
#error "Please include '<XS/XS.h>' instead of this file!"
#endif

#ifndef __XS___PRIVATE_CLASSES_XS_COLOR_H__
#define __XS___PRIVATE_CLASSES_XS_COLOR_H__

#include <XS/XSTypes.h>
#include <XS/XSMacros.h>

/*!
 * @struct      __XSColor
 * @abstract    Structure for XSColor
 */
struct __XSColor
{
    XSFloat             r;      /*! The red component */
    XSFloat             g;      /*! The green component */
    XSFloat             b;      /*! The blue component */
    XSFloat             h;      /*! The hue component */
    XSFloat             s;      /*! The saturation component */
    XSFloat             l;      /*! The luminance component */
    XSFloat             v;      /*! The value component */
    XSFloat             a;      /*! The alpha component */
    XSRecursiveLockRef  lock;   /*! The lock for thread-safety */
};

/*!
 * @var         __XSColor_ClassID
 * @abstract    Class ID
 */
XS_EXTERN XSClassID __XSColor_ClassID;

/*!
 * @var         __XSColor_Class
 * @abstract    Class info
 */
XS_EXTERN XSClassInfo __XSColor_Class;

/*!
 * @function    __XSColor_Initialize
 * @abstract    Class initializer
 */
XSStatic void __XSColor_Initialize( void );

/*!
 * @function    __XSColor_Constructor
 * @abstract    Class constructor callback
 * @param       object      The object beeing construct
 * @return      The new object
 */
XSColorRef __XSColor_Constructor( XSColorRef object );

/*!
 * @function    __XSColor_Destructor
 * @abstract    Class destructor callback
 * @param       object      The object beeing destruct
 */
void __XSColor_Destructor( XSColorRef object );

/*!
 * @function    __XSColor_Copy
 * @abstract    Class copy callback
 * @param       source      The object to copy
 * @param       destination The object beeing copied
 * @result      The copied object
 */
XSColorRef __XSColor_Copy( XSColorRef source, XSColorRef destination );

/*!
 * @function    __XSColor_Equals
 * @abstract    Class equals callback
 * @param       object1     The first object to compare
 * @param       object2     The second object to compare
 * @return      True if both objects are equals, otherwise false
 */
bool __XSColor_Equals( XSColorRef object1, XSColorRef object2 );

/*!
 * @function    __XSColor_ToString
 * @abstract    Class to-string callback
 * @param       object      The object for which to get a description
 * @return      The object's description
 */
const char * __XSColor_ToString( XSColorRef object );

/*!
 * @function    __XSColor_ConvertFromRGB
 * @abstract    Converts all values of a color object from RGB values
 * @param       object      The color object
 */
void __XSColor_ConvertFromRGB( XSColorRef object );

/*!
 * @function    __XSColor_ConvertFromHSL
 * @abstract    Converts all values of a color object from HSL values
 * @param       object      The color object
 */
void __XSColor_ConvertFromHSL( XSColorRef object );

/*!
 * @function    __XSColor_ConvertFromHSV
 * @abstract    Converts all values of a color object from HSV values
 * @param       object      The color object
 */
void __XSColor_ConvertFromHSV( XSColorRef object );

/*!
 * @function    __XSColor_RGBToHSL
 * @abstract    Converts RGB values of a color object to HSL values
 * @param       object      The color object
 */
void __XSColor_RGBToHSL( XSColorRef object );

/*!
 * @function    __XSColor_RGBToHSV
 * @abstract    Converts RGB values of a color object to HSV values
 * @param       object      The color object
 */
void __XSColor_RGBToHSV( XSColorRef object );

/*!
 * @function    __XSColor_HSLToRGB
 * @abstract    Converts HSL values of a color object to RGB values
 * @param       object      The color object
 */
void __XSColor_HSLToRGB( XSColorRef object );

/*!
 * @function    __XSColor_HSVToRGB
 * @abstract    Converts HSV values of a color object to RGB values
 * @param       object      The color object
 */
void __XSColor_HSVToRGB( XSColorRef object );

/*!
 * @function    __XSColor_Create
 * @abstract    Creates an XSColor object
 * @return      The XSColor object
 */
XSStatic struct __XSColor * __XSColor_Create( void );

#endif /* __XS___PRIVATE_CLASSES_XS_COLOR_H__ */
