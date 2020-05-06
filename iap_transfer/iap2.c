#include "iap2.h"
#include <stdio.h>

void printf_raw(u_int8_t *buffer, u_int16_t length)
{   
     int i=0;
     for(i=0;i < length;i++)
       {
         printf("%02x",buffer[i]);
       }
     printf("\n");
     return ;
}

void printf_ctrl_session_msg( unsigned int ctrl_session_len,ctrl_session_msg  temp_ctrl_session_msg)
{
 			   unsigned int totla_parameter_len = 0;
                           int i=0;
                           unsigned int temp_parameter_len=0;
                           parameter tem_parameter;
                           char str[100];
                          while ((ctrl_session_len -6) >  totla_parameter_len)
                                  {
                                     memcpy(&tem_parameter,(unsigned char *)&temp_ctrl_session_msg.ctrl_session_param+totla_parameter_len,\
                                            0x04);
                                     temp_parameter_len = tem_parameter.lengthMSL;
                                     temp_parameter_len = temp_parameter_len << 8;
                                     temp_parameter_len =temp_parameter_len +  tem_parameter.lengthLSB;

                                     memcpy(&tem_parameter,(unsigned char *)&temp_ctrl_session_msg.ctrl_session_param+totla_parameter_len,\
                                            temp_parameter_len);
                                     printf("       parameter:len=%004d ,idMSB=0x%02x ,idLSB=0x%02x data[", \
                                            temp_parameter_len,tem_parameter.idMSB,tem_parameter.idLSB);
                                     if((tem_parameter.idMSB == 0x00) &&(tem_parameter.idLSB == 0x00))
                                     {
                                          memcpy(str,tem_parameter.data,temp_parameter_len -4);
                                          printf("Name:%s ",str);
                                     }else  if((tem_parameter.idMSB == 0x00) &&(tem_parameter.idLSB == 0x01))
                                     {
                                          memcpy(str,tem_parameter.data,temp_parameter_len -4);
                                          printf("ModelIdentifier:%s ",str);
                                     }else if((tem_parameter.idMSB == 0x00) &&(tem_parameter.idLSB == 0x02))
                                     {
                                          memcpy(str,tem_parameter.data,temp_parameter_len -4);
                                          printf("Manfufacture:%s ",str);
                                     }else if((tem_parameter.idMSB == 0x00) &&(tem_parameter.idLSB == 0x0c))
                                     {
                                          memcpy(str,tem_parameter.data,temp_parameter_len -4);
                                          printf("current Language:%s ",str);
                                     }else if((tem_parameter.idMSB == 0x00) &&(tem_parameter.idLSB == 0x0d))
                                     {
                                          memcpy(str,tem_parameter.data,temp_parameter_len -4);
                                          printf("supported Language:%s ",str);
                                     }
                                     else if((tem_parameter.idMSB == 0x00) &&(tem_parameter.idLSB == 0x10))
                                     {
                                          memcpy(str,tem_parameter.data,temp_parameter_len -4);
                                          printf("supported Language:%s ",str);
                                     }
                                     else
                                     {
                                     	for(i=0;i<(temp_parameter_len-4);i++)
                                        	 {
                                           		printf("%02x",tem_parameter.data[i]);
                                         	}	
                                     }
                                     printf("] \n");
                                     totla_parameter_len = totla_parameter_len +temp_parameter_len;


                                  }



}
 
