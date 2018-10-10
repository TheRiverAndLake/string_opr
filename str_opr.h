#pragma once

#include <string>
#include <vector>

//file
//增加了GetTheName函数：传入参为文件名，获取文件的不带扩展的文件名。只针对文件不针对文件夹
//添加了GetAllFile函数: 获取当前文件夹下所有文件，不进行循环读取文件夹
//更改了GetAllFile函数: 进行循环读取文件夹，
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
	
	//查找文件名在vec中的位置,输入的文件名
	int FindFilePos(std::string name, const std::vector<File_Info> &vec_info);
	//读取当前文件下所有文件；
	void GetAllFiles( std::string &path, std::string flag_left, std::string flag_right, std::vector<File_Info>& files,bool flag_roll = false);
	std::string GetTheName(const std::string &file_name);
	std::string GetFilePath(const std::string &str_src);
	std::string GetLastExpand(const std::string &str_str, char flag);
	std::string GetDirPath(const std::string &str_src);

/*<---[NOTE]: 获取指定文件夹下的子文件夹--->*/
	void GetDir(const std::string path, std::vector<std::string> &vec_dir);
private:

};
