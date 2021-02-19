#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "config_parser.h"
#include <filesystem>
#include <unistd.h>
#include <limits.h>

std::filesystem::path test_path;

TEST_CASE("ConvertTest", "convert_test") {
  // short tests
  // min and max values
  REQUIRE(convert<short>(std::to_string(SHRT_MIN)) == SHRT_MIN);
  REQUIRE(convert<short>(std::to_string(SHRT_MAX)) == SHRT_MAX);
  REQUIRE_THROWS_AS(convert<short>("32768"), std::invalid_argument);
  REQUIRE_THROWS_AS(convert<short>("-32769"), std::invalid_argument);
  REQUIRE(convert<short>("21003") == 21003);
  REQUIRE(convert<short>("-12987") == -12987);
  REQUIRE_THROWS_AS(convert<short>(""), std::invalid_argument);
  REQUIRE_THROWS_AS(convert<short>("abc"), std::invalid_argument);

  // unsigned short tests
  // min and max values
  REQUIRE(convert<unsigned short>("0") == 0);
  REQUIRE(convert<unsigned short>(std::to_string(USHRT_MAX)) == USHRT_MAX);
  //REQUIRE_THROWS_AS(convert<unsigned short>("-1"), std::invalid_argument);
  REQUIRE_THROWS_AS(convert<unsigned short>("65536"), std::invalid_argument);
  REQUIRE(convert<unsigned short>("21003") == 21003);
  REQUIRE(convert<unsigned short>("60001") == 60001);
  REQUIRE_THROWS_AS(convert<unsigned short>(""), std::invalid_argument);
  REQUIRE_THROWS_AS(convert<unsigned short>("abc"), std::invalid_argument);

  // int tests
  // min and max values
  REQUIRE(convert<int>(std::to_string(INT_MIN)) == INT_MIN);
  REQUIRE(convert<int>(std::to_string(INT_MAX)) == INT_MAX);
  REQUIRE_THROWS_AS(convert<int>("-2147483649"), std::invalid_argument);
  REQUIRE_THROWS_AS(convert<int>("2147483648"), std::invalid_argument);
  REQUIRE(convert<int>("273884") == 273884);
  REQUIRE(convert<int>("9299818") == 9299818);
  REQUIRE_THROWS_AS(convert<int>(""), std::invalid_argument);
  REQUIRE_THROWS_AS(convert<int>("abc"), std::invalid_argument);

  // unsigned int tests
  // min and max values
  REQUIRE(convert<unsigned int>("0") == 0);
  REQUIRE(convert<unsigned int>(std::to_string(UINT_MAX)) == UINT_MAX);
  //REQUIRE_THROWS_AS(convert<unsigned int>("-1"), std::invalid_argument);
  REQUIRE_THROWS_AS(convert<unsigned int>("4294967296"), std::invalid_argument);
  REQUIRE(convert<unsigned int>("273884") == 273884);
  REQUIRE(convert<unsigned int>("9299818") == 9299818);
  REQUIRE_THROWS_AS(convert<unsigned int>(""), std::invalid_argument);
  REQUIRE_THROWS_AS(convert<unsigned int>("abc"), std::invalid_argument);

  // long tests
  // min and max values
  REQUIRE(convert<long>(std::to_string(LONG_MIN)) == LONG_MIN);
  REQUIRE(convert<long>(std::to_string(LONG_MAX)) == LONG_MAX);
  REQUIRE_THROWS_AS(convert<long>("-9223372036854775809"), std::invalid_argument);
  REQUIRE_THROWS_AS(convert<long>("9223372036854775808"), std::invalid_argument);
  REQUIRE(convert<long>("2738838939934") == 2738838939934);
  REQUIRE(convert<long>("9299810299488") == 9299810299488);
  REQUIRE_THROWS_AS(convert<long>(""), std::invalid_argument);
  REQUIRE_THROWS_AS(convert<long>("abc"), std::invalid_argument);

  // unsigned long tests
  // min and max values
  REQUIRE(convert<unsigned long>("0") == 0);
  REQUIRE(convert<unsigned long>(std::to_string(ULONG_MAX)) == ULONG_MAX);
  //REQUIRE_THROWS_AS(convert<unsigned long>("-1"), std::invalid_argument);
  REQUIRE_THROWS_AS(convert<unsigned long>("18446744073709551616"), std::invalid_argument);
  REQUIRE(convert<unsigned long>("2738838939934") == 2738838939934);
  REQUIRE(convert<unsigned long>("9299810299488") == 9299810299488);
  REQUIRE_THROWS_AS(convert<unsigned long>(""), std::invalid_argument);
  REQUIRE_THROWS_AS(convert<unsigned long>("abc"), std::invalid_argument);

  // long long tests
  // min and max values
  REQUIRE(convert<long long>(std::to_string(LONG_MIN)) == LONG_MIN);
  REQUIRE(convert<long long>(std::to_string(LONG_MAX)) == LONG_MAX);
  REQUIRE_THROWS_AS(convert<long long>("-9223372036854775809"), std::invalid_argument);
  REQUIRE_THROWS_AS(convert<long long>("9223372036854775808"), std::invalid_argument);
  REQUIRE(convert<long long>("2738838939934") == 2738838939934);
  REQUIRE(convert<long long>("9299810299488") == 9299810299488);
  REQUIRE_THROWS_AS(convert<long long>(""), std::invalid_argument);
  REQUIRE_THROWS_AS(convert<long long>("abc"), std::invalid_argument);

  // unsigned long long tests
  // min and max values
  REQUIRE(convert<unsigned long long>("0") == 0);
  REQUIRE(convert<unsigned long long>(std::to_string(ULONG_MAX)) == ULONG_MAX);
  //REQUIRE_THROWS_AS(convert<unsigned long long>("-1"), std::invalid_argument);
  REQUIRE_THROWS_AS(convert<unsigned long long>("18446744073709551616"), std::invalid_argument);
  REQUIRE(convert<unsigned long long>("2738838939934") == 2738838939934);
  REQUIRE(convert<unsigned long long>("9299810299488") == 9299810299488);
  REQUIRE_THROWS_AS(convert<unsigned long long>(""), std::invalid_argument);
  REQUIRE_THROWS_AS(convert<unsigned long long>("abc"), std::invalid_argument);

  // bool tests
  REQUIRE(convert<bool>("True") == true);
  REQUIRE(convert<bool>("TruE") == true);
  REQUIRE(convert<bool>("TRUE") == true);
  REQUIRE(convert<bool>("true") == true);
  REQUIRE(convert<bool>("False") == false);
  REQUIRE(convert<bool>("FalsE") == false);
  REQUIRE(convert<bool>("FALSE") == false);
  REQUIRE(convert<bool>("false") == false);

  // std::strin tests
  REQUIRE(convert<std::string>("string") == "string");
  
  REQUIRE(convert<double>("3.456") == 3.456);
  REQUIRE(convert<float>("12.334") == static_cast<float>(12.334));

  REQUIRE(convert<char>("3") == '3');
  REQUIRE(strcmp(convert<char*>("abc333"), "abc333") == 0);
  REQUIRE(strcmp(convert<const char*>("abc333"), "abc333") == 0);
}

