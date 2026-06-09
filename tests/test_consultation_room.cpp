#include "ConsultationRoom.hpp"
#include "Doctor.hpp"
#include "StandardPatient.hpp"
#include <gtest/gtest.h>

TEST(ConsultationRoomTest, BasicFlow) {
  ConsultationRoom room(1, 101);
  EXPECT_TRUE(room.isFree());
  EXPECT_FALSE(room.hasDoctor());

  Doctor doc("D1", "Dr.", "House", "EMP1", "Diagnostic");
  room.assignDoctor(&doc);
  EXPECT_TRUE(room.hasDoctor());
  EXPECT_FALSE(doc.isBusy());

  StandardPatient p("P1", "John", "Doe", 50, 0, 10);
  room.assignPatient(&p);

  EXPECT_FALSE(room.isFree());
  EXPECT_TRUE(doc.isBusy());

  Patient *finished = room.processTreatment(5);
  EXPECT_EQ(finished, nullptr);
  EXPECT_FALSE(room.isFree());
  EXPECT_TRUE(doc.isBusy());

  finished = room.processTreatment(5);
  ASSERT_NE(finished, nullptr);
  EXPECT_EQ(finished->getId(), "P1");
  EXPECT_TRUE(room.isFree());
  EXPECT_FALSE(doc.isBusy());
}
