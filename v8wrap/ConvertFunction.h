#pragma once

#include <v8.h>
#include "internal/ConvertFunction.h"

namespace v8wrap
{	
	template<class R>
	struct Convert<R(*)()> : public Internal::ConvertFunction<R()>
	{};

	template<class R, class P0>
	struct Convert<R(*)(P0)> : public Internal::ConvertFunction<R(P0)>
	{};

	template<class R, class P0, class P1>
	struct Convert<R(*)(P0,P1)> : public Internal::ConvertFunction<R(P0,P1)>
	{};

	template<class R, class P0, class P1, class P2>
	struct Convert<R(*)(P0,P1,P2)> : public Internal::ConvertFunction<R(P0,P1,P2)>
	{};

	template<class R, class P0, class P1, class P2, class P3>
	struct Convert<R(*)(P0,P1,P2,P3)> : public Internal::ConvertFunction<R(P0,P1,P2,P3)>
	{};

	template<class R, class P0, class P1, class P2, class P3, class P4>
	struct Convert<R(*)(P0,P1,P2,P3,P4)> : public Internal::ConvertFunction<R(P0,P1,P2,P3,P4)>
	{};
}
