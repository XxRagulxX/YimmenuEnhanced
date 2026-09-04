#pragma once
#include "Menu/Category.hpp"
#include "Menu/Submenu.hpp"

namespace YimMenu
{
	// The classic ImGui menu tree - Category/Submenu/UIManager/Items.hpp's
	// own *Item classes, drawn through RenderClassicTheme() (Classic.cpp,
	// the only theme renderer left - Modern/ModernV/Modular were deleted
	// alongside every other native ImGui page, all covered by the real
	// Grid/DirectXTK12 menu now instead - see Rendering/GridRenderer.hpp's
	// own class comment).
	//
	// This whole pipeline is no longer fed any native content at all: all
	// nine of Self/Vehicle/Teleport/Network/Players/World/Recovery/
	// Settings/Debug (see each one's own MenuXxx.cpp) still get created
	// and added here from Menu::Init() exactly as before, but each one's
	// constructor is now empty - every category it used to build now
	// lives in its own Grid equivalent instead. They stay real, empty
	// Submenu objects (rather than being deleted outright) purely so a
	// Lua script that attaches into an existing native submenu by name
	// (menu.find_submenu("Self"):add_category(...)) still has somewhere
	// real to attach to; nothing else populates them any more.
	//
	// So today this whole tree - and RenderClassicTheme()'s own draw
	// call - only ever shows something when a Lua script has actually
	// added a category/group/item to it (or a submenu it created itself),
	// including the raw cat:imgui()/group:imgui() escape hatch (see
	// Scripting/LuaMenu.cpp). Porting that Lua-facing API onto the Grid
	// renderer is out of scope for now (explicitly deferred) - this is
	// the minimal thing that keeps every existing Lua menu script working
	// unchanged while no longer drawing any of this project's own native
	// menu content through ImGui.
	enum class UITheme
	{
		Classic = 0,
	};

	class UIManager
	{
	public:
		static void AddSubmenu(const std::shared_ptr<Submenu>&& submenu)
		{
			GetInstance().AddSubmenuImpl(std::move(submenu));
		}

		static void RemoveSubmenu(const std::shared_ptr<Submenu>& submenu)
		{
			GetInstance().RemoveSubmenuImpl(submenu);
		}

		static void SetActiveSubmenu(const std::shared_ptr<Submenu> submenu)
		{
			GetInstance().SetActiveSubmenuImpl(submenu);
		}

		static void Draw()
		{
			GetInstance().DrawImpl();
		}

		static std::shared_ptr<Submenu> GetActiveSubmenu()
		{
			return GetInstance().GetActiveSubmenuImpl();
		}

		static std::shared_ptr<Category> GetActiveCategory()
		{
			return GetInstance().GetActiveCategoryImpl();
		}

		static void SetOptionsFont(ImFont* font)
		{
			GetInstance().m_OptionsFont = font;
		}

		static bool ShowingContentWindow()
		{
			return GetInstance().m_ShowContentWindow;
		}

		static void SetShowContentWindow(bool show)
		{
			GetInstance().m_ShowContentWindow = show;
		}

		static const std::vector<std::shared_ptr<Submenu>>& GetSubmenus()
		{
			return GetInstance().m_Submenus;
		}

		static ImFont* GetOptionsFont()
		{
			return GetInstance().m_OptionsFont;
		}

		// Whether any submenu (native-but-now-empty, or one Lua created
		// itself) actually has a category in it - i.e. whether a Lua
		// script has added anything to this tree at all. GUI::ToggleMouse()
		// uses this to decide whether the mouse cursor needs to come back
		// (Lua-drawn content generally needs one - real ImGui widgets,
		// unlike the Grid menu's own keyboard-only rows) without showing
		// one just for opening the native, keyboard-only Grid menu on its
		// own.
		static bool HasAnyContent()
		{
			return GetInstance().HasAnyContentImpl();
		}

	private:
		static inline UIManager& GetInstance()
		{
			static UIManager instance;
			return instance;
		}

		void AddSubmenuImpl(const std::shared_ptr<Submenu>&& submenu);
		void RemoveSubmenuImpl(const std::shared_ptr<Submenu>& submenu);
		void SetActiveSubmenuImpl(const std::shared_ptr<Submenu> submenu);
		void DrawImpl();
		std::shared_ptr<Submenu> GetActiveSubmenuImpl();
		std::shared_ptr<Category> GetActiveCategoryImpl();
		bool HasAnyContentImpl() const;

		std::shared_ptr<Submenu> m_ActiveSubmenu;
		std::vector<std::shared_ptr<Submenu>> m_Submenus;

		ImFont* m_OptionsFont = nullptr;
		bool m_ShowContentWindow = true;
	};
}
