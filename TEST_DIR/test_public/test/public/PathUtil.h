//file TraceUtil.h
/***************************************************************************************************
* 1�� Class      �� PathUtil
* 2�� Version    �� 1.0
* 3�� Description�� 
* 4�� Author     �� QNA (http://www.9cpp.com/)
* 5�� Created    �� 2012-9-7 16:27:44
* 6�� History    �� 
* 7�� Remark     �� 
****************************************************************************************************/
#ifndef __PATH_UTIL_H_
#define __PATH_UTIL_H_
#include <Windows.h>

namespace QNA
{
	//ɾ���ļ���
	//��鵱ǰĿ¼��Ҫ���ļ����Ƿ����,��������ڷ���false�����ڷ���true
	bool ChickDirExist(TCHAR* ptszInPath)
	{
		if (!ptszInPath || _tcsclen(ptszInPath)<2)
			return false;

		//����·���Ƿ����	����������򴴽�
		if (GetFileAttributes(ptszInPath) != FILE_ATTRIBUTE_DIRECTORY)
			return false;
		

		return true;
	}

	//�����༶Ŀ¼���ɹ�����true�� ʧ�ܷ���false
	bool CreateMultipleDirectory(TCHAR* ptszInPath)
	{
		int iLen = 0;    
		TCHAR* ptTemp = NULL;		
		TCHAR tszPath[MAX_PATH] = {0};
		TCHAR tszTemPath[MAX_PATH] = {0};
		_tcscpy_s(tszPath, ptszInPath);         //���Ҫ������Ŀ¼�ַ���

		//�������Ƿ���ȷ
		if (!tszPath || _tcsclen(tszPath)<4)
			return false;

		//������ȥ��β��Ϊ'\\'���ַ�
		if (_T('\\') == tszPath[_tcsclen(tszPath)-1])
		{
			tszPath[_tcsclen(tszPath)-1] = 0;
		}

		ptTemp = _tcsrchr(tszPath, _T('\\'));  //��β�������ַ�
		iLen = _tcsclen(ptTemp);
		_tcsncpy_s(tszTemPath, tszPath, _tcsclen(tszPath)-iLen); //�õ���Ŀ¼·��

		//���鸸��·���Ƿ����  		
		if (ChickDirExist(tszTemPath))
		{   //��������򴴽���Ŀ¼
			if (!CreateDirectory(tszPath, NULL))
			{	//�����ļ���ʧ��
				::MessageBox(NULL, tszPath, _T("�����ļ���ʧ��!!!!!"), MB_OK);
				return false;
			}
			else
			{
				SetFileAttributes(tszPath, FILE_ATTRIBUTE_NORMAL);	
				return true;
			}
			return true;
		}	
		else
		{	//�����������ݹ�
			if (!CreateMultipleDirectory(tszTemPath))
			{
				return false;
			}
			else
			{   //��Ŀ¼��������򴴽���Ŀ¼
				if (!CreateMultipleDirectory(tszPath))
					return false;		
			}
		}

		return true;
	}

	//��ȡ��ǰ��������Ŀ¼ �ɹ�����true��ʧ�ܷ���false
	bool GetExePath(TCHAR* ptszInPath)
	{
		TCHAR* ptTem = NULL;
		TCHAR tszTemp[MAX_PATH] = {0};
		//��ȡ��ǰĿ¼  //�����ǻ�ȡ��ǰ�����ļ�������·�� 
		if (!GetModuleFileName(NULL, tszTemp, MAX_PATH) && ptszInPath)
			return false; 

		ptTem = _tcsrchr(tszTemp, _T('\\'));
		memcpy(ptszInPath, tszTemp, (_tcslen(tszTemp)-_tcslen(ptTem))*sizeof(TCHAR));
		return true;
	}

	//��ȡָ���ļ����ȣ���λ���ֽڣ� 
	DWORD GetFileLen(WCHAR* ptszInFilePath)
	{
		//��һ�ַ���
		DWORD dwFileLen = 0;	
		HANDLE hFile = NULL;     
		hFile = CreateFile(ptszInFilePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);       
		dwFileLen = GetFileSize(hFile, NULL);       
		CloseHandle(hFile);     

		////�ڶ��ַ���
		//FILE* pFile = NULL;
		//pFile = ::fopen(ptszInFilePath, "rb");
		//if(pFile == NULL)
		//	return 0;
		//
		//::fseek(pFile, 0, SEEK_SET);    //��λ��ʼ
		//dwFileLen = ::ftell(pFile);
		//fseek(pFile, 0, SEEK_END);  
		//dwFileLen = ::ftell(pFile) - dwFileLen;
		//fclose(pFile);
		//pFile = NULL;
		
		return dwFileLen;
	}
}
#endif
