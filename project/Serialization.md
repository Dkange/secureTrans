该项目主要是做数据加密，加密就需要有密钥，密钥需要进行密钥协商，密钥协商的前提就是对数据进行序列化



# 序列化

​	**`将对象的状态信息转换为可以存储或传输的形式`**

​	**序列化和反序列化主要用于解决在跨平台和跨语言的情况下, 模块之间的交互和调用，但其本质是为了解决数据传输问题**

​	

## 1.1 网络通信中的问题



- 平台不同

  - 32bit / 64bit 
    - long
  - 平台不同, 某些数据类型占用的内存大小不同
- 如果不是字符串, 需要进行字节序转换

  - 字符串没有字节序问题, 字符在内存中只占一个字节
  - 如果发送的是结构体
  - 大小端问题
- 语言不同
  - 语言不同数据类型占用的内存有可能不同
    - c -> char -> 1字节
    - java -> char -> 2字节
- 字节对齐问题

```c++
序列化的整体过程:

- 发送端
  - 原始数据 -> 序列化 (编码) -> 特殊格式的字符串
  - 发送这个字符串
- 接收端:
  - 接收数据
  - 特殊格式的字符串 -> 反序列化 (解码) -> 原始数据
  - 对原始数据进行处理
```



## 1.2 常用的序列化方式

1. XML（ Extensible Markup Language ）类似于html

2. Json

   ```json
   // json是一种数据格式, 不是语言, 和平台语言无关
   // json数组
   [整形, 浮点型, 布尔类型, 字符串, json数组, json对象]
   [12, 12.44, true, "hello", [1,2,3]]
   // json对象
   {
       "key":"value"
   }
   json对象中是n个键值对
   key: 必须是字符串
   value: 
   	整形
   	浮点型
   	布尔
   	字符串
   	json数组
   	json对象
   
   注意事项:
   	在一个文件中只能存储一个大的数组或者对象, 但是可以嵌套使用
   	原素和原始之间使用逗号间隔(一个键值对视为一个元素)
   	最后一个元素后边没有逗号
   
   {
       "lilei":"112334",
       "tom":"helolll",
       "lucy":"xxxxyyyy"
   }
   
   ["张三", "历史"]
   
   {
       "张三":{
           "father":"张三丰",
           "mother":"xxxx",
           "sister""xxx",
           "favorite":["足球", "乒乓", "游泳"]
       }
   	"李四":{
       }
   }
   ```

   

3. Protocol Buffer

4. boost 序列化的类

# protobuf



>  分为版本2和版本3



## 2.1 操作流程



> - 准备数据
>   - 复合类型: 结构体/ 类
>   - 基础类型
> - 创建一个新文件 `xxx.proto`
> - 将我们要序列化的数据 -> 写入到proto文件
>   - 有语法格式
> - 通过一个命令 `protoc`将`xxx.proto`文件生成一个c++的类 
>   - 对应一个头文件/ 源文件
>   - 操作命令-> 在window终端中: `protoc xxx.proto --cpp_out=./`
> - 直接使用这个类
>   - 里边有对数据操作的api
>     - 读数据 api
>       - 方法名字 `变量名()`
>     - 写数据 api
>       - 方法名字: `set_变量名(arg)`



* .proto文件中的消息格式

  ```protobuf
  // protobuf的版本
  syntax = "proto3";	// proto2
  // 组织Persion结构体
  // 语法格式
  message 关键字(相当于被创建出的类的名字)
  {
  	// 成员变量
  	数据类型 变量名 = 变量的编号;	// 编号从1开始, 不能重复
  }
  
  // .proto文件 生成 c++ 类的命令
  protoc proto文件名 --cpp_out=生成目录
  ```

* 使用protobuf编译器生成C++类

  ```Vs
  protobuf编译器, 编译源码得到的 protoc.exe
  
  语法
  
  --cpp_out 生成的c++类的位置
  
  protoc.exe xxx.proto --cpp_out=目录
  ```

* 使用C++ API来读写消息

  * 读: `变量名()`
  * 写: `set_变量名(arg1, arg2, ...)`

* vs配置 -> 添加宏

  

# 3. 业务数据分析

## 3.1 客户端

```c++
/*
// 准备要发送的数据
struct RequestMsg
{
    //1 密钥协商 //2 密钥校验; // 3 密钥注销
    int cmdType; // 报文类型
    string clientId; // 客户端编号
    string serverId; // 服务器端编号
    string sign;
    string data;
};
*/

syntax = "proto3";
message RequestMsg
{
    int32 cmdType = 1;
    bytes clientId = 2;
    bytes serverId = 3;
    bytes sign = 4;
    bytes data = 5;
}
```



## 3.2 服务器端

```c
/*
struct RespondMsg
{
    bool rv; // 返回值
    int secKeyId; 		// 对称密钥编号 keysn
    string clientId; 	// 客户端编号
    string serverId; 	// 服务器编号
    string data; 	// 服务器端随机数
};
*/

syntax = "proto3";
message RespondMsg
{
    bool re = 1;
    int32 secKeyId = 2;
    bytes clientId = 3;
    bytes serverId = 4;
    bytes data = 5;
}
```



生成对应的C++类，放入工程目录下



## 3.3 编解码类的生成



> 请求数据和响应数据的格式不同因此需要分别为请求数据编解码和响应数据编解码创建不同的类。而两个类有相同的功能（编码/解码），因此创建一个编解码类，并定义虚函数共两个类继承覆写实现多态。



* 由上述两个类生成的对象可以完成编码或解码（分别完成，一个负责编码、一个负责解码）



> 分别创建了RequestCodec.cpp和RespondCodec.cpp分别用来处理请求消息和响应消息

> 自此，完成了数据序列化的功能，可供后续使用

