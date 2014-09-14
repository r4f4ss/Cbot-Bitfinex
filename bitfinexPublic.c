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
#include"bitfinexPublic.h"
#endif

bitfinexPublic_t *bitfinexPublic_Init(char *method,char *symbol){

	bitfinexPublic_t *bitfinex;
	bitfinex=malloc(sizeof(bitfinexPublic_t));

	bitfinex->methodPt=my_strcpy(bitfinex->adress,"https://api.bitfinex.com/v1/",28);
	bitfinex->symbolPt=my_strcpy(bitfinex->methodPt,method,-1);
	bitfinex->symbolPt=my_strcpy(bitfinex->symbolPt,"/",1);
	bitfinex->parameterPt=my_strcpy(bitfinex->symbolPt,symbol,-1);
	bitfinex->parameterPt=my_strcpy(bitfinex->parameterPt,"?",1);

	bitfinex->response.memory=malloc(1);
	bitfinex->response.size=0;

	bitfinex->request=curl_easy_init();
	curl_easy_setopt(bitfinex->request,CURLOPT_WRITEFUNCTION,WriteMemoryCallback);
	curl_easy_setopt(bitfinex->request,CURLOPT_WRITEDATA,(void *)&(bitfinex->response));
	curl_easy_setopt(bitfinex->request,CURLOPT_TIMEOUT,CURL_TIMEOUT);
	curl_easy_setopt(bitfinex->request, CURLOPT_SSL_VERIFYPEER,0L);

	return bitfinex;

}

void bitfinexPublic_AddParameter(bitfinexPublic_t *bitfinex,char *name,char *value){

	bitfinex->parameterPt=my_strcpy(bitfinex->parameterPt,name,-1);
	bitfinex->parameterPt=my_strcpy(bitfinex->parameterPt,"=",1);
	bitfinex->parameterPt=my_strcpy(bitfinex->parameterPt,value,-1);
	bitfinex->parameterPt=my_strcpy(bitfinex->parameterPt,"&",1);

}

void bitfinexPublic_AddMethodSymbol(bitfinexPublic_t *bitfinex,char *method,char *symbol){

	bitfinex->symbolPt=my_strcpy(bitfinex->methodPt,method,-1);
	bitfinex->symbolPt=my_strcpy(bitfinex->symbolPt,"/",1);
	bitfinex->parameterPt=my_strcpy(bitfinex->symbolPt,symbol,-1);
	bitfinex->parameterPt=my_strcpy(bitfinex->parameterPt,"?",1);

}

char *bitfinexPublic_DoRequest(bitfinexPublic_t *bitfinex,int *ret){

	bitfinex->response.memory=realloc(bitfinex->response.memory,1);
	bitfinex->response.size=0;

	curl_easy_setopt(bitfinex->request,CURLOPT_URL,bitfinex->adress);
	*retorno=execRequest(bitfinex->request);

	return bitfinex->response.memory;

}

void bitfinexPublic_CleanUp(bitfinexPublic_t *bitfinex){

	free(bitfinex->response.memory);
	curl_easy_cleanup(bitfinex->request);
	free(bitfinex);

}
