
#ifndef __DEVC_FPGA_SERIAL_H__
#define __DEVC_FPGA_SERIAL_H__

int devc_fpga_serial_open(int serial_no, int *handle);
int devc_fpga_serial_close(int handle);
int devc_fpga_serial_modify(int fd, int baud_rate, unsigned char data_bits,
                                      unsigned char parity, unsigned char stop_bits);

int devc_fpga_serial_write_data(int handle, const unsigned char *data, int len);
int devc_fpga_serial_read_data(int handle, unsigned char *data, int len);

#endif  /* __DEVC_FPGA_SERIAL_H__ */
