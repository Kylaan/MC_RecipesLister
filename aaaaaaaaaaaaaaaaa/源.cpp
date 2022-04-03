#include <iostream>
#include <D:/MyPrograms/jsoncpp/include/json/json.h>
#include <fstream>
#include <map>
using namespace Json;
using namespace std;


void changeMap(map<string, int>& mymap, string key, int value) {
    mymap[key] = value;
}

int main(void)
{


    // 1. �������ļ��е�json�ַ������������ļ�
    string FileName;
    string FileName_0 = "E:\\MOJANG_NMSL\\recipes1\\X (";
    string NameEnd = ").json";
    bool ctrl = 0;
    char Nsub[1001];


    // 2.km��ͼд�� 
    Value Root;         //Root  ��� (obj)
    Value rootObj;      //rootObj  obj�ڵ� ��root�� {...}    
    Value children;     //children  ����
    Value Data;         //Data  ����
    Value Data_up;      //Data_up  ��װ�����ڲ���children�Ķ���
    Value res;          //res  ��Ų����� (Array)
    Value DataAndChildren_itemUP;
    Value Data_itemUP;
    Value RootChildren;
    Data["created"] = 123456789;
    Data["id"] = "cj0hpwofp140";
    Data["text"] = "Item_All";
        Data_up["data"] = Data;     //�����װ�� ��data�� {...} --> �����ŵ�children��


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
 





    for (int Nname = 1; Nname <= 1178; Nname++)
    {
        map<string, int> map1;
        map<string, string> map2;
        map<string, int> mapE;
        string name;
        string table[3][3] = { " "," ", " ", " ", " ", " ", " ", " ", " " };
        _itoa_s(Nname, Nsub, 10);
        FileName = FileName_0 + Nsub + NameEnd;

        cout << "_________________________________________________________________________" << endl;
        ifstream ifs(FileName);     // 2. �����л� -> value���� r
        Value root;
        Reader r;
        r.parse(ifs, root);     // 3. ��value�����н��������ζ���
        Value::Members keys = root.getMemberNames();    //root ���ܵ�obj      keys ����obj������key
        unsigned flag = 1;
        string Lab = keys.at(flag);     //Lab ����obj�ĵ�flag��key  ����2����
        Value sub = root[keys[1]];      //sub ������obj�����ݣ���obj
        Value::Members ssub = sub.getMemberNames();     //ssub ����obj������key 
        for (unsigned Flag_0 = 0; Flag_0 < ssub.size(); ++Flag_0)
            if (ssub.at(Flag_0) == "pattern")
            {
                ctrl = 1;
                goto Lable;
            }
    Lable:
        for (unsigned Flag_0 = 0; Flag_0 < ssub.size(); ++Flag_0)
        {
            if (ssub.at(Flag_0) == "description")
            {
                Value item = sub[ssub[Flag_0]];
                Value::Members key_1 = item.getMemberNames();
                name = item[key_1[0]].asString();
                name.erase(0, 10);
                cout << "[item]\n" << name << "\n";
            }
            if (ssub.at(Flag_0) == "key")
            {
                Value item = sub[ssub[Flag_0]];
                Value::Members key_2 = item.getMemberNames();
                for (unsigned Flag_2 = 0; Flag_2 < key_2.size(); ++Flag_2)
                {
                    Value item_0 = item[key_2[Flag_2]];
                    Value::Members Sub_key_2 = item_0.getMemberNames();
                    string lable = key_2.at(Flag_2);
                    string vl = item_0["item"].asString();
                    int index = vl.find("minecraft");
                    if (index == 0)
                        vl.erase(0, 10);
                    map2.insert(pair <string, string>(lable, vl));
                }
            }
            if (ssub.at(Flag_0) == "pattern")
            {
                Value item = sub[ssub[Flag_0]];
                //item����Ǻϳɱ�δ������
                for (unsigned Flag_1 = 0; Flag_1 < item.size(); ++Flag_1)
                {
                    string SubStr = item[Flag_1].asString();
                    for (int No_repeat = 0; No_repeat < SubStr.length(); No_repeat++)
                    {
                        table[Flag_1][No_repeat] = SubStr[No_repeat];
                        map1.insert(pair <string, int>(table[Flag_1][No_repeat], 0));
                    }
                }
            }
        }

        //map1���ϳ��嵥��map2����ǩ��
        int x;
        if (ctrl)
        {
            for (int a = 0; a < 3; ++a)
            {
                for (int b = 0; b < 3; ++b)
                {
                    if (table[a][b] != " ")
                    {
                        x = int(map1.find(table[a][b])->second) + 1;
                        changeMap(map1, table[a][b], x);
                    }
                    else break;
                }
            }
            ctrl = 0;
        }
        int num;
        map<string, int> map3;
        for (map<string, int>::iterator it = map1.begin(); it != map1.end(); ++it)
        {
            string name_pt = it->first;
            num = it->second;
            string name = map2[name_pt];
            if (name != "")
                map3.insert(pair<string, int>(name, num));
        }
        if (!map3.empty())
        {
            printf("[List]");
            for (map<string, int>::iterator it3 = map3.begin(); it3 != map3.end(); ++it3)
            {
                mapE.insert(pair<string, int>(it3->first, it3->second));
                cout << "chale" << endl;
            }
        }
        else
        {
            printf("NOT Craftable!! \n");
        }

        //д��
        Data_itemUP["created"] = 123456789;
        Data_itemUP["id"] = "cj0hpwofp140";
        Data_itemUP["text"] = name;



        for (map<string, int>::iterator it_write = mapE.begin(); it_write != mapE.end(); ++it_write)
        {
            string materials = it_write->first;
            char num[1001];
            int num_int = it_write->second;
            _itoa_s(num_int, num, 10);

            res.clear();
            res.append(num);

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


    string str = Root.toStyledString();
    ofstream ofs("test.json");
    ofs << str;
    ofs.close();
    remove("nmsl.km");
    rename("test.json", "nmsl.km");
    system("pause");
    return 0;
}