#include <iostream>  
#include <fstream>  
#include <string>  
#include <windows.h>  
#include <gdiplus.h>  

#pragma comment(lib, "gdiplus.lib")  

using namespace std;
using namespace Gdiplus;

int main()
{
	GdiplusStartupInput gdiplusstartupinput;
	ULONG_PTR gdiplustoken;	
	GdiplusStartup(&gdiplustoken, &gdiplusstartupinput, NULL);
	wstring infilename(L"1.jpg");
	//读图片  
	Bitmap* bmp = new Bitmap(infilename.c_str());
	UINT height = bmp->GetHeight();
	UINT width = bmp->GetWidth();
	cout << "width " << width << ", height " << height << endl;
	Color color;
	//创建动态二位数组
	int ** pic = new int *[width];
	for (int i = 0; i < width; i++)
		pic[i] = new int[height];
	//将各像素灰度值存入动态二维数组
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			bmp->GetPixel(x, y, &color);
			pic[y][x] = (0.3*(float)color.GetRed() + 0.59*(float)color.GetGreen() + 0.11*(float)color.GetBlue())/3.6;
		}
	}
	//从char.txt导入字符数组
	char chara[70];
	ifstream fin("char.txt");
	for (int i = 0; i < 70; i++)
		fin >> chara[i];
	fin.close();
	//在屏幕上打印
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			cout << chara[pic[y][x]];
		}
		cout << endl;
	}
	//在文本文件中打印
	ofstream fout("pic_to_char.txt");
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			fout << chara[pic[y][x]];
		}
		fout << endl;
	}
	delete bmp;
	GdiplusShutdown(gdiplustoken);
	delete pic;
	system("pause");
	return 0;
}