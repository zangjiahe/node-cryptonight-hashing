#include <nan.h>
#include <node.h>
#include <node_buffer.h>
#include <v8.h>
#include <stdint.h>
#include "src/equi/equi210.h"

using namespace v8;

#define THROW_ERROR_EXCEPTION(x) Nan::ThrowError(x)

NAN_METHOD(Verify) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  if (info.Length() < 2) {
 return THROW_ERROR_EXCEPTION("You must provide two arguments.");
  }

  Local<Object> header = info[0]->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
  Local<Object> solution = info[1]->ToObject(isolate->GetCurrentContext()).ToLocalChecked();

  if(!node::Buffer::HasInstance(header) || !node::Buffer::HasInstance(solution)) {
  return THROW_ERROR_EXCEPTION("Arguments should be buffer objects.");

  }

  const char *hdr = node::Buffer::Data(header);
  const char *soln = node::Buffer::Data(solution);

  int n = 210;
  int k = 9;

  bool result = verifyEH(hdr, soln, n, k);
  info.GetReturnValue().Set(result);

}

//void Init(Handle<Object> exports) {
//  NODE_SET_METHOD(exports, "verify", Verify);
//}
NAN_MODULE_INIT(init) {
        Nan::Set(target, Nan::New("Verify").ToLocalChecked(), Nan::GetFunction(Nan::New<FunctionTemplate>(Verify)).ToLocalChecked());

}
//NODE_MODULE(equihashverify, Init)
