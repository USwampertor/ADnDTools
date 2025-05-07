#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <wchar.h>
#include <vector>
#include <chrono>
#include <string>
#include <thread>
#include <stdexcept>
#include <algorithm>
#include <map>

#define RAPIDJSON_HAS_STDSTRING 1

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>


#define BETTER_ENUMS_STRICT_CONVERSION
#include <better-enums/enum.h>

namespace ADND
{
using uint64 = uint64_t;
using int64 = int64_t;
using int32 = int32_t;
using uint32 = uint32_t;
using int8 = int8_t;
using uint8 = uint8_t;
using int16 = int16_t;
using uint16 = uint16_t;

using String = std::string;
using WString = std::wstring;

template<typename KEY,
         typename T,
         typename B = std::less<KEY>,
         typename A = std::allocator<std::pair<const KEY, T>>>
using Map = std::map<KEY, T, B, A>;

template<typename T, typename A = std::allocator<T>>
using Vector = std::vector<T, A>;

template<typename T, typename A>
using Pair = std::pair<T, A>;

using TM = std::tm;


struct Utils {
public:

  /*
   *	@brief	runs a command with the given commandLine. This is a wrapper for system() function
   *	@param	const String& commandLine the cmd line to run
   */
  static void
  runCommand(const String& commandLine) {
    system(commandLine.c_str());
  }

  /*
   *	@brief	Formats a string with given parameters.
   *          This is a snprintf() wrapper but using String objects
   *	@param  const String& format the string with formats
   *	@param  Args ... args the arguments to pass to the formatting
   *  @return	A String with the parameters formatted
   */
  template<typename ... Args>
  static String format(const String& format, Args ... args) {

    const char* formatCstr = format.c_str();

    int32 size_s = std::snprintf(nullptr, 0, formatCstr, std::forward<Args>(args)...) + 1; // Extra space for '\0'
    if (size_s <= 0) { throwRuntimeError("Error during formatting."); }
    auto size = static_cast<size_t>(size_s);
    auto buf = std::make_unique<char[]>(size);
    std::snprintf(buf.get(), size, formatCstr, std::forward<Args>(args)...);
    return String(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
  }

  /*
   *	@brief  formats the TM object into a specific string type
   *	@param  const TM& toFormat the TM to format
   *	@param  const String& format the format
   *  @return	String with the TM formatted
   */
  static String
  timeFormat(const TM& toformat, const String& format) {
    char buffer[128];
    std::strftime(buffer, sizeof(buffer), format.c_str(), &toformat);
    return String(buffer);
  }

  /*
   *	@brief Changes a number to a string. This is just a std::to_string wrapper
   *	@param  const T& number - The number to format to string
   *  @return	a String with the number
   */
  template<typename T>
  static String
  toString(const T& number) {
    return std::to_string(number);
  }

  /*
   *	@brief	Throws a std::exception with the given message
   *	@param	const String& message the message the exception will have
   */
  static void
  throwException(const String& message) {
    throw::std::exception(message.c_str());
  }

  /*
   *	@brief	throws a std::runtime_error with the given message
   *	@param	const String& message the message the runtime_error will have
   */
  static void
  throwRuntimeError(const String& message) {
    throw::std::runtime_error(message.c_str());
  }

  /*
   *	@brief	Converts a String to a Wide String
   *	@param	const String& str the string to transform
   *  @return	WString copy of the String
   */
  static WString
  toWide(const String& str) {
    WString stemp = WString(str.begin(), str.end());
    return stemp;

  }

  /*
   *	@brief  Converts a string to lowercase
   *	@param  const String& str the string to turn into lowercase
   *  @return	a copy of the string but in lowercase
   */
  static String
  toLowerCase(const String& str) {
    String copy = str;
    std::transform(copy.begin(),
      copy.end(),
      copy.begin(),
      [](unsigned char c) { return std::tolower(c); });
    return copy;
  }

  /*
   *	@brief  Converts a string to lowercase
   *	@param  const String& str the string to turn into lowercase
   *  @return	a copy of the string but in lowercase
   */
  static String
  toUpperCase(const String& str) {
    String copy = str;
    std::transform(copy.begin(),
      copy.end(),
      copy.begin(),
      [](unsigned char c) { return std::toupper(c); });
    return copy;
  }


  /*
   *	@brief  Creates a pair with given parameters. This is a wrapper for std::make_pair
   *	@param  T value1 value 1 from the pair
   *	@param  T value2 value 2 from the pair
   *  @return	a Pair<T, A> with the two given objects
   */
  template<typename T, typename A>
  static Pair<T, A>
    makePair(T value1, A value2) {
    return std::make_pair(value1, value2);
  }

};

using JSONFileReader = rapidjson::FileReadStream;

using JSONFileWriter = rapidjson::FileWriteStream;

using JSONIStream = rapidjson::IStreamWrapper;

using JSONOStream = rapidjson::OStreamWrapper;

template<typename T>
using JSONPrettyWriter = rapidjson::PrettyWriter<T>;

using JSONValue = rapidjson::Value;

template<typename T>
using JSONWriter = rapidjson::Writer<T>;

using JSONStringBuffer = rapidjson::StringBuffer;

class JSONDocument : public rapidjson::Document
{
public:

  const ADND::String
    stringify() {
    JSONStringBuffer buffer;
    JSONWriter<JSONStringBuffer> writer(buffer);
    Accept(writer);
    return buffer.GetString();
  }

  const ADND::String
    prettyString() {
    JSONStringBuffer buffer;
    JSONPrettyWriter<JSONStringBuffer> writer(buffer);
    Accept(writer);
    return buffer.GetString();
  }
};

}
