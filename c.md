> 🚀《C程序设计语言》读书笔记，总结每一章未知的知识点和优秀代码以供临摹。

# 第一章：导言

## 一、知识点

1. 像`printf`这样的函数属于标准库，并不属于 C 语言本身。
2. 「标准库」和「系统调用」的区别：标准库运行在用户空间，是为了方便使用系统调用而编写的；系统调用运行在内核空间，是最底层的 API。
3. 文件结束符`EOF`的值是 -1，windows 下使用<kbd>ctrl</kbd>+<kbd>z</kbd>输入，linux 下使用<kbd>ctrl</kbd>+<kbd>d</kbd>输入。
4. 在同一源文件中，所有「外部变量」的定义都应该放在源文件的开始处，这样就可以省略`extern`声明。

## 二、优秀代码

```c
// 伟大的 hello，world
#include <stdio.h>

int main(int argc, char* argv[]) {
    printf("hello,world");
    return 0;
}
```

```c
// 将输入复制到输出
#include <stdio.h>

int main(int argc, char* argv[]) {
    int c;
    while ((c = getchat()) != EOF) {	// 良好习惯 1 的有力说明
        putchar(c);
    }
}
```

```c
// 统计输入字符个数
#include <stdio.h>

int main(int argc, char* argv[]) {
    int nc;
    for (nc = 0; getchar() != EOF; nc++);	// 良好习惯 2 的有力说明
    return 0;
}
```

```c
// 统计输入的行数
#include <stdio.h>

int main(int argc, char* argv[]) {
    int c, nl;
    for (nl = 0; (c = getchar()) != EOF;) {	// 良好习惯 2 的有力说明
        if (c == '\n') {
            ++nl;
        }
    }
    return 0;
}
```

```c
// 将输入中连续的多个空格用一个空格代替
#include <stdio.h>

#define NONBLANK 'a'

int main(int argc, char* argv[]) {
    int c, lastc = NONBLANK;
    while ((c = getchar()) != EOF) {
        if (c != ' ' || lastc != ' ') {	// 良好习惯 5 的有力说明，这里用 for 循环也可以
            putchar(c);
        }
        lastc = c;
    }
    return 0;
}
```

```c
// wc 简陋版，这种隔离单词的方法很值得借鉴
#include <stdio.h>

#define IN  1   // 良好习惯 3 的有力说明
#define OUT 0

int main(int argc, char* argv[]) {
    int c, state = OUT;
    int nl, nw, nc;
    for (nl = nw = nc = 0; (c = getchar()) != EOF;) {
        ++nc;
        if (c == '\n') {
            ++nl;
        }
        if (c == ' ' || c == '\t' || c == '\n') {
            state = OUT;
        }else if (state == OUT) {
            ++nw;
            state = IN;
        }
    }
    return 0;
}
```

```c
// 求输入行中长度最长的
#include <stdio.h>

#define MAXLENGTH 1000

int mygetline(char*, int);
void copy(char*, char*);

int main(int argc, char* argv[]) {
    char line[MAXLENGTH], dst[MAXLENGTH];
    int length, maxlength = 0;
    while ((length = mygetline(line, MAXLENGTH)) > 0) {
        if (length > maxlength) {
           maxlength = length;
           copy(dst, line);
        }
    }
    if (maxlength > 0) {
        printf("%s", dst);
    }
    return 0;
}

// 对比第五章的指针版本来学习指针的使用
int mygetline(char* line, int maxlength) {
    int c, i;
    for (i = 0; i < maxlength - 1 && (c = getchar()) != EOF && c != '\n';) {
        line[i++] = c;  // 良好习惯 7 的有力说明
    }
    if (c == '\n') {
        line[i++] = c;
    }
    line[i] = '\0';
    return i;
}

void copy(char* s, char* t) {
    int i;
    for (i = 0; s[i] = t[i]; ++i);  // 良好习惯 6 的有力说明
}
```

# 第二章：类型、运算符与表达式

## 一、知识点

