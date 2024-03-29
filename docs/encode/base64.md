# Base64 编码/解码模块

这个模块提供了将数据进行 Base64 编码和解码的功能.

不仅支持标准的base64编码,而且支持自定义表,表中可以不是合法的ASCII字符,即字符数值范围支持`0~255`,而不是`0~127`.

## 依赖

该模块依赖于`encode/encode_pre_init.h`.

# 数据类型参考

## base64_encoder

```c
typedef struct base64_encoder {
    byte* b64_table;
    byte* reverse_table;
    int output_len;
} base64_encoder;
```

- base64_encoder是base64模块所使用的"编码器"类型.
- b64_table: 该编码器实例所使用的"base64表".
- reverse_table: 该编码器实例所使用的"base64表"所对应的"逆表",用于解码.

应该使用`new_base64`函数来创建一个`base64_encoder`实例;对应地,使用`free_base64`函数将其释放.

# API参考

## new_base64

该函数创建一个"编码器"实例,并返回其指针.

函数原型:

```c
base64_encoder *new_base64(const byte *b64_table);
```

- b64_table: 一个只读的长为64字节的byte字符串,来指定该"编码器"所使用的`Base64表`,如果想要使用`标准base64`编码,则传入`NULL`.
- 返回一个`base64_encoder *`,指向创建的`base64_encoder`实例,如果调用失败,返回`NULL`.

## free_base64

该函数销毁一个"编码器"实例.

函数原型:

```c
status free_base64(base64_encoder *encoder);
```

- encoder: 一个`base64_encoder *`的参数,指向需要销毁的`base64_encoder`实例,如果为NULL,返回值为`error`.
- 返回值为`status`,等价于`int`,成功返回`1`,失败返回`非1`.

## base64_change_table

该函数修改一个"编码器"所使用的`base64表`.

函数原型:

```c
status base64_change_table(base64_encoder *encoder, const byte *b64_table);
```

- encoder: 一个`base64_encoder *`的参数,指向要处理的`base64_encoder`实例.
- b64_table: 一个长为64字节的byte字符串,来指定要使用的新`Base64表`,该不允许为`NULL`.
- 返回值为`status`,等价于`int`,成功返回`1`,失败返回`非1`.

## base64_reset

该函数将一个"编码器"重置为标准状态,即使用默认`base64表`,并将`output`成员的值重置.

函数原型:

```c
status base64_reset(base64_encoder *encoder);
```

- encoder: 一个`base64_encoder *`的参数,指向要处理的`base64_encoder`实例.
- 返回值为`status`,等价于`int`,成功返回`1`,失败返回`非1`.

## base64_encode

该函数进行`base64编码`的操作,将输入的数据进行编码.

函数原型:

```c
status base64_encode(base64_encoder *encoder, const byte *input, int in_len, byte *output);
```

- encoder: 接受一个`base64_encoder *`的参数,指向要使用的`base64_encoder`实例,该实例`应该`被提前设置好.
- input: 接受一个只读的byte指针,指向待编码的字节数据.
- in_len: input参数指向的数据的长度,单位是`字节`.
- output: 指向一个缓冲区,用于存储生成的编码数据.
- 返回值为`status`,等价于`int`,成功返回`1`,失败返回`非1`.

## base64_decode

该函数进行`base64解码`的操作,将输入的数据进行解码.

```c
status base64_decode(base64_encoder *encoder, const byte *input, int in_len, byte *output);
```

- encoder: 接受一个`base64_encoder *`的参数,指向要使用的`base64_encoder`实例,该实例`应该`被提前设置好.
- input: 接受一个只读的byte指针,指向待解码的字节数据.
- in_len: input参数指向的数据的长度,单位是`字节`.
- output: 指向一个缓冲区,用于存储生成的解码数据.
- 返回值为`status`,等价于`int`,成功返回`1`,失败返回`非1`.