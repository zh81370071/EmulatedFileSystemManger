#include "OS.h"

//初始化超级块
void initSuperBlock(){
	//初始化超级块
	freopen("superBlock.txt", "r", stdin);
	scanf("%d%d", &fileSystem.superBlock.i_node, &fileSystem.superBlock.freei_node);
	//cin>>fileSystem.superBlock.i_node>>fileSystem.superBlock.freei_node;
	//scanf("%d%d", &fileSystem.superBlock.i_node, &fileSystem.superBlock.freei_node);
	for (int i = 0; i < fileSystem.superBlock.freei_node; i++){
		int tmp;
		scanf("%d", &tmp);
		iNode[tmp] = 1;      //i结点位示图
		fileSystem.superBlock.freeiid.push_back(tmp);
	}
	//cin>>fileSystem.superBlock.sfd>>fileSystem.superBlock.free_SFD;
	scanf("%d%d", &fileSystem.superBlock.sfd, &fileSystem.superBlock.free_SFD);
	for (int i = 0; i < fileSystem.superBlock.free_SFD; i++){
		int tmp;
		scanf("%d", &tmp);
		SFDBlock[tmp] = 1;      //空闲SFD（目录）初始化
		fileSystem.superBlock.freeSFD.push_back(tmp);
	}
	//cin>>fileSystem.superBlock.disk>>fileSystem.superBlock.freeDisk;
	scanf("%d%d", &fileSystem.superBlock.disk, &fileSystem.superBlock.freeDisk);   //空闲磁盘块
	fclose(stdin);
	freopen("CON", "r", stdin);  //重定位标准输入，将标准输入由键盘改成文件输入

	freopen("freeBlock.txt", "r", stdin);       //空闲的磁盘块成组链接法保存
	fileSystem.superBlock.freeDiskSta[0] = 1;     //放入一块
	fileSystem.superBlock.freeDiskSta[1] = -1;   //成组连接第一块
	for (int i = 0; i < fileSystem.superBlock.freeDisk; i++){
		int tmp;
		scanf("%d", &tmp);
		diskBlock[tmp] = 1;                               //1表示空闲，磁盘块位示图初始化
		int &pos = fileSystem.superBlock.freeDiskSta[0];  //每次都等于位示图栈顶数（栈顶是目前该块中存放的空闲块数
		if (pos < 50)
			fileSystem.superBlock.freeDiskSta[++pos] = tmp;    //放置空闲块
		else{   //超级块处理     //疑问
			for (int i = 0; i <= 50; i++){
				stringstream ss;
				
				
				
				string tmpstr;
				ss << fileSystem.superBlock.freeDiskSta[i];
				ss >> tmpstr;
				fileSystem.diskBlock[tmp].file += " ";
				fileSystem.diskBlock[tmp].file += tmpstr;
			}
			fileSystem.superBlock.freeDiskSta[0] = 1;
			fileSystem.superBlock.freeDiskSta[1] = tmp;
		}
	}

	fclose(stdin);
	freopen("CON", "r", stdin);
}


//初始化i结点
void initINode(){
	//初始化前9个i结点
	freopen("iNode.txt", "r", stdin);
	for (int i = 0; i <= 8; i++){
		scanf("%d%d%d%d%d", &fileSystem.iNode[i].id, &fileSystem.iNode[i].type, &fileSystem.iNode[i].sfd_id, &fileSystem.iNode[i].filelen, &fileSystem.iNode[i].qcount);
		//cin>>fileSystem.iNode[i].id>>fileSystem.iNode[i].type>>fileSystem.iNode[i].sfd_id>>fileSystem.iNode[i].filelen>>fileSystem.iNode[i].qcount;
		for (int j = 0; j < 8; j++)
			scanf("%d", &fileSystem.iNode[i].auth[j]);       //用户的权限
		//cin>>fileSystem.iNode[i].auth[j];
	}

	fclose(stdin);
	freopen("CON", "r", stdin);
	freopen("iNodeContext.txt", "r", stdin);
	//一共有128个i结点
	for (int i = 9; i < 128; i++){
		if (!iNode[i]){
			scanf("%d%d%d%d%d", &fileSystem.iNode[i].id, &fileSystem.iNode[i].type, &fileSystem.iNode[i].sfd_id, &fileSystem.iNode[i].filelen, &fileSystem.iNode[i].qcount);
			//cin>>fileSystem.iNode[i].id>>fileSystem.iNode[i].type>>fileSystem.iNode[i].sfd_id>>fileSystem.iNode[i].filelen>>fileSystem.iNode[i].qcount;
			for (int j = 0; j < 8; j++)
				scanf("%d", &fileSystem.iNode[i].auth[j]);
			//cin>>fileSystem.iNode[i].auth[j];
			if (fileSystem.iNode[i].type == 0){
				scanf("%d%d", &fileSystem.iNode[i].diskBlockNum, &fileSystem.iNode[i].diskBlockId);
				//cin>>fileSystem.iNode[i].diskBlockNum;
				//cin>>fileSystem.iNode[i].diskBlockId;
			}
		}
	}

	fclose(stdin);
	freopen("CON", "r", stdin);
}

//初始化磁盘块
void initDiskBlock(){
	//磁盘块初始化

	freopen("diskBlock.txt", "r", stdin);    //diskBlock 中存放的是每个磁盘块大小
	for (int i = 0; i < 512; i++){
		if (!diskBlock[i]){                //如果磁盘块满的话
			scanf("%d", &fileSystem.diskBlock[i].strNum);   //读入磁盘块大小
			//cin>>fileSystem.diskBlock[i].strNum;
			string str;
			for (int j = 0; j < fileSystem.diskBlock[i].strNum; j++){
				cin >> str;				//疑问
				fileSystem.diskBlock[i].file = " " + fileSystem.diskBlock[i].file + " " + str + " ";  //文件内容
			}
		}
	}

	fclose(stdin);
	freopen("CON", "r", stdin);
}

//初始化SFD
void initSFD(){
	//初始化SFD
	freopen("sfdContext.txt", "r", stdin);

	for (int i = 1; i <= 8; i++){		//修改
		string tmps;
		stringstream ss;
		ss << i;
		ss >> tmps;
		SingleSFD singleSFD;
		singleSFD.name = "root" + tmps;
		singleSFD.id = i;
		fileSystem.sfd[0].sfdVec.push_back(singleSFD);   //每个文件目录下的sfd动态数组
	}

	staSFD.push(0);    

	for (int i = 1; i < 512; i++){

		if (!SFDBlock[i]){       //只要SFDBlock不空闲
			scanf("%d", &fileSystem.sfd[i].sfdNum);
			//cin>>fileSystem.sfd[i].sfdNum;
			for (int j = 0; j < fileSystem.sfd[i].sfdNum; j++){
				SingleSFD singleSFD;
				cin >> singleSFD.name;
				scanf("%d", &singleSFD.id);     //文件对应i结点编号
				fileSystem.sfd[i].sfdVec.push_back(singleSFD);
			}
		}
	}

	fclose(stdin);
	freopen("CON", "r", stdin);
}

//初始化
void init(){

	memset(iNode, 0, sizeof(iNode));      //初始化，iNode,diskBlock  SFDblock都初始化为0,先都初始为占据状态
	memset(diskBlock, 0, sizeof(diskBlock));
	memset(SFDBlock, 0, sizeof(SFDBlock));
	initSuperBlock();  //初始化时候才开始把空闲的为1
	initINode();
	initDiskBlock();
	initSFD();
}
