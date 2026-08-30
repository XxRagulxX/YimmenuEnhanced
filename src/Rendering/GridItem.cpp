#include "GridItem.hpp"

#include "MenuFocus.hpp"
#include "MenuNavigation.hpp"

namespace YimMenu::Rendering
{
	bool GridItem::isKeyboardFocused() const
	{
		// Only meaningful for an item that's actually part of
		// MenuNavigation::Current()'s own item list - see the doc
		// comment in GridItem.hpp. Kept out of line so GridItem.hpp
		// itself doesn't need to pull in MenuFocus.hpp/MenuNavigation.hpp
		// (and, transitively, Grid.hpp) for every widget header that
		// includes it.
		return MenuFocus::GetFocusedItem(MenuNavigation::Current()) == this;
	}
}
