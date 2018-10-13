#pragma once
#include "libs.h"
class Wrapper
{
public:
	int WINDOW_WIDTH;
	int WINDOW_HEIGHT;
	int framebufferWidth;
	int framebufferHeight;
	static GLFWwindow* getWindow();
	Wrapper();
	~Wrapper();

private:
	void CreateWindow(const int, const int, const int, const int);
	void AddOptions();
	void ErrorCheck();

};

