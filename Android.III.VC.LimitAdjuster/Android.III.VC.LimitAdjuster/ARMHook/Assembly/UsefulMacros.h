/*
* Copyright (C) fastman92 <fastman92@gmail.com>, website: http://fastman92.com
* Licensed under the MIT License, see LICENSE at top level directory.
*
*/

#pragma once

/* Useful links:
	https://stackoverflow.com/questions/28109826/arm64-using-gas-on-ios
*/

// Stringify
#if !defined(STRINGIFY) || defined(TOSTRING)
#define STRINGIFY(str) #str
#define TOSTRING(x) STRINGIFY(x)
#endif

// Deference
#define ACCESS_DEF(arg) (*arg)

// Author of macro: fastman92
#define MAKE_DEAD_IF() if(0)92

#define IS_PLATFORM_ANDROID_ARM32
#define IS_ARCHITECTURE_ARM32

// ASM code macros
#ifdef __GNUC__
#define BALIGN(balignment) ".balign " #balignment"\n"
#define P2ALIGN(p2alignment) ".p2align " #p2alignment"\n"

#define PUT_LABEL_ID(label_id) #label_id":\n"

#define ASM_PUT_CONSTANT_VALUE(label_id, value, type, balignment) BALIGN(balignment) \
PUT_LABEL_ID(label_id) \
"." #type " " #value "\n"

#define ASM_PUT_CONSTANT_INT8_NO_LABEL(value) ".1byte " #value "\n"

#define ASM_PUT_CONSTANT_FLOAT(label_id, value) ASM_PUT_CONSTANT_VALUE(label_id, value, float, 4)
#define ASM_PUT_CONSTANT_DOUBLE(value) ASM_PUT_CONSTANT_VALUE(label_id, value, double, 8)
#define ASM_PUT_CONSTANT_INT8(value) ASM_PUT_CONSTANT_VALUE(label_id, value, 1byte, 1)
#define ASM_PUT_CONSTANT_INT16(value) ASM_PUT_CONSTANT_VALUE(label_id, value, 2byte, 2)
#define ASM_PUT_CONSTANT_INT32(value) ASM_PUT_CONSTANT_VALUE(label_id, value, 4byte, 4)
#define ASM_PUT_CONSTANT_INT64(value) ASM_PUT_CONSTANT_VALUE(label_id, value, 8byte, 8)
#define ASM_PUT_CONSTANT_INT128(value) ASM_PUT_CONSTANT_VALUE(label_id, value, octa, 16)
#elif defined(IS_PLATFORM_WIN)
#define BALIGN(balignment) align #balignment
#endif

#if defined(IS_PLATFORM_WIN_X86) || defined(IS_PLATFORM_WIN_X64)
#define ASM_JMP_STATIC_ADDRESS(address) __asm push address __asm retn

#define ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(symbol) jmp [symbol]
#endif

// Load address of symbol
#ifdef IS_PLATFORM_ANDROID_ARM32
#define ASM_LOAD_ADDRESS_OF_SYMBOL(reg, symbol) "ldr " #reg ", =("#symbol" - 100001f - 2*(100002f-100001f))\n" \
"100001:\n" \
"add "#reg", pc\n" \
"100002:\n"
#endif

#ifdef IS_PLATFORM_WIN_X86
#define ASM_LOAD_ADDRESS_OF_SYMBOL(reg, symbol) lea reg, [symbol]
#endif

#ifdef IS_PLATFORM_WIN_X64
#define ASM_LOAD_ADDRESS_OF_SYMBOL(reg, symbol) lea reg, [rip + symbol]
#endif

#ifdef IS_PLATFORM_ANDROID_X86
#define ASM_LOAD_ADDRESS_OF_SYMBOL(reg, symbol) "lea "#reg", ["#symbol"]\n"
#endif

#ifdef IS_PLATFORM_ANDROID_X64
// GAS syntax for RIP - relative addressing looks like symbol + RIP, but it actually means symbol with respect to RIP.
#define ASM_LOAD_ADDRESS_OF_SYMBOL(reg, symbol) "lea "#reg", [rip + "#symbol"]\n"
#endif

