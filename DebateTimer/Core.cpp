#include "stdafx.h"
#include "Core.h"
#include "ParseJson.h"
#include <fstream>

DebateRules g_drAllRules;

/*
 * ���ļ��л�ȡ����
 */
bool get_rule_from_file(DebateRules & __rule, const char * __file)
{
	std::ifstream fileInput(__file);
	if (!fileInput.is_open())
		return false;
	std::string strFileContext{ std::istreambuf_iterator<char>(fileInput), std::istreambuf_iterator<char>() };
	if (!get_rule_from_json(__rule, strFileContext.c_str()))
		return false;
	return true;
}

/*
* ������д���ļ�
*/
bool write_rule_to_file(DebateRules & __rule, const char * __file)
{
	std::string write;
	if (!get_json_from_rule(write, __rule))
		return false;
	write_to_file(write.c_str(), __file);
	return true;
}

/*
 * ����������д���ļ�
 */
bool write_to_file(const char * __context, const char * __file)
{
	std::ofstream ofs{ __file };
	if (!ofs.is_open())
		return false;
	ofs << __context;
	ofs.close();
	return true;
}


