#include "Menu/Submenu.hpp"

#include "Menu/ClassicUI.hpp"

namespace YimMenu
{
	void Submenu::SetActiveCategory(const std::shared_ptr<Category> category)
	{
		m_ActiveCategory = category;
	}

	void Submenu::AddCategory(std::shared_ptr<Category>&& category)
	{
		if (!m_ActiveCategory)
			m_ActiveCategory = category;

		m_Categories.push_back(std::move(category));
	}

	void Submenu::RemoveCategory(const std::shared_ptr<Category>& category)
	{
		std::erase(m_Categories, category);
		if (m_ActiveCategory == category)
			m_ActiveCategory = m_Categories.empty() ? nullptr : m_Categories.front();
	}

	void Submenu::DrawCategorySelectors()
	{
		// GetLength()'s own tab-width sizing no longer applies - every row
		// is full-width now (see Menu/ClassicUI.hpp's own class comment) -
		// so this is just one row per category instead of the original's
		// horizontal button strip.
		for (auto& category : m_Categories)
		{
			if (!category)
				continue;

			const auto active = category == GetActiveCategory();
			if (active)
				ClassicUI::Text("> " + category->m_Name);
			else if (ClassicUI::Button(category->m_Name))
				SetActiveCategory(category);
		}
	}

	void Submenu::Draw()
	{
		if (m_ActiveCategory)
		{
			m_ActiveCategory->Draw();
		}
	}
}
