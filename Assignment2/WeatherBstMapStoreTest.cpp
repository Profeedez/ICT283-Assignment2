// WeatherBstMapStoreTest.cpp
//
// Console test program for the WeatherBstMapStore class.
// Verifies insertion, duplicate handling, year grouping,
// month grouping, search, and selected statistics behaviour.
//
// Version
// 01 04/04/2026 Heng Kiao Woon - Initial WeatherBstMapStore unit test.
// 02 04/04/2026 Heng Kiao Woon - Updated for BST-of-years design.
//---------------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Includes
#include "WeatherBstMapStore.h"
#include "Date.h"
#include "Time.h"
#include "WeatherRecType.h"

#include <iostream>

//----------------------------------------------------------------------------
// Helper functions
void PrintTestResult(const std::string& testName, bool passed)
{
    std::cout << testName << ": "
              << (passed ? "PASSED" : "FAILED")
              << std::endl;
}

//----------------------------------------------------------------------------
// Program entry point
int main()
{
    std::cout << "===== WeatherBstMapStoreTest =====" << std::endl << std::endl;

    WeatherBstMapStore store;

    WeatherRecType record1(Date(1, 3, 2016), Time(9, 0, 0), 5.0f, 20.0f, 300.0f);
    WeatherRecType record2(Date(2, 3, 2016), Time(10, 0, 0), 7.0f, 22.0f, 360.0f);
    WeatherRecType record3(Date(1, 4, 2016), Time(9, 30, 0), 8.0f, 24.0f, 420.0f);
    WeatherRecType record4(Date(1, 3, 2017), Time(9, 30, 0), 6.0f, 21.0f, 330.0f);

    //----------------------------------------------------------------------------
    // Constructor and insertion tests
    bool test1 = (store.GetYearCount() == 0);
    PrintTestResult("Test 1 - Constructor starts empty", test1);

    bool inserted1 = store.AddRecord(record1);
    PrintTestResult("Test 2 - First insert succeeds", inserted1);

    bool test3 = store.HasYear(2016);
    PrintTestResult("Test 3 - Year 2016 exists after insert", test3);

    bool test4 = store.ContainsRecord(2016, record1);
    PrintTestResult("Test 4 - Record searchable in March 2016 BST", test4);

    bool insertedDuplicate = store.AddRecord(record1);
    PrintTestResult("Test 5 - Duplicate insert rejected", !insertedDuplicate);

    bool inserted2 = store.AddRecord(record2);
    PrintTestResult("Test 6 - Second March 2016 record inserted", inserted2);

    bool inserted3 = store.AddRecord(record3);
    PrintTestResult("Test 7 - April 2016 record inserted", inserted3);

    bool inserted4 = store.AddRecord(record4);
    PrintTestResult("Test 8 - March 2017 record inserted", inserted4);

    bool test9 = (store.GetYearCount() == 2);
    PrintTestResult("Test 9 - Outer BST contains 2 years", test9);

    bool test10 = store.HasYear(2017);
    PrintTestResult("Test 10 - Year 2017 exists", test10);

    bool test11 = store.ContainsRecord(2017, record4);
    PrintTestResult("Test 11 - Record searchable in March 2017 BST", test11);

    //----------------------------------------------------------------------------
    // Month separation tests
    bool test12 = !store.ContainsRecord(2016, record4);
    PrintTestResult("Test 12 - 2017 record not found in 2016", test12);

    float marchMean2016 = store.FindSpeedMean(3, 2016);
    bool test13 = (marchMean2016 > 5.9f && marchMean2016 < 6.1f);
    PrintTestResult("Test 13 - March 2016 speed mean is correct", test13);

    float aprilMean2016 = store.FindSpeedMean(4, 2016);
    bool test14 = (aprilMean2016 > 7.9f && aprilMean2016 < 8.1f);
    PrintTestResult("Test 14 - April 2016 speed mean is correct", test14);

    bool test15 = store.HasValidWind(3, 2016);
    PrintTestResult("Test 15 - March 2016 has valid wind", test15);

    bool test16 = store.HasValidTemperature(3, 2016);
    PrintTestResult("Test 16 - March 2016 has valid temperature", test16);

    bool test17 = store.HasValidSolar(3, 2016);
    PrintTestResult("Test 17 - March 2016 has valid solar", test17);

    float tempMean2016 = store.FindTemperatureMean(3, 2016);
    bool test18 = (tempMean2016 > 20.9f && tempMean2016 < 21.1f);
    PrintTestResult("Test 18 - March 2016 temperature mean is correct", test18);

    float solarTotal2016 = store.FindTotalSolar(3, 2016);
    bool test19 = (solarTotal2016 > 0.10f);
    PrintTestResult("Test 19 - March 2016 solar total computed", test19);

    float st = 0.0f;
    float sr = 0.0f;
    float tr = 0.0f;
    store.FindSPCCForMonthAllYears(3, st, sr, tr);
    bool test20 = true;
    PrintTestResult("Test 20 - SPCC call completed for March", test20);

    //----------------------------------------------------------------------------
    // Overall result
    bool overallPassed = test1 && inserted1 && test3 && test4 &&
                         !insertedDuplicate && inserted2 && inserted3 &&
                         inserted4 && test9 && test10 && test11 &&
                         test12 && test13 && test14 && test15 &&
                         test16 && test17 && test18 && test19 && test20;

    std::cout << "\nOverall Result: "
              << (overallPassed ? "PASSED" : "FAILED")
              << std::endl;

    return 0;
}
