#include "stdafx.h"
#include "str_opr.h"
#include <io.h>
#include <direct.h>
#include <algorithm>
#include <Windows.h>
using namespace std;
str_opr::str_opr()
{

}

str_opr::~str_opr()
{

}

bool str_opr::isNum(std::string str)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] > '9' || str[i] < '0') 
		{
			return false;
		}
	}
	return true;
}
void str_opr::userlog(int handle, char* flag_file, char* fmt, ...)
{
	char info[2048];
	va_list args;
	va_start(args, fmt);
	vsprintf_s(info, fmt, args);
	va_end(args);

	char szTime[100];
	SYSTEMTIME now_time;
	GetLocalTime(&now_time);

	sprintf_s(szTime, "[%4.4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d:%3.3d] ",
		now_time.wYear, now_time.wMonth, now_time.wDay,
		now_time.wHour, now_time.wMinute, now_time.wSecond, now_time.wMilliseconds);

	char filename[100];
	sprintf_s(filename, "d:\\Log\\%s_Handle%d_%d_%d_%d.txt", flag_file, handle, now_time.wYear, now_time.wMonth, now_time.wDay);
	FILE * fp = fopen(filename, "a");
	if (fp)
	{
		fwrite(szTime, 1, strlen(szTime), fp);
		fwrite(info, 1, strlen(info), fp);
		fwrite("\n", 1, 1, fp);
		fclose(fp);
	}
}
void str_opr::CvtString(const std::string &str_src, char flag, std::vector<std::string> &str_out, bool reverse)
{
	if (!reverse) 
	{
		int temp_pos = -1;
		for (size_t i = 0; i < str_src.length(); i++)
		{
			if (str_src[i] == flag) 
			{
				string temp = string(str_src,temp_pos+1,i-temp_pos-1);
				temp_pos = i;
				if (!temp.empty()) 
				{
					str_out.push_back(temp);
				}
			}
			else if (i == (str_src.length() - 1) && str_src[i] != flag) 
			{
				string temp = string(str_src,temp_pos+1, i+1);	
				str_out.push_back(temp);
			}
		}
	}
}

std::string str_opr::GetTheName(const std::string &file_name)
{
	int pos = file_name.find_last_of(".");
	return string(file_name, 0, pos);
}

std::string str_opr::GetLastExpand(const std::string &str_src, char flag)
{
	int pos = 0;
	for (int i = str_src.length()-1; i >= 0; i--)
	{
		if (str_src[i] == flag && pos != 0) 
		{
			return string(str_src,i+1,str_src.length());
		}
		pos++;
	}
	return str_src;
}

std::string str_opr::GetDirPath(const std::string &str_src)
{
	int pos = 0;
	for (int i = str_src.length()-1; i >= 0; i--)
	{
		if (str_src[i] == '\\' && pos != 0)
		{
			return string(str_src,0,i);
		}
		pos++;
	}
	return str_src;
}

string str_opr::GetFilePath(const std::string &str_src)
{
	if (str_src.length() < 1)
	{
		return str_src;
	}
	if (str_src[str_src.length() - 1] != '\\')
	{
		return str_src;
	}
	for (int i = str_src.length() - 1; i >= 0; i--)
	{
		if (str_src[i] != '\\')
		{
			return string (str_src, 0,i+1);
		}
	}
	return str_src;
}

void str_opr::CvtString(std::string str_src, std::string flag, std::vector<std::string> &str_out)
{
	int pos = str_src.find_first_of(flag);
	if (pos > -1) 
	{
		str_out.push_back(string(str_src,0,pos));
		str_src = string(str_src,pos+flag.length(),str_src.length());
		CvtString(str_src,flag,str_out);
	}
}

