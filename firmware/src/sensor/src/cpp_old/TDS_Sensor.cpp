//
// Created by fadi on 2022-03-11.
//

#include "../../include/cpp_old/TDS_Sensor.hpp"
#include "Arduino.h"
#define INPUT 1

TDS_Sensor::TDS_Sensor(int pin, string name) : Sensor(pin, name, "TDS")
{
    this->_readingPin = pin;
}

float TDS_Sensor::takeMeasurement()
{

    analogBuffer[analogBufferIndex] = analogRead(this->_readingPin);    //read the analog value and store into the buffer
//    analogBufferIndex++;
//    if (analogBufferIndex == SCOUNT)
//    {
//        analogBufferIndex = 0;
//    }
//
//    for (copyIndex = 0; copyIndex < SCOUNT; copyIndex++)
//    {
//        analogBufferTemp[copyIndex] = analogBuffer[copyIndex];
//    }
//    averageVoltage = getMedianNum(analogBufferTemp, SCOUNT) * (float) VREF /
//                     1024.0; // read the analog value more stable by the median filtering algorithm, and convert to voltage value
//
                     float compensationCoefficient = 1.0 + 0.02 * (temperature -
                                                  25.0);    //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));

                                                  float compensationVolatge = averageVoltage / compensationCoefficient;  //temperature compensation
    this->tdsValue = (133.42 * compensationVolatge * compensationVolatge * compensationVolatge
            - 255.86 * compensationVolatge * compensationVolatge + 857.39 * compensationVolatge) * 0.5; //convert voltage value to tds value
    return this->tdsValue;
}

int TDS_Sensor::getMedianNum(int bArray[], int iFilterLen) {
    int bTab[iFilterLen];
    for (int i = 0; i < iFilterLen; i++)
        bTab[i] = bArray[i];
    int i, j, bTemp;
    for (j = 0; j < iFilterLen - 1; j++) {
        for (i = 0; i < iFilterLen - j - 1; i++) {
            if (bTab[i] > bTab[i + 1]) {
                bTemp = bTab[i];
                bTab[i] = bTab[i + 1];
                bTab[i + 1] = bTemp;
            }
        }
    }
    if ((iFilterLen & 1) > 0)
        bTemp = bTab[(iFilterLen - 1) / 2];
    else
        bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
    return bTemp;
}