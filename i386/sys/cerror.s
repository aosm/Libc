/*
 * Copyright (c) 1999 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
/*
 * Copyright (c) 1995 NeXT Computer, Inc. All Rights Reserved
 */
#include "SYS.h"

	.globl	_errno

LABEL(cerror_cvt)
	cmpl	$102, %eax	/* EOPNOTSUPP? */
	jnz	cerror
	movl	$45, %eax	/* Yes; make ENOTSUP for compatibility */
LABEL(cerror)
	REG_TO_EXTERN(%eax, _errno)
	mov		%esp,%edx
	andl	$0xfffffff0,%esp
	subl	$16,%esp
	movl	%edx,4(%esp)
	movl	%eax,(%esp)
	CALL_EXTERN(_cthread_set_errno_self)
	movl	4(%esp),%esp
	movl	$-1,%eax
	movl	$-1,%edx /* in case a 64-bit value is returned */
	ret
