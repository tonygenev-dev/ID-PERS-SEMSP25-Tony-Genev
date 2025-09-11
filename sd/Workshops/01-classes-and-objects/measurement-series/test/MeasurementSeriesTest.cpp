#include <string>
#include "gtest/gtest.h"
#include "MeasurementSeries.h"

class MeasurementSeriesTest : public ::testing::Test
{
    protected:
        MeasurementSeriesTest()
        {
            mExamplePtr = new MeasurementSeries(name);
        }

        virtual ~MeasurementSeriesTest()
        {
            delete mExamplePtr;
            mExamplePtr = NULL;
        }

        MeasurementSeries* mExamplePtr;
        const string name = "test";
};

TEST_F(MeasurementSeriesTest, test_WhenCreatedThenObjectHasCorrectState)
{
    EXPECT_EQ(name, mExamplePtr->getName());

    int number = 0;
    mExamplePtr->getNrOfMeasurements(number);
    EXPECT_EQ(0,number);

    EXPECT_FALSE(mExamplePtr->isFull());
}

TEST_F(MeasurementSeriesTest, test_whenAddingValueItIsStored)
{
    const int someValue = 42;
    mExamplePtr->addValue(someValue);

    int number = 0;
    mExamplePtr->getNrOfMeasurements(number);
    EXPECT_EQ(1, number);

    int value = mExamplePtr->getValue(0);
    EXPECT_EQ(someValue, value);
}

TEST_F(MeasurementSeriesTest, test_whenAddingMultipleValuesTheyAreStored)
{
    
}

TEST_F(MeasurementSeriesTest, test_whenValueDoesNotExist)
{
    
}

TEST_F(MeasurementSeriesTest, test_whenNameIsUpdatedThenItStored)
{
    
}

