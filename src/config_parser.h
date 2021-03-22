#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <string>
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>


template <class T>
T convert(const std::string& str) {
  if constexpr (std::is_same_v<std::string, T>) {
    return str;
  }
  else if constexpr (std::is_same_v<char*, T>) {
    return const_cast<char*>(str.c_str());
  }
  else if constexpr (std::is_same_v<const char*, T>) {
    return str.c_str();
  }
  else if constexpr (std::is_same_v<bool, T>) {
    std::string s = str;
    std::transform(s.begin(), s.end(), s.begin(),
    [](unsigned char c){ return std::tolower(c); });
    if (s == "true")
      return true;
    else if (s == "false")
      return false;
    else
      throw std::invalid_argument("Invalid argument.");
  }
  else {
    T res;
    std::stringstream s(str);
    s >> res;
    if (s.fail()) {
      throw std::invalid_argument("Invalid argument.");
    }
    return res;
  }
}

class ConfigParser {
public:
  explicit ConfigParser(const std::string& path);
  ~ConfigParser();
  void Save();

  template <class T>
  void SetValue(const std::string& key, T value) {
    if constexpr (std::is_same_v<std::string, T>) {
      m_values[key] = value;
    }
    else if constexpr(std::is_same_v<bool, T>) {
      m_values[key] = value ? "true" : "false";
    }
    else {
      m_values[key] = std::to_string(value);
    }
  }

  bool HasValue(const std::string& key) {
    return m_values.find(key) != m_values.end();
  }

  template <class T>
  T GetValue(const std::string& key, const T& default_value) {
    try {
      T value = GetValue<T>(key);
      return value;
    } catch(...) {
      return default_value;
    }
  }

  template <class T>
  T GetValue(const std::string& key) {
    if (m_values.find(key) == m_values.end()) {
      throw std::invalid_argument("Invalid argument.");
    }
    return convert<T>(m_values[key]);
  }

private:
  std::map<std::string, std::string> m_values;
  std::fstream m_fstream;
  std::string m_path;

  void Open(std::ios_base::openmode mode = std::ios::in);
  void Load();
  void Close();
  void Parse();
  void Dump();
};

#endif // CONFIG_PARSER_H
