#include "stdafx.h"
#include "ParseJson.h"
#include "Json/json.h"

#pragma comment(lib,"lib_json")

/*
 * ��json�ж�ȡ����
 */
bool get_rule_from_json(DebateRules& __rule, const char * __json)
{
	__rule.clear();
	Json::Reader jsonReader(Json::Features::strictMode());
	Json::Value jsonVal;
	if (jsonReader.parse(__json, jsonVal, false))
	{
		auto nSize{ jsonVal.size() };
		if (!nSize)
			return false;
		SRule tmp;
		for (int i = 0; i < nSize; i++)
		{
			tmp.m_nID = jsonVal[i]["id"].asUInt();
			tmp.m_strChapter = jsonVal[i]["chapter"].asString();
			tmp.m_nTime = jsonVal[i]["time"].asUInt();
			tmp.m_nTimerNum = jsonVal[i]["timer"].asUInt();
			tmp.m_vecTimerName.clear();
			for (int j = 0; j < jsonVal[i]["timer_name"].size(); j++)
			{
				tmp.m_vecTimerName.push_back(jsonVal[i]["timer_name"][j].asString());
			}
			__rule.push_back(tmp);
		}
		return true;
	}
	return false;
}

/*
 * �ӹ�������json
 */
bool get_json_from_rule(std::string & __json, const DebateRules& __rule)
{
	__json.clear();
	if (!__rule.size())
		return false;
	Json::Value jsonAllRule;
	Json::Value tmp;
	for (auto iter = __rule.begin(); iter != __rule.end(); ++iter)
	{
		tmp["id"] = iter->m_nID;
		tmp["chapter"] = iter->m_strChapter;
		tmp["time"] = iter->m_nTime;
		tmp["timer"] = iter->m_nTimerNum;
		for (int i = 0; i < iter->m_nTimerNum; i++)
		{
			tmp["timer_name"][i] = iter->m_vecTimerName[i];
		}
		jsonAllRule.append(tmp);
	}
	Json::FastWriter jsonWriter;
	__json = jsonWriter.write(jsonAllRule);
	return true;
}

