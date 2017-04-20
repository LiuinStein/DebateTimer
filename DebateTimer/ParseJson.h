#pragma once
#ifndef __PARSE_JSON_H
#define __PARSE_JSON_H
#include <vector>
#include "DataStruct.h"

/*
* ��json�ж�ȡ����
*/
bool get_rule_from_json(std::vector<SRule> & __rule, const char * __json);

/*
* �ӹ�������json
*/
bool get_json_from_rule(std::string & __json, const std::vector<SRule>& __rule);

#endif
