#include "StandardPatient.hpp"
#include "TriagePriority.hpp"
#include "WaitingRoom.hpp"
#include <gtest/gtest.h>

TEST(WaitingRoomTest, QueueOrdering) {
  WaitingRoom wr(10);
  EXPECT_TRUE(wr.isEmpty());
  EXPECT_EQ(wr.getWaitingCount(), 0);

  StandardPatient p1("P1", "A", "B", 80, 0, 10);
  p1.setPriority(TriagePriority::GREEN);

  StandardPatient p2("P2", "C", "D", 20, 0, 10);
  p2.setPriority(TriagePriority::RED);

  StandardPatient p3("P3", "E", "F", 50, 0, 10);
  p3.setPriority(TriagePriority::YELLOW);

  wr.addPatient(&p1);
  wr.addPatient(&p2);
  wr.addPatient(&p3);

  EXPECT_FALSE(wr.isEmpty());
  EXPECT_EQ(wr.getWaitingCount(), 3);

  Patient *first = wr.getNextPatient();
  ASSERT_NE(first, nullptr);
  EXPECT_EQ(first->getId(), "P2");
  EXPECT_EQ(first->getPriority(), TriagePriority::RED);

  Patient *second = wr.getNextPatient();
  ASSERT_NE(second, nullptr);
  EXPECT_EQ(second->getId(), "P3");
  EXPECT_EQ(second->getPriority(), TriagePriority::YELLOW);

  Patient *third = wr.getNextPatient();
  ASSERT_NE(third, nullptr);
  EXPECT_EQ(third->getId(), "P1");
  EXPECT_EQ(third->getPriority(), TriagePriority::GREEN);

  EXPECT_TRUE(wr.isEmpty());
  EXPECT_EQ(wr.getNextPatient(), nullptr);
}
