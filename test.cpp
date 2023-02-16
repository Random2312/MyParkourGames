#include "test.h"
#include "game.h"


using namespace std;//声明命名空间


/*
	日志


	1.创建项目
	2.导入素材
	3.创建游戏界面
			a.实际开发流程
			b.可以先从     从用户界面入手
			c.选择图形库或其它游戏引擎（本项目基于easyX）
		1)创建游戏窗口
		2)设计游戏背景
			原理
				a.三重背景以不同速度同时进行移动
				b.循环滚动背景实现
		3)实现游戏背景
			a.加载背景资源
			b.渲染	实现打印图片效果
			遇到问题：背景透明的png格式出现黑色-----------------问题
	4.实现角色(帧动画)
		1)实现玩家奔跑
	5.实现玩家跳跃
	6.优化帧等待
	7.实现障碍物随机出现和显示
		a.创建障碍物结构体数据类型
		b.使用结构体后重新初始化
		c.封装后多个障碍物的显示
	8.实现玩家下蹲
	9.实现柱子障碍物
	10.障碍物碰撞检测！！！！！！！！！！！！！！！！！！！！
		思路：将人物和障碍物假定为两个方块或其它形状，找到各个点的坐标，
		方块就是左上角和右下角两点坐标，去判断有没有和另一个方块碰到一起，
		如果两个坐标相交，可以断定两个障碍物碰撞
	11.使用接口制作血条
	12.背景音乐和游戏结束
	13.优化障碍物死局
	14.反馈机制     分数统计
	15.显示分数
	16.判断胜利    
		加音效和图片
	17.软件打包

	结论：
		先写函数再定义 实际开发中用到什么函数就写什么函数，将一些变量设置为宏可能会更方便

*/

/**********************************************/
IMAGE imgBgs[3];//---------图片变量定义  三个背景   (大型项目尽量少定义全局变量)

int bg_x[3];//---------背景X轴

int bgSpeed[3] = { 1,2,4 };//---------------------背景移动速度

IMAGE imgHeros[12];//-----------------------角色图像类型数组

int heroX;//----------------角色x轴
int heroY;//------------角色y轴

int heroIndex; //------------玩家奔跑时的图片帧序号

bool heroJump; //----------玩家跳跃键  

int jumpHeightMax;//---------------跳跃最大高度

int heroJump0ff;//-----------跳跃偏移量

int update;//--------表示是否需要马上刷新画面

//玩家下蹲变量
IMAGE imgHeroDown[2];

//玩家下蹲键  是否处于下蹲状态
bool hero_down;

//IMAGE imgTortoise;//--------------------------------------------乌龟怪图像
////结构体优化？？？？？
//int torToise_X;//-------------------------------------------乌龟X轴
//int torToise_Y;//-------------------------------------------乌龟X轴
//bool torToiseExist;//--------------------------------------------当前窗口是否有乌龟（保证只有一个）


//玩家血量
int heroBlood;


//当前分数
int score;


//分数显示图片
IMAGE imgSz[10];

/**********封装**************************************/

//障碍物枚举类型
typedef enum
{
	TORTOISE,//乌龟   0

	LION,   //狮子   1

	PILLAR1,//四种柱子障碍物
	PILLAR2,
	PILLAR3,
	PILLAR4,


	OBSTACLE_TYPE_COUNT  //=6  障碍物数量   也就是（最后一个枚举量      因为枚举类型会自动变化）  2

}obstacle_type;



vector<vector<IMAGE>>  obstacleImgs;		//存放所有障碍物的各个图片  



//封装障碍物
typedef struct obstacle
{
	//obstacle_typ type;  
	int type;//------------------障碍物类型

	int imgIndex; //------------------当前显示的图片的序号  索引 下标
	
	int x;//------------------障碍物x坐标
	int y;//------------------障碍物y坐标

	int speed;//------------------速度
	int power;//------------------伤害

	bool exist;//------------------障碍物是否存在
	bool collide;//----------------是否已经撞到障碍物
	bool pass;//-------------是否越过障碍物

}obstacle_t;//障碍物



//特殊的二维数组   每个成员都是int   //容器  长度可变数组   存放整型数据类型
//相当于C语言表示的  IMAGE obstacleImgs[][]   行列可变
obstacle_t obstacles[OBSTACLE_COUNT]; //预备池子  定义障碍物  池子  备用  