void printf_package(u_int8_t *buffer, u_int16_t length)
{    unsigned int len=0;
     unsigned int temp_len =0;
     unsigned int temp_parameter_len=0;
     int Control_Byte=0;
     unsigned int ctrl_session_len =0;
     apacket iap_package;
     ctrl_session_msg  temp_ctrl_session_msg;
     parameter tem_parameter;
     memcpy(&iap_package,buffer,length);
     if((iap_package.msg.startMSL== 0xff) &&(iap_package.msg.startLSB == 0x55))
       {
         printf("iap2 Initialization package\n");
         return;
       }

     if((iap_package.msg.startMSL== 0xff) &&(iap_package.msg.startLSB == 0x5A))
       { len= iap_package.msg.lengthMSL;
         len = len <<8;
         len = len + iap_package.msg.lengthLSB;
       
         printf("iap2 link package : lenth=%d  type:",(int)len);
         Control_Byte = iap_package.msg.ctrl;
         if(iap_package.msg.ctrl & CONTROL_BYTE_SYN)
               {

                 printf(" SYN ");
               }        
         if(iap_package.msg.ctrl & CONTROL_BYTE_ACK)
               {

                 printf(" ACK ");
               }        
         
         if(iap_package.msg.ctrl & CONTROL_BYTE_EAK)
               {

                 printf(" EAK ");
               }        
         if(iap_package.msg.ctrl & CONTROL_BYTE_RST)
               {

                 printf(" RST ");
               }        
         if(iap_package.msg.ctrl & CONTROL_BYTE_SLP)
               {

                 printf(" SLP ");
               }        
         

          printf("\n");
           while((len -9) > (temp_len +1))
            {
              
             // printf("len=%d  temp_len=%d \n",(int)len,temp_len);
             ctrl_session_len = iap_package.data.playload[temp_len +2];
             ctrl_session_len = ctrl_session_len << 8;
             ctrl_session_len = ctrl_session_len + iap_package.data.playload[temp_len +3];

             memcpy(&temp_ctrl_session_msg,iap_package.data.playload,ctrl_session_len);
             if((temp_ctrl_session_msg.startMSL == 0x40)&&(temp_ctrl_session_msg.startLSB == 0x40))
                   {
                      printf("      control session: ");
                      if((temp_ctrl_session_msg.idMSB == 0x1D)&&(temp_ctrl_session_msg.idLSB == 0x00))
                        {
                           printf("StartIdentification \n");
                           return ;
                        }

                       if((temp_ctrl_session_msg.idMSB == 0x1D)&&(temp_ctrl_session_msg.idLSB == 0x01))
                        {
                           printf("IdentificationInformation \n");
                           printf_ctrl_session_msg(ctrl_session_len,temp_ctrl_session_msg);
                           #if 0
                           unsigned int totla_parameter_len = 0;
                           int i=0;
                           temp_parameter_len = temp_ctrl_session_msg.ctrl_session_param.lengthMSL;
                           temp_parameter_len = temp_parameter_len << 8;
                           temp_parameter_len = temp_parameter_len + temp_ctrl_session_msg.ctrl_session_param.lengthLSB;
                           while ((ctrl_session_len -6) >  totla_parameter_len)
                                  {

                                     //printf("ctrl_session_len =%d ,totla_parameter_len = %d temp_parameter_len=%d \n" \
                                        ,ctrl_session_len,totla_parameter_len,temp_parameter_len);
                                     memcpy(&tem_parameter,(unsigned char *)&temp_ctrl_session_msg.ctrl_session_param+totla_parameter_len,\
                                            temp_parameter_len);
                                     temp_parameter_len = tem_parameter.lengthMSL;
                                     temp_parameter_len = temp_parameter_len << 8;
                                     temp_parameter_len =temp_parameter_len +  tem_parameter.lengthLSB;
                                     printf("parameter:len=%d ,idMSB=0x%02x ,idLSB=0x%02x data[", \
                                            temp_parameter_len,tem_parameter.idMSB,tem_parameter.idLSB);
                                     for(i=0;i<(temp_parameter_len-4);i++)
                                         {
                                           printf("%02x",tem_parameter.data[i+4]);
                                         }
                                     printf("] \n");
                                     totla_parameter_len = totla_parameter_len +temp_parameter_len;


                                  }
                       #endif    
                            return ;
                          
                        }
                       

                        if((temp_ctrl_session_msg.idMSB == 0x1D)&&(temp_ctrl_session_msg.idLSB == 0x02))
                        {
                           printf("IdentificationAccept \n");
                           return ;
                        }


                        if((temp_ctrl_session_msg.idMSB == 0x1D)&&(temp_ctrl_session_msg.idLSB == 0x03))
                        {
                           printf("IdentificationRejected \n");
                           printf_ctrl_session_msg(ctrl_session_len,temp_ctrl_session_msg);
                           return ;
                        }




                   }     
              temp_len = temp_len+ ctrl_session_len;
                  
            


            }




       }


}



u_int8_t checksum_calculation(u_int8_t *buffer, u_int16_t start, u_int16_t length)
{
	u_int16_t i;
	u_int8_t
	sum = 0;
	for (i = start; i < (start + length); i++) {
		sum += buffer[i];
	}
	return (u_int8_t)(0x100 - sum); /* 2's complement */
}
