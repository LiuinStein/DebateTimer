#pragma once
#ifndef __DATA_STRUCT_H
#define __DATA_STRUCT_H
#include <string>
#include <vector>

// 规则集
struct SRule
{
	unsigned m_nID;				// 顺序id
	std::string m_strChapter;		// 该项名称
	unsigned m_nTime;				// 该项时间
	unsigned m_nTimerNum;			// 时钟数目,最多2个时钟
	std::vector<std::string> m_vecTimerName;	// 各时钟名称

	// 用来排序
	bool operator<(SRule & __rhs)const
	{
		return m_nID < __rhs.m_nID;
	}
};

typedef std::vector<SRule> DebateRules;
// 默认规则文件
static const char * g_strRuleFile = "rule.json";
// 默认规则
static const char * g_strDefaultRule{
R"(
[
    {
        "id": 1,
        "chapter": "正方一辩发言",
        "time": 180,
        "timer": 1,
        "timer_name": [
            "正方"
        ]
    },
    {
        "id": 2,
        "chapter": "反方四辩盘问正方一辩",
        "time": 90,
        "timer": 1,
        "timer_name": [
            "反方"
        ]
    },
    {
        "id": 3,
        "chapter": "反方一辩发言",
        "time": 180,
        "timer": 1,
        "timer_name": [
            "反方"
        ]
    },
    {
        "id": 4,
        "chapter": "正方四辩盘问反方一辩",
        "time": 90,
        "timer": 1,
        "timer_name": [
            "正方"
        ]
    },
    {
        "id": 5,
        "chapter": "正方二辩针对对方立论作驳论",
        "time": 120,
        "timer": 1,
        "timer_name": [
            "正方"
        ]
    },
    {
        "id": 6,
        "chapter": "反方二辩针对对方立论作驳论",
        "time": 120,
        "timer": 1,
        "timer_name": [
            "反方"
        ]
    },
    {
        "id": 7,
        "chapter": "正方二辩对辩反方二辩",
        "time": 90,
        "timer": 1,
        "timer_name": [
            "正方"
        ]
    },
    {
        "id": 8,
        "chapter": "正方三辩盘问",
        "time": 120,
        "timer": 1,
        "timer_name": [
            "正方"
        ]
    },
    {
        "id": 9,
        "chapter": "反方三辩盘问",
        "time": 120,
        "timer": 1,
        "timer_name": [
            "反方"
        ]
    },
    {
        "id": 10,
        "chapter": "正方三辩小结",
        "time": 90,
        "timer": 1,
        "timer_name": [
            "正方"
        ]
    },
    {
        "id": 11,
        "chapter": "反方三辩小结",
        "time": 90,
        "timer": 1,
        "timer_name": [
            "反方"
        ]
    },
    {
        "id": 12,
        "chapter": "自由辩论",
        "time": 480,
        "timer": 2,
        "timer_name": [
            "正方",
            "反方"            
        ]        
    },
    {
        "id": 13,
        "chapter": "反方四辩总结陈词",
        "time": 180,
        "timer": 1,
        "timer_name": [
            "反方"
        ]
    },
    {
        "id": 14,
        "chapter": "正方四辩总结陈词",
        "time": 180,
        "timer": 1,
        "timer_name": [
            "正方"
        ]
    }
])" };

#endif
