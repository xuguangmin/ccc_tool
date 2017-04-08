/******************************************************************************

                  版权所有 (C), 2001-2020, 北京飞利信科技股份有限公司

 ******************************************************************************
  文件名称 :
  作者    :李立敏
  生成日期 :

  版本    : 2.0
  功能描述 : 集控串口测试程序
           增加了串口串口类型的设置，需要指明：RS232 RS485 RS422


  说明：
           该项目做为一个验证项目，因为大幅度改动

           /home/flx/developer/workspace_c/ccc_tool/release
           /home/flx/developer/workspace_c/ccc_tool/build

******************************************************************************/
#include     <sys/ioctl.h>
#include     <stdio.h>      
#include     <stdlib.h>    
#include     <unistd.h>    
#include     <sys/types.h>  
#include     <sys/stat.h>  
#include     <fcntl.h>    
#include     <termios.h>    
#include     <errno.h> 
#include     <string.h>


struct FPGA_uart_init {
	unsigned long baud;
	unsigned char data_bits;//5,6,7,8
	unsigned char parity;// 0--no,1--odd,2--even,3--force parity "1",4--force parity "0"
	unsigned char data_stop_bits;// 1,2
}; 
static char *serial_name[]={"/dev/FPGA_Jikong00","/dev/FPGA_Jikong01","/dev/FPGA_Jikong02","/dev/FPGA_Jikong03","/dev/FPGA_Jikong04","/dev/FPGA_Jikong05","/dev/FPGA_Jikong06","/dev/FPGA_Jikong07"};

typedef enum UART_TYPE{RS232 = 0,RS485,RS422} serial_interface_type; 