1. 没有后缀的「浮点数常量」是`double`类型。
2. 「字符串常量」就是「字符数组」，`char* s = "hello,world"`类似这样的语句将以「字符数组」的形式存储，<u>并以`\0`结束，但是不能通过`s`修改其值</u>。
3. 「外部变量」与「静态变量」都会自动初始化为`0`。
4. 在表达式中<u>比较窄的</u>操作数自动转换为<u>比较宽的</u>操作数(`float`不会转换为`double`)，运算结果为<u>比较宽的</u>类型。
5. 当对`signed`类型的带符号值进行`>>`时，<u>根据具体机器</u>，「算术移位」用<u>符号位</u>填补左边空白部分，「逻辑移位」用`0`填补左边空白部分。
6. `x *= y + 1`等于`x = x * (y + 1)`。
7. 「三目运算符」返回的两个可选值也符合 4 中转换规则。

## 二、优秀代码

```c
// 从字符串中删除字符 c
void sequeeze(char* s, int c) {
    int i, j;
    for (i = j = 0; s[i] != '\0'; ++i) {
        if (s[i] != c) {
            s[j++] = s[i];	// 良好习惯 7 的有力说明
        }
    }
    s[j] = '\0';
}
```

```c
char* strcat(char* s, char* t) {
    int i, j;
    for (i = 0; s[i] != '\0'; ++i);
    for (j = 0; s[i] = t[j] != '\0'; ++i, ++j);	// 良好习惯 2 和 7 的有力说明
    return s;
}

char* strcat(char* s, char* t) {
    while (*s) {
        ++s;
    }
    while (*s++ = *t++)
}
```

```c
// 删除 s 在 t 中出现的字符
char* squeeze(char* s, char* t) {
    int i, j, k;
    for (i = j = 0; s[i] != '\0'; ++i) {
        for (k = 0; t[k] != '\0' && s[i] != s[k]; ++k)	// 良好习惯 10 的有力说明，按照自己以往不好的代码风格，s[i] != s[k] 会放在循环体中
        if (t[k] == '\0') {
            s[j++] = s[i];
        }
    }
    s[j] = '\0';
    return s;
}
```

```c
for (i = 0; i < n; i++) {
    printf("%6d%c", a[i], (i % 10 == 9 || i == n - 1) ? '\n' : ' ');	// 使用三目运算符控制输出格式
}
```

# 第三章：控制流

## 一、优秀代码

```c
int atoi(char* s) {
    int i, sign, n;
    for (i = 0; isspace(s[i]); ++i);	// 良好习惯 2 的有力说明
    sign = s[i] == '-' ? -1 : 1;
    if (s[i] == '-' || s[i] == '+') {
        ++i;
    }
    for (n = 0; isdigit(s[i]); ++i) {
        n = n * 10 + (s[i] - '0');
    }
    return n;
}
```

```c
/**
将字符串 s1 中类似于 a-z 一类的速记符号在字符串 s2 中扩展为等价的完整列表 abc...xyz。该函数可以处理大小写字母和数字，并可以处理 a-b-c、a-z0-9 与 a-z 等类似的情况。作为前导和尾随的字符原样复制。
 * */

void expand(char s1[], char s2[]) {
    char c;
    int i, j;
    i = j = 0;
    while ((c = s1[i++]) != '\0') {				// 想一想自己会写出什么样的垃圾代码
        if (s1[i] == '-' && s1[i + 1] >= c) {
            i++;
            while (c < s1[i]) {
                s2[j++] = c++;
            }
        }else {
            s2[j++] = c;
        }
    }
    s2[j] = '\0';
}
```

```c
void itoa(int n, char* s) {
    int sign;
    int i = 0;
    if ((sign = n) < 0) {   // 记录符号并取绝对值
        n = -n;
    }
    do {					// 良好习惯 12 的有力说明
        s[i++] = n % 10 + '0';
    }while (n /= 10);
    if (sign < 0) {
        s[i++] = '-';
    }
    s[i] = '\0';
    reverse(s);
}
```

# 第四章：函数与程序结构

## 一、知识点

