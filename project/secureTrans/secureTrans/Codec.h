#pragma once
#include<iostream>
using namespace std;
class Codec
{
public:
	Codec();
	virtual ~Codec();

	// ��д�Ļ��ຯ�� ���ڷ������л����ַ���
	virtual string encodeMsg();

	// ��д�Ļ��ຯ�� ���ڷ��ط����л������ݣ��ṹ�壩
	/*
		����void*����Ϊ��������RequestMsg�Լ�RespondMsg��Ҫ��д�ú�����
		Ϊ���ܹ����������������Է���void*����������ǿ������ת������ȡ����
		*/
	virtual void* decodeMsg();
};

