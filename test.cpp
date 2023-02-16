#include "test.h"
#include "game.h"


using namespace std;//���������ռ�


/*
	��־


	1.������Ŀ
	2.�����ز�
	3.������Ϸ����
			a.ʵ�ʿ�������
			b.�����ȴ�     ���û���������
			c.ѡ��ͼ�ο��������Ϸ���棨����Ŀ����easyX��
		1)������Ϸ����
		2)�����Ϸ����
			ԭ��
				a.���ر����Բ�ͬ�ٶ�ͬʱ�����ƶ�
				b.ѭ����������ʵ��
		3)ʵ����Ϸ����
			a.���ر�����Դ
			b.��Ⱦ	ʵ�ִ�ӡͼƬЧ��
			�������⣺����͸����png��ʽ���ֺ�ɫ-----------------����
	4.ʵ�ֽ�ɫ(֡����)
		1)ʵ����ұ���
	5.ʵ�������Ծ
	6.�Ż�֡�ȴ�
	7.ʵ���ϰ���������ֺ���ʾ
		a.�����ϰ���ṹ����������
		b.ʹ�ýṹ������³�ʼ��
		c.��װ�����ϰ������ʾ
	8.ʵ������¶�
	9.ʵ�������ϰ���
	10.�ϰ�����ײ��⣡��������������������������������������
		˼·����������ϰ���ٶ�Ϊ���������������״���ҵ�����������꣬
		����������ϽǺ����½��������꣬ȥ�ж���û�к���һ����������һ��
		������������ཻ�����Զ϶������ϰ�����ײ
	11.ʹ�ýӿ�����Ѫ��
	12.�������ֺ���Ϸ����
	13.�Ż��ϰ�������
	14.��������     ����ͳ��
	15.��ʾ����
	16.�ж�ʤ��    
		����Ч��ͼƬ
	17.������

	���ۣ�
		��д�����ٶ��� ʵ�ʿ������õ�ʲô������дʲô��������һЩ��������Ϊ����ܻ������

*/

/**********************************************/
IMAGE imgBgs[3];//---------ͼƬ��������  ��������   (������Ŀ�����ٶ���ȫ�ֱ���)

int bg_x[3];//---------����X��

int bgSpeed[3] = { 1,2,4 };//---------------------�����ƶ��ٶ�

IMAGE imgHeros[12];//-----------------------��ɫͼ����������

int heroX;//----------------��ɫx��
int heroY;//------------��ɫy��

int heroIndex; //------------��ұ���ʱ��ͼƬ֡���

bool heroJump; //----------�����Ծ��  

int jumpHeightMax;//---------------��Ծ���߶�

int heroJump0ff;//-----------��Ծƫ����

int update;//--------��ʾ�Ƿ���Ҫ����ˢ�»���

//����¶ױ���
IMAGE imgHeroDown[2];

//����¶׼�  �Ƿ����¶�״̬
bool hero_down;

//IMAGE imgTortoise;//--------------------------------------------�ڹ��ͼ��
////�ṹ���Ż�����������
//int torToise_X;//-------------------------------------------�ڹ�X��
//int torToise_Y;//-------------------------------------------�ڹ�X��
//bool torToiseExist;//--------------------------------------------��ǰ�����Ƿ����ڹ꣨��ֻ֤��һ����


//���Ѫ��
int heroBlood;


//��ǰ����
int score;


//������ʾͼƬ
IMAGE imgSz[10];

/**********��װ**************************************/

//�ϰ���ö������
typedef enum
{
	TORTOISE,//�ڹ�   0

	LION,   //ʨ��   1

	PILLAR1,//���������ϰ���
	PILLAR2,
	PILLAR3,
	PILLAR4,


	OBSTACLE_TYPE_COUNT  //=6  �ϰ�������   Ҳ���ǣ����һ��ö����      ��Ϊö�����ͻ��Զ��仯��  2

}obstacle_type;



vector<vector<IMAGE>>  obstacleImgs;		//��������ϰ���ĸ���ͼƬ  