1. 程序可以看成是<u>变量定义</u>和<u>函数定义</u>的集合。

2. 如果要在「外部变量」<u>定义之前</u>使用该变量，或者外部变量的定义与变量的使用<u>不在同一个源文件</u>中，则必须在相应的变量声明中强制性低使用关键字`extern`。在一个源程序的所有源文件中，<u>一个外部变量只能在某个文件中定义一次</u>，而其他文件可以通过`extern`声明来访问它，对于外部数组来说，定义中必须指明长度，但`extern`声明则不一定要指定数组的长度。如要在同一个源文件中先使用后定义变量，也需要进行`extern`声明。

3. 对于头文件的组织考虑：

   + 一方面是每个文件只能访问它完成任务所需的声明信息。
   + 另一个方面是现实中维护较多的头文件比较困难。

   > 结论：对于某些中等规模的程序，最好只用一个头文件存放程序中各部分共享的对象。较大的程序需要使用更多的头文件，我们需要精心地组织它们。

4. `static`可修饰「变量」也可修饰「函数」。

5. `register`变量放在机器的「寄存器」中（`register`变量只适用于「自动变量」以及函数的「形式参数」），这样可以使程序更小、执行速度更快。<u>但编译器可以忽略此选项</u>。另外，无论寄存器变量是不是存放在寄存器中，<u>它的地址都是不能访问的</u>。

6. 「外部变量」和「静态变量」的初始化表达式必须是「常量表达式」。<u>自动变量的初始化等效于简写的赋值语句</u>。

7. 对于数组来说，如果<u>初始化表达式的个数比数组元素少</u>，则对外部变量、静态变量和自动变量来说，没有初始化表达式的元素将被初始化为`0`。对于字符数组来说，`char pattern[] = "ould"`的初始化相当于`char pattern[] = {'o', 'u', 'l', 'd', '\0'}`，数组长度是 5，但是使用`strlen`得出的值为 4，`'\0'`一般不算在内。

8. `#include <文件名>`将<u>根据相应的规则</u>查找该文件，这个规则同具体的实现有关；`#include "文件名"`将在<u>源文件所在位置</u>查找该文件，找不到就同<u>尖括号</u>一样到相应路径下面找。

9. 使用宏定义可以避免调用函数所需的运行时开销。`getchar`和`putchar`就是宏，其底层使用的是系统调用`getc`和`putc`。

## 二、优秀代码

```c
// 模式匹配
int strindex(char* s, char* t) {
    int i, j, k;

    for (i = 0; s[i] != '\0'; ++i) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; ++j, ++k) {}	// 良好习惯 2、10 的有力说明
        if (k > 0 && t[k] == '\0') {
            return i;
        }
    }
    return -1;
}
```

```c
double atof(char* s) {
    int i, sign;
    double answer = 0;

    for (i = 0; s[i] != '\0' && isspace(s[i]); ++i);    // 跳过空格
    sign = s[i] == '-' ? -1 : 1;
    if (s[i] == '-' || s[i] == '+') {
        ++i;
    }
    for (; isdigit(s[i]); ++i) {
        answer = answer * 10.0 + s[i] - '0';
    }
    if (s[i] == '.') {
        ++i;
    }
    double power;
    for (power = 1.0; isdigit(s[i]); ++i) {
        answer = answer * 10.0 + s[i] - '0';
        power *= 10.0;
    }
    answer = answer * sign / power;
    if (s[i] == 'e' || s[i] == 'E') {
        ++i;
        sign = s[i] == '-' ? -1 : 1;
        if (s[i] == '-' || s[i] == '+') {
            ++i;
        }
        int exp;
        for (exp = 0; isdigit(s[i]); ++i) {
            exp = exp * 10 + s[i] - '0';
        }
        if (sign == 1) {
            while (exp--) {
                answer *= 10.0;
            }
        }else {
            while (exp--) {
                answer /= 10.0;
            }
        }
    }
    return answer;
}
```

