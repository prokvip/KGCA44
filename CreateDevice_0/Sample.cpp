#include "Sample.h"
void   Sample::Init() 
{
}
void   Sample::Frame()  
{

}
void   Sample::Render() 
{    

}
void   Sample::Release() 
{
  
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