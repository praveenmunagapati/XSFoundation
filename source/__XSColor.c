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
 * @file        __XSColor.c
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    ...
 */

#include "XS.h"
#include "__XSColor.h"

/*!
 * @var         __XSColorClass
 * @abstract    Runtime class definition
 */
static const XSClassInfos __XSColorClass =
{
    "XSColor",              /* Class name */
    sizeof( __XSColor ),    /* Object size */
    NULL,                   /* Constructor */
    NULL,                   /* Destructor */
    NULL,                   /* Object copy */
    NULL                    /* Object description */
};

/*!
 * @var         __XSColorClassID
 * @abstract    Type ID for the runtine class
 */
static XSClassID __XSColorClassID;

/*!
 * @function    __XSColor_Initialize
 * @abstract    Runtime initialization
 * @result      void
 */
void __XSColor_Initialize( void )
{
    __XSColorClassID = XSRuntime_RegisterClass( &__XSColorClass );
}

/*!
 * @function    __XSColor_Alloc
 * @abstract    Object allocator
 * @result      A pointer to the allocated object
 */
__XSColor * __XSColor_Alloc( void )
{
    return ( __XSColor * )XSRuntime_CreateInstance( __XSColorClassID );
}

/*!
 * @function    __XSColor_RGBToHSL
 * @abstract    Converts the RGB components to HSV
 * @param       color   The color object
 * @result      void
 */
void __XSColor_RGBToHSL( __XSColor * color )
{
    XSFloat h;
    XSFloat s;
    XSFloat l;
    XSFloat r;
    XSFloat g;
    XSFloat b;
    XSFloat max;
    XSFloat min;
    XSFloat delta;
    XSFloat r_delta;
    XSFloat g_delta;
    XSFloat b_delta;
    
    h = 0;
    s = 0;
    l = 0;
    r = color->red   / 255;
    g = color->green / 255;
    b = color->blue  / 255;
    
    max = MAX( r, MAX( g, b ) );
    min = MIN( r, MIN( g, b ) );
    
    delta = max - min;
    l     = ( max + min ) / 2;
    
    if( delta == 0 )
    {
        h = 0;
        s = 0;
    }
    else
    {
        if( l < 0.5 )
        {
            s = delta / ( max + min );
        }
        else
        {
            s = delta / ( 2 - max - min );
        }
        
        r_delta = ( ( ( max - r ) / 6 ) + ( delta / 2 ) ) / delta;
        g_delta = ( ( ( max - g ) / 6 ) + ( delta / 2 ) ) / delta;
        b_delta = ( ( ( max - b ) / 6 ) + ( delta / 2 ) ) / delta;
        
        if( r_delta == max )
        {
            h = b_delta - g_delta;
        }
        else if( g == max )
        {
            h = ( 1 / 3 ) + r_delta - b_delta;
        }
        else if( b == max )
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
    
    color->hue        = h * 360;
    color->saturation = s * 100;
    color->luminance  = l * 100;
}

/*!
 * @function    __XSColor_RGBToHSV
 * @abstract    Converts the RGB components to HSL
 * @param       color   The color object
 * @result      void
 */
void __XSColor_RGBToHSV( __XSColor * color )
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
    
    h = 0;
    s = 0;
    v = 0;
    r = color->red   / 255;
    g = color->green / 255;
    b = color->blue  / 255;
    
    max = MAX( r, MAX( g, b ) );
    min = MIN( r, MIN( g, b ) );
    
    delta = max - min;
    v     = max;
    
    if( delta == 0 )
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
        
        if( r == max )
        {
            h = b_delta - g_delta;
        }
        else if( g == max )
        {
            h = ( 1 / 3 ) + r_delta - b_delta;
        }
        else if( b == max )
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
    
    color->hue        = h * 360;
    color->saturation = s * 100;
    color->value      = v * 100;
}

/*!
 * @function    __XSColor_HSVToRGB
 * @abstract    Converts the HSV components to RGB
 * @param       color   The color object
 * @result      void
 */
