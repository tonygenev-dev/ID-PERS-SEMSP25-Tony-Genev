//============================================================================
// Name        : MeetSerie.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "MeasurementSeries.h"
#include "menu.h"

#include <iostream>

using namespace std;

int main()
{
    cout << "MeasurementSeries:" << endl; 

    MeasurementSeries ms("Example");
    bool running = true;

    while(running)
    {
        show_menu();
        int selection = get_menu_selection();
        
        switch(selection) {
            case MENU_SHOW_ALL_VALUES:
            show_all_values(ms);
            break;
            case MENU_ADD_MEASUREMENT_VALUE:
            add_measurement_value(ms);
            break;
            case MENU_TEST_IF_MEASUREMENT_CAN_BE_ADDED:
            test_if_measurement_value_be_added(ms);
            break;
            case MENU_SHOW_HOW_OFTEN_VALUE_IS_STORED:
            show_how_often_a_value_is_stored(ms);
            break;
            case MENU_SHOW_MEASUREMENT_SERIES_NAME:
            show_measurement_series_name(ms);
            break;
            case MENU_CHANGE_MEASUREMENT_SERIES_NAME:
            change_measurement_series_name(ms);
            break;
            case MENU_TEST_IF_VALUE_IS_STORED:
            test_if_value_is_stored(ms);
            break;                                   
            case MENU_QUIT:
                cout << "Bye!" << endl;
                running = false;
            break;
            default:
                cout << "Unknow selection: " << selection << endl;
        }
    }

    return 0;
}
