#pragma once

#include <memory>
#include <v8.h>
#include "ClassDescription.h"

namespace v8wrap
{
	template<class CLASS>
	struct Convert<CLASS *>
	{
		static CLASS * FromJS(const v8::Local<v8::Value> & js)
		{
			V8WRAP_ASSERT(js->IsObject());

			if (!js->IsObject())
				return nullptr;

			auto obj(v8::Local<v8::Object>::Cast(js));
			if (obj->InternalFieldCount() != 3)
				return nullptr;

			TypeId id = obj->GetPointerFromInternalField(0);
			TypeId target = Internal::type_id<CLASS>();
			V8WRAP_ASSERT(id == target);
			if (id != target)
				return nullptr;

			return static_cast<CLASS *>(obj->GetPointerFromInternalField(2));
		}
		
		static v8::Handle<v8::Value> ToJS(CLASS * inst)
		{
			auto fn = ClassDescription<CLASS>::FunctionTemplate()->GetFunction();
			v8::Handle<v8::Value> ext = v8::External::New(inst);
			v8::Local<v8::Object> jsref = fn->NewInstance(1, &ext);

			return jsref;
		}
	};

	template<class CLASS>
	struct Convert<std::shared_ptr<CLASS> *>
	{
		static std::shared_ptr<CLASS> * FromJS(const v8::Local<v8::Value> & js)
		{
			V8WRAP_ASSERT(js->IsObject());

			if (!js->IsObject())
				return nullptr;

			auto obj(v8::Local<v8::Object>::Cast(js));
			if (obj->InternalFieldCount() != 3)
				return nullptr;

			TypeId id = obj->GetPointerFromInternalField(0);
			TypeId target = Internal::type_id<CLASS>();
			V8WRAP_ASSERT(id == target);
			if (id != target)
				return NULL;

			return static_cast<std::shared_ptr<CLASS> *>(obj->GetPointerFromInternalField(1));
		}
		
		static v8::Handle<v8::Value> ToJS(std::shared_ptr<CLASS> * inst)
		{
			auto fn = ClassDescription<CLASS>::FunctionTemplate()->GetFunction();
			v8::Handle<v8::Value> ext = v8::External::New(inst->get());
			v8::Local<v8::Object> jsref = fn->NewInstance(1, &ext);

			return jsref;
		}
	};

	template<class CLASS>
	struct Convert<const std::shared_ptr<CLASS> &>
	{
		static const std::shared_ptr<CLASS> & FromJS(const v8::Local<v8::Value> & js)
		{
			V8WRAP_ASSERT(js->IsObject());

			v8::Local<v8::Object> obj(v8::Local<v8::Object>::Cast(js));
			V8WRAP_ASSERT(obj->InternalFieldCount() == 3);

			TypeId id = obj->GetPointerFromInternalField(0);
			TypeId target = Internal::type_id<CLASS>();
			V8WRAP_ASSERT(id == target);

			auto shared = static_cast<std::shared_ptr<CLASS> *>(obj->GetPointerFromInternalField(1));
			V8WRAP_ASSERT(shared != nullptr);

			return *shared;
		}
		
		static v8::Handle<v8::Value> ToJS(const std::shared_ptr<CLASS> & inst)
		{
			auto fn = ClassDescription<CLASS>::FunctionTemplate()->GetFunction();
			v8::Handle<v8::Value> ext[2] = { v8::External::New(&inst), v8::Undefined() };
			v8::Local<v8::Object> jsref = fn->NewInstance(2, ext);

			return jsref;
		}
	};
}