TEST_CASE("ValueTypesTest", "[value_types_test]") {
  ConfigParser parser(test_path / "data/test_config1.ini");
  REQUIRE(parser.GetValue<std::string>("str_value") == "str");
  REQUIRE(parser.GetValue<int>("int_value") == 1234);
  REQUIRE(parser.GetValue<double>("double_value") == 12.344);
  REQUIRE(parser.GetValue<bool>("bool_value") == true);

  // This should throw an exception because default value is not given
  REQUIRE_THROWS(parser.GetValue<bool>("bool_value1"));

  REQUIRE(parser.GetValue("bool_value1", true) == true);
  REQUIRE(parser.GetValue("bool_value1", false) == false);
  //short a = parser.GetValue<short>("int_value");
  //std::cout << a << std::endl;
}

TEST_CASE("CommentTest", "[comment_test]") {
  ConfigParser parser(test_path / "data/test_config2.ini");
  REQUIRE(!parser.HasValue("value1"));
  REQUIRE(parser.GetValue<int>("value2") == 45);
  REQUIRE(parser.GetValue<int>("value3") == 456);
}

TEST_CASE("SpacesTest", "[spaces_test]") {
  ConfigParser parser(test_path / "data/test_config3.ini");
  REQUIRE(parser.GetValue<std::string>("value1") == "abc");
  REQUIRE(parser.GetValue<int>("value2") == 1234);
  REQUIRE(parser.GetValue<std::string>("value3") == "   abc ");
  REQUIRE(parser.GetValue<std::string>("value4") == "xyz");
  REQUIRE(parser.GetValue<bool>("value5") == true);
  REQUIRE_THROWS(parser.GetValue<bool>("value6"));
  REQUIRE(parser.GetValue<std::string>("value7") == "\" abc");
  REQUIRE(parser.GetValue<std::string>("value8") == "abc \"");

  REQUIRE(parser.GetValue<int>("value9") == 45);
  REQUIRE(parser.GetValue<std::string>("value9") == "45 66");
  REQUIRE_THROWS(parser.GetValue<bool>("value10"));
}

