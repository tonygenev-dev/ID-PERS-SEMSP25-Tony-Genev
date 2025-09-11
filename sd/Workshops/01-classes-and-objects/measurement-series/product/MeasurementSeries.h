#pragma once

#include <string>
using namespace std;

const unsigned int MaxNumberOfMeasurements = 10;

class MeasurementSeries
{
private:
   //TODO: Add the necessary fields
   string name;
   int measurements[MaxNumberOfMeasurements];
   unsigned int currentIndex;

public:   
    MeasurementSeries(string name);
    /* pre : -
       post: MeasurementSeries contains no measurements and the
             name of MeasurementSeries is name
    */

    ~MeasurementSeries();

    string getName();
    /* pre : -
       post: returns the name of MeasurementSeries
    */

    void setName(string name);
    /* pre : -
       post: the name of MeasurementSeries is name
    */

    bool isFull();
    /* pre : -
       post: If the number of measurements in MeasurementSeries is maximal
            Then true
            Else false
    */

    void addValue(int value);
    /* pre : the number of measurements in MeasurementSeries is not maximal
       post: measurement has been added to the measurements of MeasurementSeries
    */

    bool valueExists(int measurement);
    /* pre : -
       post: If measurement exists among the measurements of MeasurementSeries
             Then return true
             Else return false
    */

    int getValue(unsigned index);
    /* pre :  0<=index<number of measurements
       post:  returns the i-th measurement
    */


    void getNrOfMeasurements(int& number);
    /* pre : -
       post : variable “number” is equal to the
              number of measurements of <MeasurementSeries>
    */
};
