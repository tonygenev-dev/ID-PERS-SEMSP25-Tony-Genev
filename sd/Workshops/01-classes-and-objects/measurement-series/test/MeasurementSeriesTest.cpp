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
    int someValues[] = {42, 24, 7, 13};  
    int size = sizeof(someValues) / sizeof(someValues[0]);  

    // Add all values
    for (int i = 0; i < size; i++) {
        mExamplePtr->addValue(someValues[i]);
    }

    // Check number of stored values
    int number = 0;
    mExamplePtr->getNrOfMeasurements(number);
    EXPECT_EQ(size, number);

    // Verify each stored value
    for (int i = 0; i < size; i++) {
        EXPECT_EQ(someValues[i], mExamplePtr->getValue(i));
    }
    
    
}

TEST_F(MeasurementSeriesTest, test_whenValueDoesNotExist)
{
    const int nonExistentValue = 12;
    const int existentValue = 42;

    mExamplePtr->addValue(existentValue);

    EXPECT_FALSE(mExamplePtr->valueExists(nonExistentValue));
    EXPECT_TRUE(mExamplePtr->valueExists(existentValue));
    
}

TEST_F(MeasurementSeriesTest, test_whenNameIsUpdatedThenItStored)
{
    const string newName = "newName";

    mExamplePtr->setName(newName);
    
    EXPECT_EQ(newName, mExamplePtr->getName());
    
}