//��װ�ϰ���
typedef struct obstacle
{
	//obstacle_typ type;  
	int type;//------------------�ϰ�������

	int imgIndex; //------------------��ǰ��ʾ��ͼƬ�����  ���� �±�
	
	int x;//------------------�ϰ���x����
	int y;//------------------�ϰ���y����

	int speed;//------------------�ٶ�
	int power;//------------------�˺�

	bool exist;//------------------�ϰ����Ƿ����
	bool collide;//----------------�Ƿ��Ѿ�ײ���ϰ���
	bool pass;//-------------�Ƿ�Խ���ϰ���

}obstacle_t;//�ϰ���



//����Ķ�ά����   ÿ����Ա����int   //����  ���ȿɱ�����   ���������������
//�൱��C���Ա�ʾ��  IMAGE obstacleImgs[][]   ���пɱ�
obstacle_t obstacles[OBSTACLE_COUNT]; //Ԥ������  �����ϰ���  ����  ����  


//�ϴβ����ϰ�������
int lastObsIndex;






/***********************************************************/











//��Ϸ��ʼ��
void init()
{
	////��������  ��ʾ����̨
	//initgraph(WIN_WIDTH, WIN_HEIGHT, EW_SHOWCONSOLE);

	//��������  ����ʾ����̨
	initgraph(WIN_WIDTH, WIN_HEIGHT);

	//���ر�����Դ
	char name[64];//�ļ���������

	for (int i = 0; i < 3; i++) {
		//��ʽ��"res/bg001,png"   "res/bg002,png"   "res/bg003,png"
		//�������ܣ�����ʽ������д��ĳ���ַ�����
		//	����1�����յ��ַ��� 
		//	����2��Ҫ�����ַ���
		//	����3���Եڶ��������Ĳ���
		sprintf_s(name, "res/bg%03d.png", i + 1);

		//װ��ͼ�꣬��꣬��λͼ
		//����1 �� ��������λ��  
		//����2 �� �ļ���
		loadimage(&imgBgs[i], name);//���������������ַ���--��Ŀ--����--�߼�--�ַ����ĳɶ��ֽ��ַ���

		bg_x[i] = 0;//����x�Ὺʼ��Ϊ0

	}


	//���ؽ�ɫ
	//������ҽ�ɫ��hero������ͼƬ��name������
	for (int i = 0; i < 12; i++)
	{
		//�ļ���"res/hero1.png"...
		sprintf_s(name, "res/hero%d.png", i + 1);//�������name�е��ַ���

		//װ��λͼ��ͼƬ�ļ�λ��name��hero����ɫ�������У�
		loadimage(&imgHeros[i], name);
	}



	//������ҳ�ʼλ��(���ڿ��һ�� - ��ɫ���һ��)
	heroX = 100;//WIN_WIDTH * 0.5 - imgHeros[0].getwidth() * 0.5;
	//Y = �ŷ�һ���ڲݴ��У��ݵĿ�ȣ� - ���
	heroY = 440 - imgHeros[0].getheight();//����ֵ��ʼ��ǰimgHeros�����ʼ����ϣ���ΪҪ�������ͼƬ�ĸ߶ȣ���

	//�����Ѫ
	heroBlood = 100;

	heroIndex = 0;//��ұ���ͼƬ�±�

	heroJump = false;//�����Ծ����

	//��Ծ���߶�  (�ʼ�߶�-����߶ȣ�������)
	jumpHeightMax = 440 - imgHeros[0].getheight() - 120;

	//��ʼ����Ծƫ����
	heroJump0ff = -6;






	//�����ڹ�
	IMAGE imgTort;

	//�����ڹ�
	loadimage(&imgTort, "res/t1.png");

	vector<IMAGE>imgTortArray;  //�����ڹ�����

	imgTortArray.push_back(imgTort); //��ͼƬ��ӵ�������    push_back��β��׷��һ����Ա
	
	obstacleImgs.push_back(imgTortArray);//����ڹ�����







	//����ʨ��
	IMAGE imgLion;//����ʨ��ͼƬ
	
	vector<IMAGE>imgLionArray;//ʨ������ͼƬ����   һά

	//���ͼƬ������
	for (int i = 0; i < 6; i++)
	{
		sprintf_s(name, "res/p%d.png", i + 1);//  д���ļ�λ��

		//����ͼ��ʨ��������
		loadimage(&imgLion, name);

		//��ʨ������β��׷��ʨ��ͼƬ
		imgLionArray.push_back(imgLion);
	}

	obstacleImgs.push_back(imgLionArray);//β��׷��ʨ�����鵽�����У�������








	

	











	//��ʼ���ϰ������  ȫ����ʼ��Ϊ�����ϳ�   
	for (int i = 0; i < OBSTACLE_COUNT; i++)
	{
		obstacles[i].exist = false;
	}














	//��������¶��ز�
	for (int i = 0; i < 2; i++)
	{
		sprintf_s(name, "res/d%d.png", i + 1);//  д���ļ�λ��

		loadimage(&imgHeroDown[i], name);
	}


	//��ʼ���¶׼�
	hero_down = false;










	//�����ĸ�����

	IMAGE imgH;

	for (int i = 0; i < 4; i++)
	{

		//�����ϰ�������           ��ֹ�������  ��ѭ���г�ʼ��   ��֤ÿ��ѭ�������ǿյ�
		vector<IMAGE> imgHookArray;

		//�����ļ���
		sprintf_s(name, sizeof(name),"res/h%d.png", i + 1);

		//����ͬʱ��������
		loadimage(&imgH, name, 63, 260, true);

		//��ӵ�������  ��ӵ����
		imgHookArray.push_back(imgH);

		//������鵽�ϰ��������  β��׷�ӣ�
		obstacleImgs.push_back(imgHookArray);

		//
	}







	//Ԥ������Ч    �����һ����ײ������				͵�Ľӿ�
	preLoadSound("res/hit.mp3");







	//������������
	mciSendString("play res/bg.mp3 repeat", 0, 0, 0);


	//�ϴ��ϰ���Ϊ  ��   -1
	lastObsIndex = -1;

	//������ʼ��
	score = 0;

	//��������ͼƬ
	for (int i = 0; i < 10; i++)
	{
		//�����ļ���
		sprintf_s(name, "res/sz/%d.png",i);

		//���ط���
		loadimage(&imgSz[i],name);
	}
	
}











