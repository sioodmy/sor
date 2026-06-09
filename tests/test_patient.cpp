#include "CardiacPatient.hpp"
#include "StandardPatient.hpp"
#include "TraumaPatient.hpp"
#include "TriagePriority.hpp"
#include <gtest/gtest.h>

TEST(PatientTest, Initialization) {
  StandardPatient p("P1", "John", "Doe", 50, 10, 20);
  EXPECT_EQ(p.getId(), "P1");
  EXPECT_EQ(p.getFullName(), "John Doe");
  EXPECT_EQ(p.getHealthStatus(), 50);
  EXPECT_EQ(p.getPriority(), TriagePriority::GREEN);
  EXPECT_FALSE(p.isTreated());
  EXPECT_EQ(p.getDiagnosis(), "Standard Illness");
}

TEST(PatientTest, SetPriority) {
  StandardPatient p("P1", "John", "Doe", 50, 10, 20);
  p.setPriority(TriagePriority::RED);
  EXPECT_EQ(p.getPriority(), TriagePriority::RED);
}

TEST(PatientTest, ReduceTreatmentTime) {
  StandardPatient p("P1", "John", "Doe", 50, 10, 20);
  EXPECT_FALSE(p.isTreated());

  p.reduceTreatmentTime(10);
  EXPECT_FALSE(p.isTreated());

  p.reduceTreatmentTime(15);
  EXPECT_TRUE(p.isTreated());

  p.reduceTreatmentTime(100);
  EXPECT_TRUE(p.isTreated());
}

TEST(PatientTest, TraumaDeterioration) {
  TraumaPatient p("P1", "John", "Doe", 40, 10, 20);
  p.setPriority(TriagePriority::YELLOW);

  EXPECT_FALSE(p.performWaitingStep());
  EXPECT_EQ(p.getPriority(), TriagePriority::YELLOW);
  EXPECT_EQ(p.getHealthStatus(), 35);

  EXPECT_FALSE(p.performWaitingStep());
  EXPECT_EQ(p.getPriority(), TriagePriority::YELLOW);

  EXPECT_TRUE(p.performWaitingStep());
  EXPECT_EQ(p.getPriority(), TriagePriority::RED);
}
