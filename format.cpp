
#include "OS.h"
//�û��ĸ�ʽ��
void formatUser(){
	//��¼ʱ��ѡ��ʽ������¼�û��ļ����µ������ļ�
	for (int i = 0; i < fileSystem.sfd[cur_SFD].sfdVec.size();){
		//cout<< fileSystem.sfd[cur_SFD].sfdVec.size();
		int inodeNo = fileSystem.sfd[cur_SFD].sfdVec[i].id;
		int type = fileSystem.iNode[inodeNo].type;
		if (type == 1) deleteDir(fileSystem.sfd[cur_SFD].sfdVec[i].name);
		else freeFile(fileSystem.sfd[cur_SFD].sfdVec[i].name);
	}
}