//上次产生障碍物的序号
int lastObsIndex;






/***********************************************************/











//游戏初始化
void init()
{
	////创建窗口  显示控制台
	//initgraph(WIN_WIDTH, WIN_HEIGHT, EW_SHOWCONSOLE);

	//创建窗口  不显示控制台
	initgraph(WIN_WIDTH, WIN_HEIGHT);

	//加载背景资源
	char name[64];//文件名接收者

	for (int i = 0; i < 3; i++) {
		//格式，"res/bg001,png"   "res/bg002,png"   "res/bg003,png"
		//参数功能：将格式化数据写入某个字符串中
		//	参数1：接收的字符串 
		//	参数2：要传的字符串
		//	参数3：对第二个参数的补充
		sprintf_s(name, "res/bg%03d.png", i + 1);

		//装载图标，光标，或位图
		//参数1 ： 背景加载位置  
		//参数2 ： 文件名
		loadimage(&imgBgs[i], name);//这个函数报错更改字符集--项目--属性--高级--字符集改成多字节字符集

		bg_x[i] = 0;//背景x轴开始都为0

	}


	//加载角色
	//加载玩家角色（hero）奔跑图片到name数组中
	for (int i = 0; i < 12; i++)
	{
		//文件名"res/hero1.png"...
		sprintf_s(name, "res/hero%d.png", i + 1);//不会清空name中的字符串

		//装载位图（图片文件位置name到hero（角色）数组中）
		loadimage(&imgHeros[i], name);
	}



	//设置玩家初始位置(窗口宽度一半 - 角色宽度一半)
	heroX = 100;//WIN_WIDTH * 0.5 - imgHeros[0].getwidth() * 0.5;
	//Y = 脚放一点在草丛中（草的宽度） - 身高
	heroY = 440 - imgHeros[0].getheight();//此数值初始化前imgHeros必须初始化完毕（因为要计算这个图片的高度）！

	//玩家满血
	heroBlood = 100;

	heroIndex = 0;//玩家奔跑图片下标

	heroJump = false;//玩家跳跃开关

	//跳跃最大高度  (最开始高度-本身高度？？？？)
	jumpHeightMax = 440 - imgHeros[0].getheight() - 120;

	//初始化跳跃偏移量
	heroJump0ff = -6;






	//加载乌龟
	IMAGE imgTort;

	//加载乌龟
	loadimage(&imgTort, "res/t1.png");

	vector<IMAGE>imgTortArray;  //定义乌龟数组

	imgTortArray.push_back(imgTort); //将图片添加到数组中    push_back在尾部追加一个成员
	
	obstacleImgs.push_back(imgTortArray);//添加乌龟数组







	//加载狮子
	IMAGE imgLion;//定义狮子图片
	
	vector<IMAGE>imgLionArray;//狮子所有图片数组   一维

	//添加图片到数组
	for (int i = 0; i < 6; i++)
	{
		sprintf_s(name, "res/p%d.png", i + 1);//  写入文件位置

		//加载图像到狮子数组中
		loadimage(&imgLion, name);

		//在狮子数组尾部追加狮子图片
		imgLionArray.push_back(imgLion);
	}

	obstacleImgs.push_back(imgLionArray);//尾部追加狮子数组到容器中？？？？








	

	











	//初始化障碍物池子  全部初始化为不能上场   
	for (int i = 0; i < OBSTACLE_COUNT; i++)
	{
		obstacles[i].exist = false;
	}














	//加载玩家下蹲素材
	for (int i = 0; i < 2; i++)
	{
		sprintf_s(name, "res/d%d.png", i + 1);//  写入文件位置

		loadimage(&imgHeroDown[i], name);
	}


	//初始化下蹲键
	hero_down = false;










	//加载四个柱子

	IMAGE imgH;

	for (int i = 0; i < 4; i++)
	{

		//定义障碍物数组           防止数组过大  在循环中初始化   保证每次循环他都是空的
		vector<IMAGE> imgHookArray;

		//创建文件名
		sprintf_s(name, sizeof(name),"res/h%d.png", i + 1);

		//加载同时进行缩放
		loadimage(&imgH, name, 63, 260, true);

		//添加到数组中  添加到最后
		imgHookArray.push_back(imgH);

		//添加数组到障碍物池子中  尾部追加？
		obstacleImgs.push_back(imgHookArray);

		//
	}







	//预加载音效    解决第一次碰撞不出声				偷的接口
	preLoadSound("res/hit.mp3");







	//开启背景音乐
	mciSendString("play res/bg.mp3 repeat", 0, 0, 0);


	//上次障碍物为  空   -1
	lastObsIndex = -1;

	//分数初始化
	score = 0;

	//加载数组图片
	for (int i = 0; i < 10; i++)
	{
		//生成文件名
		sprintf_s(name, "res/sz/%d.png",i);

		//加载分数
		loadimage(&imgSz[i],name);
	}
	
}











