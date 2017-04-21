#pragma once
#ifndef __CORE_H
#define __CORE_H
#include "DataStruct.h"

// 当前规则
extern DebateRules g_drAllRules;

/*
* 从文件中获取规则
*/
bool get_rule_from_file(DebateRules & __rule, const char * __file = g_strRuleFile);

/*
 * 将规则写入文件
 */
bool write_rule_to_file(DebateRules & __rule, const char * __file = g_strRuleFile);

/*
 * 将任意内容写入文件
 */
bool write_to_file(const char * __context, const char * __file);

#endif

