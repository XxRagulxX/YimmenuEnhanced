#include "Commands/Extra/CommandWeb.hpp"

#include "lib/soup/ObfusString.hpp"

#include "Commands/Extra/CommandWebOpen.hpp"

namespace Stand
{
    CommandWeb::CommandWeb(CommandList* const parent)
        : CommandListQrcode(parent, LOC("WEB2"), {}, LOC("WEB2_H"))
    {
        this->createChild<CommandWebOpen>();
    }

    std::string CommandWeb::getText() const
    {
        return getUri();
    }

    std::string CommandWeb::getUri()
    {
        return soup::ObfusString("https://stand.sh/web#");
    }
}