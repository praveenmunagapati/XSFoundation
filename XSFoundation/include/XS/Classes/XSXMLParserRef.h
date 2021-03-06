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
 * @header      XSXMLParserRef.h
 * @copyright   (c) 2010-2014 - Jean-David Gadina - www.xs-labs.com
 * @author      Jean-David Gadina - www.xs-labs.com
 * @abstract    XSXMLParser class
 * @discussion  ...
 */

#ifndef __XS_H__
#error "Please include '<XS/XS.h>' instead of this file!"
#endif

#ifndef __XS_CLASSES_XS_XML_PARSER_H__
#define __XS_CLASSES_XS_XML_PARSER_H__

#include <XS/XSTypes.h>
#include <XS/XSMacros.h>

/*!
 * @typedef     XSXMLParserRef
 * @abstract    Opaque type for XSXMLParser
 */
typedef const struct __XSXMLParser * XSXMLParserRef;

/*!
 * @typedef     XSXMLParser_ErrorHandlerMethod
 * @abstract    XSXMLParser error handler method
 * @param       handler     The handler object (receiver)
 * @param       parser      The XML parser object
 * @param       error       The error object
 */
typedef void ( * XSXMLParser_ErrorHandlerMethod )( XSObjectRef handler, XSXMLParserRef parser, XSErrorRef error );

/*!
 * @typedef     XSXMLParser_DocumentStartHandlerMethod
 * @abstract    XSXMLParser document start handler method
 * @param       handler     The handler object (receiver)
 * @param       parser      The XML parser object
 */
typedef void ( * XSXMLParser_DocumentStartHandlerMethod )( XSObjectRef handler, XSXMLParserRef parser );

/*!
 * @typedef     XSXMLParser_DocumentEndHandlerMethod
 * @abstract    XSXMLParser document end handler method
 * @param       handler     The handler object (receiver)
 * @param       parser      The XML parser object
 */
typedef void ( * XSXMLParser_DocumentEndHandlerMethod )( XSObjectRef handler, XSXMLParserRef parser );

/*!
 * @typedef     XSXMLParser_ElementStartHandlerMethod
 * @abstract    XSXMLParser element start handler method
 * @param       handler     The handler object (receiver)
 * @param       parser      The XML parser object
 * @param       e           The element's name
 * @param       ns          The element's namespace (may be NULL)
 * @param       attributes  The element's attributes (may be NULL)
 */
typedef void ( * XSXMLParser_ElementStartHandlerMethod )( XSObjectRef handler, XSXMLParserRef parser, XSStringRef e, XSStringRef ns, XSDictionaryRef attributes );

/*!
 * @typedef     XSXMLParser_ElementEndHandlerMethod
 * @abstract    XSXMLParser element end handler method
 * @param       handler     The handler object (receiver)
 * @param       parser      The XML parser object
 * @param       e           The element's name
 * @param       ns          The element's namespace (may be NULL)
 */
typedef void ( * XSXMLParser_ElementEndHandlerMethod )( XSObjectRef handler, XSXMLParserRef parser, XSStringRef e, XSStringRef ns );

/*!
 * @typedef     XSXMLParser_ErrorHandlerMethod
 * @abstract    XSXMLParser character handler method
 * @param       handler     The handler object (receiver)
 * @param       parser      The XML parser object
 * @param       characters  The characters
 */
typedef void ( * XSXMLParser_CharacterHandlerMethod )( XSObjectRef handler, XSXMLParserRef parser, XSStringRef characters );

/*!
 * @typedef     XSXMLParser_CDataHandlerMethod
 * @abstract    XSXMLParser CData handler method
 * @param       handler     The handler object (receiver)
 * @param       parser      The XML parser object
 * @param       cData       The bytes of the CData section
 */
typedef void ( * XSXMLParser_CDataHandlerMethod )( XSObjectRef handler, XSXMLParserRef parser, XSDataRef cData );

