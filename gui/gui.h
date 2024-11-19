#pragma once
#include <d3d9.h>
#include <cmath>
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx9.h"
#include "../imgui/imgui_impl_win32.h"
#include "byte.h"

#define OILER 2.718281828459045

namespace fonts 
{
    inline ImFont* medium;
    inline ImFont* semibold;
}

// Caffeine equation, C(t) = C_0 * e^t(-ln(2)/k)
// Where:
//	k is the half life, ex: 5hr
//	C_0 is initial intake in mg
//	And t is hours passed

namespace caf 
{
	inline int halfLife = 5; //standard hl for average metabolic function
	inline float initialIntake = 200.f;
	inline int hoursPassed = 1;

	inline float compute(float t) {
		float k = (-std::log(2) / caf::halfLife);
		return caf::initialIntake * std::exp(t * k);
	}

	inline float effectiveness(float t, float peakTime = 0.75f, float sigma = 2.5f) {
		float caffeineInBody = caf::compute(t);
		float sensitivity = std::exp(-std::pow(t - peakTime, 2) / (2.0f * sigma * sigma));
		float effectiveness = caffeineInBody * sensitivity;

		return effectiveness;
	}
}

namespace gui
{
	// constant window size
	constexpr int WIDTH = 500;
	constexpr int HEIGHT = 300;

	// when this changes, exit threads
	// and close menu :)
	inline bool isRunning = true;

	// winapi window vars
	inline HWND window = nullptr;
	inline WNDCLASSEX windowClass = { };

	// points for window movement
	inline POINTS position = { };

	// direct x state vars
	inline PDIRECT3D9 d3d = nullptr;
	inline LPDIRECT3DDEVICE9 device = nullptr;
	inline D3DPRESENT_PARAMETERS presentParameters = { };

	// handle window creation & destruction
	void CreateHWindow(const char* windowName) noexcept;
	void DestroyHWindow() noexcept;

	// handle device creation & destruction
	bool CreateDevice() noexcept;
	void ResetDevice() noexcept;
	void DestroyDevice() noexcept;

	// handle ImGui creation & destruction
	void CreateImGui() noexcept;
	void DestroyImGui() noexcept;

	void BeginRender() noexcept;
	void EndRender() noexcept;
	void Render() noexcept;
}
