#include <string>
#include "gtest/gtest.h"


TEST(EmptyProjectLooseTests, test_construction_with_count)
{
    
    
}

class TestEmptyProject : public ::testing::Test
{
    protected:

        TestEmptyProject()
        {
            
        }

        virtual ~TestEmptyProject()
        {
            
        }
        
};

TEST_F(TestEmptyProject, test_example)
{
    // in here you can directly use variables from the TestEmptyProject class (i.e. mExamplePtr and maxNrElements)
    EXPECT_TRUE(true);
}
