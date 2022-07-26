#include "OS.h"


int *getIaddr(int indexnum){

	string str[256];
	int *iaddr = new int[256];
	int flag = 0;
	for (int j = 0, i = 0; j < fileSystem.diskBlock[indexnum].file.size(); j++){
		if (fileSystem.diskBlock[indexnum].file[j] == ' ' && flag == 0){
			continue;
		}
		else if (fileSystem.diskBlock[indexnum].file[j] == ' '){
			i++;
			flag = 0;
		}
		else{
			flag = 1;
			str[i] += fileSystem.diskBlock[indexnum].file[j];
		}
	}

	for (int i = 0; i < fileSystem.diskBlock[indexnum].strNum; i++){
		iaddr[i] = atoi(str[i].c_str());   //atoi 是将字符串转化为int型，c_str()提供一个可读不可改字符数组指针
	}
	return iaddr;
}


//返回当前文件所占用的最后磁盘块
int getCur_blockNo(int inodeNo){
	int blocknum = fileSystem.iNode[inodeNo].diskBlockNum;  //文件占用磁盘块个数
	int indexnum = fileSystem.iNode[inodeNo].diskBlockId;   //所占磁盘块的id号的索引块
	if (blocknum == 1){
		return -2;
	}
	else if (blocknum > 1){
		int *iaddr = getIaddr(indexnum);   //得到索引块中存放的内容
		for (int i = 0; i < 10; i++){
			if (iaddr[i] == -1)
				return iaddr[i - 1];    //最后一块以-1结束
		}
		for (int j = 10; j < 13; j++){
			if (iaddr[j] == -1){
				if (j == 10)
					return iaddr[j - 1];
				else{
					int *iaddr_f1 = getIaddr(iaddr[j - 1]);
					return iaddr_f1[127];           //0-9是直接，10-12间接
				}
			}
			else{
				int *iaddr_1 = getIaddr(iaddr[j]);//两级索引
				for (int i = 0; i < 128; i++){
					if (iaddr_1[i] == -1)
						return iaddr_1[i - 1];
				}
			}
		}
	}
	return -1;
}




//将数组中的索引内容写回到相应的索引块中，磁盘文件中
void writeiaddr(int BlockNo, int *iaddr){   //写入磁盘文件中，读文件，写文件,Block是对应的索引块的块号
	fileSystem.diskBlock[BlockNo].file = "";
	for (int i = 0; i < 13; i++){
		string str;
		stringstream ss;
		ss << iaddr[i];
		ss >> str;
		fileSystem.diskBlock[BlockNo].file = " " + fileSystem.diskBlock[BlockNo].file + " " + str + " ";
	}
}





int writeIndexBlock(int indexnum, int BlockNo){

	int *iaddr = getIaddr(indexnum);         //读出索引块内容
	for (int i = 0; i < 10; i++){
		if (iaddr[i] == -1){

			iaddr[i] = BlockNo;
			writeiaddr(indexnum, iaddr);
			delete[] iaddr;
			return BlockNo;                 //返回最后写入的块号
		}
	}

	for (int j = 10; j < 13; j++){
		if (iaddr[j] == -1){                          //说明上一块二次间址索引是满的，只能从当前的再建新的二级索引
			iaddr[j] = BlockNo;                      //BlockNo是要放入的索引中的块号
			int cur_B = allocateOneBlock();
			fileSystem.diskBlock[BlockNo].strNum = 128;
			int iaddr_all1[128];
			for (int i = 0; i < 128; i++){
				iaddr_all1[i] = -1;
			}
			iaddr_all1[0] = cur_B;                  //iaddre_all1[0]中存放的是二级索引块块号
			writeiaddr(BlockNo, iaddr_all1);
			delete[] iaddr_all1;
			delete[] iaddr;
			return cur_B;                           //返回最后写入的块号
		}
		else{                                 //否则直接在二级索引中找相应的空位写入当前块号
			int *iaddr_1 = getIaddr(iaddr[j]);
			for (int i = 0; i < 128; i++){
				if (iaddr_1[i] == -1){
					iaddr_1[i] = BlockNo;
					writeiaddr(iaddr[j], iaddr_1);
					return BlockNo;
				}
			}
			delete iaddr_1;
		}
	}
	delete[] iaddr;
	return -1;
}


