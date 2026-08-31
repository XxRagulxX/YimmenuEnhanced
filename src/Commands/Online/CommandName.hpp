#pragma once
#include <string>

// Verbatim port of stand-reference's src/Commands/Online/CommandName.hpp.
// Stand can build with wide command names (for engines where narrow
// command-box parsing isn't workable); COMPACT_COMMAND_NAMES=true is
// its own default and the only variant this project has any reason to
// use, so that's the only one ported here.
#define COMPACT_COMMAND_NAMES true

namespace Stand
{
#if COMPACT_COMMAND_NAMES
	using CommandName = std::string;
#else
	using CommandName = std::wstring;
#endif
}
