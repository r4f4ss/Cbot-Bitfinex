//Cbot Bitfinex is a wrapper to hide the low work and allow more easily programing to access the Bitfinex API.
    /*Copyright (C) 2014  Rafael Sampaio

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

    //author contact:rafasampaio1@gmail.com
#ifndef _BITFINEXAPI_H
#define _BITFINEXAPI_H

#ifndef _MISC_H
#include"misc.h"
#endif
#ifndef _MALLOC_H
#include<malloc.h>
#endif
#ifndef _STRING_H
#include<string.h>
#endif
#ifndef _TIME_H
#include<time.h>
#endif
#ifndef _STDIO_H
#include<stdio.h>
#endif
#ifndef _CURLEXTRA_H
#include"curlExtra.h"
#endif
#ifndef HEADER_HMAC_H
#include<openssl/hmac.h>
#endif

typedef struct{
char key[57];
char secret[44];
char payload[1000];
char *payloadPt;
char data[1000];
char *dataPt;
char adress[50];
char *adressPt;
time_t nonce;
CURL *request;
struct curl_slist *headers;
struct MemoryStruct response;
HMAC_CTX ctx;
}bitfinexApi_t;

bitfinexApi_t *bitfinexApi_Init(char *key,char *secret);
void bitfinexApi_CleanUp(bitfinexApi_t *bitfinex);
void bitfinexApi_AddMethod(bitfinexApi_t *bitfinex,char *method);
void bitfinexApi_AddOptionString(bitfinexApi_t *,char *name,char *value);
void bitfinexApi_AddOptionInt(bitfinexApi_t *,char *name,char *value);
char *bitfinexApi_DoRequest(bitfinexApi_t *bitfinex,int *ret);

#endif
