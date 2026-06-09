#include "Nurse.hpp"
#include "StandardPatient.hpp"
#include "TriagePriority.hpp"
#include <gtest/gtest.h>

TEST(NurseTest, PerformTriage) {
  Nurse nurse("N1", "Anna", "Smith", "EMP_N1");
  EXPECT_FALSE(nurse.isBusy());

  StandardPatient redPatient("P1", "A", "B", 20, 0, 10);
  StandardPatient yellowPatient("P2", "C", "D", 50, 0, 10);
  StandardPatient greenPatient("P3", "E", "F", 80, 0, 10);

  nurse.performTriage(&redPatient);
  nurse.performTriage(&yellowPatient);
  nurse.performTriage(&greenPatient);

  EXPECT_EQ(redPatient.getPriority(), TriagePriority::RED);
  EXPECT_EQ(yellowPatient.getPriority(), TriagePriority::YELLOW);
  EXPECT_EQ(greenPatient.getPriority(), TriagePriority::GREEN);
}
