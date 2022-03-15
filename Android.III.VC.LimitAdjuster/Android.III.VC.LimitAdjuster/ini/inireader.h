#pragma once
#include <stdlib.h>
#include <stdbool.h>

int str2int(char* s, int base);

struct inireader_t {
	const char* iniName;
	void (*SetIniPath)(const char* szFileName);
	int (*ReadInteger)(char* szSection, char* szKey, int iDefaultValue);
	float (*ReadFloat)(char* szSection, char* szKey, float fltDefaultValue);
	bool (*ReadBoolean)(char* szSection, char* szKey, bool bolDefaultValue);
	char* (*ReadString)(char* szSection, char* szKey, char* szDefaultValue, char* Buffer, int BufferSize);
	int (*WriteInteger)(char* szSection, char* szKey, int iValue);
	int (*WriteFloat)(char* szSection, char* szKey, float fltValue);
	int (*WriteBoolean)(char* szSection, char* szKey, bool bolValue);
	int (*WriteString)(char* szSection, char* szKey, char* szValue);
};
extern struct inireader_t inireader;