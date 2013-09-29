/*************************************************************************
    > File Name: tempsensor.cgi.c
    > Author: onerhao
    > Mail: haodu@hustunique.com
    > Created Time: Sat 31 Aug 2013 08:51:24 PM CST
 ************************************************************************/

#include <ftd2xx.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "tempsensor.h"

#define MAX_ACTION 64
#define MAX_ARG    64
#define MAX_BUF	   64

#define MAX_ARG_N  4

#define DEBUG      0

int parse_request(char *request);
char *get_request();

char *get_request()
{
	char *method=NULL,*data=NULL;
	method=getenv("REQUEST_METHOD");
	if(method&&strcmp(method,"GET")==0)
	{
		data=getenv("QUERY_STRING");
	}
	return data;
}

int parse_request(char *request)
{
	char action[MAX_ACTION],arg[MAX_ARG_N][MAX_ARG],buf[MAX_BUF];
	char path[MAX_PATH];
	//time_t time_start,time_stop;
	struct tm tm1,tm2;//start & stop time
	time_t t1,t2;
	float max_temp,min_temp,ave_temp;
	float t;
	FT_HANDLE fthandle;
	if(!request)
	{
		return -1;
	}
	sscanf(request,"%*[^=]=%[^&]",action);
	if(strcmp(action,"queryTemperature")==0)
	{
		fthandle=scan_device();
		if(fthandle)
		{
			query_temperature(fthandle,&t);
			printf("[%ld,%g]",time(NULL),t);
		}
		else
		{
			return -1;
		}
	}
	else if(strcmp(action,"get_extrema_temp")==0)
	{
		sscanf(request,"%*[^&]&%*[^=]=%[^&]&%*[^=]=%[^&]%*[^=]=%s",arg[0],arg[1],arg[2]);
		sprintf(path,"%s.log",arg[0]);
		strncpy(buf,arg[0],4);
		buf[4]='\0';
		tm1.tm_year=tm2.tm_year=atoi(buf)-1900;
		strncpy(buf,arg[0]+5,2);
		buf[2]='\0';
		tm1.tm_mon=tm2.tm_mon=atoi(buf)-1;
		strncpy(buf,arg[0]+8,2);
		buf[2]='\0';
		tm1.tm_mday=tm2.tm_mday=atoi(buf);
		strncpy(buf,arg[1],2);
		buf[2]='\0';
		tm1.tm_hour=atoi(buf);
		strncpy(buf,arg[2],2);
		buf[2]='\0';
		tm2.tm_hour=atoi(buf);
		strncpy(buf,arg[1]+3,2);
		buf[2]='\0';
		tm1.tm_min=atoi(buf);
		strncpy(buf,arg[2]+3,2);
		buf[2]='\0';
		tm2.tm_min=atoi(buf);
		tm1.tm_sec=0;
		tm2.tm_sec=0;
		tm1.tm_isdst=tm2.tm_isdst=0;
		t1=mktime(&tm1);
		t2=mktime(&tm2);
#if DEBUG
		printf("%ld",t1);
		printf("%ld",t2);
#endif
		sprintf(path,"%s.log",arg[0]);
		if(get_extrema_temp(path,t1,t2,&max_temp,&min_temp,&ave_temp)==0)
		{
			printf("[%g,%g,%g]",max_temp,min_temp,ave_temp);
		}
		else
		{
			printf("[\"ERROR\",\"ERROR\",\"ERROR\"]");
		}
	}
	return 0;
}

int main()
{
	//FT_HANDLE fthandle=scan_device();
	//float t;
	//char entry[MAX_ENTRY];
	char *request=NULL;
	printf("Content-type: text/plain\n\n");
#if DEBUG
	request=get_request();
	parse_request(request);
#else
	request=get_request();
	parse_request(request);
#endif
	return 0;
}