//创建障碍物     在池子里找一个可用的障碍物
void createObstacle()
{
	int i;

	for (i = 0; i < OBSTACLE_COUNT; i++)
	{
		//找到障碍物
		if (obstacles[i].exist == false)
		{
			break;
		}
	}

	if (i >= OBSTACLE_COUNT)	//根据i的值判断   找没找到障碍物
	{
		return;//没找到 障碍物 返回
	}


	//找到后初始化第i个障碍物

	//障碍物存在
	obstacles[i].exist = true;

	//没有碰到障碍物
	obstacles[i].collide = false;

	//没有越过障碍物
	obstacles[i].pass = false;


	//将（图片）索引置0   第一个图片
	obstacles[i].imgIndex = 0;

	//障碍物类型  ，对障碍物种类（数量）取余						
	//obstacles[i].type = (obstacle_type)(rand() % OBSTACLE_COUNT);//(obstacle_type) (rand() % 2);//OBSTACLE_COUNT
	obstacles[i].type = (obstacle_type)(rand() % 3);   //更改后防止柱子出现次数过多



	//判断是不是死局
	//lastObsIndex    上一次障碍物的序号 
	// 
	// （下标大于等于0   防止下标越界     &&
	//	障碍物类型是柱子  &&
	//  这次出现的障碍物是狮子&&
	//  上一次障碍物位置在屏幕中无法躲开的位置）
	if (lastObsIndex >= 0 &&
		obstacles[lastObsIndex].type >= PILLAR1 &&
		obstacles[lastObsIndex].type <= PILLAR4 &&
		obstacles[i].type == LION &&
		obstacles[lastObsIndex].x > (WIN_WIDTH - 500))
	{
		//将障碍物 重新 改成乌龟
		obstacles[i].type = TORTOISE;
	}

	//上一次障碍物			44下标更新成最新的值    再从更新后的障碍物开始判断下一个障碍物是不是无法躲开
	lastObsIndex = i;



	if (obstacles[i].type == PILLAR1) 
	{
		obstacles[i].type +=  rand() % 4;//在柱子类型中挑选障碍物    0..3范围
	}

	//x坐标   游戏窗口宽    最右边
	obstacles[i].x = WIN_WIDTH;//400; //

	//y坐标   地面高度  -  障碍物身高
	obstacles[i].y = 440 - obstacleImgs[obstacles[i].type][0].getheight();//340; //440;

	//障碍物速度

	//如果是乌龟
	if (obstacles[i].type == TORTOISE)
	{
		obstacles[i].speed = 0;   //速度
		obstacles[i].power = 5;   //伤害				可修改！！！！！！！！！！！！！！！！
	}
	else if (obstacles[i].type == LION)//如果是狮子
	{
		obstacles[i].speed = 4;  //速度
		obstacles[i].power = 20;	//伤害				可修改！！！！！！！！！！！！！！！！
	}
	else if (obstacles[i].type >= PILLAR1 && obstacles[i].type <= PILLAR4)//如果是柱子(因为有四个柱子，所以进行精准判断)
	{
		obstacles[i].speed = 0;  //速度
		obstacles[i].power = 20;	//伤害				可修改！！！！！！！！！！！！！！！！

		obstacles[i].y = 100;  //////////////////////////////////////////////柱子是在最顶部出现的 要改变y坐标
	}





}












//角色 跳跃键控制  判断
void hero_jump()
{
	heroJump = true;
	//打开刷新界面   直接刷新
	update = true;
}



