#pragma once

#include <map>
#include <string>

class ConfigParser {
private:
  std::map<std::string, std::string> configData;

public:
  ConfigParser(const std::string &filename);

  int getInt(const std::string &key, int defaultValue) const;

  std::string getString(const std::string &key,
                        const std::string &defaultValue) const;
};
