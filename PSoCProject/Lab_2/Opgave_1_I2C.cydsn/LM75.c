/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
    #include <stdint.h>
    #include <stdbool.h>
    #include "project.h"
    #include "CustomPrint.h"



    float getTemp(uint8_t slaveAddress)
    {
        float temperature;
        
        UART_CT_PutString("reading temp \r\n");
        uint8_t status;
        status = I2C_M_MasterSendStart(slaveAddress, 1); 
        PrintStringInt("status", 6, status);
        
        if (status == I2C_M_MSTR_NO_ERROR)
        {
            UART_CT_PutString("status no error\r\n");
            uint8_t bH = I2C_M_MasterReadByte(I2C_M_ACK_DATA);
            uint8_t bL = I2C_M_MasterReadByte(I2C_M_NAK_DATA);
            
            //cleaning trash bits
            bL = bL & 0x10000000;
            
            I2C_M_MasterSendStop();
            //creating a 16 bit number from the two bytes.
            uint16_t byte = (bH << 8) | bL; 
            byte = byte >> 8; 
            
           //convertin to normal binary number.
            byte = ((~byte) & 0x01ff) + 1;
            
            if (byte & 0x0100)
            {
                temperature = (((byte & 0x00ff) * -1) / 2); //does this need 
            }
            else
                temperature = (byte & 0x00ff) / 2;
                
            return temperature;
        }
        else
        {
            PrintStringInt("Fejl: ", 9, status);
            I2C_M_MasterSendStop();
            return 0xffff;
        }
    }
    
    float convertToCeltius(int16_t temp)
    {
        return ((float)temp / 2);
    }
    

/* [] END OF FILE */
