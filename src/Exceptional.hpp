#pragma once

#include <Windows.h>
#include <string>

namespace YimMenu
{
	enum class ExceptionContext : uint8_t
	{
		LUA = 1,
		OTHER = 0,
	};

	struct ExceptionData
	{
		_EXCEPTION_POINTERS* const exp;
		const ExceptionContext ctx;
	};

	long handle_exception_spec(void*) noexcept;
	using handle_exception_t = decltype(&handle_exception_spec);

	long handle_caught_exception_spec(ExceptionData*) noexcept;
	using handle_caught_exception_t = decltype(&handle_caught_exception_spec);

	long handle_uncaught_exception_spec(_EXCEPTION_POINTERS*) noexcept;
	using handle_uncaught_exception_t = decltype(&handle_uncaught_exception_spec);

	class Exceptional
	{
	public:
		static void report(const std::string&)
		{
			// TODO: Full Stand implementation later.
		}
	};
}

extern "C"
{
	void exceptional_init(
	    YimMenu::handle_caught_exception_t,
	    YimMenu::handle_uncaught_exception_t);

	void disable_exception_handling();

	[[nodiscard]]
	bool exceptional_has_exp();

	void exceptional_get_exp(
	    void**,
	    YimMenu::handle_exception_t*);

	void exceptional_clear_exp();

	long exceptional_on_exception(
	    YimMenu::ExceptionData*,
	    YimMenu::handle_caught_exception_t);

	long exceptional_on_caught_exception(
	    YimMenu::ExceptionData*);

	long exceptional_on_uncaught_exception(
	    _EXCEPTION_POINTERS*);

	void exceptional_set_retval(long);
}

#define __EXCEPTIONAL_CTX(ctx)                   \
	__except (::exceptional_on_caught_exception( \
	    new ::YimMenu::ExceptionData{            \
	        GetExceptionInformation(),           \
	        ::YimMenu::ExceptionContext::ctx}))

#define __EXCEPTIONAL() __EXCEPTIONAL_CTX(OTHER)
#define __EXCEPTIONAL_LUA() __EXCEPTIONAL_CTX(LUA)

#define __EXCEPTIONAL_CUSTOM_CTX(handler, ctx) \
	__except (::exceptional_on_exception(      \
	    new ::YimMenu::ExceptionData{          \
	        GetExceptionInformation(),         \
	        ::YimMenu::ExceptionContext::ctx}, \
	    handler))

#define __EXCEPTIONAL_CUSTOM(handler) \
	__EXCEPTIONAL_CUSTOM_CTX(handler, OTHER)

#define __EXCEPTIONAL_CUSTOM_LUA(handler) \
	__EXCEPTIONAL_CUSTOM_CTX(handler, LUA)