#pragma once
#ifndef __CORE_H
#define __CORE_H
#include "DataStruct.h"

// ��ǰ����
extern DebateRules g_drAllRules;

/*
* ���ļ��л�ȡ����
*/
bool get_rule_from_file(DebateRules & __rule, const char * __file = g_strRuleFile);

/*
 * ������д���ļ�
 */
bool write_rule_to_file(DebateRules & __rule, const char * __file = g_strRuleFile);

/*
 * ����������д���ļ�
 */
bool write_to_file(const char * __context, const char * __file);

#endif