```c
#define MAXOP  100
#define NUMBER '0'

int getop(char* op);
int getch(void);
void ungetch(int);
void push(double value);
double pop(void);

int main(int argc, char* argv[]) {
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                push(pop() / op2);
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: xxxxxxxxxxxxx");
                break;
        }
    }
    return 0;
}

int getop(char s[]) {
    int c, i;

    while ((s[0] = c = getch()) == ' ' || c == '\t');
    s[1] = '\0';
    i = 0;
    if (!isdigit(c) && c != '.' && c != '-') {
        return c;
    }
    if (c == '-') {
        if (isdigit(c = getch()) || c == '.') {
           s[++i] = c;
        }else {
            if (c != EOF) {
                ungetch(c);
            }
            return '-';
        }
    }
    if (isdigit(c)) {
        while (isdigit(s[++i] = c = getch()));
    }
    if (c == '.') {
        while (isdigit(s[++i] = c = getch()));
    }
    s[i] = '\0';
    if (c != EOF) { // 因为最后一个插入 s[] 的字符是多余的
        ungetch(c);
    }
    return NUMBER;
}

#define BUFFSIZE 100
static int bp;
static int buf[BUFFSIZE];

int getch() {
    return bp > 0 ? buf[--bp] : getchar();
}

void ungetch(int c) {
    if (bp < BUFFSIZE) {
        buf[bp++] = c;
    }else {
        printf("error: xxxxxxxxxxxxxxxxxxxxxxxx");
    }
}

#define STACKSIZE 100
static int sp;
static double stack[STACKSIZE];

void push(double value) {
    if (sp < STACKSIZE) {
        stack[sp++] = value;
    }else {
        printf("error: xxxxxxxxxxxxxxxxxxx");
    }
}

double pop(void) {
    if (sp > 0) {
        return stack[--sp];
    }else {
        printf("error: xxxxxxxxxxxxxxxxx");
        return 0.0;
    }
}
```

# 第五章：指针与数组

## 一、知识点

1. 数组名所代表的就是该数组<u>首元素地址</u>，<u>数组名直接可以像指针一样使用</u>，但是数组名不是写成`a++`或者`a = pa`的形式。
2. `a[i]`会被转换为`*(a + i)`，所以使用指针的效率比使用数组下标的<u>效率</u>高。
3. 指针与整数之间不能相互转换，但`0`是唯一的例外：常量`0`可以赋值给指针，指针也可以和常量`0`进行比较。程序中经常用符号常量`NULL`代替常量`0`。
4. 头文件`<stddef.h>`中定义的类型`ptrdiff_t`足以表示两个指针之间的带符号差值。
5. `char amessage[] = "now is the time"`是一个仅仅足以存放初始化字符串以及空字符`'\0'`的一维数组。<u>数组中的单个字符可以进行修改</u>，`amessage`作为数组名始终指向同一个存储位置；`char* pmessage = "now is the time"`是一个指针，其初值指向一个「字符串常量」，<u>之后它可以被修改以指向其他地址，但是其不能修改字符串的内容</u>。
6. <u>凡是指针都可以使用下标运算</u>，不管是`int*`还是`int *[]`。
7. 指针数组：`int *array[10]`里面每个元素都是指针；数组指针：`int (*array)[10]`一个`int*`指针，该指针指向一片具有 10 个元素的空间，<u>二维数组中的每一纬度都是一个数组指针</u>。
8. 如果将二维数组作为参数传递给函数，那么在函数的参数声明中必须<u>指明数组的列数</u>，在参数列表中声明二维数组的方式：`f(int array2[2][13])`或`f(int array2[][13])`或`f(int (*array2)[13])`，另外，二维数组的数组名就相当于一个<u>二级指针</u>。
9. 若有定义`int a[10][20]`和`int *b[10]`，则`a[3][4]`和`b[3][4]`都是对一个`int`对象的合法引用，对于`b`来说，`b[3]`得到一个`int*`，`b[3][4]`则得到`int*`前面的第 4 个`int`对象。
10. 指针数组的一个重要优点在于数组的每一行长度可以不同。

## 二、优秀代码

