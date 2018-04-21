# Map

## 性质
Map是STL的一个关联容器，Map内部自建一颗红黑树，这颗树具有对数据自动排序的功能，所以在Map内部所有的数据都是**有序**的。
## 功能
1. 自动建立Key － value的对应。key 和 value可以是任意你需要的类型。
2. 根据key值快速查找记录，查找的复杂度基本是Log(N)，如果有1000个记录，最多查找10次，1,000,000个记录，最多3查找20次。
3. 快速插入Key - Value 记录。
4. 快速删除记录
5. 根据Key 修改value记录。
6. 遍历所有记录。

## 引用方法

使用map得包含map类所在的头文件
```cpp
#include <map> 
```
map对象是模板类，需要关键字和存储对象两个模板参数：
```cpp
std:map<int, string> student;
```

这样就定义了一个用int作为索引,并拥有相关联的指向string的指针的Map。

为了使用方便，可以对模板类进行一下类型定义，下面均使用这种类型定义
```cpp
typedef std::map<int, std::string> MAP_INT_STRING; 
MAP_INT_STRING student;
```
## 使用方法

### 插入元素

1. 使用重载过的"[]"的操作符
```cpp
student[1]="Eric";
student[2]="Anmy";
```
直观但每次要查找新建节点再赋值，效率低
2. 使用自带的insert方法
```cpp
student.insert(MAP_INT_STRING::value_type(3,"Mike"));
```
### 查找获取元素
1.使用重载过的"[]"操作符
```cpp
std::string leader=student[1];
```
只有当map中有这个键的实例时才对，否则会自动插入一个实例，值为初始化值。

2. 使用自带的find和count方法
使用count(key)，返回的是被查找元素的个数。如果有，返回1；否则，返回0。注意，map中不存在相同元素，所以返回值只能是1或0。
使用find(key)，返回的是被查找元素的位置，没有则返回map.end()(数据类型是iterator)。
### 删除元素
移除某个map中某个条目用自带的erase方法
该成员方法的定义如下：
```cpp
iterator erase(iterator it); //通过一个条目对象删除
iterator erase(iterator first, iterator last); //删除一个范围
size_type erase(const Key& key); //通过关键字删除
```
### 清除所有的元素
使用自带方法clear
就相当于 
```cpp
student.erase(student.begin(), student.end());
```
### 后记
Set 与Map 类似只是key和val相同，因此不再赘述。