//�����ϰ���     �ڳ�������һ�����õ��ϰ���
void createObstacle()
{
	int i;

	for (i = 0; i < OBSTACLE_COUNT; i++)
	{
		//�ҵ��ϰ���
		if (obstacles[i].exist == false)
		{
			break;
		}
	}

	if (i >= OBSTACLE_COUNT)	//����i��ֵ�ж�   ��û�ҵ��ϰ���
	{
		return;//û�ҵ� �ϰ��� ����
	}


	//�ҵ����ʼ����i���ϰ���

	//�ϰ������
	obstacles[i].exist = true;

	//û�������ϰ���
	obstacles[i].collide = false;

	//û��Խ���ϰ���
	obstacles[i].pass = false;


	//����ͼƬ��������0   ��һ��ͼƬ
	obstacles[i].imgIndex = 0;

	//�ϰ�������  �����ϰ������ࣨ������ȡ��						
	//obstacles[i].type = (obstacle_type)(rand() % OBSTACLE_COUNT);//(obstacle_type) (rand() % 2);//OBSTACLE_COUNT
	obstacles[i].type = (obstacle_type)(rand() % 3);   //���ĺ��ֹ���ӳ��ִ�������



	//�ж��ǲ�������
	//lastObsIndex    ��һ���ϰ������� 
	// 
	// ���±���ڵ���0   ��ֹ�±�Խ��     &&
	//	�ϰ�������������  &&
	//  ��γ��ֵ��ϰ�����ʨ��&&
	//  ��һ���ϰ���λ������Ļ���޷��㿪��λ�ã�
	if (lastObsIndex >= 0 &&
		obstacles[lastObsIndex].type >= PILLAR1 &&
		obstacles[lastObsIndex].type <= PILLAR4 &&
		obstacles[i].type == LION &&
		obstacles[lastObsIndex].x > (WIN_WIDTH - 500))
	{
		//���ϰ��� ���� �ĳ��ڹ�
		obstacles[i].type = TORTOISE;
	}

	//��һ���ϰ���			44�±���³����µ�ֵ    �ٴӸ��º���ϰ��￪ʼ�ж���һ���ϰ����ǲ����޷��㿪
	lastObsIndex = i;



	if (obstacles[i].type == PILLAR1) 
	{
		obstacles[i].type +=  rand() % 4;//��������������ѡ�ϰ���    0..3��Χ
	}

	//x����   ��Ϸ���ڿ�    ���ұ�
	obstacles[i].x = WIN_WIDTH;//400; //

	//y����   ����߶�  -  �ϰ������
	obstacles[i].y = 440 - obstacleImgs[obstacles[i].type][0].getheight();//340; //440;

	//�ϰ����ٶ�

	//������ڹ�
	if (obstacles[i].type == TORTOISE)
	{
		obstacles[i].speed = 0;   //�ٶ�
		obstacles[i].power = 5;   //�˺�				���޸ģ�������������������������������
	}
	else if (obstacles[i].type == LION)//�����ʨ��
	{
		obstacles[i].speed = 4;  //�ٶ�
		obstacles[i].power = 20;	//�˺�				���޸ģ�������������������������������
	}
	else if (obstacles[i].type >= PILLAR1 && obstacles[i].type <= PILLAR4)//���������(��Ϊ���ĸ����ӣ����Խ��о�׼�ж�)
	{
		obstacles[i].speed = 0;  //�ٶ�
		obstacles[i].power = 20;	//�˺�				���޸ģ�������������������������������

		obstacles[i].y = 100;  //////////////////////////////////////////////��������������ֵ� Ҫ�ı�y����
	}





}












