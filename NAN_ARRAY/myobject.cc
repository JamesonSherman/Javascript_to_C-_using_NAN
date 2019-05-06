#include "myobject.h"
#include <iostream>
#include <string>

using namespace v8;
using namespace Nan;

Nan::Persistent<v8::Function> MyObject::constructor;

MyObject::MyObject(double value) : value_(value) {
}

MyObject::~MyObject() {
}

void MyObject::Init(v8::Local<v8::Object> exports) {
  Nan::HandleScope scope;

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("MyObject").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  Nan::SetPrototypeMethod(tpl, "value", GetValue);
  Nan::SetPrototypeMethod(tpl, "printArr", PrintVector);
  Nan::SetPrototypeMethod(tpl, "longest", LongestString);

  constructor.Reset(tpl->GetFunction());
  exports->Set(Nan::New("MyObject").ToLocalChecked(), tpl->GetFunction());
}

void MyObject::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.IsConstructCall()) {
//    if (info.Length() == 2 && info[0]->IsObject() && info[1]->IsInt32()) 
//      {
//        obj = new MyObject(Nan::To<v8::Object>(info[0]).ToLocalChecked(), 
//						Nan::To<int>(info[1]).FromJust()
//        );
//      }

    // Invoked as constructor: `new MyObject(...)`
    //double value = info[0]->IsUndefined() ? 0 : info[0]->NumberValue();
    double value = info[0]->IsUndefined() ? 0 : Nan::To<double>(info[0]).FromJust();
    MyObject* obj = new MyObject(value);
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    // Invoked as plain function `MyObject(...)`, turn into construct call.
    const int argc = 1;
    v8::Local<v8::Value> argv[argc] = { info[0] };
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    //info.GetReturnValue().Set(cons->NewInstance(argc, argv));
    info.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked());
  }
}

void MyObject::PrintVector(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  MyObject* obj = ObjectWrap::Unwrap<MyObject>(info.Holder());
  obj->printVector();
  //info.GetReturnValue().Set(Nan::New(obj->value_));
}

void MyObject::GetValue(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  MyObject* obj = ObjectWrap::Unwrap<MyObject>(info.Holder());
  info.GetReturnValue().Set(Nan::New(obj->value_));
}


void MyObject::printVector() {
  for(auto& v : vec) { std::cout << v << std::endl; }
}


 void MyObject::LongestString(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  MyObject* obj = ObjectWrap::Unwrap<MyObject>(info.Holder());
  // We need one and only one parameter which is an array in JavaScript. 
  if(info.Length() > 1) {
    return Nan::ThrowError(Nan::New("LongestString takes only 1 parameter.").ToLocalChecked());
  }
  // more error checking
  if(!info[0]->IsArray()) {
    return Nan::ThrowError(Nan::New("The parameter must be an array.").ToLocalChecked());  
  }
  std::vector<std::string> stringVector;
  // We cast the array as the first parameter 
  v8::Local<v8::Array> inputArray = v8::Local<v8::Array>::Cast(info[0]);
  v8::Local<v8::Array> outputArray = Nan::New<v8::Array>(10);
  int raboof = 0;
  for (int i = 0; i < inputArray->Length(); i++) {
    v8::String::Utf8Value param1(inputArray->Get(i)->ToString());
    std::string foo = std::string(*param1);
    stringVector.push_back(foo);
  }

  std::sort(stringVector.begin(), stringVector.end(), [](std::string a, std::string b) -> bool { return (a.length() < b.length()); });

    //for (std::vector<std::string>::iterator it = stringVector.end(); it != stringVector.end() - 10; --it)
    for (int it = stringVector.size() - 1; it >= 0 && it > stringVector.size() - 11; --it)
    {
       
        std::string tmpstr = stringVector.at(it);
        Nan::Set(outputArray, raboof, Nan::New<String>(tmpstr.c_str()).ToLocalChecked());
        ++raboof;
    }

  info.GetReturnValue().Set(outputArray);
  
  } 