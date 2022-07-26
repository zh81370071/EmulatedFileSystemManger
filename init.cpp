#include "OS.h"

//��ʼ��������
void initSuperBlock(){
	//��ʼ��������
	freopen("superBlock.txt", "r", stdin);
	scanf("%d%d", &fileSystem.superBlock.i_node, &fileSystem.superBlock.freei_node);
	//cin>>fileSystem.superBlock.i_node>>fileSystem.superBlock.freei_node;
	//scanf("%d%d", &fileSystem.superBlock.i_node, &fileSystem.superBlock.freei_node);
	for (int i = 0; i < fileSystem.superBlock.freei_node; i++){
		int tmp;
		scanf("%d", &tmp);
		iNode[tmp] = 1;      //i���λʾͼ
		fileSystem.superBlock.freeiid.push_back(tmp);
	}
	//cin>>fileSystem.superBlock.sfd>>fileSystem.superBlock.free_SFD;
	scanf("%d%d", &fileSystem.superBlock.sfd, &fileSystem.superBlock.free_SFD);
	for (int i = 0; i < fileSystem.superBlock.free_SFD; i++){
		int tmp;
		scanf("%d", &tmp);
		SFDBlock[tmp] = 1;      //����SFD��Ŀ¼����ʼ��
		fileSystem.superBlock.freeSFD.push_back(tmp);
	}
	//cin>>fileSystem.superBlock.disk>>fileSystem.superBlock.freeDisk;
	scanf("%d%d", &fileSystem.superBlock.disk, &fileSystem.superBlock.freeDisk);   //���д��̿�
	fclose(stdin);
	freopen("CON", "r", stdin);  //�ض�λ��׼���룬����׼�����ɼ��̸ĳ��ļ�����

	freopen("freeBlock.txt", "r", stdin);       //���еĴ��̿�������ӷ�����
	fileSystem.superBlock.freeDiskSta[0] = 1;     //����һ��
	fileSystem.superBlock.freeDiskSta[1] = -1;   //�������ӵ�һ��
	for (int i = 0; i < fileSystem.superBlock.freeDisk; i++){
		int tmp;
		scanf("%d", &tmp);
		diskBlock[tmp] = 1;                               //1��ʾ���У����̿�λʾͼ��ʼ��
		int &pos = fileSystem.superBlock.freeDiskSta[0];  //ÿ�ζ�����λʾͼջ������ջ����Ŀǰ�ÿ��д�ŵĿ��п���
		if (pos < 50)
			fileSystem.superBlock.freeDiskSta[++pos] = tmp;    //���ÿ��п�
		else{   //�����鴦��     //����
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


//��ʼ��i���
void initINode(){
	//��ʼ��ǰ9��i���
	freopen("iNode.txt", "r", stdin);
	for (int i = 0; i <= 8; i++){
		scanf("%d%d%d%d%d", &fileSystem.iNode[i].id, &fileSystem.iNode[i].type, &fileSystem.iNode[i].sfd_id, &fileSystem.iNode[i].filelen, &fileSystem.iNode[i].qcount);
		//cin>>fileSystem.iNode[i].id>>fileSystem.iNode[i].type>>fileSystem.iNode[i].sfd_id>>fileSystem.iNode[i].filelen>>fileSystem.iNode[i].qcount;
		for (int j = 0; j < 8; j++)
			scanf("%d", &fileSystem.iNode[i].auth[j]);       //�û���Ȩ��
		//cin>>fileSystem.iNode[i].auth[j];
	}

	fclose(stdin);
	freopen("CON", "r", stdin);
	freopen("iNodeContext.txt", "r", stdin);
	//һ����128��i���
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

//��ʼ�����̿�
void initDiskBlock(){
	//���̿��ʼ��

	freopen("diskBlock.txt", "r", stdin);    //diskBlock �д�ŵ���ÿ�����̿��С
	for (int i = 0; i < 512; i++){
		if (!diskBlock[i]){                //������̿����Ļ�
			scanf("%d", &fileSystem.diskBlock[i].strNum);   //������̿��С
			//cin>>fileSystem.diskBlock[i].strNum;
			string str;
			for (int j = 0; j < fileSystem.diskBlock[i].strNum; j++){
				cin >> str;				//����
				fileSystem.diskBlock[i].file = " " + fileSystem.diskBlock[i].file + " " + str + " ";  //�ļ�����
			}
		}
	}

	fclose(stdin);
	freopen("CON", "r", stdin);
}

//��ʼ��SFD
void initSFD(){
	//��ʼ��SFD
	freopen("sfdContext.txt", "r", stdin);

	for (int i = 1; i <= 8; i++){		//�޸�
		string tmps;
		stringstream ss;
		ss << i;
		ss >> tmps;
		SingleSFD singleSFD;
		singleSFD.name = "root" + tmps;
		singleSFD.id = i;
		fileSystem.sfd[0].sfdVec.push_back(singleSFD);   //ÿ���ļ�Ŀ¼�µ�sfd��̬����
	}

	staSFD.push(0);    

	for (int i = 1; i < 512; i++){

		if (!SFDBlock[i]){       //ֻҪSFDBlock������
			scanf("%d", &fileSystem.sfd[i].sfdNum);
			//cin>>fileSystem.sfd[i].sfdNum;
			for (int j = 0; j < fileSystem.sfd[i].sfdNum; j++){
				SingleSFD singleSFD;
				cin >> singleSFD.name;
				scanf("%d", &singleSFD.id);     //�ļ���Ӧi�����
				fileSystem.sfd[i].sfdVec.push_back(singleSFD);
			}
		}
	}

	fclose(stdin);
	freopen("CON", "r", stdin);
}

//��ʼ��
void init(){

	memset(iNode, 0, sizeof(iNode));      //��ʼ����iNode,diskBlock  SFDblock����ʼ��Ϊ0,�ȶ���ʼΪռ��״̬
	memset(diskBlock, 0, sizeof(diskBlock));
	memset(SFDBlock, 0, sizeof(SFDBlock));
	initSuperBlock();  //��ʼ��ʱ��ſ�ʼ�ѿ��е�Ϊ1
	initINode();
	initDiskBlock();
	initSFD();
}
