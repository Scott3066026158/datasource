#include "..\\stdafx.h"
#include "CFile.h"
#include "CStr.h"

bool CFileA::Append(const char *file, const char *content)
{
	ofstream fs(file, ios::app);
	if(fs)
	{
		fs << content;
		fs.close();
		return true;
	}
	return false;
}

bool CFileA::Append(const String &file, const String &content)
{
	string sFile, sContent;
	CStrA::wstringTostring(sFile, file);
	CStrA::wstringTostring(sContent, content);
	return Append(sFile.c_str(), sContent.c_str());
}

void CFileA::CreateDirectory(const char *dir)
{
	_mkdir(dir);
}

void CFileA::CreateDirectory(const String &dir)
{
	string sDir;
	CStrA::wstringTostring(sDir, dir);
	return CreateDirectory(sDir.c_str());
}

bool CFileA::IsDirectoryExist(const char *dir)
{
	if((_access(dir, 0 )) != -1 )
	{
		return true;
	}
	return false;
}

bool CFileA::IsDirectoryExist(const String &dir)
{
	string sDir;
	CStrA::wstringTostring(sDir, dir);
	return IsDirectoryExist(sDir.c_str());
}

bool CFileA::IsFileExist(const char *file)
{
	ifstream fs;
	fs.open(file, ios::in);
	if(fs)
	{
		fs.close();
		return true;
	}
	else
	{
		return false;
	}
}

bool CFileA::IsFileExist(const String &file)
{
	string sFile;
	CStrA::wstringTostring(sFile, file);
	return IsFileExist(sFile.c_str());
}

bool CFileA::GetDirectories(const char *dir, vector<string> *dirs)
{
	long hFile = 0;  
	struct _finddata_t fileinfo;  
	string p;  
	if((hFile = (long)_findfirst(p.assign(dir).append("\\*").c_str(),&fileinfo)) !=  -1)  
	{  
		do  
		{  
			if(fileinfo.attrib &  _A_SUBDIR)  
			{  
				if(strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					dirs->push_back(p.assign(dir).append("\\").append(fileinfo.name));  
				}
			}  
		}
		while(_findnext(hFile, &fileinfo)  == 0);  
		_findclose(hFile); 
	} 
	return dirs->size() > 0;
}

bool CFileA::GetDirectories(const String &file, vector<String> *dirs)
{
	vector<string> vectors;
	string sFile;
	String dir;
	CStrA::wstringTostring(sFile, file);
	bool res = GetDirectories(sFile.c_str(), &vectors);
	int size=(int)vectors.size();
	for (int i = 0; i < size; i++)
	{
		CStrA::stringTowstring(dir, vectors[i]);
		dirs->push_back(dir);
	}
	return res;
}

_int64 CFileA::GetFileMTime(const char* file)
{
    struct stat fileInfo;
    int status = stat(file, &fileInfo);
    if(status == -1)
    {
        return 0;
    }
    else if(status == 0)
    {
        return fileInfo.st_mtime + 28800;
    }
	else
	{
		return 0;
	}
}

int CFileA::GetFileLength(const char *file)
{
	FILE* fp = 0;
	int fileLen = 0;
	fp = fopen(file, "rb");
	if (!fp)
	{
		return 0;
	}
	fseek(fp, 0, SEEK_END);        
	fileLen = ftell(fp);
	fclose(fp);
	return fileLen;
}

int CFileA::GetFileLength(const String &file)
{
	string sFile;
	CStrA::wstringTostring(sFile, file);
	return GetFileLength(sFile.c_str());
}

bool CFileA::GetFiles(const char *dir, vector<string> *files)
{
	long hFile = 0;  
	struct _finddata_t fileinfo;  
	string p;  
	if((hFile = (long)_findfirst(p.assign(dir).append("\\*").c_str(),&fileinfo)) !=  -1)  
	{  
		do  
		{  
			if(!(fileinfo.attrib &  _A_SUBDIR))  
			{  
				files->push_back(p.assign(dir).append("\\").append(fileinfo.name));  
			}  
		}
		while(_findnext(hFile, &fileinfo)  == 0);  
		_findclose(hFile); 
	} 
	return files->size() > 0;
}

bool CFileA::GetFiles(const String &dir, vector<String> *files)
{
	string sDir;
	String file;
	vector<string> vectors;
	CStrA::wstringTostring(sDir, dir);
	bool res = GetFiles(sDir.c_str(), &vectors);
	int size=(int)vectors.size();
	for (int i = 0; i < size; i++)
	{
		CStrA::stringTowstring(file, vectors[i]);
		files->push_back(file);
	}
	return res;
}

int CFileA::GetFileState(const char *file, struct stat *buf)
{
	return stat(file, buf);
}

int CFileA::GetFileState(const String &file, struct stat *buf)
{
	string sFile;
	CStrA::wstringTostring(sFile, file);
	return GetFileState(sFile.c_str(), buf);
}

bool CFileA::Read(const char *file, string *content)
{
	if(CFileA::IsFileExist(file))
	{
		int fileLength = GetFileLength(file);
		char *szContent = new char[fileLength + 1];
		memset(szContent, '\0', fileLength + 1);
		ifstream fs(file, ios::in); 
		if(fs)
		{
			if(fileLength > 0)
			{
				while(!fs.eof())
				{
					fs.read(szContent, fileLength); 
				}
			}
			fs.close();
		}
		*content = szContent;
		delete[] szContent;
		szContent = 0;
		return true;
	}
	return false;
}	

bool CFileA::ReadLine(ifstream *fs, string *lineContent, int lineLength)
{
	char *szContent = new char[lineLength];
	memset(szContent, '\0', lineLength);
	//ifstream fs(file, ios::in); 
	if(fs)
	{
		if(!fs->eof())
		{
			fs->getline(szContent, lineLength); 
		}
	}
	*lineContent = szContent;
	delete[] szContent;
	szContent = 0;
	return true;
}

bool CFileA::ReadLine(ifstream *fs, String *lineContent, int lineLength)
{
	char *szContent = new char[lineLength];
	memset(szContent, '\0', lineLength);
	//ifstream fs(file, ios::in); 
	if(fs)
	{
		if(!fs->eof())
		{
			fs->getline(szContent, lineLength); 
		}
	}
	string sContent(szContent);
	String wsContent;
	CStrA::stringTowstring(wsContent, sContent);	
	*lineContent = wsContent;
	delete[] szContent;
	szContent = 0;
	return true;
}

bool CFileA::Read(const String &file, String *content)
{
	string sFile;
	CStrA::wstringTostring(sFile,file);
	string str;
	bool res = Read(sFile.c_str(), &str);
	String temp;
	CStrA::stringTowstring(temp, str);
	*content = temp;
	return res;
}

void CFileA::RemoveFile(const char *file)
{
	if(CFileA::IsFileExist(file))
	{
		String wFile;
		CStrA::stringTowstring(wFile, file);
		::DeleteFile(wFile.c_str());
	}
}

void CFileA::RemoveFile(const String &file)
{
	string sFile;
	CStrA::wstringTostring(sFile, file);
	return RemoveFile(sFile.c_str());
}

bool CFileA::Write(const char *file, const char *content)
{
	ofstream fs(file, ios::out);
	if(fs)
	{
		fs << content;
		fs.close();
		return true;
	}
	return false;
}

bool CFileA::Write(const String &file, const String &content)
{
	string sFile,sContent;
	CStrA::wstringTostring(sFile, file);
	CStrA::wstringTostring(sContent, content);
	return Write(sFile.c_str(), sContent.c_str());
}