//玩家下蹲键 
void heroDown()
{

	hero_down = true;
	//打开刷新界面   直接刷新
	update = true;

	//下蹲了  从0张开始显示下蹲图片
	heroIndex = 0;
}















//处理用户按键的输入
void keyEvent() {

	//判断有没有按键按下去
	if (_kbhit()) //如果有按键按下  此函数返回 TRUE
	{
		char key;
		key = _getch();		//此函数不需要按回车 (保证游戏不会停止

		if (key == ' ') //按键是空格实现跳跃
		{	

			hero_jump();

		}
		else if (key == 'x')
		{

			heroDown();

		}
	}
}








//碰撞检测      思路判断两个矩形（将角色和障碍假做一个矩形）    区域是否相交
void checkHit()
{
	//
	for (int i = 0; i < OBSTACLE_COUNT; i++)
	{
		//检查是否存在   并且障碍物没被碰到   
		if(obstacles[i].exist&&obstacles[i].collide==false)
		{
			//计算角色两点坐标
			//定义角色  矩形  左上和右下坐标变量
			int a1x, a1y, a2x, a2y;

			int off = 30;											 //偏移量   防止碰到障碍物一点就执行

			//
			if (!hero_down)   //非下蹲    （就是跑和跳跃）
			{
				a1x = heroX + off;  //左上x
				a1y = heroY + off;  //左上y    

				a2x = heroX + imgHeros[heroIndex].getwidth() - off;//右下x
				a2y = heroY + imgHeros[heroIndex].getheight();//右下y

			}
			else//下蹲状态
			{
				//玩家左上角坐标
				a1x = heroX + off;
				a1y = 440 - imgHeroDown[heroIndex].getheight();			//懒得调试，改成固定值了	有bug请看一下这里！  	//      //地面-玩家下蹲身高


				//右下角
				a2x = heroX + imgHeroDown[heroIndex].getwidth() - off;  //
			 	a2y = 360+80;//360;   //地面///////////////////////////////////////////////////////////////////////

			}








			//计算障碍物两点坐标
			//当前障碍物图片
			IMAGE img = obstacleImgs[obstacles[i].type][obstacles[i].imgIndex];

			int b1x = obstacles[i].x + off;  //左上
			int	b1y = obstacles[i].y + off;  

			int	b2x = obstacles[i].x+ img.getwidth() - off;//右下
			int	b2y = obstacles[i].y + img.getheight() - 10;  //-10  防止偏移量过大		y位置等于草地///////////////////////////这里碰撞发生问题//////////////////////////////////////////////////////////发现问题！！！！！他的图片和我的图片高度不一样！坐标不能照抄  要自己算！

			
			//判断有没有相交  （碰撞）
			if (rectIntersect(a1x, a1y, a2x, a2y, b1x, b1y, b2x, b2y))
			{
				heroBlood -= obstacles[i].power;

				printf("血量剩余%d\n", heroBlood);

				//播放声音
				playSound("res/hit.mp3");

				//碰到了障碍物  
				obstacles[i].collide = true;

				

			}


		}




	}

}










