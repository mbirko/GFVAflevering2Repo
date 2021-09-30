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

//includes 
#include "project.h"
#include <stdint.h>
#include "CustomPrint.h"
#include "LM75.h"

//interubt service rutines prototypes 
CY_ISR_PROTO (UART_Rx_CT_Handeler);



//bools 
bool correctRead = false;
bool readTemp = false;

//global variebels 
uint16_t temp = 0;
float temperatureFloat;



int main(void)
{

    //interrubt enablers! 
    CyGlobalIntEnable; /* Enable global interrupts. */
    isr_UART_CT_StartEx(UART_Rx_CT_Handeler);
    
    //componet enables 
    UART_CT_Start();
    I2C_M_Start();
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    UART_CT_PutString("Program started!\r\n");
    
    for(;;)
    {
        /*
        temp = getTemp2(LM75_1);
        PrintStringSiInt16("binary read", 11, temp);
        PrintStringSiInt16("tempeture read", 14, convertToCeltius(temp));
        */
        
        
        if (readTemp)  
        {
            UART_CT_PutString("trying to read temp \r\n");
            temperatureFloat = getTemp(LM75_1);
            correctRead = true; 
            readTemp = false;
        }
        if (correctRead)
        {
            PrintStringFloat("temperature", 11, temperatureFloat);
            correctRead = false;
        }   
        
    }
}


// interubt services rutines 


CY_ISR (UART_Rx_CT_Handeler)
{
    uint8_t numberOfBytes = UART_CT_GetRxBufferSize();
    
    for (uint8_t i = 0; i < numberOfBytes; i++)
    {
        char c = UART_CT_GetChar();
        
        // takes actions based on input. 
        switch (c)
        {
            case 't' :             
            {
            UART_CT_PutString("test!\r\n");
                        PrintStringSiInt16("before", 6, temp);
            PrintStringFloat("T.C. Float", 10, (float)temp);            
            PrintStringFloat("temperature", 11, convertToCeltius(temp));


            }
            break;
            case 'i' :             
            {
                UART_CT_PutString("testing print int!\r\n");
                PrintStringFloat("int", 3, 7);
            }
            break;
            case 'f' :             
            {   
                UART_CT_PutString("test print float!\r\n");
                PrintStringFloat("float", 5, 3.6);
            }
            break;
            case 'g' :             
            {   
                UART_CT_PutString("testing getting temp\r\n");
                readTemp = true; 
            }
            break;
            case '1' :             
            {   
                UART_CT_PutString("testing converting -25!\r\n");
                temp = 0xFFCE;
                PrintStringSiInt16("before", 6, temp);
                PrintStringFloat("T.C Float", 9, (float)temp);                
                PrintStringFloat("converted", 9, convertToCeltius(temp));
            }
            break;
            case '2' :             
            {   
                UART_CT_PutString("testing converting -55!\r\n");
                temp = 0xFF92;
                PrintStringSiInt16("before", 6, temp);
                PrintStringFloat("T.C Float", 9, (float)temp);
                PrintStringFloat("converted", 9, convertToCeltius(temp));
            }
            break;
            case '3' :             
            {   
                UART_CT_PutString("testing converting 125!\r\n");
                temp = 0x00FA;
                PrintStringSiInt16("before", 6, temp);
                PrintStringFloat("T.C Float", 9, (float)temp);
                PrintStringFloat("converted", 9, convertToCeltius(temp));
            }
            break;
            default:                
            {
                UART_CT_PutChar(c);
                UART_CT_PutString("\r\n");
            }
            break;
        }
    }
} // end of uart handeler

/* [] END OF FILE */
