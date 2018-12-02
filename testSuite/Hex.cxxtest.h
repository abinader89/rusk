#ifndef HEX_CXXTEST_H
#define HEX_CXXTEST_H

#include <cxxtest/TestSuite.h>
#include "Hex.h"

class TestHexSuite : public CxxTest::TestSuite
{
    public:
    void testEmptyConstructor() {
        Hex test_hex;

        TS_ASSERT_EQUALS(test_hex.owner, -1);
        TS_ASSERT_EQUALS(test_hex.numberOfArmies, 0);
        TS_ASSERT(!(test_hex.isSelected));
        TS_ASSERT(!(test_hex.isAttackTarget));
    }

    void testParameterConstructor() {
        Hex test_hex(1, 10);

        TS_ASSERT_EQUALS(test_hex.owner, 1);
        TS_ASSERT_EQUALS(test_hex.numberOfArmies, 10);
    }

};

#endif
