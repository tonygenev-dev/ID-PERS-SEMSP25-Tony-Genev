#include "menu.h"

#include <iostream>

using namespace std;


/*-------------------------------------------------------------------------------*/
/* Displaying the menu:                                                          */
/*-------------------------------------------------------------------------------*/
void show_menu()
{
    cout << "(1) Show all values" << endl;
    cout << "(2) Add a measurement value" << endl;
    cout << "(3) Test if another measurement value can be added" << endl;
    cout << "(4) Show how often a certain value is stored" << endl;
    cout << "(5) Show the measurement series' name" << endl;
    cout << "(6) Change the measurement series' name" << endl;
    cout << "(7) Test if a certain value is stored" << endl;
    cout << "(9) QUIT" << endl;
}

int read_value()
{    
    int value = -1;

    cout << "Please provide a value:" << endl;
    cin >> value;

    return value;
}

int get_menu_selection()
{
    cout << "Please provide menu selection:" << endl;
    int selection = -1;
    cin >> selection;

    return selection;
}
/*-------------------------------------------------------------------------------*/
/* Methods to handle all menu options:                                           */
/*-------------------------------------------------------------------------------*/
void show_all_values(MeasurementSeries& ms)
{
    int number_of_measurements = 0;
    ms.getNrOfMeasurements(number_of_measurements);

    cout << "Number of values present: " << number_of_measurements << endl;

    for(int i = 0; i < number_of_measurements; i++)
    {
        cout << i << ": " << ms.getValue(i) << endl;
    }
}

void add_measurement_value(MeasurementSeries& ms)
{
    int value = read_value();

    ms.addValue(value);
}

void test_if_measurement_value_be_added(MeasurementSeries& ms)
{
    cout << "Measurement can " <<  (ms.isFull() ? "NOT" : "") << " be added" << endl;
}

void show_how_often_a_value_is_stored(MeasurementSeries& ms)
{
    int count = 0;
    int value = read_value();

    int number_of_measurements = 0;
    ms.getNrOfMeasurements(number_of_measurements);

    for(int i = 0; i < number_of_measurements; i++)
    {
        if(value == ms.getValue(i) )
        {
            count++;
        }
    }

    cout << "Value " << value << " was present for " << count << " times" << endl;

}

void show_measurement_series_name(MeasurementSeries& ms)
{
    cout  << "Name: " << ms.getName() << endl;
}

void change_measurement_series_name(MeasurementSeries& ms)
{
    cout << "Please provide a new name:" << endl;
    string newName = "";
    cin >> newName;

    ms.setName(newName);
}

void test_if_value_is_stored(MeasurementSeries& ms)
{
    int value = read_value();

    bool isStored = ms.valueExists(value);
    cout << "Measurement with value: " << value;
    cout << (isStored ? " does" : " does NOT") << " exist." << endl;
}

int get_value()
{
    cout << "Please provide a value: " << endl;
    int value = -1; 

    cin >> value;
    return value;
}
