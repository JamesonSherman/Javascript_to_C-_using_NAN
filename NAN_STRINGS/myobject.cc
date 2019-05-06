#include "myobject.h"
#include <vector>
#include <cctype>
#include <iostream>
using namespace Nan;
using namespace v8;

Nan::Persistent<v8::Function> MyObject::constructor;

MyObject::MyObject(double value) : value_(value) {
}

MyObject::~MyObject() {
}

void MyObject::Init(v8::Local<v8::Object> exports) {
  Nan::HandleScope scope;

  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("MyObject").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "findUpper", findUpper);
  Nan::SetPrototypeMethod(tpl, "hasUpper", hasUpper);
  Nan::SetPrototypeMethod(tpl, "findLower", findLower);

  constructor.Reset(tpl->GetFunction());
  exports->Set(Nan::New("MyObject").ToLocalChecked(), tpl->GetFunction());
}

void MyObject::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.IsConstructCall()) {
    double value = info[0]->IsUndefined() ? 0 : Nan::To<double>(info[0]).FromJust();
    MyObject* obj = new MyObject(value);
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    const int argc = 1;
    v8::Local<v8::Value> argv[argc] = { info[0] };
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    info.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked());
  }
}



// This function finds a string that contains upper case letters
void MyObject::findUpper(const Nan::FunctionCallbackInfo<v8::Value>& info) {
   MyObject* obj = ObjectWrap::Unwrap<MyObject>(info.Holder());
  if (info.Length() < 1 || info.Length() > 2) {
    return Nan::ThrowError(Nan::New("findUpper takes at most 2 parameters").ToLocalChecked());
  }
  if (!info[0]->IsString() || (info.Length() == 2 && !info[1]->IsString())) {
    return Nan::ThrowError(Nan::New("findUpper can only take in a string as an argument").ToLocalChecked());
  }
  v8::String::Utf8Value stringValue(info[0]->ToString());
  std::string inputString (*stringValue, stringValue.length());
  std::string tempstr = "";
  v8::String::Utf8Value v8String(info[0]->ToString());
  std::string firstString(*v8String);
  int firstStringSize = firstString.size();
  if (info.Length() == 2)
  {
    v8::String::Utf8Value v8String2(info[1]->ToString());
    std::string secondString(*v8String2);
    secondString =  secondString + " ";
    int secondStringSize = secondString.size();

    for (int i = 0; i < secondStringSize - 1; ++i)
    {
      for (int j = 0; j < firstStringSize - 1; ++j)
      {
        if ((isupper(firstString[j]) != 0) && (tolower(firstString[j]) == tolower(secondString[i])))
          tempstr = tempstr + firstString[j];
      }
    }
  }
  else
  {
    for (int j = 0; j < firstStringSize - 1; ++j)
    {
      if (isupper(firstString[j]) != 0)
        tempstr = tempstr + firstString[j];
    }
  }

  obj->ucletters = obj->ucletters + tempstr;
  info.GetReturnValue().Set(Nan::New<String>(tempstr.c_str()).ToLocalChecked());
}

void MyObject::hasUpper(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  MyObject* obj = ObjectWrap::Unwrap<MyObject>(info.Holder());
  if (info.Length() < 1 || info.Length() > 1) {
    return Nan::ThrowError(Nan::New("hasUpper only takes one parameter").ToLocalChecked());
  }
  if(!info[0]->IsString()) {
    return Nan::ThrowError(Nan::New("hasUpper can only take in a string as an argument").ToLocalChecked());
  }
  v8::String::Utf8Value stringValue(info[0]->ToString());

  std::string inputString (*stringValue, stringValue.length());
  std::string tempstr = "";
  v8::String::Utf8Value v8String(info[0]->ToString());
  std::string firstString(*v8String);
  int firstStringSize = firstString.size();
  bool UCFlag = false;
  for (int i = 0; i < firstStringSize - 1; i++) {
    if (isupper(firstString[i]) != 0)
        tempstr = tempstr + firstString[i];
        UCFlag ? UCFlag = UCFlag : UCFlag = true;
  }
  Local<Boolean> outflag = Nan::New(UCFlag);
  obj->ucletters = obj->ucletters + tempstr;
  info.GetReturnValue().Set(outflag);
}

void MyObject::findLower(const Nan::FunctionCallbackInfo<v8::Value> &info)
{
  MyObject *obj = ObjectWrap::Unwrap<MyObject>(info.Holder());
  if (info.Length() != 3)
  {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }
  if (!info[0]->IsFunction() || !info[1]->IsString() || !info[2]->IsString())
  {
    Nan::ThrowTypeError("Wrong argument type");
    return;
  }
  v8::Local<v8::Function> callbackFunc = v8::Local<v8::Function>::Cast(info[0]);
  Nan::Callback cb(callbackFunc);

  const int argc = 2;
  v8::Local<v8::Value> args1[argc];

  v8::String::Utf8Value v8str1(info[1]->ToString());
  std::string str1(*v8str1);
  v8::String::Utf8Value v8str2(info[2]->ToString());
  std::string str2(*v8str2);

  args1[0] = Nan::New(str1).ToLocalChecked();
  args1[1] = Nan::New(str2).ToLocalChecked();

  v8::Local<v8::Value> jsReturnValue1 = cb.Call(argc, args1);
  bool ret1 = jsReturnValue1->BooleanValue();
  std::string tempstr = "";

 
 str1 = str1 + " ";
  str2 = str2 + " ";
  int s1sz = str1.size();
  int s2sz = str2.size();
  if (str2.length() > 1 )
  {
    for (int i = 0; i < s2sz - 1; ++i)
    {
      for (int j = 0; j < s1sz - 1; ++j)
      {
        if (islower(str1[j]) != 0 && (tolower(str1[j]) == tolower(str2[i])))
        {
          tempstr = tempstr + str1[j];
        }
      }
    }
  }
  else
  {
    for (int j = 0; j < s1sz - 1; ++j)
      {
        if (islower(str1[j]) != 0)
        {
          tempstr = tempstr + str1[j];
        }
      }
  }
  
  obj->lcletters = obj->lcletters + tempstr;
  info.GetReturnValue().Set(Nan::New<String>(tempstr.c_str()).ToLocalChecked());
}