/*获取所有文件*/
//循环读取文件夹
void str_opr::GetAllFiles( string &path, string flag_left, string flag_right, vector<string>& files )
{
	//文件句柄
	intptr_t   hFile   =   0;
	//文件信息
	struct _finddata_t fileinfo;
	memset(&fileinfo, 0, sizeof(_finddata_t));
	string p;
	if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)
	{
		do
		{
			//如果是目录,迭代之
			//如果不是,加入列表
			if((fileinfo.attrib &  _A_SUBDIR))
			{
				if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)
					GetAllFiles( p.assign(path).append("\\").append(fileinfo.name),flag_left,flag_right, files );
			}
			else
			{
				string temp = p.assign(path).append("\\").append(fileinfo.name);

				string temp_ex = string(temp,temp.length()-flag_right.size(),temp.length());

				int pos = temp.find_last_of('\\');
				string name = string(temp,pos+1,temp.length());

				string name_left = string(name,0,flag_left.length());

				std::transform(temp_ex.begin(), temp_ex.end(), temp_ex.begin(), ::toupper);  
				std::transform(flag_right.begin(), flag_right.end(), flag_right.begin(), ::toupper); 



				if(temp_ex == flag_right && name_left == flag_left && flag_left !="" /*&&(right_str == flag_right)*/)
				{
					files.push_back(temp);
				}
				else if (temp_ex == flag_right&& flag_left =="" /*&&(right_str == flag_right)*/)
				{
					files.push_back(temp);
				}

			}
		}while(_findnext(hFile, &fileinfo)  == 0);
		_findclose(hFile);
	}
}

int str_opr::FindFilePos(std::string name, const vector<File_Info> &vec_info)
{
	int flag = -1;
	for (int i = 0; i < vec_info.size(); i++)
	{
		if (name.compare(vec_info[i].file_name) == 0)
		{
			flag = i;
			break;
		}		
	}
	return flag;
}

void str_opr::GetAllFiles( std::string &path, std::string flag_left, std::string flag_right, std::vector<File_Info>& files,bool flag_roll)
{

	//文件句柄
	intptr_t   hFile   =   0;
	//文件信息
	struct _finddata_t fileinfo;
	memset(&fileinfo, 0, sizeof(_finddata_t));
	string p;
	if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)
	{
		do
		{
			//如果是目录,迭代之
			//如果不是,加入列表
			if((fileinfo.attrib &  _A_SUBDIR))
			{
				if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)
				{
					if (flag_roll)
					{
						GetAllFiles(path,flag_left,flag_right,files,flag_roll);
					}
					continue;
				}
			}
			else
			{
				File_Info file_temp;
				string temp = p.assign(path).append("\\").append(fileinfo.name);
				string temp_ex = string(temp,temp.length()-flag_right.size(),temp.length());
				int pos = temp.find_last_of("\\");
				string name = string(temp,pos+1,temp.length());
				string name_left = string(name,0,flag_left.length());

				std::transform(temp_ex.begin(), temp_ex.end(), temp_ex.begin(), ::toupper);  
				std::transform(flag_right.begin(), flag_right.end(), flag_right.begin(), ::toupper); 

				if(temp_ex == flag_right && name_left == flag_left && flag_left !="" /*&&(right_str == flag_right)*/)
				{
					file_temp.file_path = temp;
					file_temp.file_name = GetLastExpand(temp,'\\');
					files.push_back(file_temp);
				}
				else if (temp_ex == flag_right&& flag_left =="" /*&&(right_str == flag_right)*/)
				{
					file_temp.file_path = temp;
					file_temp.file_name = GetLastExpand(temp,'\\');
					files.push_back(file_temp);
				}

			}
		}while(_findnext(hFile, &fileinfo)  == 0);
		_findclose(hFile);
	}
}
void str_opr::GetDir(const std::string path, std::vector<std::string> &vec_dir)
{
	//文件句柄
	intptr_t   hFile   =   0;
	//文件信息
	struct _finddata_t fileinfo;
	memset(&fileinfo, 0, sizeof(_finddata_t));
	string p;
	if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)
	{
		do
		{
			//如果是目录,迭代之
			//如果不是,加入列表
			if((fileinfo.attrib &  _A_SUBDIR))
			{
				if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)
				{
					//GetAllFiles( p.assign(path).append("\\").append(fileinfo.name),flag_left,flag_right, files );
					vec_dir.push_back(p.assign(path).append("\\").append(fileinfo.name));
				}
			}
			
		}while(_findnext(hFile, &fileinfo)  == 0);
		_findclose(hFile);
	}
}
