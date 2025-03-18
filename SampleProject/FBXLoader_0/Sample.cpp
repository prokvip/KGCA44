#include "Sample.h"


void Sample::Init()
{
	m_FbxImporter.Load(
		L"../../data/fbx/box.fbx",
		m_FbxBox);
}
void Sample::Tick() 
{
	m_FbxBox.Tick();
}
void Sample::Render() {

	m_FbxBox.Render();
}
void Sample::Release() 
{
	m_FbxBox.Destroy();
}

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR    lpCmdLine,
	int       nCmdShow)
{
	Sample sample;
	sample.SetWindowClass(hInstance);
	sample.SetWindow(L"test", 800, 600);
	sample.GameRun();
}