void fly()
{
	for (int i = 0; i < 3; i++)
	{
		//窗口
		bg_x[i] -= bgSpeed[i];
		//实现背景重复播放
		if (bg_x[i] < -2000)
		{
			bg_x[i] = 0;
		}

	}


	//实现跳跃,改变玩家Y坐标   
	/*(跳跃思路)：
	* 上升，当到最大高度时下降，当到最低高度时上升
	*/
	if (heroJump)//如果跳跃开关为真  （玩家按跳跃）  （此时角色Y位置处于 + -4状态（上升））
	{
		if (heroY < jumpHeightMax)//如果到最大高度      
		{
			heroJump0ff = 6;//将偏移量变正  （此时角色会向下移动）
		}

		heroY += heroJump0ff;//每次跳跃 角色Y轴位置 + 偏移量  （Y轴位置会随偏移量改变而改变）

		if (heroY > 440 - imgHeros[0].getheight())//如果落地 （Y坐标大于英雄初始高）
		{
			heroJump = false;//跳跃结束
			heroJump0ff = -6;//偏移量改成初始状态 （复位）(向上移动)
		}

	}
	else if(hero_down)			//实现下蹲		//不跳跃的时候，判断有没有下蹲
	{
		//连续调用几次 更新下一张下蹲图片   计数
		static int count = 0;

		int downDelay[2] = { 8,40 };		//下蹲两张图片的播放时长

		count++;

		if (count >= downDelay[heroIndex])		//调用多少次  才更新下一帧图片   帧数延迟  防止下蹲画面过快
		{
			count = 0;

			heroIndex++;

			//判断有没有结束下蹲动作
			if (heroIndex >= 2)
			{
				heroIndex = 0;	//复位  开始播放奔跑图片       为奔跑下标

				hero_down = false;
			}
			//heroIndex = (heroIndex + 1) % 2;

		}
	}
	else                                //最后没跳跃也没下蹲     英雄图片帧动
	{
		//英雄图片帧变化  保证下标在0-12（张图片）范围内，防止下标越界，每次+1后对12取余
		heroIndex = (heroIndex + 1) % 12;
	}





	










	//创建障碍物
	//每一帧计数    statci  静态  保证 变量不会销毁   下次调用时值不会变
	static int frameCount = 0;

	//乌龟出现频率
	static int enemyFre = 50;

	//计数器++
	frameCount++;

	if (frameCount > enemyFre)
	{
		frameCount = 0;//将秒数清零
		   
		//torToiseFre = 200 + rand() % 301;//更改乌龟出现频率   每200-500出现一次 （  rand%301   0-300）

		enemyFre = 50 + rand() % 50;//每次更改乌龟出现频率    50.....99

		//创建障碍物函数
		createObstacle();

		//create0bstacle();//创建障碍物

		//if (!torToiseExist)//当前界面没有乌龟
		//{
		//	//将键设置为有乌龟
		//	torToiseExist = true;

		//	//乌龟x轴
		//	torToise_X = WIN_WIDTH;//位置等于窗口宽度  在最右侧出现
		//}
	}

	//乌龟移动  速度   是地面移动速度   每次 -去 地面速度变量
	//	torToise_X -= bgSpeed[2];
	//if (torToise_X < -imgTortoise.getwidth())  //如果X位置小于负的乌龟图像宽   （猜测：乌龟到最左边时x轴会停住，一旦小于乌龟的宽，就消失）
	//{
	//	torToiseExist = false;//更新键
	//}



	//更新障碍物坐标
	for (int i = 0; i < OBSTACLE_COUNT; i++)
	{
		//障碍物存在
		if (obstacles[i].exist)
		{
			//更改坐标  移动   -= 速度 + 草坪速度
			obstacles[i].x -= obstacles[i].speed + bgSpeed[2];

			//当小于负的窗口宽度   （跑出图片外）
			if (obstacles[i].x < -obstacleImgs[obstacles[i].type][0].getwidth() * 2)
			{
				obstacles[i].exist = false;//障碍物消失
			}
			//根据障碍物类型
			int len = obstacleImgs[obstacles[i].type].size();
			obstacles[i].imgIndex = (obstacles[i].imgIndex + 1) % len;

		}
	}







	//玩家和障碍物的   碰撞检测  处理 
	checkHit();
}











//渲染游戏背景
void update_background()	
{
	
	//显示游戏背景图片
	putimagePNG2(bg_x[0], 0, &imgBgs[0]);
	putimagePNG2(bg_x[1], 65, &imgBgs[1]);
	putimagePNG2(bg_x[2], 360, &imgBgs[2]);
}





//渲染障碍物
void updateEnemy()
{

	//通过池子大小判断循环大小     （通过结构体渲染）
	for (int i = 0; i < OBSTACLE_COUNT; i++)
	{
		if (obstacles[i].exist)//当障碍物存在进行渲染
		{
			putimagePNG2(obstacles[i].x,   obstacles[i].y,   WIN_WIDTH,
				&obstacleImgs[obstacles[i].type][obstacles[i].imgIndex]);
			
		}
	}

}