/*!
 * @typedef     XSXMLParser_WhitespaceHandlerMethod
 * @abstract    XSXMLParser whitespace handler method
 * @param       handler     The handler object (receiver)
 * @param       parser      The XML parser object
 * @param       whitespace  The whitespace characters
 */
typedef void ( * XSXMLParser_WhitespaceHandlerMethod )( XSObjectRef handler, XSXMLParserRef parser, XSStringRef whitespace );

/*!
 * @typedef     XSXMLParser_CommentHandlerMethod
 * @abstract    XSXMLParser comment handler method
 * @param       handler     The handler object (receiver)
 * @param       parser      The XML parser object
 * @param       comment     The comment characters
 */
typedef void ( * XSXMLParser_CommentHandlerMethod )( XSObjectRef handler, XSXMLParserRef parser, XSStringRef comment );

/*!
 * @typedef     XSXMLParser_ProcessingInstructionHandlerMethod
 * @abstract    XSXMLParser processing instruction handler method
 * @param       handler     The handler object (receiver)
 * @param       parser      The XML parser object
 * @param       target      The processing instruction target
 * @param       data        The processing instruction data
 */
typedef void ( * XSXMLParser_ProcessingInstructionHandlerMethod )( XSObjectRef handler, XSXMLParserRef parser, XSStringRef target, XSDataRef data );

/*!
 * @function    XSXMLParser_GetClassID
 * @abstract    Gets the class ID for XSXMLParser
 * @return      The class ID for XSXMLParser
 */
XS_EXPORT XSStatic XSClassID XSXMLParser_GetClassID( void );

/*!
 * @function    XSXMLParser_XMLParserWithData
 * @abstract    Gets an XML parser object with specific data
 * @param       data        The XML data
 * @return      The XML parser object
 */
XS_EXPORT XSStatic XSAutoreleased XSXMLParserRef XSXMLParser_XMLParserWithData( XSDataRef data );

/*!
 * @function    XSXMLParser_CreateWithData
 * @abstract    Creates an XML parser object with specific data
 * @param       data        The XML data
 * @return      The XML parser object
 */
XS_EXPORT XSStatic XSXMLParserRef XSXMLParser_CreateWithData( XSDataRef data );

/*!
 * @function    XSXMLParser_Parse
 * @abstract    Parses the XML data
 * @param       parser      The XML parser object
 * @return      True if the parsing was sucessfull, otherwise false
 */
XS_EXPORT bool XSXMLParser_Parse( XSXMLParserRef parser );

/*!
 * @function    XSXMLParser_AbortParsing
 * @param       parser      The XML parser object
 * @abstract    Aborts parsing the XML data
 */
XS_EXPORT void XSXMLParser_AbortParsing( XSXMLParserRef parser );

/*!
 * @function    XSXMLParser_GetParserError
 * @abstract    Gets the current parse error, if any
 * @param       parser      The XML parser object
 * @return      The error object for the parse error
 */
XS_EXPORT XSErrorRef XSXMLParser_GetParserError( XSXMLParserRef parser );

/*!
 * @function    XSXMLParser_GetCurrentLineNumber
 * @abstract    Gets the current line number beeing parsed
 * @param       parser      The XML parser object
 * @return      The line number beeing parsed
 */
XS_EXPORT XSUInteger XSXMLParser_GetCurrentLineNumber( XSXMLParserRef parser );

/*!
 * @function    XSXMLParser_GetCurrentColumnNumber
 * @abstract    Gets the current column number beeing parsed
 * @param       parser      The XML parser object
 * @return      The column number beeing parsed
 */
XS_EXPORT XSUInteger XSXMLParser_GetCurrentColumnNumber( XSXMLParserRef parser );

/*!
 * @function    XSXMLParser_SetHandlerObject
 * @abstract    Sets the handler object for XML parsing callbacks
 * @param       parser      The XML parser object
 * @param       handler     The handler object
 */
XS_EXPORT void XSXMLParser_SetHandlerObject( XSXMLParserRef parser, XSObjectRef handler );

/*!
 * @function    XSXMLParser_SetErrorHandler
 * @abstract    Sets the error handler method
 * @param       parser      The XML parser object
 * @param       method      The method
 * @see         XSXMLParser_ErrorHandlerMethod
 */
