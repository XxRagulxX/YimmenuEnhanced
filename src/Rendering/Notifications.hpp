#pragma once

#include <chrono>
#include <cstdint>
#include <functional>
#include <mutex>
#include <string>
#include <unordered_map>

namespace YimMenu
{
	// Card geometry/animation speed - H-space units now (Stand's own
	// virtual 1920x1080 HUD canvas - see GridRenderer.hpp's own class
	// comment for what that means), not raw client pixels the way these
	// were read before this ported to DirectXTK12/GridRenderer's own
	// primitives. The numbers themselves are unchanged (350/100/50, the
	// original ImGui window size/position math) - since that canvas is
	// also 1920x1080, they still mean exactly what they used to at
	// 1080p, but now actually scale correctly at every other resolution
	// too (something the raw-client-pixel version never did).
	static inline float m_CardSizeX = 350.f;
	static inline float m_CardSizeY = 100.f;
	static inline float m_CardAnimationSpeed = 50.f;

	enum class NotificationType
	{
		Info,
		Success,
		Warning,
		Error
	};

	struct Notification
	{
		NotificationType m_Type;
		std::string m_Title;
		std::string m_Message;
		std::chrono::time_point<std::chrono::system_clock> m_CreatedOn;
		int m_Duration;
		std::function<void()> m_ContextFunc;
		std::string m_ContextFuncName;
		float m_AnimationOffset = -m_CardSizeX;
		bool m_Erasing = false;
		std::uint32_t m_Identifier;
	};

	// Toast notification stack, drawn via GridRenderer's own DirectXTK12
	// primitives (DrawRect/DrawText/MeasureText) instead of the classic
	// menu's ImGui windows this used to open one of per card (see
	// Notifications.cpp's own history for that version) - the first of
	// this project's non-menu ImGui-drawing subsystems to move over (see
	// GridRenderer.hpp's own class comment on what else is still ImGui-
	// based). Unlike every Grid/GridItem-based page in this system, this
	// isn't a Grid at all - it's a free-standing overlay always drawn on
	// top of everything else, the same shape MenuPopup already is, except
	// unconditionally every frame rather than only while the Stand-style
	// menu itself is open (a toast needs to show up whether or not any
	// menu is even open) - see GridRenderer::DrawImpl's own call site for
	// where that split lives now.
	//
	// Two-pass draw, split along the same rect/text boundary every other
	// DirectXTK12 consumer in this system already has to (PrimitiveBatch
	// vs SpriteBatch - see GridRenderer.hpp's own DrawRect/DrawText doc
	// comments for why): Draw() MUST run first each frame - besides
	// drawing each card's background/progress bar rects, it's also what
	// advances each card's slide animation and expires/erases finished
	// ones, exactly like the pre-port DrawImpl() already did. DrawText()
	// only reads whatever state Draw() left this frame (title/message/
	// context-function text) - it doesn't re-advance anything, so calling
	// it more than once (or before Draw()) per frame would show stale or
	// duplicate-advanced state. GridRenderer::DrawImpl calls them in that
	// order, once each, every frame - nothing else should call these.
	//
	// The classic menu's own "context function" (a clickable follow-up
	// action shown under the message - e.g. LuaNotify's own callers never
	// actually use this today, so it's untested here beyond mirroring the
	// data model) has no click to bind to any more (this whole overlay is
	// mouseless, same as the rest of the new renderer) - its name still
	// draws as an informational text line rather than being silently
	// dropped.
	class Notifications
	{
	private:
		std::unordered_map<std::string, Notification> m_Notifications = {};
		std::mutex m_mutex;

		// duration is in milliseconds
		Notification ShowImpl(std::string title, std::string message, NotificationType type, int duration, std::function<void()> context_function, std::string context_function_name);
		void DrawImpl();
		void DrawTextImpl();
		bool EraseImpl(Notification notification);

		static Notifications& GetInstance()
		{
			static Notifications instance;
			return instance;
		}

	public:
		static void ShowInGame(const std::string& title, const std::string& message, const std::string& icon, const std::string& color);
		static Notification Show(std::string title, std::string message, NotificationType type = NotificationType::Info, int duration = 5000, std::function<void()> context_function = nullptr, std::string context_function_name = "")
		{
			return GetInstance().ShowImpl(title, message, type, duration, context_function, context_function_name);
		}

		// Rect pass (background/progress bar) - also advances animation
		// and expires finished cards. Must run before DrawText() each
		// frame - see this class's own comment above.
		static void Draw()
		{
			GetInstance().DrawImpl();
		}

		// Text pass (title/message/context-function line). Must run
		// after Draw() each frame - see this class's own comment above.
		static void DrawText()
		{
			GetInstance().DrawTextImpl();
		}

		static bool Erase(Notification notification)
		{
			return GetInstance().EraseImpl(notification);
		}
	};

}
