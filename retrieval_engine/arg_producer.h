#ifndef ARG_PRODUCER
#define ARG_PRODUCER

#include <vector>
#include <iostream>
#include <string>
#include <direct.h> 
#include <io.h>

using namespace std;

void produceArgArray(char** const argv, vector<char *>& arg)
{
	vector<string> arg_str;
	string begName(argv[1]);
	string endName(argv[2]);
	
	int begNumStart = 0;//begName.find('(') + 1;
	int begNumEnd = 6;//begName.find(')');
	int begNumLen = begNumEnd - begNumStart;
	
	int endNumStart = 0;//endName.find('(') + 1;
	int endNumEnd = 6;//endName.find(')');
	int endNumLen = endNumEnd - endNumStart;
	
	int argStartNum = atoi(begName.substr(begNumStart, begNumLen).c_str());
	int argEndNum = atoi(endName.substr(endNumStart, endNumLen).c_str());
	
	cout << "Input argument contour number range = " << argStartNum << " to " << argEndNum << endl;

	begName.erase(begNumStart, begNumLen);
	
	for(long double i = argStartNum; i <= argEndNum; i++)
	{
		string fileName(begName);
		stringstream ss;
		ss << setw(6) << setfill('0') << i;
		string fileNum = ss.str();
		
		fileName.insert(begNumStart, fileNum);
		//cout << "fileName = " << fileName << endl;
		arg_str.push_back(fileName);
	}

	for(int i = 0; i < arg_str.size(); i++)
	{
		char* c_ptr = new char[arg_str[i].size()+1];
		copy(arg_str[i].begin(), arg_str[i].end(), c_ptr);
		c_ptr[arg_str[i].size()] = '\0';
		arg.push_back(c_ptr);
		
	}
	
}


void produceArgArray2(char** const argv, vector<char *>& arg)
{
	vector<string> arg_str;
	string begName(argv[3]);
	string endName(argv[4]);
	
	int begNumStart = 0;//begName.find('(') + 1;
	int begNumEnd = 6;//begName.find(')');
	int begNumLen = begNumEnd - begNumStart;
	
	int endNumStart = 0;//endName.find('(') + 1;
	int endNumEnd = 6;//endName.find(')');
	int endNumLen = endNumEnd - endNumStart;
	
	int argStartNum = atoi(begName.substr(begNumStart, begNumLen).c_str());
	int argEndNum = atoi(endName.substr(endNumStart, endNumLen).c_str());
	
	cout << "Input argument img number range = " << argStartNum << " to " << argEndNum << endl;

	begName.erase(begNumStart, begNumLen);
	
	for(long double i = argStartNum; i <= argEndNum; i++)
	{
		string fileName(begName);
		stringstream ss;
		ss << setw(6) << setfill('0') << i;
		string fileNum = ss.str();
		
		fileName.insert(begNumStart, fileNum);
		//cout << "fileName = " << fileName << endl;
		arg_str.push_back(fileName);
	}

	for(int i = 0; i < arg_str.size(); i++)
	{
		char* c_ptr = new char[arg_str[i].size()+1];
		copy(arg_str[i].begin(), arg_str[i].end(), c_ptr);
		c_ptr[arg_str[i].size()] = '\0';
		arg.push_back(c_ptr);
		
	}
	
}

void fileInFolder( char* sdir, char* filter, vector<string> &filepath )
{
	char path[256];
	struct _finddata_t c_file;
	long hFile;

	_chdir( sdir );
	hFile = _findfirst(filter, &c_file);

	//cout << "open the fellow file:" << endl;

	if( hFile!=-1 )
	{
		do{
			sprintf( path, "%s\\%s", sdir, c_file.name );
			filepath.push_back(path);
			//cout << *(filepath.end()-1) << endl;
		}while( _findnext( hFile, &c_file )==0 );	
	}
}


#endif