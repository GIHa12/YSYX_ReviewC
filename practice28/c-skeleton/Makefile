CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
#OPTFLAGS变量可以让使用者按需扩展构建选项
LIBS=-ldl $(OPTLIBS)
PREFIX?=/usr/local
#使用make命令时，扩展构建：
#$ make PREFIX=/tmp install
#$ make OPTFLAGS=-pthread
#传入匹配Makefile中相同名称的变量，它们会在构建中生效。你可以利用它来修改Makefile的运行方式
#第一条命令改变了PREFIX，使它安装到/tmp。第二条设置了OPTFLAGS，为之添加了pthread选项。

SOURCES=$(wildcard src/**/*.c src/*.c)#搜索src文件夹中所有的*.c文件
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))#获取SOURCE对象中的所有*.c文件把所有%.c扩展为%.o

TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

TARGET=build/libYOUR_LIBRARY.a#设置最终目标为指定的库文件
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

# The Target Build
all: $(TARGET) $(SO_TARGET) tests #make 没有提供目标的时候，默认运行第一个目标，此处为all

dev: CFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS) #开发者构建？
dev: all

$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS) #描述TARGET的依赖文件,$@表示构建的目标此处指的是$(TARGET)
	ar rcs $@ $(OBJECTS)   
	ranlib $@ 
#运行ranlib库


$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

build: #创建文件夹，且用@修饰，不显示该命令
	@mkdir -p build  
	@mkdir -p bin

################################# The Unit Tests ########################################
.PHONY: tests
tests: CFLAGS += $(TARGET) #将TARGET添加到构建中，于是每个测试程序都会链接TARGET库。
tests: $(TESTS)
	sh ./tests/runtests.sh

valgrind:
	VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE)

# The Cleaner
clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f tests/tests.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

# The Install
install: all #通常指的是/usr/local/lib
	install -d $(DESTDIR)/$(PREFIX)/lib/ 
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

# The Checker
BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)'
check:
	@echo Files with potentially dangerous functions.
	@egrep $(BADFUNCS) $(SOURCES) || true