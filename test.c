/*************************************************************************
    > File Name: test.c
    > Author: onerhao
    > Mail: haodu@hustunique.com
    > Created Time: Sat 24 Aug 2013 11:51:49 PM CST
 ************************************************************************/

#include "tempsensor.h"
#include <stdio.h>
#include <stdlib.h>
//#include "tempsensor.c"
//#include "tempsensor.cgi.c"
#include <ftd2xx.h>

extern char * get_request();

int main()
{
	//time_t t=time(NULL);
	//save2json(t,23.43);
	//float max_temp,min_temp;
	//get_extrema_temp(1379085900,1379168928,"2013-9-14.log",
	//		&max_temp,&min_temp);
	//printf("max: %g,min: %g\n",max_temp,min_temp);
	//printf("%s\n",getenv("PATH"));
	printf("%s\n",getenv("REQUEST_METHOD"));
	return 0;
}

