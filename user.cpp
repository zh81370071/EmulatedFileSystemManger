#include "OS.h"


int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);        //更改文字颜色
	return 0;
}

void title()
{
	color(15);						//亮白色
	gotoxy(28,3);
    printf("N  E  U  文件管理系统 \n");	//输出标题
	color(11); 						//亮蓝色
	gotoxy(18,5);
    printf("■    ■");	
	gotoxy(18,6);
    printf("■■  ■");
    gotoxy(18,7);
    printf("■ ■ ■");							
    gotoxy(18,8); 
    printf("■  ■■");					
    gotoxy(18,9);
    printf("■    ■");
    
    color(14); 							//黄色
	gotoxy(26,5);
    printf("■■■■");					
	gotoxy(26,6);
    printf("■ ");					
    gotoxy(26,7);						//  ■■
    printf("■■■■");
    gotoxy(26,8);
	printf("■ ");
	gotoxy(26,9);
    printf("■■■■");					
	
    color(10); 						//绿色
    gotoxy(36,5);					//■■
    printf("■    ■");	
	gotoxy(36,6);					//■■
    printf("■    ■");				//■■
    gotoxy(36,7);
    printf("■    ■");
	 gotoxy(36,8);
    printf("■    ■");
	 gotoxy(36,9);
    printf("■■■■");

    color(13); 						//粉色
	gotoxy(45,5);
    printf("■■■■");					
	gotoxy(45,6);
    printf("■ ");					
    gotoxy(45,7);						//  ■■
    printf("■■■■");
    gotoxy(45,8);
	printf("■ ");
	gotoxy(45,9);
    printf("■");
	
	
	color(11); 						//亮蓝色
	gotoxy(54,5);
    printf("■         ■");	
	gotoxy(54,6);
    printf("■■     ■■");
    gotoxy(54,7);
    printf("■ ■   ■ ■");							
    gotoxy(54,8); 
    printf("■  ■ ■  ■");					
    gotoxy(54,9);
    printf("■   ■    ■");
}

void flower()
{
	gotoxy(66,11);   	//确定屏幕上要输出的位置
	color(12);			//设置颜色
	printf("(_)");  		//红花上边花瓣

	gotoxy(64,12);
	printf("(_)");      //红花左边花瓣

	gotoxy(68,12);
	printf("(_)");      //红花右边花瓣

	gotoxy(66,13);
	printf("(_)");      //红花下边花瓣

	gotoxy(67,12);      //红花花蕊
	color(6);
	printf("@");
	
	gotoxy(72,10);
	color(13);
	printf("(_)");      //粉花左边花瓣

	gotoxy(76,10);
	printf("(_)");      //粉花右边花瓣

	gotoxy(74,9);
	printf("(_)");      //粉花上边花瓣
	
	gotoxy(74,11);
	printf("(_)");      //粉花下边花瓣
	
	gotoxy(75,10);
	color(6);
	printf("@");        //粉花花蕊
	
	gotoxy(71,12);
	printf("|");      	//两朵花之间的连接

	gotoxy(72,11);
	printf("/");      	//两朵花之间的连接

	gotoxy(70,13);
	printf("\\|");     //注意、\为转义字符。想要输入\，必须在前面需要转义

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
	printf("\\\\\\\\");      //草地
	gotoxy(73,17);
	printf("//");

	gotoxy(67,18);
	color(2);
	printf("^^^^^^^^");
	
	gotoxy(65,19);			
	color(5);
	printf("东北大学");
	
	gotoxy(68,20);
	printf("周辉");			//开发者的名字
}

//登录用户名
void login(){
	system("cls");
    title();
	flower(); 
	while (1){
		textcolor(13);
		cout << "\n请输入用户名(输入exit退出文件系统)： ";
		cin >> user;
		if (user == "exit"){
			textcolor(9);
			cout << "\n退出成功，谢谢使用！\n";
			exit(0);
		}
		int res = checkUser(user);
		if (!res){
			textcolor(12);
			cout << "\n不存在的用户，请重新输入！\n";
			continue;
		}
		textcolor(10);
		cout << "\n登陆成功，回车进入文件系统" << endl;
		getchar();
		getchar();
		break;
	}

}

//判断此时用户

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


//检查当前用户对文件的读写权限
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
	if (fileSystem.iNode[cur_inode].type == 1)        //1表示当前i结点是目录
		return -3;
	int use = checkUser(user) - 1;
	return fileSystem.iNode[cur_inode].auth[use];
}



//检查当前用户对目录的读写权限
int checkDirAuth(string filename){
	int pos = -1;
	for (int i = 0; i < fileSystem.sfd[cur_SFD].sfdVec.size(); i++){   //检查当前目录下是否存在
		if (filename == fileSystem.sfd[cur_SFD].sfdVec[i].name){
			pos = i;
			break;
		}
	}
	if (pos != -1)
		return -2;

	int cur_inode = getInodeNum();       //获得当前目录的i结点号
	int use = checkUser(user);
	if (use == fileSystem.iNode[cur_inode].id)   //检查是否有权限
		return 1;
	return 0;
}

//登出
void logout(){
	exitSystem();
	user = "";
}

