
#include "OS.h"
//用户的格式化
void formatUser(){
	//登录时可选格式化所登录用户文件夹下的所有文件
	for (int i = 0; i < fileSystem.sfd[cur_SFD].sfdVec.size();){
		//cout<< fileSystem.sfd[cur_SFD].sfdVec.size();
		int inodeNo = fileSystem.sfd[cur_SFD].sfdVec[i].id;
		int type = fileSystem.iNode[inodeNo].type;
		if (type == 1) deleteDir(fileSystem.sfd[cur_SFD].sfdVec[i].name);
		else freeFile(fileSystem.sfd[cur_SFD].sfdVec[i].name);
	}
}
