#include <iostream>
#include <json/json.h>
#include <fstream>
#include <cstring>
#include <map>


void changeMap(std::map<std::string, int>& mymap, const std::string& key, int value) {
	mymap[key] = value;
}

template <size_t size>
void itoa(int value, char (&buffer)[size]) {
	buffer[size - 1] = '\0';
	char* p = buffer + (size - 2);
	
	do {
		*(p--) = (char)('0' + value%10);
	} while(value /= 10);
	memmove(buffer, ++p, size + buffer - p);
}

int main() {
	// 1. 将磁盘文件中的json字符串读到磁盘文件
	std::string FileName;
	std::string FileName_0 = R"(E:\MOJANG_NMSL\recipes1\X ()";
	std::string NameEnd = ").json";
	bool ctrl = false;
	char Nsub[1001];
	
	// 2.km脑图写入
	Json::Value Root;         //Root  最高 (obj)
	Json::Value rootObj;      //rootObj  obj内的 “root” {...}
	Json::Value children;     //children  数组
	Json::Value Data;         //Data  对象
	Json::Value Data_up;      //Data_up  封装后用于插入children的对象
	Json::Value res;          //res  存放材料数 (Array)
	Json::Value DataAndChildren_itemUP;
	Json::Value Data_itemUP;
	Json::Value RootChildren;
	Data["created"] = 123456789;
	Data["id"] = "cj0hpwofp140";
	Data["text"] = "Item_All";
	Data_up["data"] = Data;     //顶层封装到 “data” {...} --> 用来放到children里
	
	//children.append(Data_up);
	rootObj["data"] = Data;
	rootObj["children"] = children;
	Root["template"] = "default";
	Root["theme"] = "fresh-blue";
	Root["version"] = "1.4.43";
	Root["root"] = rootObj;
	Data.clear();
	Data_up.clear();
	children.clear();
	rootObj.clear();
	Root.clear();
	
	
	for(int Nname = 1; Nname <= 1178; Nname++) {
		std::map<std::string, int> map1;
		std::map<std::string, std::string> map2;
		std::map<std::string, int> mapE;
		std::string name;
		std::string table[3][3] = {" ", " ", " ", " ", " ", " ", " ", " ", " "};
		itoa(Nname, Nsub);
		FileName = FileName_0 + Nsub + NameEnd;
		
		std::cout << "_________________________________________________________________________" << std::endl;
		std::ifstream ifs(FileName);     // 2. 反序列化 -> value对象 r
		Json::Value root;
		Json::Reader r;
		r.parse(ifs, root);     // 3. 从value对象中将数据依次读出
		Json::Value::Members keys = root.getMemberNames();    //root ：总的obj      keys ：总obj的所有key
		unsigned flag = 1;
		std::string Lab = keys.at(flag);     //Lab ：总obj的第flag个key  （共2个）
		Json::Value sub = root[keys[1]];      //sub ：描述obj的内容，新obj
		Json::Value::Members ssub = sub.getMemberNames();     //ssub ：新obj的所有key
		for(auto& Flag_0: ssub) {
			if(Flag_0 == "pattern") {
				ctrl = true;
				break;
			}
		}
		for(auto& Flag_0: ssub) {
			if(Flag_0 == "description") {
				Json::Value item = sub[Flag_0];
				Json::Value::Members key_1 = item.getMemberNames();
				name = item[key_1[0]].asString();
				name.erase(0, 10);
				std::cout << "[item]\n" << name << "\n";
			}
			if(Flag_0 == "key") {
				Json::Value item = sub[Flag_0];
				Json::Value::Members key_2 = item.getMemberNames();
				for(auto& Flag_2: key_2) {
					Json::Value item_0 = item[Flag_2];
					Json::Value::Members Sub_key_2 = item_0.getMemberNames();
					std::string lable = Flag_2;
					std::string vl = item_0["item"].asString();
					int index = vl.find("minecraft");
					if(index == 0)
						vl.erase(0, 10);
					map2.insert(std::pair<std::string, std::string>(lable, vl));
				}
			}
			if(Flag_0 == "pattern") {
				Json::Value item = sub[Flag_0];
				//item存的是合成表（未改名）
				for(unsigned Flag_1 = 0; Flag_1 < item.size(); ++Flag_1) {
					std::string SubStr = item[Flag_1].asString();
					for(int No_repeat = 0; No_repeat < SubStr.length(); No_repeat++) {
						table[Flag_1][No_repeat] = SubStr[No_repeat];
						map1.insert(std::pair<std::string, int>(table[Flag_1][No_repeat], 0));
					}
				}
			}
		}
		
		//map1：合成清单，map2：标签表
		int x;
		if(ctrl) {
			for(auto& a: table) {
				for(auto& b: a) {
					if(b != " ") {
						x = int(map1.find(b)->second) + 1;
						changeMap(map1, b, x);
					} else break;
				}
			}
			ctrl = false;
		}
		int num;
		std::map<std::string, int> map3;
		for(auto& it: map1) {
			std::string name_pt = it.first;
			num = it.second;
			std::string name = map2[name_pt];
			if(!name.empty())
				map3.insert(std::pair<std::string, int>(name, num));
		}
		if(!map3.empty()) {
			printf("[List]");
			for(auto& it3: map3) {
				mapE.insert(std::pair<std::string, int>(it3.first, it3.second));
				std::cout << "chale" << std::endl;
			}
		} else {
			printf("NOT Craftable!! \n");
		}
		
		//写入
		Data_itemUP["created"] = 123456789;
		Data_itemUP["id"] = "cj0hpwofp140";
		Data_itemUP["text"] = name;
		
		for(auto& it_write: mapE) {
			std::string materials = it_write.first;
			char num_str[1001];
			int num_int = it_write.second;
			itoa(num_int, num_str);
			
			res.clear();
			res.append(num_str);
			
			Data["created"] = 123456789;
			Data["id"] = "cj0hpwofp140";
			Data["text"] = materials;
			Data["resource"] = res;
			Data_up["data"] = Data;
			children.append(Data_up);
		}
		DataAndChildren_itemUP.clear();
		//children.clear();
		DataAndChildren_itemUP["children"] = children;
		children.clear();
		DataAndChildren_itemUP["data"] = Data_itemUP;
		RootChildren.append(DataAndChildren_itemUP);
		rootObj["children"] = RootChildren;
		Root["root"] = rootObj;
	}
	
	
	std::string str = Root.toStyledString();
	std::ofstream ofs("test.json");
	ofs << str;
	ofs.close();
	remove("nmsl.km");
	rename("test.json", "nmsl.km");
	system("pause");
	return 0;
}
