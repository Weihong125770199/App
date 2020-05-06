/*
 *
 *  BlueZ - Bluetooth protocol stack for Linux
 *
 *  Copyright (C) 2002-2010  Marcel Holtmann <marcel@holtmann.org>
 *
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <signal.h>
#include <termios.h>
#include <poll.h>
#include <sys/param.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <assert.h>
#define IAP2_MAX_LEN   1024
#include "iap2.h"
int main(int argc, char *argv[])
{

       int ret,f_ret;
        int usb_read_bytes;
        int bt_write_bytes;
        int bt_read_bytes;
        int usb_write_bytes;
        int i=0;
        struct pollfd p_usb;
        struct pollfd p_bt;
        int fd_usb,fd;
        unsigned char buf_in[IAP2_MAX_LEN];
        unsigned char buf_out[IAP2_MAX_LEN];
	char dst[18], devname[MAXPATHLEN];
       
        pthread_mutex_t mutex;
        if(pthread_mutex_init(&mutex,NULL) != 0)
          {
               perror("pthread_mutex_init");

          }
      

	snprintf(devname, MAXPATHLEN - 1, "/dev/rfcomm0");
        while ((fd = open(devname, O_RDWR | O_NOCTTY)) < 0) {
                if (errno == EACCES) {
                        perror("Can't open RFCOMM device");
                        usleep(1000 * 1000);

                }
          }

        snprintf(devname, MAXPATHLEN - 1, "/dev/iAP0");
        while ((fd_usb = open(devname, O_RDWR | O_NOCTTY)) < 0) {
                if (errno == EACCES) {
                        perror("Can't open /dev/iAP0");
                        
                                usleep(100 * 1000);
                }
          }


        p_usb.fd = fd_usb;
        p_usb.events = POLLIN ;

        p_bt.fd = fd;
        p_bt.events = POLLIN ;


        pid_t n=fork();

        if(n==0)  //sub process
       {
              while(1)
              {
                  ret =  poll(&p_usb, 1, -1);//调用sys_poll系统调用，如果5S内没有产生POLLIN事件，那么返回，如果有POLLIN事件，直接返回
                  if(!ret)
                  {
                     perror("time out\n");
                  }
                   else
                  {
                         if(p_usb.revents==POLLIN)//如果返回的值是POLLIN，说明有数据POLL才返回的
                          {
                            pthread_mutex_lock(&mutex);
                           //printf("begin to read \n"); 
                            usb_read_bytes=read(fd_usb, buf_in,IAP2_MAX_LEN );           //读取USBIAPS DATA
                         
                            if(usb_read_bytes >0)
                            {
                               bt_write_bytes=write(fd,buf_in,usb_read_bytes);
                                             
                               printf(">>>>");
                               
                               printf_raw(buf_in,usb_read_bytes);
                               printf_package(buf_in,usb_read_bytes);
                               printf("\n");
                               //yield();
                                
                               pthread_mutex_unlock(&mutex);

                              

                               if(usb_read_bytes != bt_write_bytes)
                                  {
                                       printf(">>>> error-----:usb_read_bytes=%d ,bt_write_bytes=%d \n",usb_read_bytes,bt_write_bytes);
                                  }

                               }else
                                {

                                  //printf(">>>> error-----:usb_read_bytes=%d  erron=%s \n",usb_read_bytes,strerror(errno));
                                }
                            } else {

                                      printf("p_usb.revents =0x%04x \n",p_usb.revents);
                                   }
                       }
                   }
       }else
        {   //father process
          while(1)
              {
                  f_ret =  poll(&p_bt, 1, -1);//调用sys_poll系统调用，如果5S内没有产生POLLIN事件，那么返回，如果有POLLIN事件，直接返回
                  if(!f_ret)
                  {
                     perror("father time out\n");
                  }
                   else
                  {
                         if(p_bt.revents==POLLIN)//如果返回的值是POLLIN，说明有数据POLL才返回的
                          {
                            pthread_mutex_lock(&mutex);
                            bt_read_bytes=read(fd, buf_out,IAP2_MAX_LEN );           //读取bt DATA
                           
                            if(bt_read_bytes >0)
                            {
                               usb_write_bytes=write(fd_usb,buf_out,bt_read_bytes);
                                               //flush(fd_usb);
                               
                               printf("<<<<");
                               printf_package(buf_out,bt_read_bytes);
                               //printf_raw(buf_out,bt_read_bytes);
                               printf("\n"); 
                              
                               pthread_mutex_unlock(&mutex);
                               if(bt_read_bytes != usb_write_bytes)
                                  {
                                       printf("<<< error-----:bt_read_bytes=%d ,usb_write_bytes=%d \n",bt_read_bytes, usb_write_bytes);
                                  }

                               }
                            }
                       }
                   }
           }



return 0;
}
