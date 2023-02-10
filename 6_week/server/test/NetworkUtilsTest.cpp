#include "../include/Server.h"
#include "../include/NetworkUtils.h"
#include <gtest/gtest.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::AtLeast;

class MockNetworkUtils : public NetworkUtils {
  public:
    MOCK_METHOD0(listen, void());
    MOCK_METHOD0(accept, void());
    MOCK_METHOD1(read, void(int));
    MOCK_METHOD1(send, void(int));
};

// TEST(Netwr)