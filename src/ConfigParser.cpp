#include "ConfigParser.hpp"
#include <fstream>
#include <sstream>

ConfigParser::ConfigParser(const std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open())
    return;

  std::string line;
  while (std::getline(file, line)) {
    if (line.empty() || line[0] == '#' || line[0] == ';')
      continue;

    auto delimiterPos = line.find('=');
    if (delimiterPos == std::string::npos) {
      delimiterPos = line.find(':');
    }

    if (delimiterPos != std::string::npos) {
      std::string key = line.substr(0, delimiterPos);
      std::string value = line.substr(delimiterPos + 1);

      key.erase(0, key.find_first_not_of(" \t"));
      key.erase(key.find_last_not_of(" \t") + 1);
      value.erase(0, value.find_first_not_of(" \t"));
      value.erase(value.find_last_not_of(" \t") + 1);

      configData[key] = value;
    }
  }
}

int ConfigParser::getInt(const std::string &key, int defaultValue) const {
  auto it = configData.find(key);
  if (it != configData.end()) {
    try {
      return std::stoi(it->second);
    } catch (...) {
      return defaultValue;
    }
  }
  return defaultValue;
}

std::string ConfigParser::getString(const std::string &key,
                                    const std::string &defaultValue) const {
  auto it = configData.find(key);
  if (it != configData.end()) {
    return it->second;
  }
  return defaultValue;
}
