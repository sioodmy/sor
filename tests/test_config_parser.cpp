#include "ConfigParser.hpp"
#include <cstdio>
#include <fstream>
#include <gtest/gtest.h>

TEST(ConfigParserTest, ReadValues) {
  std::string filename = "temp_test_config.ini";
  std::ofstream out(filename);
  out << "num_rooms = 5\n";
  out << "total_time= 100 \n";
  out << "name =  Simulation SOR \n";
  out << "# comment\n";
  out << "missing_value=\n";
  out.close();

  ConfigParser parser(filename);

  EXPECT_EQ(parser.getInt("num_rooms", 3), 5);
  EXPECT_EQ(parser.getInt("total_time", 60), 100);
  EXPECT_EQ(parser.getString("name", "Default"), "Simulation SOR");

  EXPECT_EQ(parser.getInt("not_found", 42), 42);
  EXPECT_EQ(parser.getString("not_found", "N/A"), "N/A");

  std::remove(filename.c_str());
}