//��ɫ ��Ծ������  �ж�
void hero_jump()
{
	heroJump = true;
	//��ˢ�½���   ֱ��ˢ��
	update = true;
}



//����¶׼� 
void heroDown()
{

	hero_down = true;
	//��ˢ�½���   ֱ��ˢ��
	update = true;

	//�¶���  ��0�ſ�ʼ��ʾ�¶�ͼƬ
	heroIndex = 0;
}















//�����û�����������
void keyEvent() {

	//�ж���û�а�������ȥ
	if (_kbhit()) //����а�������  �˺������� TRUE
	{
		char key;
		key = _getch();		//�˺�������Ҫ���س� (��֤��Ϸ����ֹͣ

		if (key == ' ') //�����ǿո�ʵ����Ծ
		{	

			hero_jump();

		}
		else if (key == 'x')
		{

			heroDown();

		}
	}
}








//��ײ���      ˼·�ж��������Σ�����ɫ���ϰ�����һ�����Σ�    �����Ƿ��ཻ
void checkHit()
{
	//
	for (int i = 0; i < OBSTACLE_COUNT; i++)
	{
		//����Ƿ����   �����ϰ���û������   
		if(obstacles[i].exist&&obstacles[i].collide==false)
		{
			//�����ɫ��������
			//�����ɫ  ����  ���Ϻ������������
			int a1x, a1y, a2x, a2y;

			int off = 30;											 //ƫ����   ��ֹ�����ϰ���һ���ִ��

			//
			if (!hero_down)   //���¶�    �������ܺ���Ծ��
			{
				a1x = heroX + off;  //����x
				a1y = heroY + off;  //����y    

				a2x = heroX + imgHeros[heroIndex].getwidth() - off;//����x
				a2y = heroY + imgHeros[heroIndex].getheight();//����y

			}
			else//�¶�״̬
			{
				//������Ͻ�����
				a1x = heroX + off;
				a1y = 440 - imgHeroDown[heroIndex].getheight();			//���õ��ԣ��ĳɹ̶�ֵ��	��bug�뿴һ�����  	//      //����-����¶����


				//���½�
				a2x = heroX + imgHeroDown[heroIndex].getwidth() - off;  //
			 	a2y = 360+80;//360;   //����///////////////////////////////////////////////////////////////////////

			}








			//�����ϰ�����������
			//��ǰ�ϰ���ͼƬ
			IMAGE img = obstacleImgs[obstacles[i].type][obstacles[i].imgIndex];

			int b1x = obstacles[i].x + off;  //����
			int	b1y = obstacles[i].y + off;  

			int	b2x = obstacles[i].x+ img.getwidth() - off;//����
			int	b2y = obstacles[i].y + img.getheight() - 10;  //-10  ��ֹƫ��������		yλ�õ��ڲݵ�///////////////////////////������ײ��������//////////////////////////////////////////////////////////�������⣡������������ͼƬ���ҵ�ͼƬ�߶Ȳ�һ�������겻���ճ�  Ҫ�Լ��㣡

			
			//�ж���û���ཻ  ����ײ��
			if (rectIntersect(a1x, a1y, a2x, a2y, b1x, b1y, b2x, b2y))
			{
				heroBlood -= obstacles[i].power;

				printf("Ѫ��ʣ��%d\n", heroBlood);

				//��������
				playSound("res/hit.mp3");

				//�������ϰ���  
				obstacles[i].collide = true;

				

			}


		}




	}

}










