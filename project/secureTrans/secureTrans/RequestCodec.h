#pragma once
#include<iostream>
#include"RequestMsg.pb.h"
//#include"RespondMsg.pb.h"
#include"Codec.h"
using namespace std;

struct RequestInfo
{
	int cmd;
	string clientId;
	string severId;
	string sign;
	string data;
};

class RequestCodec :public Codec
{
public:
	// �ն���
	RequestCodec();

	// ������Ķ������� ���� �ĳ���
	RequestCodec(string encStr);

	// ������Ķ������� ���� �ĳ���
	RequestCodec(RequestInfo* Info);

	// ���չ���׼����
	void initMessage(string encstr);
	void initMessage(RequestInfo* Info);

	// ��д�Ļ��ຯ�� ���ڷ������л����ַ���
	string encodeMsg();

	// ��д�Ļ��ຯ�� ���ڷ��ط����л������ݣ��ṹ�壩
	/*
		����void*����Ϊ��������RequestMsg�Լ�RespondMsg��Ҫ��д�ú�����
		Ϊ���ܹ�������������(������ķ���ֵ��һ��)���Է���void*����������ǿ������ת������ȡ����
		*/
	void* decodeMsg();

private:
	string m_encStr;

	//Ҫ���л���������RequestMsg���У� ͨ������������л����
	RequestMsg m_msg;
};

