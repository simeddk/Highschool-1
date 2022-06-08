#pragma once


struct GuiText
{
	Vector2 Position;
	Color Color;
	string Content;

	GuiText()
	{
		
	}
};

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

class Gui
{
public:
	static void Create();
	static void Delete();

	static Gui* Get();

	LRESULT MsgProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
	void Resize();

	void Update();
	void Render();

	void RenderText(GuiText& text);
	void RenderText(float x, float y, string content);
	void RenderText(float x, float y, float r, float g, float b, string content);
	void RenderText(Vector2 position, Color color, string content);

private:
	Gui();
	~Gui();

private:
	void ApplyStyle();

private:
	static Gui* instance;

	vector<GuiText> texts;
};