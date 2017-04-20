#pragma once
#ifndef __DATA_STRUCT_H
#define __DATA_STRUCT_H
#include <string>

// ����
struct SRule
{
	unsigned m_nID;				// ˳��id
	std::string m_strChapter;		// ��������
	unsigned m_nTime;				// ����ʱ��
	unsigned m_nTimerNum;			// ʱ����Ŀ,���4��ʱ��
	std::vector<std::string> m_vecTimerName;	// ��ʱ������

	// ��������
	bool operator<(SRule & __rhs)const
	{
		return m_nID < __rhs.m_nID;
	}
};


// Ĭ������
const char * g_strDefaultRule{
R"(
[
    {
        "id": 1,
        "chapter": "����һ�緢��",
        "time": 180,
        "timer": 1,
        "timer_name": [
            "ʣ��ʱ��"
        ]
    },
    {
        "id": 2,
        "chapter": "�����ı���������һ��",
        "time": 90,
        "timer": 1,
        "timer_name": [
            "ʣ��ʱ��"
        ]
    },
    {
        "id": 3,
        "chapter": "����һ�緢��",
        "time": 180,
        "timer": 1,
        "timer_name": [
            "ʣ��ʱ��"
        ]
    },
    {
        "id": 4,
        "chapter": "�����ı����ʷ���һ��",
        "time": 90,
        "timer": 1,
        "timer_name": [
            "ʣ��ʱ��"
        ]
    },
    {
        "id": 5,
        "chapter": "����������ԶԷ�����������",
        "time": 120,
        "timer": 1,
        "timer_name": [
            "ʣ��ʱ��"
        ]
    },
    {
        "id": 6,
        "chapter": "����������ԶԷ�����������",
        "time": 120,
        "timer": 1,
        "timer_name": [
            "ʣ��ʱ��"
        ]
    },
    {
        "id": 7,
        "chapter": "��������Ա練������",
        "time": 90,
        "timer": 1,
        "timer_name": [
            "ʣ��ʱ��"
        ]
    },
    {
        "id": 8,
        "chapter": "������������",
        "time": 120,
        "timer": 1,
        "timer_name": [
            "ʣ��ʱ��"
        ]
    },
    {
        "id": 9,
        "chapter": "������������",
        "time": 120,
        "timer": 1,
        "timer_name": [
            "ʣ��ʱ��"
        ]
    },
    {
        "id": 10,
        "chapter": "��������С��",
        "time": 90,
        "timer": 1,
        "timer_name": [
            "ʣ��ʱ��"
        ]
    },
    {
        "id": 11,
        "chapter": "��������С��",
        "time": 90,
        "timer": 1,
        "timer_name": [
            "ʣ��ʱ��"
        ]
    },
    {
        "id": 12,
        "chapter": "���ɱ���",
        "time": 480,
        "timer": 2,
        "timer_name": [
            "����ʣ��ʱ��",
            "����ʣ��ʱ��"            
        ]        
    },
    {
        "id": 13,
        "chapter": "�����ı��ܽ�´�",
        "time": 180,
        "timer": 1,
        "timer_name": [
            "ʣ��ʱ��"
        ]
    },
    {
        "id": 14,
        "chapter": "�����ı��ܽ�´�",
        "time": 180,
        "timer": 1,
        "timer_name": [
            "ʣ��ʱ��"
        ]
    }
])" };

#endif