#ifdef IS_PLATFORM_ANDROID_ARM64
#define ASM_LOAD_ADDRESS_OF_SYMBOL(reg, symbol) "adrp " #reg ", "#symbol"\n" \
"add "#reg", "#reg", #:lo12:"#symbol"\n"
#endif

#ifdef IS_PLATFORM_IOS_ARM64
#define ASM_LOAD_ADDRESS_OF_SYMBOL(reg, symbol) "adrp " #reg ", "#symbol"@PAGE\n"  \
"add "#reg", "#reg", #"#symbol"@PAGEOFF\n"
#endif

//////////////
#if defined(IS_PLATFORM_ANDROID_ARM32) || defined(IS_PLATFORM_ANDROID_ARM64)
#define ASM_LOAD_BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(reg, symbol) ASM_LOAD_ADDRESS_OF_SYMBOL(reg, symbol) \
"LDRB "#reg", ["#reg"]\n"
#define ASM_LOAD_2BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(reg, symbol) ASM_LOAD_ADDRESS_OF_SYMBOL(reg, symbol) \
"LDRH "#reg", ["#reg"]\n"
#define ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(reg, symbol) ASM_LOAD_ADDRESS_OF_SYMBOL(reg, symbol) \
"LDR "#reg", ["#reg"]\n"

#define __ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(reg, symbol) ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(reg, symbol)
#endif

#ifdef IS_PLATFORM_ANDROID_ARM64
#define ASM_LOAD_8BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(reg, symbol) ASM_LOAD_ADDRESS_OF_SYMBOL(reg, symbol) \
"LDR "#reg", ["#reg"]\n"
#endif
//////////////

#ifdef IS_ARCHITECTURE_ARM32
// Different register
#define DIFF_REG1_R0 R1
#define DIFF_REG1_R1 R0
#define DIFF_REG1_R2 R0
#define DIFF_REG1_R3 R0
#define DIFF_REG1_R4 R0
#define DIFF_REG1_R5 R0
#define DIFF_REG1_R6 R0
#define DIFF_REG1_R7 R0
#define DIFF_REG1_R8 R0
#define DIFF_REG1_R9 R0
#define DIFF_REG1_R10 R0
#define DIFF_REG1_R11 R0
#define DIFF_REG1_R12 R0
#define DIFF_REG1_SP R0
#define DIFF_REG1_LR R0
#define DIFF_REG1_PC R0
#define DIFF_REG1(reg) DIFF_REG##reg
#endif

#ifdef IS_PLATFORM_ANDROID_ARM32
#define ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(reg, symbol) ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(reg, symbol)

#define ASM_JUMP_TO_ADDRESS_OF_SYMBOL(symbol) "PUSH            {R0,R1}\n" \
ASM_LOAD_ADDRESS_OF_SYMBOL(R0, symbol) \
"STR R0, [SP, #4]\n" \
"POP            {R0,PC}\n"

#define ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(symbol) "PUSH            {R0,R1}\n" \
ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R0, symbol) \
"STR R0, [SP, #4]\n" \
"POP            {R0,PC}\n"

#define ASM_CALL_TO_ADDRESS_STORED_ON_SYMBOL(symbol) "PUSH            {R0,R1}\n" \
"ADR LR, 100015f + ((4 - (100011f - 100010f)) / 2)\n" \
ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(R0, symbol) \
"100010:\n" \
"STR R0, [SP, #4]\n" \
"100011:\n" \
"POP            {R0,PC}\n" \
"100015:\n"