void __XSColor_HSVToRGB( __XSColor * color )
{
    XSFloat   r;
    XSFloat   g;
    XSFloat   b;
    XSFloat   h;
    XSFloat   s;
    XSFloat   v;
    XSFloat   c1;
    XSFloat   c2;
    XSFloat   c3;
    XSFloat   vr;
    XSFloat   vg;
    XSFloat   vb;
    XSFloat   vh;
    XSInteger ih;
    
    r = 0;
    g = 0;
    b = 0;
    h = color->hue        / 360;
    s = color->saturation / 100;
    v = color->value      / 100;
    
    if( s == 0 )
    {
        r = v * 255;
        g = v * 255;
        b = v * 255;
    }
    else
    {
        vh = h * 6;
        ih = ( XSInteger )vh;
        
        c1 = v * ( 1 - s );
        c2 = v * ( 1 - s * ( vh - ih ) );
        c3 = v * ( 1 - s * ( 1 - ( vh - ih ) ) );
        
        if( ih == 0 )
        {
            vr = v;
            vg = c3;
            vb = c1;
        }
        else if( ih == 1 )
        {
            vr = c2;
            vg = v;
            vb = c1;
        }
        else if( ih == 2 )
        {
            vr = c1;
            vg = v;
            vb = c3;
        }
        else if( ih == 3 )
        {
            vr = c1;
            vg = c2;
            vb = v;
            
        }
        else if( ih == 4 )
        {
            vr = c3;
            vg = c1;
            vb = v;
        }
        else
        {
            vr = v;
            vg = c1;
            vb = c2;
        }
        
        color->red   = vr * 255;
        color->green = vg * 255;
        color->blue  = vb * 255;
    }
}

/*!
 * @function    __XSColor_HSVToHSL
 * @abstract    Converts the HSV components to HSL
 * @param       color   The color object
 * @result      void
 */
void __XSColor_HSVToHSL( __XSColor * color )
{
    __XSColor_HSVToRGB( color );
    __XSColor_RGBToHSL( color );
}

/*!
 * @function    __XSColor_HSLToRGB
 * @abstract    Converts the HSL components to RGB
 * @param       color   The color object
 * @result      void
 */
void __XSColor_HSLToRGB( __XSColor * color )
{
    XSFloat    r;
    XSFloat    g;
    XSFloat    b;
    XSFloat    h;
    XSFloat    s;
    XSFloat    l;
    XSFloat    v;
    XSFloat    c1;
    XSFloat    c2;
    XSFloat    vh;
    XSUInteger i;
    
    r  = 0;
    g  = 0;
    b  = 0;
    vh = 0;
    h  = color->hue        / 360;
    s  = color->saturation / 100;
    l  = color->luminance  / 100;
    
    if( s == 0 )
    {
        r = l * 255;
        g = l * 255;
        b = l * 255;
    }
    else
    {
        if( l < 0.5 )
        {
            c2 = l * ( 1 + s );
        }
        else
        {
            c2 = ( l + s ) - ( s * l );
        }
        
        c1 = 2 * l - c2;
        
        for( i = 0; i < 3; i++ )
        {
            switch( i )
            {
                case 0: vh = h + ( 1 / 3 ); break;
                case 1: vh = h;             break;
                case 2: vh = h - ( 1 / 3 ); break;
            }
            
            if( vh < 0 )
            {
                vh += 1;
            }
            else if( vh > 1 )
            {
                vh -= 1;
            }
            
            if( ( 6 * vh ) < 1 )
            {
                v = c1 + ( c2 - c1 ) * 6 * vh;
            }
            else if( ( 2 * vh ) < 1 )
            {
                v = c2;
            }
            else if( ( 3 * vh ) < 2 )
            {
                v = c1 + ( c2 - c1 ) * ( ( 2 / 3 ) - vh ) * 6;
            }
            else
            {
                v = c1;
            }
            
            switch( i )
            {
                case 0: r = v; break;
                case 1: g = v; break;
                case 2: b = v; break;
            }
        }
        
        color->red   = r * 255;
        color->green = g * 255;
        color->blue  = b * 255;
    }
}

/*!
 * @function    __XSColor_HSLToHSV
 * @abstract    Converts the HSL components to HSV
 * @param       color   The color object
 * @result      void
 */
void __XSColor_HSLToHSV( __XSColor * color )
{
    __XSColor_HSLToRGB( color );
    __XSColor_RGBToHSV( color );
}
