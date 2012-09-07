#pragma once

#include <v8.h>

namespace v8wrap
{
	void InstallGC()
	{
		v8::V8::SetFlagsFromString("--expose-gc", 12);
	}

	void ForceGC()
	{
		auto ctx = v8::Context::New();
		ctx->Enter();
		v8::HandleScope scope;
		auto gc = ctx->Global()->Get(v8::String::New("gc"));
		v8::Handle<v8::Function>::Cast(gc)->Call(ctx->Global(), 0, NULL);
		ctx->Exit();
		ctx.Dispose();
	}
}
