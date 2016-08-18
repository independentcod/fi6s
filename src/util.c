#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

void ipv6_string(char *dst, const uint8_t *addr)
{
	// TODO: make use of zero compression
	int pos = 0;
	for(int i = 0; i < 8; i++) {
		pos += snprintf(&dst[pos], 5, "%x", addr[i*2] << 8 | addr[i*2 + 1]);
		if(i != 7)
			pos += snprintf(&dst[pos], 2, ":");
	}
}

int parse_mac(const char *str, uint8_t *dst)
{
	const char *p = str;
	for(int i = 0; i < 6; i++) {
		char cur[3];
		int j = 0;
		while(*p && *p != ':' && *p != '-' && j < 2)
			cur[j++] = *(p++);
		cur[2] = '\0';
		j = strtol_simple(cur, 16);
		if(j == -1)
			return -1;
		dst[i] = j & 0xff;
		if(!*p && j != 5)
			return -1;
		p++;
	}
	return 0;
}

int strtol_suffix(const char *str)
{
	char *endptr;
	int value = strtol(str, &endptr, 10);
	if(endptr == str || strlen(endptr) > 1)
		return -1;
	if(*endptr == '\0')
		value *= 1;
	else if(*endptr == 'k')
		value *= 1000;
	else
		return -1;
	return value;
}

int strtol_simple(const char *str, int base)
{
	char *endptr;
	int value = strtol(str, &endptr, base);
	if(endptr == str || *endptr != '\0')
		return -1;
	return value;
}

int strchr_count(const char *str, int c)
{
	const char *p = str;
	int ret = 0;
	while(*p)
		ret += *(p++) == c;
	return ret;
}