void fly()
{
	for (int i = 0; i < 3; i++)
	{
		//����
		bg_x[i] -= bgSpeed[i];
		//ʵ�ֱ����ظ�����
		if (bg_x[i] < -2000)
		{
			bg_x[i] = 0;
		}

	}


	//ʵ����Ծ,�ı����Y����   
	/*(��Ծ˼·)��
	* �������������߶�ʱ�½���������͸߶�ʱ����
	*/
	if (heroJump)//�����Ծ����Ϊ��  ����Ұ���Ծ��  ����ʱ��ɫYλ�ô��� + -4״̬����������
	{
		if (heroY < jumpHeightMax)//��������߶�      
		{
			heroJump0ff = 6;//��ƫ��������  ����ʱ��ɫ�������ƶ���
		}

		heroY += heroJump0ff;//ÿ����Ծ ��ɫY��λ�� + ƫ����  ��Y��λ�û���ƫ�����ı���ı䣩

		if (heroY > 440 - imgHeros[0].getheight())//������ ��Y�������Ӣ�۳�ʼ�ߣ�
		{
			heroJump = false;//��Ծ����
			heroJump0ff = -6;//ƫ�����ĳɳ�ʼ״̬ ����λ��(�����ƶ�)
		}

	}
	else if(hero_down)			//ʵ���¶�		//����Ծ��ʱ���ж���û���¶�
	{
		//�������ü��� ������һ���¶�ͼƬ   ����
		static int count = 0;

		int downDelay[2] = { 8,40 };		//�¶�����ͼƬ�Ĳ���ʱ��

		count++;

		if (count >= downDelay[heroIndex])		//���ö��ٴ�  �Ÿ�����һ֡ͼƬ   ֡���ӳ�  ��ֹ�¶׻������
		{
			count = 0;

			heroIndex++;

			//�ж���û�н����¶׶���
			if (heroIndex >= 2)
			{
				heroIndex = 0;	//��λ  ��ʼ���ű���ͼƬ       Ϊ�����±�

				hero_down = false;
			}
			//heroIndex = (heroIndex + 1) % 2;

		}
	}
	else                                //���û��ԾҲû�¶�     Ӣ��ͼƬ֡��
	{
		//Ӣ��ͼƬ֡�仯  ��֤�±���0-12����ͼƬ����Χ�ڣ���ֹ�±�Խ�磬ÿ��+1���12ȡ��
		heroIndex = (heroIndex + 1) % 12;
	}





	










	//�����ϰ���
	//ÿһ֡����    statci  ��̬  ��֤ ������������   �´ε���ʱֵ�����
	static int frameCount = 0;

	//�ڹ����Ƶ��
	static int enemyFre = 50;

	//������++
	frameCount++;

	if (frameCount > enemyFre)
	{
		frameCount = 0;//����������
		   
		//torToiseFre = 200 + rand() % 301;//�����ڹ����Ƶ��   ÿ200-500����һ�� ��  rand%301   0-300��

		enemyFre = 50 + rand() % 50;//ÿ�θ����ڹ����Ƶ��    50.....99

		//�����ϰ��ﺯ��
		createObstacle();

		//create0bstacle();//�����ϰ���

		//if (!torToiseExist)//��ǰ����û���ڹ�
		//{
		//	//��������Ϊ���ڹ�
		//	torToiseExist = true;

		//	//�ڹ�x��
		//	torToise_X = WIN_WIDTH;//λ�õ��ڴ��ڿ��  �����Ҳ����
		//}
	}

	//�ڹ��ƶ�  �ٶ�   �ǵ����ƶ��ٶ�   ÿ�� -ȥ �����ٶȱ���
	//	torToise_X -= bgSpeed[2];
	//if (torToise_X < -imgTortoise.getwidth())  //���Xλ��С�ڸ����ڹ�ͼ���   ���²⣺�ڹ굽�����ʱx���ͣס��һ��С���ڹ�Ŀ�����ʧ��
	//{
	//	torToiseExist = false;//���¼�
	//}



	//�����ϰ�������
	for (int i = 0; i < OBSTACLE_COUNT; i++)
	{
		//�ϰ������
		if (obstacles[i].exist)
		{
			//��������  �ƶ�   -= �ٶ� + ��ƺ�ٶ�
			obstacles[i].x -= obstacles[i].speed + bgSpeed[2];

			//��С�ڸ��Ĵ��ڿ��   ���ܳ�ͼƬ�⣩
			if (obstacles[i].x < -obstacleImgs[obstacles[i].type][0].getwidth() * 2)
			{
				obstacles[i].exist = false;//�ϰ�����ʧ
			}
			//�����ϰ�������
			int len = obstacleImgs[obstacles[i].type].size();
			obstacles[i].imgIndex = (obstacles[i].imgIndex + 1) % len;

		}
	}







	//��Һ��ϰ����   ��ײ���  ���� 
	checkHit();
}