XS_EXPORT void XSXMLParser_SetErrorHandler( XSXMLParserRef parser, XSXMLParser_ErrorHandlerMethod method );

/*!
 * @function    XSXMLParser_SetDocumentStartHandler
 * @abstract    Sets the document start handler method
 * @param       parser      The XML parser object
 * @param       method      The method
 * @see         XSXMLParser_DocumentStartHandlerMethod
 */
XS_EXPORT void XSXMLParser_SetDocumentStartHandler( XSXMLParserRef parser, XSXMLParser_DocumentStartHandlerMethod method );

/*!
 * @function    XSXMLParser_SetDocumentEndHandler
 * @abstract    Sets the document end handler method
 * @param       parser      The XML parser object
 * @param       method      The method
 * @see         XSXMLParser_DocumentEndHandlerMethod
 */
XS_EXPORT void XSXMLParser_SetDocumentEndHandler( XSXMLParserRef parser, XSXMLParser_DocumentEndHandlerMethod method );

/*!
 * @function    XSXMLParser_SetElementStartHandler
 * @abstract    Sets the element start handler method
 * @param       parser      The XML parser object
 * @param       method      The method
 * @see         XSXMLParser_ElementStartHandlerMethod
 */
XS_EXPORT void XSXMLParser_SetElementStartHandler( XSXMLParserRef parser, XSXMLParser_ElementStartHandlerMethod method );

/*!
 * @function    XSXMLParser_SetElementEndHandler
 * @abstract    Sets the element end handler method
 * @param       parser      The XML parser object
 * @param       method      The method
 * @see         XSXMLParser_ElementEndHandlerMethod
 */
XS_EXPORT void XSXMLParser_SetElementEndHandler( XSXMLParserRef parser, XSXMLParser_ElementEndHandlerMethod method );

/*!
 * @function    XSXMLParser_SetCharacterHandler
 * @abstract    Sets the character handler method
 * @param       parser      The XML parser object
 * @param       method      The method
 * @see         XSXMLParser_CharacterHandlerMethod
 */
XS_EXPORT void XSXMLParser_SetCharacterHandler( XSXMLParserRef parser, XSXMLParser_CharacterHandlerMethod method );

/*!
 * @function    XSXMLParser_SetCDataHandler
 * @abstract    Sets the CData handler method
 * @param       parser      The XML parser object
 * @param       method      The method
 * @see         XSXMLParser_CDataHandlerMethod
 */
XS_EXPORT void XSXMLParser_SetCDataHandler( XSXMLParserRef parser, XSXMLParser_CDataHandlerMethod method );

/*!
 * @function    XSXMLParser_SetWhitespaceHandler
 * @abstract    Sets the whitespace handler method
 * @param       parser      The XML parser object
 * @param       method      The method
 * @see         XSXMLParser_WhitespaceHandlerMethod
 */
XS_EXPORT void XSXMLParser_SetWhitespaceHandler( XSXMLParserRef parser, XSXMLParser_WhitespaceHandlerMethod method );

/*!
 * @function    XSXMLParser_SetCommentHandler
 * @abstract    Sets the comment handler method
 * @param       parser      The XML parser object
 * @param       method      The method
 * @see         XSXMLParser_CommentHandlerMethod
 */
XS_EXPORT void XSXMLParser_SetCommentHandler( XSXMLParserRef parser, XSXMLParser_CommentHandlerMethod method );

/*!
 * @function    XSXMLParser_SetProcessingInstructionHandler
 * @abstract    Sets the processing instruction handler method callback
 * @param       parser      The XML parser object
 * @param       method      The method callback
 * @see         XSXMLParser_ProcessingInstructionHandlerMethod
 */
XS_EXPORT void XSXMLParser_SetProcessingInstructionHandler( XSXMLParserRef parser, XSXMLParser_ProcessingInstructionHandlerMethod method );

#endif /* __XS_CLASSES_XS_XML_PARSER_H__ */
