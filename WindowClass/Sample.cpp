#include "Sample.h"
void   Sample::Init() 
{
    int a = 0;
}
void   Sample::Frame()  
{
    int a = 0;
}
void   Sample::Render() 
{
    int a = 0;
}
void   Sample::Release() 
{
    int a = 0;
}

//GameStart(800, 600);
int WINAPI wWinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR    lpCmdLine,
    int       nCmdShow)
{
    Sample sample;
    sample.SetWindowClass(hInstance);
    sample.SetWindow();
    sample.GameRun();    
}