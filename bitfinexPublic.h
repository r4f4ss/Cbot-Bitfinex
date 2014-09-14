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
#ifndef _BITFINEXPUBLIC_H
#define _BITFINEXPUBLIC_H

#ifndef _MISC_H
#include"misc.h"
#endif
#ifndef _CURLEXTRA_H
#include"curlExtra.h"
#endif

typedef struct{
char adress[1000];
char *methodPt;
char *symbolPt;
char *parameterPt;
CURL *request;
struct MemoryStruct response;
}bitfinexPublic_t;

bitfinexPublic_t *bitfinexPublic_Init(char *method,char *symbol);
void bitfinexPublic_AddParameter(bitfinexPublic_t *bitfinex,char *name,char *value);
void bitfinexPublic_AddMethodSymbol(bitfinexPublic_t *bitfinex,char *method,char *symbol);
char *bitfinexPublic_DoRequest(bitfinexPublic_t *bitfinex,int *ret);
void bitfinexPublic_CleanUp(bitfinexPublic_t *bitfinex);


#endif
