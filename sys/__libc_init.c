/*
 * Copyright (c) 2005-2007 Apple Inc. All rights reserved.
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
 * __libc_init() is called from libSystem_initializer()
 */

#include <limits.h>
#include <stdint.h>
#include <string.h>
#include <machine/cpu_capabilities.h>
#include <TargetConditionals.h>

#if TARGET_IPHONE_SIMULATOR
extern void __chk_init(void);
extern void __xlocale_init(void);

void
_libc_sim_init(void) {
	__chk_init();
	__xlocale_init();
}

#else /* TARGET_IPHONE_SIMULATOR */
struct ProgramVars; /* forward reference */

extern void _program_vars_init(const struct ProgramVars *vars);
extern void _libc_fork_init(void (*prepare)(void), void (*parent)(void), void (*child)(void));
extern void _init_clock_port(void);
extern void __chk_init(void);
extern void __xlocale_init(void);
extern void __guard_setup(const char *apple[]);

void
__libc_init(const struct ProgramVars *vars, void (*atfork_prepare)(void), void (*atfork_parent)(void), void (*atfork_child)(void), const char *apple[])
{
	_program_vars_init(vars);
	_libc_fork_init(atfork_prepare, atfork_parent, atfork_child);
	_init_clock_port();
	__chk_init();
	__xlocale_init();
	__guard_setup(apple);
}
#endif /* TARGET_IPHONE_SIMULATOR */
