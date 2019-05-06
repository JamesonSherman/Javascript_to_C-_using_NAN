#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <nan.h>
#include <string>

class MyObject : public Nan::ObjectWrap {
 public:
  static void Init(v8::Local<v8::Object> exports);

 private:
  explicit MyObject(double value = 0);
  ~MyObject();

  static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void findUpper(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void hasUpper(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void findLower(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static Nan::Persistent<v8::Function> constructor;
  double value_;
  std::string lcletters = "";
  std::string ucletters = "";
  
};

#endif