```c
int strlen(char* s) {
    int n;
    for (n = 0; *s != '\0'; ++s) {
        ++n;
    }
    return n;
}

int strlen(char* s) {
    int i;
    for (i = 0; s[i] != '\0'; ++i);
    return i;
}
```

```c
void strcpy(char* s, char* t) {
    while ((*s++ = *t++));	// 良好习惯 1、6、7 的有力说明
}
```

```c
int strcmp(char* s, char* t) {
    while (*s++ == *t++) {	// 良好习惯 2、7 的有力说明
        if (*s == '\0') {
            return 0;
        }
    }
    return s - t;
}
```

```c
// 指针版本
char* strcat(char* s, char* t) {
    while (*s) {
        ++s;
    }
    while (*s++ = *t++)
}

int getline(char* s, int lim) {
    int c;
    char* t = s;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
        *s++ = c;
    }
    if (c == '\n') {
        *s++ = c;
    }
    *s = '\0';
    return s - t;
}

int atoi(char* s) {
    int n, sign;
    for (; isspace(*s); ++s);
    sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-') {
        s++;
    }
    for (n = 0; isdigit(*s); s++) {
        n = 10 * n + *s - '0';
    }
    return sign * n;
}

void itoa(int n, char* s) {
    int sign;
    char* t = s;
    if ((sign = n) < 0) {
        n = -n;
    }
    do {
        *s++ = n % 10 + '0';
    }while ((n /= 10) > 0);
    if (sign < 0) {
        *s++ = '-';
    }
    *s = '\0';
    reverse(t);
}

int strindex(char* s, char* t) {
    char* b = s;
    char* p, *r;

    for (; *s != '\0'; s++) {
        for (p = s, r = t; *r != '\0' && *p == *r; p++, r++);
        if (r > t && *r == '\0') {
            return s - b;
        }
    }
    return -1;
}

double atof(char* s) {
    double val, power;
    int sign;

    for (; isspace(*s); s++);
    sign = *s == '-' ? -1 : 1;
    if (*s == '+' || *s == '-') {
        s++;
    }
    for (val = 0.0; isdigit(*s); s++) {
        val = val * 10.0 + (*s - '0');
    }
    if (*s == '.') {
        s++;
    }
    for (power = 1.0; isdigit(*s); s++) {
        val = val * 10.0 + (*s - '0');
        power *= 10.0;
    }
    return sign * val / power;
}

int getop(char* s) {
    int c;

    while ((*s = c = getch()) == ' ' || c == '\t');
    *(s + 1) = '\0';
    if (!isdigit(c) && c != '.') {
        return c;
    }
    if (isdigit(c)) {
        while (isdigit(*++s = c = getch()));
    }
    if (c == '.') {
        while (isdigit(*++s = c = getch()));
    }

    *s = '\0';
    if (c != EOF) {
        ungetch(c);
    }
    return NUMBER;
}
```

```c
void echo(int argc, char* argv[]) {
    while (--argc > 0) {
        printf("%s%s", *++argv, argc  > 1 ? " " : "");
    }
    printf("\n");
}
```

```c
#define MAXLINE 100

int mygetline(char*, int);

int find(int argc, char* argv[]) {
    int c;
    int except = 0, number = 0, found = 0;

    while (--argc > 0 && (*++argv)[0] == '-') {		// 结合运算符优先级好好体会 (*++argv[0]) 和 *++argv[0]
        while ((c = *++argv[0])) {
            switch (c) {
                case 'x':
                    except = 1;
                    break;
                case 'n':
                    number = 1;
                    break;
                default:
                    printf("find: illegal option %c\n", c);
                    argc = 0;
                    found = -1;
                    break;
            }
        }
    }
    if (argc != 1) {
        printf("error:xxxxxxxxxxxxxx");
        return found;
    }else {
        int lineno = 0;
        char line[MAXLINE];
        while ((mygetline(line, MAXLINE)) > 0) {
            lineno++;
            if ((strstr(line, *argv) != NULL) != except) {
                if (number) {
                    printf("%d ", lineno);
                }
                printf("%s\n", line);
                ++found;
            }
        }
    }
    return found;
}
```

