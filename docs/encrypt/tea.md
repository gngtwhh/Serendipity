# TEA 加密/解密模块

该模块实现了`TEA`,`XTEA`,`XXTEA`三种加密算法,并支持如下自定义:
- 三种加密自定义`delta`值.
- `TEA`,`XTEA`自定义加密轮次`round`.

## 依赖

该模块依赖于`encrypt/encrypt_pre_init.h`.

# 数据类型参考

## tea_encipher

```C
typedef struct tea_encipher {  
    uint32_t delta;  
    int rounds; // not available for XXTEA  
    int n; // the count of blocks  
    uint32_t key[4];  
} tea_encipher;
```

- tea_encipher是tea模块所使用的"加密器"类型. 
- delta: TEA系加密所使用的delta值,可以设置为默认值.
- rounds: `TEA`和`XTEA`的加密轮次,默认为32.
- n: 需要加密/解密的分组数,一个分组为`32-bits`.

应该使用`new_tea`函数来创建一个`tea_encipher`实例;对应地,使用`free_tea`函数将其释放.
`TEA`,`XTEA`,`XXTEA`均使用相同`tea_encipher*`类型的"加密器"参数,其中无关参数`rounds`对`XXTEA`的加密/解密无影响.

`tea_encipher`结构体的成员也可以直接设置其值进行修改,以达到复用等效果.

# API参考

## new_tea

该函数创建一个`tea_encipher`实例,并返回其指针.

函数原型:
```C
tea_encipher *new_tea(uint32_t delta, const uint32_t key[4], int rounds);
```

- delta: 一个无符号的32位整数,来指定`DELTA`值,如果该参数为零,则使用默认`DELTA`值.
- key: 一个长为4的32位整数数组,用于指定`密钥`. 即TEA系加密的`128-bits`密钥.
- rounds: 一个整数,用于指定加密轮次,当该加密器用于`XXTEA`时,`round`参数无效.
- 返回一个`tea_encipher *`,指向创建的`tea_encipher`实例,如果调用失败,返回`NULL`.

## free_tea

该函数销毁一个`tea_encipher`实例.
函数原型:

```C
status free_tea(tea_encipher *tea);
```

- tea: 一个`tea_encipher *`的参数,指向需要销毁的`tea_encipher`实例,如果为NULL,返回值为`error`.
- 返回值为`status`,等价于`int`,成功返回`1`,失败返回`非1`.

## tea_encrypt

该函数对输入的数据进行`TEA`加密.
函数原型:
```C
status tea_encrypt(tea_encipher *tea, const uint32_t *plain, uint32_t *cipher);
```

其中:
- tea: 一个`tea_encrypt`的指针,指向一个`tea_encrypt`实例. 其信息指定特定的加密过程.
- plain: 一个只读的`uint32_t`指针,指向待加密的若干分组,分组个数必须是偶数.
- cipher: 一个`uint32_t`指针,指向caller分配好的内存段,用于存储加密结果.
- 返回值为`status`,等价于`int`,成功返回`1`,失败返回`非1`.
注意:
- 在调用该函数之前,`tea->n`必须被设置为待处理数据的分组数.
## tea_decrypt

该函数对输入的数据进行`TEA`解密.
函数原型:
```C
status tea_decrypt(tea_encipher *tea,const uint32_t *cipher, uint32_t *plain);
```

其中:
- tea: 一个`tea_encrypt`的指针,指向一个`tea_encrypt`实例. 其信息指定特定的解密过程.
- cipher: 一个只读的`uint32_t`指针,指向待解密的若干分组,分组个数必须是偶数.
- plain: 一个`uint32_t`指针,指向caller分配好的内存段,用于存储解密结果.
- 返回值为`status`,等价于`int`,成功返回`1`,失败返回`非1`.
注意:
- 在调用该函数之前,`tea->n`必须被设置为待处理数据的分组数.

## xtea_encrypt

该函数对输入的数据进行`XTEA`加密.
函数原型:
```C
status xtea_encrypt(tea_encipher *tea, const uint32_t *plain, uint32_t *cipher);
```

其中:
- tea: 一个`tea_encrypt`的指针,指向一个`tea_encrypt`实例. 其信息指定特定的加密过程.
- plain: 一个只读的`uint32_t`指针,指向待加密的若干分组,分组个数必须是偶数.
- cipher: 一个`uint32_t`指针,指向caller分配好的内存段,用于存储加密结果.
- 返回值为`status`,等价于`int`,成功返回`1`,失败返回`非1`.
注意:
- 在调用该函数之前,`tea->n`必须被设置为待处理数据的分组数.
## xtea_decrypt

该函数对输入的数据进行`XTEA`解密.
函数原型:
```C
status xtea_decrypt(tea_encipher *tea,const uint32_t *cipher, uint32_t *plain);
```

其中:
- tea: 一个`tea_encrypt`的指针,指向一个`tea_encrypt`实例. 其信息指定特定的解密过程.
- cipher: 一个只读的`uint32_t`指针,指向待解密的若干分组,分组个数必须是偶数.
- plain: 一个`uint32_t`指针,指向caller分配好的内存段,用于存储解密结果.
- 返回值为`status`,等价于`int`,成功返回`1`,失败返回`非1`.
注意:
- 在调用该函数之前,`tea->n`必须被设置为待处理数据的分组数.

## xxtea_encrypt

该函数对输入的数据进行`XXTEA`加密.
函数原型:
```C
status xxtea_encrypt(tea_encipher *tea, const uint32_t *plain, uint32_t *cipher);
```

其中:
- tea: 一个`tea_encrypt`的指针,指向一个`tea_encrypt`实例. 其信息指定特定的加密过程.
- plain: 一个只读的`uint32_t`指针,指向待加密的若干分组,分组个数必须是偶数.
- cipher: 一个`uint32_t`指针,指向caller分配好的内存段,用于存储加密结果.
- 返回值为`status`,等价于`int`,成功返回`1`,失败返回`非1`.
注意:
- 在调用该函数之前,`tea->n`必须被设置为待处理数据的分组数,并且不能为零.
- 对于`XXTEA`,`tea->rounds`没有作用,但其值是否被设置并无影响.
## xxtea_decrypt

该函数对输入的数据进行`XXTEA`解密.
函数原型:
```C
status tea_decrypt(tea_encipher *tea,const uint32_t *cipher, uint32_t *plain);
```

其中:
- tea: 一个`tea_encrypt`的指针,指向一个`tea_encrypt`实例. 其信息指定特定的解密过程.
- cipher: 一个只读的`uint32_t`指针,指向待解密的若干分组,分组个数必须是偶数.
- plain: 一个`uint32_t`指针,指向caller分配好的内存段,用于存储解密结果.
- 返回值为`status`,等价于`int`,成功返回`1`,失败返回`非1`.
注意:
- 在调用该函数之前,`tea->n`必须被设置为待处理数据的分组数,并且不能为零.
- 对于`XXTEA`,`tea->rounds`没有作用,但其值是否被设置并无影响.
