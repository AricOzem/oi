# Vector
## 性质
vector是一个能够存放任意类型的动态数组，能够增加和压缩数据.
## 功能
### 查询容量

向量大小： vec.size();

向量最大容量： vec.max_size();

更改向量大小： vec.resize();

向量真实大小： vec.capacity();

向量判空： vec.empty();

减少向量大小到满足元素所占存储空间的大小：
 
vec.shrink_to_fit(); //shrink_to_fit

### 修改

多个元素赋值： vec.assign(); //类似于初始化时用数组
进行赋值

末尾添加元素： vec.push_back();

末尾删除元素： vec.pop_back();

任意位置插入元素： vec.insert();

//插入位置靠后 数据小时很快
任意位置删除元素： vec.erase();

交换两个向量的元素： vec.swap();

清空向量元素： vec.clear();

### 迭代器
开始指针：vec.begin();
末尾指针：vec.end(); //指向最后一个元素的下一个位置
指向常量的开始指针： vec.cbegin(); //意思就是不能通过这个指针来修改所指的内容，但还是可以通过其他方式修改的，而且指针也是可以移动的。
指向常量的末尾指针： vec.cend();
### 访问元素
下标访问： vec[1]; //并不会检查是否越界
at方法访问： vec.at(1); //以上两者的区别就是at会检查是否越界，是则抛出out of range异常
访问第一个元素： vec.front();
访问最后一个元素： vec.back();
返回一个指针： int* p = vec.data(); //可行的原因在于vector在内存中就是一个连续存储的数组，所以可以返回一个指针指向这个数组。这是是C++11的特性。
## 引用方法
```cpp
#include<vector>
std::vector<int> a;
```