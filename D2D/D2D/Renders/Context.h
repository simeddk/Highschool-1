#pragma once

class Context
{
public:
	static void Create();
	static void Delete();
	static Context* Get();

private:
	Context();
	~Context();

public:
	void Update();

	const Matrix& GetView();
	const Matrix& GetProjection();

	class Camera* GetCamera() { return camera; }
	void SetFollowMode(class IFollow* focusObject = nullptr);
	void SetFreedomMode();

private:
	static Context* instance;

private:
	class Camera* camera = nullptr;
	Matrix projection;
};