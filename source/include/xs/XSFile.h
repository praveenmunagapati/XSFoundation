/*******************************************************************************
 * Copyright (c) 2010, Jean-David Gadina <macmade@eosgarden.com>
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
 * @header      
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    
 */

#ifndef _XS_FILE_H_
#define _XS_FILE_H_
#pragma once

#include "XSMacros.h"

XS_EXTERN_C_BEGIN

#include "XS.h"

typedef struct XSFile * XSFileRef;

extern XSFileRef XSStdin;
extern XSFileRef XSStdout;
extern XSFileRef XSStderr;

XSFileRef    XSFile_Open( const char * filename, const char * mode );
XSInteger    XSFile_Flush( XSFileRef file );
XSInteger    XSFile_Close( XSFileRef file );
XSInteger    XSFile_Printf( XSFileRef file, const char * format, ... );
XSInteger    XSFile_VPrintf( XSFileRef file, const char * format, va_list arg );
XSInteger    XSFile_Getc( XSFileRef file );
XSInteger    XSFile_Putc( XSInteger c, XSFileRef file );
XSInteger    XSFile_Puts( const char * s, XSFileRef file );
size_t       XSFile_Read( void * ptr, size_t size, size_t nobj, XSFileRef file );
size_t       XSFile_Write( const void * ptr, size_t size, size_t nobj, XSFileRef file );
XSInteger    XSFile_Seek( XSFileRef file, XSInteger offset, XSInteger origin );
XSInteger    XSFile_Tell( XSFileRef file );
void         XSFile_Rewind( XSFileRef file );
XSInteger    XSFile_GetPos( XSFileRef file, fpos_t * ptr );
XSInteger    XSFile_SetPos( XSFileRef file, const fpos_t * ptr );
void         XSFile_ClearErr( XSFileRef file );
XSInteger    XSFile_EndOfFile( XSFileRef file );
XSInteger    XSFile_Error( XSFileRef file );
const char * XSFile_Filename( XSFileRef file );
const char * XSFile_OpenMode( XSFileRef file );
BOOL         XSFile_IsReadable( XSFileRef file );
BOOL         XSFile_IsWriteable( XSFileRef file );
BOOL         XSFile_Copy( char * name, char * new_name );
XSInteger    XSFile_GetBit( XSFileRef file );
XSInteger    XSFile_PutBit( XSFileRef file, uint8_t bit );
XSInteger    XSFile_GetBits( XSFileRef file, XSUInteger count );
XSInteger    XSFile_PutBits( XSFileRef file, uint64_t bits, XSUInteger count );
dev_t        XSFile_DeviceID( XSFileRef file );
ino_t        XSFile_SerialNumber( XSFileRef file );
nlink_t      XSFile_NumberOfLinks( XSFileRef file );
uid_t        XSFile_UID( XSFileRef file );
gid_t        XSFile_GID( XSFileRef file );
size_t       XSFile_Size( XSFileRef file );
XSFloat      XSFile_HumanReadableSize( XSFileRef file, char unit[] );
time_t       XSFile_AccessTime( XSFileRef file );
time_t       XSFile_ModifictaionTime( XSFileRef file );
time_t       XSFile_CreationTime( XSFileRef file );
BOOL         XSFile_IsBlockDevice( XSFileRef file );
BOOL         XSFile_IsCharacterDevice( XSFileRef file );
BOOL         XSFile_IsFIFO( XSFileRef file );
BOOL         XSFile_IsRegularFile( XSFileRef file );
BOOL         XSFile_IsDirectory( XSFileRef file );
BOOL         XSFile_IsLink( XSFileRef file );
BOOL         XSFile_IsSocket( XSFileRef file );
BOOL         XSFile_IsUserReadable( XSFileRef file );
BOOL         XSFile_IsUserWriteable( XSFileRef file );
BOOL         XSFile_ISUserExecutable( XSFileRef file );
BOOL         XSFile_IsGroupReadable( XSFileRef file );
BOOL         XSFile_IsGroupWriteable( XSFileRef file );
BOOL         XSFile_IsGroupExecutable( XSFileRef file );
BOOL         XSFile_IsWorldReadable( XSFileRef file );
BOOL         XSFile_IsWorldWriteable( XSFileRef file );
BOOL         XSFile_IsWorldExecutable( XSFileRef file );
BOOL         XSFile_HasSUID( XSFileRef file );
BOOL         XSFile_HasSGID( XSFileRef file );

XS_EXTERN_C_END

#endif /* _XS_FILE_H_ */
