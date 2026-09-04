#include "Menu/UIManager.hpp"
#include "Config/Themes.hpp"

namespace YimMenu
{
	void UIManager::AddSubmenuImpl(const std::shared_ptr<Submenu>&& submenu)
	{
		if (!m_ActiveSubmenu)
			m_ActiveSubmenu = submenu;

		m_Submenus.push_back(std::move(submenu));
	}

	void UIManager::RemoveSubmenuImpl(const std::shared_ptr<Submenu>& submenu)
	{
		std::erase(m_Submenus, submenu);

		if (m_ActiveSubmenu == submenu)
			m_ActiveSubmenu = m_Submenus.empty() ? nullptr : m_Submenus.front();
	}

	void UIManager::SetActiveSubmenuImpl(const std::shared_ptr<Submenu> submenu)
	{
		m_ActiveSubmenu = submenu;
	}

	void UIManager::DrawImpl()
	{
		// Only one theme renderer left (Classic) - see UIManager.hpp's
		// own class comment for why the others (and the style-selector
		// choice between them) are gone.
		RenderClassicTheme();
	}

	std::shared_ptr<Submenu> UIManager::GetActiveSubmenuImpl()
	{
		return m_ActiveSubmenu;
	}

	std::shared_ptr<Category> UIManager::GetActiveCategoryImpl()
	{
		if (m_ActiveSubmenu)
		{
			return m_ActiveSubmenu->GetActiveCategory();
		}

		return nullptr;
	}

	bool UIManager::HasAnyContentImpl() const
	{
		for (auto& submenu : m_Submenus)
			if (!submenu->m_Categories.empty())
				return true;

		return false;
	}
}
