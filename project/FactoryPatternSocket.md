# 1. 工厂模式



## 1.1 简单工厂模式



> 工厂: 用来创建某个基类的子类对象的。

```c++
# 简单工厂模式的使用:

1. 创建一个工厂类
2. 在这个类中提供一个公共的成员方法
   - 创建对象, 一般情况下创建某些实现多态的子类对象
   - 返回这个对象的地址
```



### 简单工厂实现：

~~~ c++ 
// 通过创建工厂类, 添加工厂函数, 创建对象
// 两个编解码的子类
class RequestCodec : public Codec	// 编解码请求数据
class RespondCodec : public Codec	// 编解码响应数据


/*
	知识点:
		做条件判断的时候, if..else if .. else 效率比 switch 低
		如果判断的情况比较少使用 if .. else
		如果情况比较多, 建议使用 switch
*/
    
// 创建工厂类, 创建编解码对象
class Factory
{
public:
    Factory();
    ~Factory();
    // 工厂函数, 创建对象
    // flag==1 -> RequestCodec
    // flag==2 -> RespondCodec
    Codec* createObject(int flag)
    {
        Codec* c = NULL;
        // 判断
        if(flag == 1)
        {
            c = new RequestCodec();
        }
        else if(flag == 2)
        {
            c = new RespondCodec();
        }
        return c;
    }
}
~~~



### 简单工厂使用：

~~~ c++
// 1. 创建工厂类对象
Factory* fac = new Factory;
// 2. 通过工厂函数创建编解码对象
Codec* c = fac->createObject(1);
// 3. 编码
string str = c->encoceMsg();
~~~



## 1.2 工厂模式



> 每种产品由一种工厂来创建，一个子类工厂保存一个new



~~~c++
# 工厂模式流程
1. 创建一个工厂类的基类
2. 在这个基类中定义一个虚函数 -> 创建对象的方法
3. 创建子工厂类(编解码的基类有多少子类, 就创建多少个子工厂类)
	- 每个编解码的子类, 都对应一个工厂类
4. 在子工厂类中重写工厂类基类中的虚函数
~~~



工厂类的使用:

```c++
// 两个编解码的子类
class RequestCodec : public Codec
class RespondCodec : public Codec
class TestCodec : public Codec	// 编解码响应数据
```

### 工厂模式实现

```c++
// 创建工厂类的基类
class BaseFactory
{
public:
    BaseFactory();
    ~BaseFactory;
    virtual Codec* createObject()
    {
        return NULL;
    }
}

// 工厂类子类
class RequestFactory : public BaseFactory
{
public:
    RequestFactory();
    ~RequestFactory;
    Codec* createObject()
    {
        return new RequestCodec;
    }
}

class RespondFactory : public BaseFactory
{
public:
    RespondFactory();
    ~RespondFactory;
    Codec* createObject()
    {
        return new RespondCodec;
    }
}

class TestFactory : public BaseFactory
{
public:
    TestFactory();
    ~TestFactory;
    Codec* createObject()
    {
        return new TestCodec;
    }
}
```

### 工厂模式使用

~~~c++
// 1. 创建工厂类对象
BaseFactory* fac = new RespondFactory;
// 2. 得到了编解码对象
Codec* c = fac->createObject();
// 3. 编码
string str = c->encodeMsg();
~~~



> 有新的子类对象就创建新的子工厂类添加上去，避免了修改代码的流程。



~~~c++
//在序列化中生成的两个类RequestCodec和RespondCodec都继承于Codec类，因此可以创建一个工厂类的基类CodecFactory并编写创建子类对象的虚函数。分别创建两个子类工厂并覆写创建子类对象的虚函数（返回Codec* 指针）基类工厂指针可以指向不同子类工厂对象并调用其创建对象的函数（多态）。最终使用父类指针（Codec*）调用不同对象的虚函数。（多态）
~~~







# 2. 套接字通信



 