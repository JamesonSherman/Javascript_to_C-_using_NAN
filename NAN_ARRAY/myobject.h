#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <nan.h>

class MyObject : public Nan::ObjectWrap {
 public:
  static void Init(v8::Local<v8::Object> exports);

 private:
  explicit MyObject(double value = 0);
  MyObject(const v8::Local<v8::Object> &inBuffer, int size);
  ~MyObject();

  static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void GetValue(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void PrintVector(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void PassArr(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void LongestString(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static Nan::Persistent<v8::Function> constructor;
  void printVector();
  double value_;
  std::vector<double> vec;
};

#endif
