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
#include"bitfinexApi.h"
#endif

static unsigned char *mac;
static char *sign;
static char *bufferPt;

bitfinexApi_t *bitfinexApi_Init(char *key,char *secret){

	mac=(unsigned char *)malloc(sizeof(char)*128);
	sign=(char *)malloc(sizeof(char)*113);
	bufferPt=my_strcpy(sign,"X-BFX-SIGNATURE:",16);

	bitfinexApi_t *bitfinex;
	bitfinex=malloc(sizeof(bitfinexApi_t));

	char *keyPt;
	keyPt=my_strcpy(bitfinex->key,"X-BFX-APIKEY:",13);
	my_strcpy(keyPt,key,43);

	my_strcpy(bitfinex->secret,secret,43);

	bitfinex->payloadPt=my_strcpy(bitfinex->payload,"X-BFX-PAYLOAD:",14);

	bitfinex->adressPt=my_strcpy(bitfinex->adress,"https://api.bitfinex.com",24);

	bitfinex->nonce=time(NULL);

	bitfinex->headers=NULL;
	bitfinex->response.memory=malloc(1);
	bitfinex->response.size=0;

	bitfinex->request=curl_easy_init();
	curl_easy_setopt(bitfinex->request,CURLOPT_WRITEFUNCTION,WriteMemoryCallback);
	curl_easy_setopt(bitfinex->request,CURLOPT_WRITEDATA,(void *)&(bitfinex->response));
	curl_easy_setopt(bitfinex->request,CURLOPT_TIMEOUT,CURL_TIMEOUT);
	curl_easy_setopt(bitfinex->request,CURLOPT_POST,1L);
	curl_easy_setopt(bitfinex->request,CURLOPT_POSTFIELDS,"");
	curl_easy_setopt(bitfinex->request, CURLOPT_SSL_VERIFYPEER,0L);

	Hmac_CTX_init(&(bitfinex->ctx));

	return bitfinex;

}

void bitfinexApi_CleanUp(bitfinexApi_t *bitfinex){
	curl_slist_free_all(bitfinex->headers);
	free(bitfinex->response.memory);
	curl_easy_cleanup(bitfinex->request);
	Hmac_CTX_cleanup(&(bitfinex->ctx));
	free(bitfinex);
	free(mac);
	free(sign);
}

void bitfinexApi_AddMethod(bitfinexApi_t *bitfinex,char *method){

	bitfinex->dataPt=my_strcpy(bitfinex->data,"{\"request\":\"",12);
	bitfinex->dataPt=my_strcpy(bitfinex->dataPt,method,-1);
	bitfinex->dataPt=my_strcpy(bitfinex->dataPt,"\",",2);

	my_strcpy(bitfinex->adressPt,method,-1);

}

void bitfinexApi_AddOptionString(bitfinexApi_t *bitfinex,char *name,char *value){

	bitfinex->dataPt=my_strcpy(bitfinex->dataPt,"\"",1);
	bitfinex->dataPt=my_strcpy(bitfinex->dataPt,name,-1);
	bitfinex->dataPt=my_strcpy(bitfinex->dataPt,"\":\"",3);
	bitfinex->dataPt=my_strcpy(bitfinex->dataPt,value,-1);
	bitfinex->dataPt=my_strcpy(bitfinex->dataPt,"\",",2);

}

void bitfinexApi_AddOptionInt(bitfinexApi_t *bitfinex,char *name,char *value){

	bitfinex->dataPt=my_strcpy(bitfinex->dataPt,"\"",1);
	bitfinex->dataPt=my_strcpy(bitfinex->dataPt,name,-1);
	bitfinex->dataPt=my_strcpy(bitfinex->dataPt,"\":",2);
	bitfinex->dataPt=my_strcpy(bitfinex->dataPt,value,-1);
	bitfinex->dataPt=my_strcpy(bitfinex->dataPt,",",1);

}

char *bitfinexApi_DoRequest(bitfinexApi_t *bitfinex,int *ret){

	char *dataPt;
	bitfinex->nonce+=1;
	dataPt=my_strcpy(bitfinex->dataPt,"\"nonce\":",8);
	sprintf(dataPt,"\"%d\"}",(int)bitfinex->nonce);

	int bytes_to_encode=strlen(bitfinex->data)*sizeof(char);
	char *data_encoded=base64encode(bitfinex->data,bytes_to_encode);

	my_strcpy(bitfinex->payloadPt,data_encoded,-1);

	Hmac_Init_ex(&(bitfinex->ctx),bitfinex->secret,43,EVP_sha384(),NULL);
	Hmac_Update(&(bitfinex->ctx),(unsigned char *)&(*data_encoded),strlen(data_encoded));
	Hmac_Final(&(bitfinex->ctx),mac,NULL);

	int i;
	char *p;
	p=bufferPt;
	for(i=0;i<48;i++){
 		sprintf(p,"%02x",(unsigned int)mac[i]);
 		p+=2;
	}

	bitfinex->response.memory=realloc(bitfinex->response.memory,1);
	bitfinex->response.size=0;
	bitfinex->headers=NULL;
	bitfinex->headers=curl_slist_append(bitfinex->headers,bitfinex->key);
	bitfinex->headers=curl_slist_append(bitfinex->headers,bitfinex->payload);
	bitfinex->headers=curl_slist_append(bitfinex->headers,sign);
	curl_easy_setopt(bitfinex->request,CURLOPT_HTTPHEADER,bitfinex->headers);
	curl_easy_setopt(bitfinex->request,CURLOPT_URL,bitfinex->adress);

	*ret=execRequest(bitfinex->request);

	return bitfinex->response.memory;

}
