#ifndef JSON_H

#define JSON_H

#include <map>
#include <string>
#include <vector>
using namespace std;

namespace hongzhe {
class Json {

private:
  enum Type {
    json_null = 0,
    json_bool,
    json_int,
    json_double,
    json_string,
    json_array,
    json_object
  };

public:
  Json();
  Json(bool value);
  Json(int value);
  Json(double value);
  Json(const char *value);
  Json(const string &value);
  Json(const Json &other);
  Json(Type type);

  operator bool();
  operator int();
  operator double();
  operator string();

  Json &operator[](int index);
  void append(const Json &other);

  string str();

  Json &operator[](const string &key);
  Json &operator[](const char *key2);

public:
  virtual ~Json(){};

private:
  union Value {
    bool m_bool;
    int m_int;
    double m_double;
    string *m_string;
    vector<Json> *m_array;
    map<string, Json> *m_object;
  };

public:
  Value m_value;
  Type m_type;
};
} // namespace hongzhe

#endif /* end of include guard: JSON_H */
