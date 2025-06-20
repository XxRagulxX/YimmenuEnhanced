#include "StyleSelector.hpp"
#include "core/commands/ListCommand.hpp"
#include "core/frontend/manager/UIManager.hpp"

namespace YimMenu
{
	static const std::vector<std::pair<int, const char*>> g_StyleOptions = {
	    {0, "Classic"},
	    {1, "Modern"},
	    {2, "ModernV"},
	};

	class StyleSelector : public ListCommand
	{
	public:
		using ListCommand::ListCommand;

		void OnChange() override
		{
			int selectedIndex = GetState();

			UITheme selectedTheme = UITheme::Classic; // Default Theme

			// Set the selected theme based on the index, append when adding new themes
			switch (selectedIndex)
			{
			case 0:
				selectedTheme = UITheme::Classic;
				break;
			case 1:
				selectedTheme = UITheme::Modern;
				break;
			case 2:
				selectedTheme = UITheme::ModernV;
				break;
			default:
				selectedTheme = UITheme::Classic;
				break;
			}
		}
	};

	// Expose as global reference so other code can use it
	static StyleSelector g_InternalStyleSelector{
	    "styleselector",
	    "UI Style",
	    "Choose the UI style",
	    g_StyleOptions,
	    0};

	ListCommand& g_StyleSelector = g_InternalStyleSelector;
}
