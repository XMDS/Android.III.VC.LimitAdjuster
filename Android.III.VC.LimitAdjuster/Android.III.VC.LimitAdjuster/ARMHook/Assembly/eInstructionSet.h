/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/


#pragma once

enum eInstructionSet
{
	INSTRUCTION_SET_UNDEFINED,

	INSTRUCTION_SET_X86,
	INSTRUCTION_SET_X64,

	INSTRUCTION_SET_ARM,
	INSTRUCTION_SET_THUMB,

	INSTRUCTION_SET_ARM64,

	INSTRUCTION_SET_MIPS
};

/*
Thumb 2
B.W instruction

if bit 11 = 0 and bit 27 = 0
	base = PC + 4 MB
else if bit 11 = 1 and bit 27 = 0
	base = PC - 8 MB
else if bit 11 = 0 and bit 27 = 1
	base = PC
else if bit 11 = 1 and bit 27 = 1
	base = PC - 4 MB
*/

enum eThumbRelativeOffsetBase
{
	THUMB_RELATIVE_OFFSET_BASE_PC_PLUS_4_MB,
	THUMB_RELATIVE_OFFSET_BASE_PC_MINUS_8_MB,
	THUMB_RELATIVE_OFFSET_BASE_PC,
	THUMB_RELATIVE_OFFSET_BASE_PC_MINUS_4_MB
};