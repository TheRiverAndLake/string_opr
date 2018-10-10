#pragma once

#include <string>
#include <vector>

//file
//������GetTheName�����������Ϊ�ļ�������ȡ�ļ��Ĳ�����չ���ļ�����ֻ����ļ�������ļ���
//�����GetAllFile����: ��ȡ��ǰ�ļ����������ļ���������ѭ����ȡ�ļ���
//������GetAllFile����: ����ѭ����ȡ�ļ��У�
struct File_Info
{
	std::string file_path;
	std::string file_name;
};

/*============< [Note] class: str_opr >============*/
class str_opr
{
public:
	str_opr();
	virtual ~str_opr();

public:
	bool isNum(std::string str);
	void userlog(int handle, char* flag_file, char* fmt, ...);
	void CvtString(std::string str_src, std::string flag, std::vector<std::string> &str_out);
	void CvtString(const std::string &str_src, char flag, std::vector<std::string> &str_out, bool reverse = false);
	void GetAllFiles( std::string &path, std::string flag_left, std::string flag_right, std::vector<std::string>& files);
	
	//�����ļ�����vec�е�λ��,������ļ���
	int FindFilePos(std::string name, const std::vector<File_Info> &vec_info);
	//��ȡ��ǰ�ļ��������ļ���
	void GetAllFiles( std::string &path, std::string flag_left, std::string flag_right, std::vector<File_Info>& files,bool flag_roll = false);
	std::string GetTheName(const std::string &file_name);
	std::string GetFilePath(const std::string &str_src);
	std::string GetLastExpand(const std::string &str_str, char flag);
	std::string GetDirPath(const std::string &str_src);

/*<---[NOTE]: ��ȡָ���ļ����µ����ļ���--->*/
	void GetDir(const std::string path, std::vector<std::string> &vec_dir);
private:

};