```c
#define MAXLINES 5000
char* lineptr[MAXLINES];

int readlines(char* lineptr[], int nlines);
void writelines(char* lineptr[], int nlines);

void qsort(void* lineptr[], int left, int right, int (*comp)(void*, void*));
int numcmp(char*, char*);

int main(int argc, char* argv[]) {
    int nlines;
    int numeric = 0;

    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        numeric = 1;
    }
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort((void**)lineptr, 0, nlines - 1, (int (*)(void*, void*)) (numeric ? numcmp : strcmp)); // 函数指针的用法
        writelines(lineptr, nlines);
        return 0;
    }else {
        printf("input too big to sort\n");
        return 1;
    }
    return 0;
}
```

# 第六章：结构

## 一、知识点

1. 「结构」的初始化可以在定义的后面使用初值表进行。初值表中同每个成员对应的<u>初值必须是常量表达式</u>。
2. 「结构」之间不能进行比较。
3. `sizeof 对象`和`sizeof 类型名`是等价的。
4. 条件编译语句`#if`中不能使用`sizeof`，因为预处理器不对类型名进行分析。但预处理器并不计算`#define`语句中的表达式，所以在`#define`中使用`sizeof`是合法的。
5. 可以取<u>数组最后一个元素</u>的地址，即`&array[n]`是合法的。
6. 结构中可以存在<u>自身结构类型的指针</u>，但不能存在自身结构类型的<u>变量</u>。

## 二、优秀代码

```c
#define MAXWORD 100

struct key {
    char* word;
    int count;
} keytab[] = {
    {"auto", 0}
};

#define LEN (sizeof keytab / sizeof keytab[0])

int getword(char*, int);
int binsearch(char*, struct key*, int);

int main() {
    int n;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            if ((n = binsearch(word, keytab, LEN))) {
                ++keytab[n].count;
            }
        }
    }
    return 0;
}

int getword(char* word, int maxword) {
    int c, getch(void);
    void ungetch(int);
    char* w = word;
    
    while (isspace(c = getch()));
    if (c != EOF) {
        *w++ = c;		// 良好习惯 17 的有力说明
    }
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for (; --maxword > 0; w++) {
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
}
```

# 第七章：输入与输出

## 一、知识点

1. 「标准库」并不是 C 语言本身的组成部分。
2. 如果程序`prog`中使用了<u>标准输入函数</u>，`prog <infile`将使得程序从输入文件 infile（而不是键盘）中读取字符；另外，`otherprog | prog`使得`prog`从程序`otherprog`的标准输出上读取字符。
3. 类比第 2 点，`prog >输出文件名`和`prog | anotherprog`将`prog`的标准输出进行了重定向。
4. `int printf(char* format, ...);`返回值为打印的字符数，在字符`%`和<u>转换字符</u>中间可能依次包含下列组成部分：
   - 负号，用于指定被转换的参数按照左对齐的形式输出。
   - 数，用于指定最小字段宽度。转换后的参数将打印不小于最小字段宽度的字段。如果有必要，字段左边（如果使用左对齐的方式，则为右边）多余的字符位置用空格填充以保证最小字段宽。
   - 小数点，用于将字段宽度和精度分开。
   - 数，用于指定精度，即指定字符串中要打印的最大字符数、浮点数小数点后的位数、整型最少输出的数字数目。
   - 字母 h 或 l，字母 h 表示将整数作为`short`类型打印，字母 l 表示将整数作为`long`类型打印。
5. `scanf`返回成功匹配并赋值的输入项的个数，下一次调用`scanf`或其他输入函数将从上一次转换的最后一个字符的下一个字符开始继续搜索，如果到达文件末尾，返回`EOF`。
6. `scanf`函数忽略「格式串」中的空格和制表符，在读取输入值时，它将<u>跳过</u>空白符。
7. `fopen`返回的指针`FILE*`指向一个包含文件信息的结构，这些信息包括：缓冲区的位置、缓冲区中当前字符的位置、文件的读或写状态、是否出错或是否已经到达文件结尾等等。
8. 启动一个 C 语言程序时，操作系统环境负责打开 3 个文件，并将这 3 个文件的`FILE*`常量指针提供给该程序。这 3 个文件分别是<u>标准输入`stdin`</u>、<u>标准输出`stdout`</u>和<u>标准错误`stderr`</u>。

