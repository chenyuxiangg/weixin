#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>		//srand()与rand()的头文件，前者用来生成随机数种子，后者用来生成随机数
#include <ctime>		//time()函数头文件
#include <fstream>
#include <stdio.h>
#include <unistd.h>
using namespace std;

namespace cyx {
enum ZhuboJiNeng {SING, DOUJIAN, LOULIAN};

class Fans{
	public:
		Fans(ZhuboJiNeng act) {
			m_name = GetName();
			
			switch (act) {
				case SING:
					{
						cout << m_name << ": ";
						cout << "哇！主播的声音好好听，关注一波！" << endl;
						break;
					}
				case DOUJIAN:
					{
						cout << m_name << ": ";
						cout << "嘿嘿嘿，画面真是不可描述呢。^_^，别拦我，我要冲钱！！" << endl;
						break;
					}
				case LOULIAN:
					{
						cout << m_name << ": ";
						cout << "aaaaaaaa!!!!还我血汗钱！！" << "我的24k帅眼瞎了！！！"<< endl;
						break;
					}
				default:
					break;
			}
		}

		~Fans() {
			cout << m_name << ": ";
			cout << "我要静静。。。。。" << endl;
		}

	private:
		string GetName(){
			ifstream fs("name.txt");
			string words;
			//获取name.txt中的一行
			getline(fs,words);
			fs.close();
			//从一行汉字中随机取出两个来组成名字
			if (words.empty()) {
				return "小红";
			}
			srand(time(0));
			size_t size = words.size();
			string res;
			res.push_back(words[rand()%size]);
			res.push_back(words[rand()%size]);
			return res;
		}

	private:
		string m_name;
};

class Zhubo{
	public:
		Zhubo(const string& name, int age) {
			m_name = name;
			m_age = age;
			cout << "大家好！！我 20岁" << "(" << m_age << ")" << name << " 上线了！" << endl;
			cout << "今天，你冲榜一了么？" << endl;
		}
		~Zhubo() {
			cout << "人家累了，下播了下播了。" << endl;
		}

		string Ask() {
			cout << "碧粉们～你们想听我唱哪首歌呢？" << endl;
			string songname;
			cin >> songname;
			return songname;
		}
		int Increase(int base = 2) {
			srand(time(0));
			return (rand()%10 + base);	//随机生成base及以上个数的粉丝
		}
		void Diaofans() {
			cout << "空气突然安静..." << endl;
			cout << ".............." << endl;
			size_t size = m_fans.size();
			for (size_t i = 0; i < size; ++i) {
				delete m_fans[i];
			}
			m_fans.clear();
			cout << "掉粉1000000000" << "w" << endl;
		}
		void Sing() {
			//随机涨粉
			string songname = Ask();
			cout << "咳咳～我先清清嗓子，我要开始唱啰～" << endl;
			cout << "#$%^&*@!@#$#@#%##$......" << endl;
			cout << "哦呵呵呵呵～我唱完了，觉得好听的关注我一波哟，爱你么么哒～^&^" << endl;
			cout << "涨粉中..." << endl;
			int num = Increase();
			for (int i = 0;i < num;++i) {
				m_fans.push_back(new Fans(SING));
			}
			cout << "主播涨粉 " << num << "w" << endl;
		}
		int DouJian() {
			cout << "==========旁白： 请自行脑补清(su)新(bu)脱(ke)俗(nai)的画面==========" << endl;
			cout << "涨粉中..." << endl;
			int num = Increase(5);
			for (int i = 0;i < num;++i) {
				m_fans.push_back(new Fans(DOUJIAN));
			}
			cout << "主播涨粉 " << num << "w" << endl;
		}
		void LouLian() {
			cout << m_name << ": ";
			cout << "哎呀！！！我怎么就露脸了呢？？（惊慌失措ing)...哦哈哈哈哈，跟大家开个玩笑哈～我刚刚开了个变脸软件，大家觉得好不好完啊哈哈哈哈哈." << endl;
			Diaofans();
		}

	private:
		string m_name;
		int m_age;
		vector<Fans*> m_fans;
};

}

int main(int argc,char* argv[])
{
	cyx::Zhubo qiao("乔碧罗",60);
	bool flag = true;
	while (flag) {
		cout << "主播准备做什么动作呢？" << endl;
		cout << "================================" << endl;
		cout << "  1. 唱歌" << endl;
		cout << "  2. 抖肩" << endl;
		cout << "================================" << endl;
		cout << "请输入序号：" << endl;
		int i;
		cin >> i;
		switch (i) {
			case 1:
				{
					qiao.Sing();
					break;
				}
			case 2:
				{
					qiao.DouJian();
					break;
				}
			default:
				{
					cout << "输入有误" << endl;
					break;
				}
		}
		srand(time(0));
		int x = rand()%10;
		if (x == 9 || x == 5 || x == 2) {
			qiao.LouLian();
			flag = false;
		}
		sleep(5);
		system("reset");	//清屏
	}
	return 0;
}