int main(void)
{
	int cmd,i,j,k;
	//unsigned short len = 0;
	//unsigned long total_len = 0;
	unsigned short temp[10];
	char buffer[6024];
	typedef struct FPGA_uart_init {
	unsigned long baud;
	unsigned char data_bits;//5,6,7,8
	unsigned char parity;// 0--no,1--odd,2--even,3--force parity "1",4--force parity "0"
	unsigned char data_stop_bits;// 1,2,32(1.5)
	serial_interface_type uart_type;
	}FPGA_uart_init_t;
        
	temp[0]=0x00ff;
	struct FPGA_uart_init argp;
	
	
	printf("0:FPGA_Jikong00\n");
	printf("1:FPGA_Jikong01\n");
	printf("2:FPGA_Jikong02\n");
	printf("3:FPGA_Jikong03\n");
	printf("4:FPGA_Jikong04\n");
	printf("5:FPGA_Jikong05\n");
	printf("6:FPGA_Jikong06\n");
	printf("7:FPGA_Jikong07\n");
	printf("please input the open serial:");
	scanf("%d",&i);
	int fd = open(serial_name[i],O_RDWR);//270
	if(fd<0)
	{
		perror("Cannot Open Serial Port !\n");
	}
	
	
	printf("1: 9600,8,0,1  2: 115200,8,1,1   3: 9600,5,0,1.5 \n");
	printf("4: 115200,7,2,1 5: 115200,6,0,2\n");
	printf("6: 14400,8,0,1\n");
	printf("7: 19200,8,0,1\n");
	printf("8: 38400,8,0,1\n");
	printf("9: 56000,8,0,1\n");
	printf("10: 57600,8,0,1\n");
	printf("11: 1200,8,0,1\n");
	printf("12: 2400,8,0,1\n");
	printf("13: 4800,8,0,1\n");
	printf("14: 115200,8,0,1\n");
	printf("15: 460800,8,0,1\n");
	printf("16: 230400,8,0,1\n");
	printf("17: 153600,8,0,1\n");
	printf("18: 76800,8,0,1\n");
	printf("19: 256000,8,0,1\n");
	printf("please input the serial setting:");
	scanf("%d",&j);
	switch (j)
	{
         case 1:
		argp.baud = 9600;
		argp.data_bits = 8;
		argp.parity = 0;
		argp.data_stop_bits = 1;
		break;
	case 2:
		argp.baud = 115200;
		argp.data_bits = 8;
		argp.parity = 1;
		argp.data_stop_bits = 1;
		break;
	case 3:
		argp.baud = 9600;
		argp.data_bits = 5;
		argp.parity = 0;
		argp.data_stop_bits = 32;
		break;
	case 4:
		argp.baud = 115200;
		argp.data_bits = 7;
		argp.parity = 2;
		argp.data_stop_bits = 1;
		break;
	case 5:
		argp.baud = 115200;
		argp.data_bits = 6;
		argp.parity = 0;
		argp.data_stop_bits = 2;
		break;
	case 6:
		argp.baud = 14400;
		argp.data_bits = 8;
		argp.parity = 0;
		argp.data_stop_bits = 1;
		break;
	case 7:
		argp.baud = 19200;
		argp.data_bits = 8;
		argp.parity = 0;
		argp.data_stop_bits = 1;
		break;
	case 8:
		argp.baud = 38400;
		argp.data_bits = 8;
		argp.parity = 0;
		argp.data_stop_bits = 1;
		break;
	case 9:
		argp.baud = 56000;
		argp.data_bits = 8;
		argp.parity = 0;
		argp.data_stop_bits = 1;
		break;
	case 10:
		argp.baud = 57600;
		argp.data_bits = 8;
		argp.parity = 0;
		argp.data_stop_bits = 1;
		break;
	case 11:
		argp.baud = 1200;
		argp.data_bits = 8;
		argp.parity = 0;
		argp.data_stop_bits = 1;
		break;
	case 12:
		argp.baud = 2400;
		argp.data_bits = 8;
		argp.parity = 0;
		argp.data_stop_bits = 1;
		break;
	case 13:
		argp.baud = 4800;
		argp.data_bits = 8;
		argp.parity = 0;
		argp.data_stop_bits = 1;
		break;
	case 14:
		argp.baud = 115200;
		argp.data_bits = 8;
		argp.parity = 0;
		argp.data_stop_bits = 1;
		break;
	case 15:
		argp.baud = 460800;
		argp.data_bits = 8;
		argp.parity = 0;
		argp.data_stop_bits = 1;
		break;
	case 16:
		argp.baud = 230400;
		argp.data_bits = 8;
		argp.parity = 0;
		argp.data_stop_bits = 1;
		break;
	case 17:
		argp.baud = 153600;
		argp.data_bits = 8;
		argp.parity = 0;
		argp.data_stop_bits = 1;
		break;
	case 18:
		argp.baud = 76800;
		argp.data_bits = 8;
		argp.parity = 0;
		argp.data_stop_bits = 1;
		break;
	case 19:
		argp.baud = 256000;
		argp.data_bits = 8;
		argp.parity = 0;
		argp.data_stop_bits = 1;
		break;
	default:
		argp.baud = 115200;
		argp.data_bits = 8;
		argp.parity = 0;
		argp.data_stop_bits = 1;
	}
     	cmd = 1;
	printf("%d,%d,%d,%d\n", (int)argp.baud,argp.data_bits, argp.parity,argp.data_stop_bits);
	
	printf("please input the open serial(RS232:0,RS485:1,RS422:2):");
	scanf("%d",&k);
	switch (k)
	{
         case 0:
		argp.uart_type = 0;
		break;
	case 1:
		argp.uart_type = 1;
		break;
	case 2:
		argp.uart_type = 2;
		break;
	default:
		argp.uart_type = 0;
	}

	if (ioctl(fd, cmd, &argp) < 0)
	 {
	     printf("Call cmd IOCPRINT fail\n");
	     return -1;
	 }

	int ii = 0;
	while (1)
	{
#if 0
		len=read(fd, buffer, 1);
		buffer[len] = '\0';
		total_len += len;
		//printf("len = %d\n",len);
		printf("%s\n",buffer);
		//printf("total_len=%8x\n",total_len);
#endif

#if 1
		//printf("please input data:\n");
		//gets(buffer);
		//printf("data count:%d,%s\n",strlen(buffer),buffer);
		//strcpy(buffer,"0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,0123456789,abcdefghijklm");
		if (ii == 0) {
			strcpy(buffer, "255");
			ii++;
		} else {
			strcpy(buffer, "0");
			ii = 0;
		}

		printf("data count:%d,%s\n", strlen(buffer), buffer);
		write(fd, buffer, strlen(buffer));
		usleep(1);
#endif

	}
	return 0;
}
