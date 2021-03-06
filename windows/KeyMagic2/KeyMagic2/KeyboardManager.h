#pragma once

#include <list>
#include <vector>
#include <keymagic.h>
#include "json.hpp"

class Keyboard
{
private:
	HBITMAP hIcon = NULL;
	libkm::KeyMagicEngine *m_engine = nullptr;

public:
	std::wstring basePath;

	int index; // index for convience
	int imageListIndex;

	std::wstring name;
	std::wstring path;
	HBITMAP GetKeyboardIcon();

private:
	std::wstring KeyboardFullPath();
	void LoadKeyboardIcon();

public:
	libkm::KeyMagicEngine * GetKeyMagicEngine();
};

typedef std::vector<Keyboard> TKeyboardList;
typedef std::function<void(bool)> onDidChangeCallback;
typedef std::map<HWND, Keyboard*> TMapWindowKeyboard;

class KeyboardManager
{
private:
	TKeyboardList m_keyboards;
	BOOL windowMode = false;
	TMapWindowKeyboard m_windows;
	HWND m_currentWindow;
	//Keyboard* m_selectedKeyboard;
	Keyboard* m_lastSelectedKeyboard;
	std::wstring m_basePath;
	std::vector<onDidChangeCallback> m_callbacks;

	void notifyCallbacks(bool isToggle);

public:
	static KeyboardManager * sharedManager();

	void addOnKeyboardDidChangeHandler(onDidChangeCallback callback)
	{
		m_callbacks.push_back(callback);
	}

	std::wstring const& basePath() const;
	void basePath(std::wstring const& newBasePath);
	Keyboard * SelectedKeyboard();
	Keyboard * KeyboardAtIndex(int index);
	BOOL SetKeyboards(nlohmann::json);
	TKeyboardList& GetKeyboards();
	BOOL SelectKeyboard(Keyboard * keyboard, bool isAdvancing = false);
	BOOL ToggleKeyboard();
	BOOL AdvanceToNextKeyboard();
	HWND GetWindowHandle();
	void SetWindowHandle(HWND);
	void SetWindowMode(BOOL);
};