//角色下蹲
void updateHero()
{
	//如果没下蹲   继续输出角色奔跑图片
	if (!hero_down)
	{
		putimagePNG2(heroX, heroY, &imgHeros[heroIndex]);
	}
	else
	{
		//地面高度(脚的高度)  -  当前要渲染的下蹲图片高度
		int y = 440 - imgHeroDown[heroIndex].getheight();

		//通过更改heroindex下标来实现角色下蹲图片播放  在fly中
		putimagePNG2(heroX, y, &imgHeroDown[heroIndex]);
	}
}





//绘制血条
void updateBloodBar()
{
	//绘制血条函数
	drawBloodBar(10, 10, 200, 10, 2,
				BLUE, DARKGRAY, RED, heroBlood / 100.0);
}







//检查游戏是否结束
void checkOver()
{

	//血掉光！    结束
	if (heroBlood <= 0)
	{
		//第一个参数是0   直接加载窗口
		loadimage(0,"res/over.png");

		//强制刷新      显示缓冲
		FlushBatchDraw();

		//关闭背景音乐
		mciSendString("stop res/bg.mp3", 0, 0, 0);

		system("pause");




		//暂停之后，继续玩，充钱或直接复活       继续开始初始化游戏数据
		heroBlood = 100;//血加满

		score = 0;//分数清零

		//开启背景music
		mciSendString("play res/bg.mp3 repeat",0,0,0);
	}

}









//检查分数
void checkScore()
{
	for (int i = 0; i < OBSTACLE_COUNT; i++)
	{
		if (obstacles[i].exist &&
			obstacles[i].x+obstacleImgs[obstacles[i].type][0].getwidth()<heroX &&
			obstacles[i].pass==false &&
			obstacles[i].collide==false
			)
		{
			score++;
			printf("分数%d\n",score);

			//防止重复计分
			obstacles[i].pass = true;
		}
	}
}






//更新分数*******************************难点？***********************************************************************************************************
void updateScore()
{
	//50  =>  "50"
	char str[8];

	//将文件名写入数组
	sprintf_s(str, "%d", score);

	int x = 20;
	int y = 25;

	for (int i = 0; str[i]; i++)
	{
		int sz = str[i] - '0';


		putimagePNG(x, y, &imgSz[sz]);

		//图片本身宽度+偏移量
		x += imgSz[sz].getwidth() + 5;
	}

}











//判断游戏胜利
void checkWin()
{
	if (score >= WIN_SCORE)
	{

		//手动刷新        解决游戏结束分数不变问题
		FlushBatchDraw();


		//放曲
		mciSendString("play res/win.mp3", 0, 0, 0);

		Sleep(2000);

		//加载图片到窗口
		loadimage(0, "res/win.jpg");

		//刷新画面
		FlushBatchDraw();

		//停音乐
		mciSendString("stop res/bg.mp3", 0, 0, 0);
		system("pause");

		heroBlood = 100;
		score = 0;
		mciSendString("play res/bg.mp3 repeat",0,0,0);



	}
}
















void test()
{
//初始化
	init();

	//显示初始化
	////音乐关
	//mciSendString("stop res/bg.mp3", 0, 0, 0);
	loadimage(0, "res/over.png");
	system("pause");


	

	//刷新计时 帧等待时间  （每次循环计时，时间到时刷新界面）
	int timer = 0;

	while (1)
	{
		//跳跃按键检测
		keyEvent();

		//此函数返回距离上次调用它相隔多少毫秒
		timer += getDelay();

		//大于30毫秒是刷新界面   (使用这个方法好处是即使没到30毫秒，按键也会生效)
		if (timer > 30)
		{
			//计数器清零
			timer = 0;
			//打开刷新开关
			update = true;
		}

		if (update)  //判断是否需要马上刷新
		{

			//刷新后开关关闭
			update = false;

			//双缓冲开始
			BeginBatchDraw();

			//渲染背景 
			update_background();

			//渲染角色  （输出角色奔跑每一张图片）
			//putimagePNG2(heroX, heroY, &imgHeros[heroIndex]);
			updateHero();

			//渲染障碍物
			updateEnemy();

			//更新血条
			updateBloodBar();

			//更新分数
			updateScore();

			//判断游戏是否胜利
			checkWin();

			//双缓冲结束   全部 帧率 刷新
			EndBatchDraw();


			//检查游戏是否结束
			checkOver();

			//检查得分
			checkScore();

			


			//实现  移动  (数据函数)
			fly();



		}
	}
}