TEST_CASE("BoolTest", "[bool_test]") {
  ConfigParser parser(test_path / "data/test_config4.ini");
  REQUIRE(parser.GetValue<bool>("bool_value1") == true);
  REQUIRE(parser.GetValue<bool>("bool_value2") == true);
  REQUIRE(parser.GetValue<bool>("bool_value3") == true);
  REQUIRE(parser.GetValue<bool>("bool_value4") == true);
  REQUIRE(parser.GetValue<bool>("bool_value5") == false);
  REQUIRE(parser.GetValue<bool>("bool_value6") == false);
  REQUIRE(parser.GetValue<bool>("bool_value7") == false);
  REQUIRE(parser.GetValue<bool>("bool_value8") == false);
}

TEST_CASE("SetValue", "[set_value]") {
  ConfigParser parser(test_path / "data/test_config.ini");
  parser.SetValue<std::string>("value1", "val");
  parser.SetValue("value2", 129);
  parser.SetValue("value3", true);
  parser.SetValue("value4", 12.987);

  REQUIRE(parser.GetValue<std::string>("value1") == "val");
  REQUIRE(parser.GetValue<int>("value2") == 129);
  REQUIRE(parser.GetValue<bool>("value3") == true);
  REQUIRE(parser.GetValue<double>("value4") == 12.987);
}

TEST_CASE("SaveTest", "[save_test]") {
  ConfigParser parser(test_path / "data/test_config5.ini");
  parser.SetValue<std::string>("value1", "val");
  parser.SetValue("value2", 349);
  parser.SetValue("value3", false);
  parser.SetValue("value4", 443.44);
  parser.SetValue<std::string>("value5", "");
  parser.Save();

  ConfigParser parser1(test_path / "data/test_config5.ini");
  REQUIRE(parser1.GetValue<std::string>("value1") == "val");
  REQUIRE(parser1.GetValue<int>("value2") == 349);
  REQUIRE(parser1.GetValue<bool>("value3") == false);
  REQUIRE(parser1.GetValue<double>("value4") == 443.44);
  REQUIRE(parser1.GetValue<std::string>("value5") == "");
}

TEST_CASE("GetWithDefaultTest", "[get_with_default]") {
  ConfigParser parser(test_path / "data/test_config6.ini");
  REQUIRE(parser.GetValue<std::string>("abc", "abc") == "abc");
  parser.SetValue<std::string>("abc", "value");
  REQUIRE(parser.GetValue<std::string>("abc", "abc") == "value");

  REQUIRE(parser.GetValue("int_num", 1323) == 1323);
  parser.SetValue("int_num", 11111);
  REQUIRE(parser.GetValue("int_num", 1323) == 11111);
}

int main(int argc, char* argv[]) {
  std::filesystem::path p(argv[0]);

  test_path = std::filesystem::current_path() / p.parent_path();
  int result = Catch::Session().run(argc, argv);
  return result;
}
