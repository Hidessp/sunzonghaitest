#pragma once
class GPS
{
public:
	GPS();
	~GPS();
	//导航文件计算所得卫星坐标

public:
	int prn;
	double X;
	double Y;
	double Z;

};