//��Ⱦ��Ϸ����
void update_background()	
{
	
	//��ʾ��Ϸ����ͼƬ
	putimagePNG2(bg_x[0], 0, &imgBgs[0]);
	putimagePNG2(bg_x[1], 65, &imgBgs[1]);
	putimagePNG2(bg_x[2], 360, &imgBgs[2]);
}





//��Ⱦ�ϰ���
void updateEnemy()
{

	//ͨ�����Ӵ�С�ж�ѭ����С     ��ͨ���ṹ����Ⱦ��
	for (int i = 0; i < OBSTACLE_COUNT; i++)
	{
		if (obstacles[i].exist)//���ϰ�����ڽ�����Ⱦ
		{
			putimagePNG2(obstacles[i].x,   obstacles[i].y,   WIN_WIDTH,
				&obstacleImgs[obstacles[i].type][obstacles[i].imgIndex]);
			
		}
	}

}



//��ɫ�¶�
void updateHero()
{
	//���û�¶�   ���������ɫ����ͼƬ
	if (!hero_down)
	{
		putimagePNG2(heroX, heroY, &imgHeros[heroIndex]);
	}
	else
	{
		//����߶�(�ŵĸ߶�)  -  ��ǰҪ��Ⱦ���¶�ͼƬ�߶�
		int y = 440 - imgHeroDown[heroIndex].getheight();

		//ͨ������heroindex�±���ʵ�ֽ�ɫ�¶�ͼƬ����  ��fly��
		putimagePNG2(heroX, y, &imgHeroDown[heroIndex]);
	}
}





