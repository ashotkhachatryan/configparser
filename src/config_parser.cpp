#include "config_parser.h"

namespace {

static inline void ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) { return !std::isspace(ch); }));
}

static inline void rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), s.end());
}

static inline void trim(std::string &s) {
  ltrim(s);
  rtrim(s);
}

}

ConfigParser::ConfigParser(const std::string& path) :
  m_path(path) {
  Load();
}

ConfigParser::~ConfigParser() {
  Close();
}

void ConfigParser::Load() {
  Open();
  Parse();
  Close();
}

void ConfigParser::Save() {
  Open(std::ios::out);
  Dump();
  Close();
}

void ConfigParser::Dump() {
  for (const auto& m : m_values) {
    m_fstream << m.first << "=" << m.second << std::endl;
  }
}

void ConfigParser::Open(std::ios_base::openmode mode) {
  if (!m_fstream.is_open()) {
    m_fstream.open(m_path, mode);
  }
}

void ConfigParser::Close() {
  if (m_fstream.is_open()) {
    m_fstream.close();
  }
}

void ConfigParser::Parse() {
  if (m_fstream.is_open()) {
    std::string line;
    while (getline(m_fstream, line)) {
      int pos = line.find('=');
      if (pos != -1) {
        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1, line.size() - pos - 1);

        trim(key);
        trim(value);

        if (value[0] == '"' && value[value.length() - 1] == '"') {
          value = value.substr(1, value.length() - 2);
        }

        m_values[key] = value;
      }
    }
  }
}
