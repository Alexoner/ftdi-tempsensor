/*************************************************************************
    > File Name: tempsensor.h
    > Author: onerhao
    > Mail: haodu@hustunique.com
    > Created Time: Sat 31 Aug 2013 09:27:37 PM CST
 ************************************************************************/

#include <ftd2xx.h>
#define MAX_DEVICES 5
#define BUF_SIZE    0xFFF
#define INSTRUCTION_SIZE 16
#define MAX_PATH    128
#define MAX_ENTRY   32
#define MAX_BUF     64

//board instructions

#define QUERY_SLAVE_S         "\x23\x00\x0D"
#define QUERY_AD1_S           "\x23\x01\x0D"
#define QUERY_AD2_S           "\x23\x02\x0D"
#define QUERY_AD3_S           "\x23\x03\x0D"
#define QUERY_AD4_S           "\x23\x04\x0D"
#define QUERY_TEMPERATURE_S   "\x23\x05\x0D"

#define SET_AD1_S			  "#\x06\x01\x01\x0D"
#define SET_AD2_S			  "#\x06\x00\x02\x0D"
#define SET_AD3_S             "#\x06\x01\x04\x0D"
#define SET_AD4_S             "#\x06\x01\x07\x0D"

#define RIGHT_SLAVE			  "\x31"
#define ERROR_TEMP            "ERR0\x0D"
#define ERROR_AD1_S			  "ERR1\x0D"
#define ERROR_AD2_S			  "ERR2\x0D"
#define ERROR_AD3_S			  "ERR3\x0D"
#define ERROR_AD4_S			  "ERR4\x0D"


FT_HANDLE scan_device();
int close_device();
int handle_device(
		FT_HANDLE fthanlde,
		unsigned char *txbuf,
		unsigned char *rxbuf,
		DWORD txBytes,
		DWORD *rxBytes);
int verify_tempsensor(FT_HANDLE fthandle);
int config_serial(FT_HANDLE fthandle,DWORD baudrate);

int query_slave(FT_HANDLE fthandle);
int query_ad1(FT_HANDLE fthandle);
int query_ad2(FT_HANDLE fthandle);
int query_ad3(FT_HANDLE fthandle);
int query_ad4(FT_HANDLE fthandle);
int query_temperature(FT_HANDLE fthandle,float *t);

/*t is time in timer_t,temp stands for temperature.
 * save the data into json file
 */
int save2json(long t,float temp);

//get extrema temperature and average temperature
int get_extrema_temp(
    char *path,time_t time_start,time_t time_stop,
    float *max_temp,float *min_temp,float *ave_temp);

