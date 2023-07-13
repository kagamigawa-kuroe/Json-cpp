#include "json.h"
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <vector>
using namespace hongzhe;

Json::Json() : m_type(json_null) {}

Json::Json(bool value) : m_type(json_bool) { m_value.m_bool = value; }

Json::Json(int value) : m_type(json_int) { m_value.m_int = value; }

Json::Json(double value) : m_type(json_double) { m_value.m_double = value; }

Json::Json(const char *value) : m_type(json_string) {
  m_value.m_string = new string(value);
}

Json::Json(const string &value) : m_type(json_string) {
  m_value.m_string = new string(value);
}

Json::Json(const Json &other) : m_type(other.m_type) {
  // 指针需要用深拷贝
  if (m_type == json_string) {
    m_value.m_string = new string(*(other.m_value.m_string));
  } else if (m_type == json_array) {
    m_value.m_array = new vector<Json>();
    for (auto &i : *(other.m_value.m_array)) {
      m_value.m_array->push_back(i);
    }
  } else if (m_type == json_object) {
    m_value.m_object = new map<string, Json>();
    for (auto &[k, v] : *(other.m_value.m_object)) {
      (*(m_value.m_object))[k] = v;
    }
  } else {
    m_value = other.m_value;
  }
}

Json::Json(Type type) : m_type(type) {
  switch (m_type) {
  case json_null:
    break;
  case json_bool:
    m_value.m_bool = false;
  case json_int:
    m_value.m_int = 0;
  case json_string:
    m_value.m_string = new string("");
  case json_double:
    m_value.m_double = 0;
  case json_array:
    m_value.m_array = new vector<Json>();
  case json_object:
    m_value.m_object = new map<string, Json>();
  default:
    break;
  }
}

Json::operator bool() {
  if (m_type != json_bool) {
    throw logic_error("type error, not bool");
  }
  return m_value.m_bool;
}

Json::operator int() {
  if (m_type != json_int) {
    throw logic_error("type error, not int");
  }
  return m_value.m_int;
}

Json::operator double() {
  if (m_type != json_double) {
    throw logic_error("type error, not double");
  }
  return m_value.m_double;
}

Json::operator string() {
  if (m_type != json_string) {
    throw logic_error("type error, not string");
  }
  return *m_value.m_string;
}

Json &Json::operator[](int index) {
  if (m_type != json_array) {
    m_type = json_array;
    m_value.m_array = new vector<Json>();
  }
  if (index < 0) {
    throw new logic_error("array index < 0");
  }
  int size = m_value.m_array->size();
  if (index >= size) {
    for (int i = size; i <= index; ++i) {
      m_value.m_array->push_back(Json());
    }
  }
  return m_value.m_array->at(index);
}

void Json::append(const Json &other) {
  if (m_type != json_array) {
    m_type = json_array;
    m_value.m_array = new vector<Json>();
  }
  (m_value.m_array)->push_back(other);
}

string Json::str() {
  stringstream ss;
  switch (m_type) {
  case json_null:
    ss << "null";
    break;
  case json_bool:
    if (m_value.m_bool) {
      ss << "true";
    } else {
      ss << "false";
    }
    break;
  case json_int:
    ss << m_value.m_int;
    break;
  case json_double:
    ss << m_value.m_double;
    break;
  case json_string:
    ss << '\"' << *(m_value.m_string) << '\"';
    break;
  case json_array:
    ss << '[';
    for (auto it = (m_value.m_array)->begin(); it != (m_value.m_array)->end();
         it++) {
      if (it != (m_value.m_array)->begin()) {
        ss << ',';
      }
      ss << it->str();
    }
    ss << ']';
    break;
  case json_object:
    ss << '{';
    for (auto it = (m_value.m_object)->begin(); it != (m_value.m_object)->end();
         it++) {
      if (it != (m_value.m_object)->begin()) {
        ss << ',';
      }
      ss << '\"' << it->first << '\"' << ':' << (it->second).str();
    }
    ss << '}';
  }

  return ss.str();
}

Json &Json::operator[](const string &key) {
  if (m_type == json_null) {
    m_value.m_object = new map<string, Json>();
    m_type = json_object;
  } else if (m_type != json_object) {
    throw new logic_error("invalid operator []");
  }
  auto it = (m_value.m_object)->find(key);
  if (it == m_value.m_object->end()) {
    (*(m_value.m_object))[key] = Json();
  }
  return (*(m_value.m_object))[key];
}

Json &Json::operator[](const char *key2) {
  string key(key2);
  if (m_type == json_null) {
    m_value.m_object = new map<string, Json>();
    m_type = json_object;
  } else if (m_type != json_object) {
    throw new logic_error("invalid operator []");
  }
  auto it = (m_value.m_object)->find(key);
  if (it == m_value.m_object->end()) {
    (*(m_value.m_object))[key] = Json();
  }
  return (*(m_value.m_object))[key];
}