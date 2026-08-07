#include "Exceptional.hpp"

namespace YimMenu
{
	long handle_exception_spec(void*) noexcept
	{
		return EXCEPTION_EXECUTE_HANDLER;
	}

	long handle_caught_exception_spec(ExceptionData*) noexcept
	{
		return EXCEPTION_EXECUTE_HANDLER;
	}

	long handle_uncaught_exception_spec(_EXCEPTION_POINTERS*) noexcept
	{
		return EXCEPTION_EXECUTE_HANDLER;
	}
}

extern "C"
{
	void exceptional_init(
	    YimMenu::handle_caught_exception_t,
	    YimMenu::handle_uncaught_exception_t)
	{
	}

	void disable_exception_handling()
	{
	}

	bool exceptional_has_exp()
	{
		return false;
	}

	void exceptional_get_exp(
	    void**,
	    YimMenu::handle_exception_t*)
	{
	}

	void exceptional_clear_exp()
	{
	}

	long exceptional_on_exception(
	    YimMenu::ExceptionData*,
	    YimMenu::handle_caught_exception_t)
	{
		return EXCEPTION_EXECUTE_HANDLER;
	}

	long exceptional_on_caught_exception(
	    YimMenu::ExceptionData*)
	{
		return EXCEPTION_EXECUTE_HANDLER;
	}

	long exceptional_on_uncaught_exception(
	    _EXCEPTION_POINTERS*)
	{
		return EXCEPTION_EXECUTE_HANDLER;
	}

	void exceptional_set_retval(long)
	{
	}
}