## 二、优秀代码

```c
// 变长参数
#include <stdio.h>
#include <stdarg.h>

void minprintf(char* fmt, ...) {
    va_list ap;
    char *p, *sval;
    int ival;
    double dval;

    va_start(ap, fmt);
    for (p = fmt; *p; ++p) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch (*++p) {
            case 'd':
                ival = va_arg(ap, int);
                printf("%d", ival);
                break;
            case 'f':
                dval = va_arg(ap, double);
                printf("%f", dval);
                break;
            case 's':
                for (sval = va_arg(ap, char*); *sval; ++sval) {
                    putchar(*sval);
                }
                break;
            default:
                putchar(*p);
                break;
        }
    }
    va_end(ap);
}
```

```c
#include <stdio.h>

void filecopy(FILE*, FILE*);

int main(int argc, char* argv[]) {
    if (argc == 1) {
        filecopy(stdin, stdout);
    }else {
        FILE* fp;		// 良好习惯 18 的有力说明
        while (--argc) {
            if ((fp = fopen(*++argv, "r")) == NULL) {
                printf("error: xxxxxxxxxxxxxxxxxx");
                return 0;
            }else {
                filecopy(fp, stdout);
                fclose(fp);
            }
        }
    }
    return 0;
}

void filecopy(FILE* in, FILE* out) {
    int c;
    while((c = getc(in)) != EOF) {
        putc(c, out);
    }
}
```

```c
#include <stdio.h>

char* fgets(char* s, int n, FILE* iop) {
    register int c;
    register char* cs = s;
    while (--n > 0 && (c = getc(iop)) != EOF) {
        if ((*cs++ = c) == '\n') {
            break;
        }
    }
    *cs = '\0';
    return (c == EOF && cs == s) ? NULL : s;
}

int fputs(char* s, FILE* iop) {
    int c;
    while (c = *s++) {
        putc(c, iop);
    }
    return ferror(iop) ? EOF : 1;
}
```

# 第八章：UNIX 系统接口

## 一、知识点

1. 系统调用是操作系统内的函数，它们可以被用户程序调用，C 标准库是以 UNIX 系统为基础建立起来的。
2. 第七章介绍的输入/输出接口对任何操作系统都是一样的，只是这些函数使用的输入/输出系统调用可能不一样。
3. 「标准库」操作文件使用的是文件指针`FILE*`，系统调用操作文件使用的是「文件描述符」。
4. 相对于标准库使用的文件指针`stdin`、`stdout`、`stderr`，系统调用相应的文件描述符是`0`、`1`、`2`。
5. 输入输出重定向格式：`prog <输入文件名>输出文件名`。
6. 每次调用`read`和`write`进行读写的位置紧跟在前一次操作的位置之后。
6. 函数返回`EOF`不一定是到达了文件末尾，读取文件失败时也有可能返回`EOF`，所以用函数`feof`来代替`EOF`是最正确的做法。

# 良好习惯