//����Ѫ��
void updateBloodBar()
{
	//����Ѫ������
	drawBloodBar(10, 10, 200, 10, 2,
				BLUE, DARKGRAY, RED, heroBlood / 100.0);
}







//�����Ϸ�Ƿ����
void checkOver()
{

	//Ѫ���⣡    ����
	if (heroBlood <= 0)
	{
		//��һ��������0   ֱ�Ӽ��ش���
		loadimage(0,"res/over.png");

		//ǿ��ˢ��      ��ʾ����
		FlushBatchDraw();

		//�رձ�������
		mciSendString("stop res/bg.mp3", 0, 0, 0);

		system("pause");




		//��֮ͣ�󣬼����棬��Ǯ��ֱ�Ӹ���       ������ʼ��ʼ����Ϸ����
		heroBlood = 100;//Ѫ����

		score = 0;//��������

		//��������music
		mciSendString("play res/bg.mp3 repeat",0,0,0);
	}

}









//������
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
			printf("����%d\n",score);

			//��ֹ�ظ��Ʒ�
			obstacles[i].pass = true;
		}
	}
}






//���·���*******************************�ѵ㣿***********************************************************************************************************
void updateScore()
{
	//50  =>  "50"
	char str[8];

	//���ļ���д������
	sprintf_s(str, "%d", score);

	int x = 20;
	int y = 25;

	for (int i = 0; str[i]; i++)
	{
		int sz = str[i] - '0';


		putimagePNG(x, y, &imgSz[sz]);

		//ͼƬ������+ƫ����
		x += imgSz[sz].getwidth() + 5;
	}

}











//�ж���Ϸʤ��
void checkWin()
{
	if (score >= WIN_SCORE)
	{

		//�ֶ�ˢ��        �����Ϸ����������������
		FlushBatchDraw();


		//����
		mciSendString("play res/win.mp3", 0, 0, 0);

		Sleep(2000);

		//����ͼƬ������
		loadimage(0, "res/win.jpg");

		//ˢ�»���
		FlushBatchDraw();

		//ͣ����
		mciSendString("stop res/bg.mp3", 0, 0, 0);
		system("pause");

		heroBlood = 100;
		score = 0;
		mciSendString("play res/bg.mp3 repeat",0,0,0);



	}
}
















void test()
{
//��ʼ��
	init();

	//��ʾ��ʼ��
	////���ֹ�
	//mciSendString("stop res/bg.mp3", 0, 0, 0);
	loadimage(0, "res/over.png");
	system("pause");


	

	//ˢ�¼�ʱ ֡�ȴ�ʱ��  ��ÿ��ѭ����ʱ��ʱ�䵽ʱˢ�½��棩
	int timer = 0;

	while (1)
	{
		//��Ծ�������
		keyEvent();

		//�˺������ؾ����ϴε�����������ٺ���
		timer += getDelay();

		//����30������ˢ�½���   (ʹ����������ô��Ǽ�ʹû��30���룬����Ҳ����Ч)
		if (timer > 30)
		{
			//����������
			timer = 0;
			//��ˢ�¿���
			update = true;
		}

		if (update)  //�ж��Ƿ���Ҫ����ˢ��
		{

			//ˢ�º󿪹عر�
			update = false;

			//˫���忪ʼ
			BeginBatchDraw();

			//��Ⱦ���� 
			update_background();

			//��Ⱦ��ɫ  �������ɫ����ÿһ��ͼƬ��
			//putimagePNG2(heroX, heroY, &imgHeros[heroIndex]);
			updateHero();

			//��Ⱦ�ϰ���
			updateEnemy();

			//����Ѫ��
			updateBloodBar();

			//���·���
			updateScore();

			//�ж���Ϸ�Ƿ�ʤ��
			checkWin();

			//˫�������   ȫ�� ֡�� ˢ��
			EndBatchDraw();


			//�����Ϸ�Ƿ����
			checkOver();

			//���÷�
			checkScore();

			


			//ʵ��  �ƶ�  (���ݺ���)
			fly();



		}
	}
}