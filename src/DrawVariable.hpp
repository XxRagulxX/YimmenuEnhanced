#pragma once
#include "SavedVariables.hpp"

namespace YimMenu
{
	extern void DrawSavedVariableEdit(const SavedVariableBase& var, void* value);
	extern void DrawSavedVariablePreview(const SavedVariableBase& var, void* value);
	extern void DrawSavedVariable(SavedVariableBase& var);
}