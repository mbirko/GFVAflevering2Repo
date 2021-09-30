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

#ifndef CUSTOMPRINT_H
#define CUSTOMPRINT_H

    #include <stdint.h>
    //prints a sring followed by a interger number 
    void PrintStringInt(char string[], uint8_t strLen, uint8_t number);
        //prints a sring followed by a 16 bit signed interger number 
    void PrintStringSiInt16(char str[], uint8_t len, int16_t num);
    //prints a string followed by a float type number
    void PrintStringFloat(char string[], uint8_t strLen, float number);    
    
#endif

/* [] END OF FILE */
