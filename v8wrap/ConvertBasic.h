#pragma once
#include <v8.h>
#include <stdint.h>

namespace v8wrap
{
	template<class TYPE> struct Convert;

	template<>
	struct Convert<int32_t>
	{
		static int32_t FromJS(const v8::Handle<v8::Value> & js)
		{
			return js->Int32Value();
		}

		static v8::Handle<v8::Value> ToJS(int32_t val)
		{
			return v8::Int32::New(val);
		}
	};

	template<>
	struct Convert<uint32_t>
	{
		static uint32_t FromJS(const v8::Handle<v8::Value> & js)
		{
			return js->Uint32Value();
		}

		static v8::Handle<v8::Value> ToJS(uint32_t val)
		{
			return v8::Uint32::New(val);
		}
	};

	template<>
	struct Convert<float>
	{
		static float FromJS(const v8::Handle<v8::Value> & js)
		{
			return (float)js->NumberValue();
		}

		static v8::Handle<v8::Value> ToJS(float val)
		{
			return v8::Number::New((double)val);
		}
	};

	template<>
	struct Convert<bool>
	{
		static bool FromJS(const v8::Handle<v8::Value> & js)
		{
			return js->BooleanValue();
		}

		static v8::Handle<v8::Value> ToJS(bool val)
		{
			return v8::Boolean::New(val);
		}
	};

	template<>
	struct Convert<std::string>
	{
		static std::string FromJS(const v8::Handle<v8::Value> & js)
		{
			static const std::string empty;
			v8::String::Utf8Value utf(js->ToString());
			const char * str = *utf;
			return str ? std::string(str, utf.length()) : empty;
		}
		
		static v8::Handle<v8::Value> ToJS(const std::string & str)
		{
			return v8::String::New(str.c_str(), str.length());
		}
	};
	
	template<>
	struct Convert<const std::string &> : public Convert<std::string>
	{};
}

