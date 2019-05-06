#include "./node_modules/nan/nan.h"
#include "myobject.h"
#include <string>

void InitAll(v8::Local<v8::Object> exports) {
  MyObject::Init(exports);
}

NODE_MODULE(addon, InitAll)