1. 赋值语句可以用做条件判断，需要注意`!=`和`=`的优先级问题。
2. `for`和`while`的选择：有初始化过程时选择`for`，个人认为由于`for`拥有 3 个部分，如果使用`for`能让程序更简洁，但是如果<u>只包含判断条件</u>或者<u>迭代部分可以合并到判断条件时</u>则用`while`更清新，因为缺少迭代部分，可能`while`的效率比`for`高。
3. 变量名使用小写字母，「符号常量」全部使用大写字母，程序中的「符号常量」都用宏定义来代替，<u>宏定义中的每个部分都用括号包裹</u>。
4. `++nc`的效率高于`nc = nc + 1`。
5. 对于`if`和`else if`的<u>执行语句相同</u>的情况下，可以使用`||`来代替。
6. 可以用`'\0'`用作条件判断。
7. 「前缀/后缀」运算符配合<u>数组下标</u>和<u>指针</u>使用。
8. 头文件中<u>只存放</u>变量和函数的`extern`声明，所有定义都应该只存在于「源文件」。
9. <u>无初始化</u>和<u>有初始化</u>的变量分在不同的行。
10. 在`for`和`while`循环中注意<u>合并判断条件</u>，比如循环体中存在`if(xxx){break;}`语句可以将`xxx`合并在循环的判断条件中。
11. 不要把<u>执行结果</u>和<u>代码的执行顺序</u>挂钩，比如`k = f() + g()`和`a[i] = i++`。
12. 当值为`0`时都需要进行至少 1 次循环时应该使用`do-while`。
13. 程序应该由<u>许多小的函数</u>组成，而不是由<u>少量较大的函数</u>组成。
14. 函数没有参数时应该这么声明`int func(void)`。
15. 避免出现「变量名」隐藏外部作用域中相同名字的情况，否则，很可能引起混乱和错误。
16. 进栈和出栈的标准写法：`*p++ = val; val = *--p;`
17. 多利用指针的「自增」、「自减」来进行编写程序。
18. 变量在临近使用之前再进行定义。

# 标准库常用 API 总结

## 一、输入输出

```c
#define getchar() getc(stdin)
int getchar(void);

#define putchar(c) putc((c), stdout)
int putchar(int);

int printf( const char *restrict format, ... );

int sprintf(char *string, char *format [,argument,...]);

int fprintf (FILE* stream, const char* format, [argument])

int scanf(const char * restrict format,...);

int sscanf(const char *buffer, const char *format, [ argument ] ...   );

int fscanf(FILE *stream, char *format[,argument...]);

int getc(FILE *stream);

int putc(int c, FILE* fp);

int ungetc(int c, FILE* fp);

FILE* fopen(char* name, char* mode);

int fclose(FILE* fp);

int ferror(FILE* fp);

int feof(FILE* fp);

char* fgets(char* line, int maxline, FILE* fp);

char *gets(char *str);

int puts(const char *string);

int fputs(char* line, FILE* fp);

size_t fread ( void *ptr, size_t size, size_t count, FILE *fp );

size_t fwrite ( void * ptr, size_t size, size_t count, FILE *fp );
```

## 二、计算

```c
double pow( double x, double y );

double sqrt(double);

double fabs(double x );

double log (double x);

double log10(double x);

double exp(double x);

int bitcount(int x);

int abs(int i);

char *itoa (int value, char *str, int base);

void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*))
    
int system(char *command);
```

## 三、字符相关

```c
int isdigit(int c);

int isalpha(int c);

int isalnum(int c);

int isspace(int c);

int isupper(char c);

int islower(int c);

size_t strlen(const char *string);

char *strcat(char *dest, const char *src);

int tolower(int c);

int toupper(int c);

void trim(char *s);

char *strstr(char *str1, const char *str2);

int atoi(const char *nptr);

double atof(const char *nptr);

char *strcpy(char* dest, const char *src);

int strcmp(const char *s1,const char *s2);

char *strchr(const char *str, int c);

char *strrchr(const char *str, int c);
```

## 四、空间分配

```c
void* malloc(size_t n);

void* calloc(size_t n, size_t size);

void *realloc( void *ptr, size_t new_size );

void free(void *ptr)
```

## 五、其他

```c
int rename(const char *oldname, const char *newname);
```

```c
// 每种 errno 对应一种错误
char *strerror(int errno);
void perror(const char *str)；
```

# 系统调用常用 API 总结

## 一、低级 I/O

```c
ssize_t read (int fd, void *buf, size_t count);

int write(int handle, void *buf, int nbyte);

void error (int status, int errnum, const char *format，...);

long lseek(int fd, long offset, int origin);
```

## 二、打开文件

```c
int open(char* name, int flags, int perms);

int creat(char*name, int perms);

int close(int fd);

int stat(char*, struct stat*);
```

