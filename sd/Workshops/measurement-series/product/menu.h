#pragma once

#include "MeasurementSeries.h"

#define MENU_SHOW_ALL_VALUES (1)
#define MENU_ADD_MEASUREMENT_VALUE (2)
#define MENU_TEST_IF_MEASUREMENT_CAN_BE_ADDED (3)
#define MENU_SHOW_HOW_OFTEN_VALUE_IS_STORED (4)
#define MENU_SHOW_MEASUREMENT_SERIES_NAME (5)
#define MENU_CHANGE_MEASUREMENT_SERIES_NAME (6)
#define MENU_TEST_IF_VALUE_IS_STORED (7)
#define MENU_QUIT (9)

void show_menu();
int get_menu_selection();

void show_all_values(MeasurementSeries& ms);
void add_measurement_value(MeasurementSeries& ms);
void test_if_measurement_value_be_added(MeasurementSeries& ms);
void show_how_often_a_value_is_stored(MeasurementSeries& ms);
void show_measurement_series_name(MeasurementSeries& ms);
void change_measurement_series_name(MeasurementSeries& ms);
void test_if_value_is_stored(MeasurementSeries& ms);