//写指定文件名的文件
int writeFile(string name){          //应该先输入文件名字再去找文件所对应的i结点，这个地方应该是可以实现共享的
	int pos = checkExitsfd(name);      //检查当前目录下有没有该文件
	char c;
	char num[100];
	char s[10240];
	int a;
	int len2;
	printf("文件输入-----1\n");
	printf("手动输入-----2\n");
	cin >> a;
	if (a == 2){
		readFile(name);
		cin >> s;
		len2 = strlen(s);
		if (len2 == 0)
		{
			textcolor(12);
			cout << "输入为空\n";
			return 1;
		}
	}
	else {
		cout << "请输入文件名：";
		cin >> num;
		char filename[100];
		sprintf(filename, "%s", num);
		ifstream fin(filename);
		fin.getline(s, 10240, '#');
		if (s[0] == '#'){
			textcolor(12);
			cout << "文件为空\n";
			return 1;
		}
	}
	int len = strlen(s);
	int inodeNo = fileSystem.sfd[cur_SFD].sfdVec[pos].id;     //找到已有文件的i结点号
	int indexnum = fileSystem.iNode[inodeNo].diskBlockId;     //所占磁盘块的id号的索引块
	int cur_blockNo = getCur_blockNo(inodeNo);                //返回当前文件所对占的最后一块磁盘块

	if (cur_blockNo == -1){
		textcolor(12);
		cout << "写文件发现磁盘块存储错误\n";
		return 0;
	}
	else if (cur_blockNo == -2){               //文件所对应的磁盘块个数为1，返回-2
		cur_blockNo = allocateOneBlock();
		fileSystem.iNode[inodeNo].diskBlockNum++;
		cur_blockNo = writeIndexBlock(indexnum, cur_blockNo);
	}
	int remainstr = len;
	int m = 512 - fileSystem.diskBlock[cur_blockNo].file.size();  //文件对应最后磁盘块剩余空间
	int flag = 0, num1 = 0;
	for (int n = m; n > 0; n--){
		c = s[0];
		for (int ii = 1; ii <= len - num1; ii++){
			s[ii - 1] = s[ii];                      //把s中内容左移一位
		}
		num1++;
		remainstr--;
		fileSystem.diskBlock[cur_blockNo].file += c;
		if (remainstr == 0)
			break;  //已经全部存放完成
		if (c != ' ' && flag == 0){     //?????????????????????????????????????????????
			fileSystem.diskBlock[cur_blockNo].strNum++;
			flag = 1;
			continue;
		}
		else if (c != ' ')
			continue;
		else
			flag = 0;
	}
	if (remainstr != 0){
		flag = 0;
		cur_blockNo = allocateOneBlock();
		fileSystem.iNode[inodeNo].diskBlockNum++;
		cur_blockNo = writeIndexBlock(indexnum, cur_blockNo);
		for (int k = 0, j = 0; k < remainstr; k++, j++){
			if (j == 512){                  //当前块中的最后一个字节
				k--;
				j = 0;
				cur_blockNo = allocateOneBlock();
				fileSystem.iNode[inodeNo].diskBlockNum++;
				cur_blockNo = writeIndexBlock(indexnum, cur_blockNo);
				continue;
			}
			else{
				c = s[0];
				for (int ii = 1; ii <= len - num1; ii++){
					s[ii - 1] = s[ii];
				}
				num1++;
				fileSystem.diskBlock[cur_blockNo].file += c;
				if (c != ' ' && flag == 0){
					fileSystem.diskBlock[cur_blockNo].strNum++;
					flag = 1;
					continue;
				}
				else if (c != ' ')
					continue;
				else
					flag = 0;
			}
		}
	}
	textcolor(10);
	cout << "写文件成功！\n";
}

//输出文件磁盘块内容
void outputBlock(int blockNO){
	string output;
	output = fileSystem.diskBlock[blockNO].file;
	textcolor(15);
	cout << output;
}

//读文件内容函数
void readFile(string name){

	int pos = checkExitsfd(name);  //查看是当前目录下的第几个文件
	if (pos == -1){
		textcolor(12);
		cout << "文件不存在\n";
	}
	else{
		int inodeNo = fileSystem.sfd[cur_SFD].sfdVec[pos].id;   //文件对应的i结点编号
		int indexnum = fileSystem.iNode[inodeNo].diskBlockId;    //文件对应的索引块
		int *iaddr = getIaddr(indexnum);                      //对应磁盘块中的内容
		for (int i = 0; i < 10; i++){
			if (iaddr[i] != -1)
				outputBlock(iaddr[i]);  //iaddr[i]中直接存放文件内容，可直接输出
			else{
				//cout << endl; //文件输出结束
				return;
			}
		}

		for (int j = 10; j < 13; j++){
			if (iaddr[j] == -1)
				return;
			else{
				int *iaddr_1 = getIaddr(iaddr[j]);
				for (int i = 0; i < 128; i++){
					if (iaddr_1[i] != -1)
						outputBlock(iaddr_1[i]);
					else
						return;
				}
				delete iaddr_1;
			}
		}
		delete[] iaddr;
	}
}
