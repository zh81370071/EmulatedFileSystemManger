#include "OS.h"


int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);        //����������ɫ
	return 0;
}

void title()
{
	color(15);						//����ɫ
	gotoxy(28,3);
    printf("N  E  U  �ļ�����ϵͳ \n");	//�������
	color(11); 						//����ɫ
	gotoxy(18,5);
    printf("��    ��");	
	gotoxy(18,6);
    printf("����  ��");
    gotoxy(18,7);
    printf("�� �� ��");							
    gotoxy(18,8); 
    printf("��  ����");					
    gotoxy(18,9);
    printf("��    ��");
    
    color(14); 							//��ɫ
	gotoxy(26,5);
    printf("��������");					
	gotoxy(26,6);
    printf("�� ");					
    gotoxy(26,7);						//  ����
    printf("��������");
    gotoxy(26,8);
	printf("�� ");
	gotoxy(26,9);
    printf("��������");					
	
    color(10); 						//��ɫ
    gotoxy(36,5);					//����
    printf("��    ��");	
	gotoxy(36,6);					//����
    printf("��    ��");				//����
    gotoxy(36,7);
    printf("��    ��");
	 gotoxy(36,8);
    printf("��    ��");
	 gotoxy(36,9);
    printf("��������");

    color(13); 						//��ɫ
	gotoxy(45,5);
    printf("��������");					
	gotoxy(45,6);
    printf("�� ");					
    gotoxy(45,7);						//  ����
    printf("��������");
    gotoxy(45,8);
	printf("�� ");
	gotoxy(45,9);
    printf("��");
	
	
	color(11); 						//����ɫ
	gotoxy(54,5);
    printf("��         ��");	
	gotoxy(54,6);
    printf("����     ����");
    gotoxy(54,7);
    printf("�� ��   �� ��");							
    gotoxy(54,8); 
    printf("��  �� ��  ��");					
    gotoxy(54,9);
    printf("��   ��    ��");
}

void flower()
{
	gotoxy(66,11);   	//ȷ����Ļ��Ҫ�����λ��
	color(12);			//������ɫ
	printf("(_)");  		//�컨�ϱ߻���

	gotoxy(64,12);
	printf("(_)");      //�컨��߻���

	gotoxy(68,12);
	printf("(_)");      //�컨�ұ߻���

	gotoxy(66,13);
	printf("(_)");      //�컨�±߻���

	gotoxy(67,12);      //�컨����
	color(6);
	printf("@");
	
	gotoxy(72,10);
	color(13);
	printf("(_)");      //�ۻ���߻���

	gotoxy(76,10);
	printf("(_)");      //�ۻ��ұ߻���

	gotoxy(74,9);
	printf("(_)");      //�ۻ��ϱ߻���
	
	gotoxy(74,11);
	printf("(_)");      //�ۻ��±߻���
	
	gotoxy(75,10);
	color(6);
	printf("@");        //�ۻ�����
	
	gotoxy(71,12);
	printf("|");      	//���仨֮�������

	gotoxy(72,11);
	printf("/");      	//���仨֮�������

	gotoxy(70,13);
	printf("\\|");     //ע�⡢\Ϊת���ַ�����Ҫ����\��������ǰ����Ҫת��

	gotoxy(70,14);
	printf("`|/");

	gotoxy(70,15);
	printf("\\|");

	gotoxy(71,16);
	printf("| /");

	gotoxy(71,17);
	printf("|");
	
	gotoxy(67,17);
	color(10);
	printf("\\\\\\\\");      //�ݵ�
	gotoxy(73,17);
	printf("//");

	gotoxy(67,18);
	color(2);
	printf("^^^^^^^^");
	
	gotoxy(65,19);			
	color(5);
	printf("������ѧ");
	
	gotoxy(68,20);
	printf("�ܻ�");			//�����ߵ�����
}

//��¼�û���
void login(){
	system("cls");
    title();
	flower(); 
	while (1){
		textcolor(13);
		cout << "\n�������û���(����exit�˳��ļ�ϵͳ)�� ";
		cin >> user;
		if (user == "exit"){
			textcolor(9);
			cout << "\n�˳��ɹ���ллʹ�ã�\n";
			exit(0);
		}
		int res = checkUser(user);
		if (!res){
			textcolor(12);
			cout << "\n�����ڵ��û������������룡\n";
			continue;
		}
		textcolor(10);
		cout << "\n��½�ɹ����س������ļ�ϵͳ" << endl;
		getchar();
		getchar();
		break;
	}

}

//�жϴ�ʱ�û�

int checkUser(string user){
	if (user == "user1")
		return 1;
	else if (user == "user2")
		return 2;
	else if (user == "user3")
		return 3;
	else if (user == "user4")
		return 4;
	else if (user == "user5")
		return 5;
	else if (user == "user6")
		return 6;
	else if (user == "user7")
		return 7;
	else if (user == "user8")
		return 8;
	else
		return 0;
}


//��鵱ǰ�û����ļ��Ķ�дȨ��
int checkFileAuth(string filename){
	int pos = -1;
	for (int i = 0; i < fileSystem.sfd[cur_SFD].sfdVec.size(); i++){
		if (filename == fileSystem.sfd[cur_SFD].sfdVec[i].name){
			pos = i;
			break;
		}
	}
	if (pos == -1)
		return -2;
	int cur_inode = fileSystem.sfd[cur_SFD].sfdVec[pos].id;
	if (fileSystem.iNode[cur_inode].type == 1)        //1��ʾ��ǰi�����Ŀ¼
		return -3;
	int use = checkUser(user) - 1;
	return fileSystem.iNode[cur_inode].auth[use];
}



//��鵱ǰ�û���Ŀ¼�Ķ�дȨ��
int checkDirAuth(string filename){
	int pos = -1;
	for (int i = 0; i < fileSystem.sfd[cur_SFD].sfdVec.size(); i++){   //��鵱ǰĿ¼���Ƿ����
		if (filename == fileSystem.sfd[cur_SFD].sfdVec[i].name){
			pos = i;
			break;
		}
	}
	if (pos != -1)
		return -2;

	int cur_inode = getInodeNum();       //��õ�ǰĿ¼��i����
	int use = checkUser(user);
	if (use == fileSystem.iNode[cur_inode].id)   //����Ƿ���Ȩ��
		return 1;
	return 0;
}

//�ǳ�
void logout(){
	exitSystem();
	user = "";
}

