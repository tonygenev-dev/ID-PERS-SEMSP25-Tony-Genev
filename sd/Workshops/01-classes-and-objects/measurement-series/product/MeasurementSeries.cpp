#include "MeasurementSeries.h"

#include <iostream>
using namespace std;

MeasurementSeries::MeasurementSeries(string name)
   :name(name),currentIndex(0)
{
  
}

MeasurementSeries::~MeasurementSeries()
{
   
}

bool MeasurementSeries::isFull()
{
   return currentIndex >= MaxNumberOfMeasurements;
}

string MeasurementSeries::getName()
{
   return name;
}

void MeasurementSeries::setName(string name)
{
   this->name = name;
}

void MeasurementSeries::addValue(int value)
{
   if (!isFull()) {
       measurements[currentIndex] = value;
       currentIndex++;
   } else {
       cerr << "Measurement series is full. Cannot add more values." << endl;
   }

}

bool MeasurementSeries::valueExists(int measurment){

   for (unsigned int i = 0; i < currentIndex; i++){
      if (measurements[i] == measurment){
         return true;
      } 
   }
   return false;
}

int MeasurementSeries::getValue(unsigned index)
{
   if (index < currentIndex) {
       return measurements[index];
   } else {
       cerr << "Index out of bounds." << endl;
       return 0;
   }
}

void MeasurementSeries::getNrOfMeasurements(int& number)
{
   number = currentIndex;
}


