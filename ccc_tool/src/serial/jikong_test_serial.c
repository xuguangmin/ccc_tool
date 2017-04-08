/******************************************************************************

                  版权所有 (C), 2001-2020, 北京飞利信科技股份有限公司

 ******************************************************************************
  文件名称 :
  作者    :贾延刚
  生成日期 :2014-6-12

  版本    : 2.0
  功能描述 : 集控串口测试程序
           增加了串口串口类型的设置，需要指明：RS232 RS485 RS422


  说明：
           /home/flx/developer/workspace_c/ccc_tool/release
           /home/flx/developer/workspace_c/ccc_tool/build

******************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "devc_fpga_serial.h"
#include "thread_wrapper.h"


typedef struct _options_menu{
	int   select;
	char *desc;
	int   value;
}OPTIONS_MENU;


static OPTIONS_MENU  l_menu_serial[] = {
	{1,	     "serial1",    1},
	{2,	     "serial2",    2},
	{3,	     "serial3",    3},
	{4,	     "serial4",    4},
	{5,	     "serial5",    5},
	{6,	     "serial6",    6},
	{7,	     "serial7",    7},
	{8,	     "serial8",    8},
	{-1,      NULL,        -1}
};
/*
static OPTIONS_MENU  l_menu_serial_type[] = {
	{1,	     "RS232",    0},
	{2,	     "RS485",    1},
	{3,	     "RS422",    2},
	{-1,      NULL,     -1}
};
*/
static OPTIONS_MENU  l_menu_serial_baud[] = {
	{1,	     "1200",    1200},
	{2,	     "2400",    2400},
	{3,	     "4800",    4800},
	{4,	     "9600",    9600},
	{5,	     "19200",   19200},
	{6,	     "38400",   38400},
	{7,	     "57600",   57600},
	{8,	     "76800",   76800},
	{9,	     "115200",  115200},
	{10,	 "153600",  153600},
	{11,	 "230400",  230400},
	{12,	 "460800",  460800},
	{-1,      NULL,     -1}
};

static OPTIONS_MENU  l_menu_serial_data_bits[] = {
	{1,	     "data_bits 5",    5},
	{2,	     "data_bits 6",    6},
	{3,	     "data_bits 7",    7},
	{4,	     "data_bits 8",    8},
	{-1,      NULL,     -1}
};

static OPTIONS_MENU  l_menu_serial_parity[] = {
	{1,	     "none(0)",  0},
	{2,	     "odd(1)",   1},
	{3,	     "even(2)",  2},
	{-1,      NULL,     -1}
};

static OPTIONS_MENU  l_menu_serial_stop_bits[] = {
	{1,	     "stop_bits 1",        1},
	{2,	     "stop_bits 2",        2},
	{-1,      NULL,     -1}
};


static void show_menu_serial(const OPTIONS_MENU *menu)
{
	int k;

	printf("\n");
	for(k = 0; ;k++)
	{
		if(menu[k].desc == NULL)
			break;

		printf("<%d> %10s\n", menu[k].select, menu[k].desc);
	}
}

static int get_option_value(const OPTIONS_MENU *menu, int select)
{
	int k;
	if(!menu)
		return -1;

	for(k = 0; ;k++)
	{
		if(menu[k].desc == NULL)
			break;

		if(menu[k].select == select)
		{
			return menu[k].value;
		}
	}
	return -1;
}

int get_input(char *buffer, int len)
{
	int ix = 0;
	if(!buffer || len <= 0)
		return 0;

	while(1)
	{
		int ch = getchar();
		if(0x0A == ch || ix >= len)
			break;

		buffer[ix++] = (char)ch;
	}
	return ix;
}

/*  */
int check_input(int *select)
{
	int k, len;
	char buffer[256];

	len = get_input(buffer, 256-1);
	buffer[len] = '\0';
	if(len <= 0)
		return 0;

	for(k = 0; k < len; ++k)
	{
		if(buffer[k] < '0' || buffer[k] > '9')
			return 0;
	}

	/* too max */
	if(len > 3)
		return 0;

	*select = atoi(buffer);
	return 1;
}

static int fd;
static void thread_func_serial_recv(void *param)
{
	uint8_t recBuffer[1024];
	printf("%s running\n", __FUNCTION__);
    while(1)
    {
		int len = devc_fpga_serial_read_data(fd, recBuffer, 1024);
		if (len > 0)
		{
			recBuffer[len] = '\0';
		 	printf("<%s\n", recBuffer);
		}
    }
}

int main(void)
{
	int select;
	int serial_no = 1;
	//int serial_type = 0;
	int baud = 115200;
	int data_bits = 8;
	int parity = 0;
	int stop_bits = 1;
	char buffer[] = "123";

	// serial no
	show_menu_serial(l_menu_serial);
	printf("please select serial(default = 1):");
	if(check_input(&select))
	{
		serial_no = get_option_value(l_menu_serial, select);
		if(serial_no < 1 || serial_no > 8)
			return -1;
	}


	/*/ serial type
	show_menu_serial(l_menu_serial_type);
	printf("please select serial type(default = RS232):");
	if(check_input(&select))
	{
		serial_type = get_option_value(l_menu_serial_type, select);
		if(serial_type < 0 || serial_type > 2)
			return -1;
	}
	*/

	// serial baud rate
	show_menu_serial(l_menu_serial_baud);
	printf("please select serial baud(default = 115200):");
	if(check_input(&select))
	{
		baud = get_option_value(l_menu_serial_baud, select);
	}

	// serial data bits
	show_menu_serial(l_menu_serial_data_bits);
	printf("please select serial data bits(default = 8):");
	if(check_input(&select))
	{
		data_bits = get_option_value(l_menu_serial_data_bits, select);
		if(data_bits < 5 || data_bits > 8)
			return -1;
	}


	// serial parity
	show_menu_serial(l_menu_serial_parity);
	printf("please select serial parity(default = none):");
	if(check_input(&select))
	{
		parity = get_option_value(l_menu_serial_parity, select);
		if(parity < 0 || parity > 2)
			return -1;
	}


	// serial stop bits
	show_menu_serial(l_menu_serial_stop_bits);
	printf("please select stop bits(default = 1):");
	if(check_input(&select))
	{
		stop_bits = get_option_value(l_menu_serial_stop_bits, select);
		if(stop_bits < 1 || parity > 2)
			return -1;
	}


	printf("\n");
	printf("select finished, run ...\n");
	printf("serial %d :%d %d-%d-%d\n", serial_no, baud, data_bits, parity, stop_bits);
	printf("\n");


	if(devc_fpga_serial_open(serial_no, &fd) != 0)
	{
		perror("Cannot Open Serial Port !\n");
		return -1;
	}

	if(devc_fpga_serial_modify(fd, baud, data_bits, parity, stop_bits) != 0)
	{
		perror("devc_fpga_serial_modify");
		return -1;
	}

	if(!thread_create((void *)thread_func_serial_recv, 0))
	{
		printf("%s thread_create error\n", __FUNCTION__);
		return -1;
	}

	while (1)
	{
		devc_fpga_serial_write_data(fd, (unsigned char *)buffer, strlen(buffer));
		printf(">%s\n", buffer);
		sleep(1);
	}
	return 0;
}