// Make instruction with register and symbol
#define ASM_MAKE_INSTRUCTION_REG_AND_VALUE_STORED_ON_SYMBOL(instruction, reg, symbol) "PUSH            {" TOSTRING(DIFF_REG1_##reg) "}\n" \
__ASM_LOAD_4BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(DIFF_REG1_##reg, symbol) \
#instruction " " #reg", " TOSTRING(DIFF_REG1_##reg) "\n" \
"POP            {" TOSTRING(DIFF_REG1_##reg) "}\n"

// ADD register, value on symbol
#define ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(reg, symbol) ASM_MAKE_INSTRUCTION_REG_AND_VALUE_STORED_ON_SYMBOL(ADD, reg, symbol)
#define ASM_ADD_ADDRESS_STORED_ON_SYMBOL(reg, symbol) ASM_ADD_4BYTE_VALUE_STORED_ON_SYMBOL(reg, symbol)

#define ASM_SUB_4BYTE_VALUE_STORED_ON_SYMBOL(reg, symbol) ASM_MAKE_INSTRUCTION_REG_AND_VALUE_STORED_ON_SYMBOL(SUB, reg, symbol)

#define ASM_CMP_4BYTE_VALUE_STORED_ON_SYMBOL(reg, symbol) ASM_MAKE_INSTRUCTION_REG_AND_VALUE_STORED_ON_SYMBOL(CMP, reg, symbol)
#define ASM_MUL_4BYTE_VALUE_STORED_ON_SYMBOL(reg, symbol) ASM_MAKE_INSTRUCTION_REG_AND_VALUE_STORED_ON_SYMBOL(MUL, reg, symbol)

#define ASM_LOAD_NEON_VALUE_STORED_ON_SYMBOL(reg, symbol) "PUSH            {R0,R1}\n" \
ASM_LOAD_ADDRESS_OF_SYMBOL(R0, symbol) \
"VLDR            "#reg", [R0]\n" \
"POP            {R0,R1}\n"
#endif

#ifdef IS_ARCHITECTURE_ARM32
// Instruction set
#define GET_CODE_START(address) ((uintptr_t)(address) & (~1))
#define GET_INSTRUCTION_SET_FROM_ADDRESS(address) (address & 1 ? INSTRUCTION_SET_THUMB : INSTRUCTION_SET_ARM)

#define ASM_GET_ARM_ADDRESS_FOR_JUMP(address) address
#define ASM_GET_THUMB_ADDRESS_FOR_JUMP(address) (address | 1)
#endif

#ifdef IS_PLATFORM_ANDROID_ARM64
#define ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(reg, symbol) ASM_LOAD_8BYTE_UNSIGNED_VALUE_STORED_ON_SYMBOL(reg, symbol)

// Remember, X0 gets pushed to stack, needs to be restored.
#define ASM_JUMP_TO_ADDRESS_OF_SYMBOL(symbol) "STR X0, [SP, #-16]!\n" \
ASM_LOAD_ADDRESS_OF_SYMBOL(X0, symbol) \
"BR X0\n"

// Remember, X0 gets pushed to stack, needs to be restored.
#define ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(symbol) "STR X0, [SP, #-16]!\n" \
ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(X0, symbol) \
"BR X0\n"

// Remember, X0 gets pushed to stack, needs to be restored.
#define ASM_CALL_TO_ADDRESS_STORED_ON_SYMBOL(symbol) "ADR LR, 100015f\n" \
ASM_JUMP_TO_ADDRESS_STORED_ON_SYMBOL(symbol) \
"100015:\n"
#endif

#ifdef IS_PLATFORM_WIN_X86
#define ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(reg, symbol) mov reg, [symbol]
#endif

#ifdef IS_PLATFORM_WIN_X64
#define ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(reg, symbol) mov reg, [rip + symbol]
#endif

#ifdef IS_PLATFORM_ANDROID_X86
#define ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(reg, symbol) "mov "#reg", ["#symbol"]\n"
#endif

#ifdef IS_PLATFORM_ANDROID_X64
#define ASM_LOAD_ADDRESS_STORED_ON_SYMBOL(reg, symbol) "mov "#reg", [rip + "#symbol"]\n"
#endif

// JNI
#define break_on_jni_exception(jniEnv) if (jniEnv->ExceptionCheck()) break;

// Returns void pointer to method
template<typename T> void* GetMethodAsVoidPointer(T method)
{
	return *reinterpret_cast<void**>(&method);
}