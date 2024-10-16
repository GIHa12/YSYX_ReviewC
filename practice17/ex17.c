#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512 //姓名和邮箱的最大字节数
#define MAX_ROWS 100 //最大数据条数

struct Address { //1024+8 Byte+4 Byte
    int id; // 4Byte
    int set; // 4Byte
    char name[MAX_DATA];//512Byte
    char email[MAX_DATA];//512Byte
    char test; //1Byte+[3Byte] = 4Byte
};

struct Database {
    struct Address rows[MAX_ROWS]; 
    //100*1024Byte + 100*8Byte +100*4Byte  = 103200Byte+400Byte  = 100.78KB /101.17KB
    //但是在磁盘中存储的时候根据块大小对其原理，通过du -ah --max-depth=1命令可以看到最小块大小为4K，
    //因此即使此处计算出来的大小为100.78K也会扩充到104KB进行存储
};

struct Connection {
    FILE *file;
    struct Database *db;
};
void Database_close(struct Connection *conn);
void die(const char *message,struct Connection *conn)
{
    if(errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }
    if(conn!=NULL)
    {
        Database_close(conn);
    }
    
    exit(1);
}

void Address_print(struct Address *addr)
{
    printf("%d %s %s\n",
            addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn)
{
    int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
    if(rc != 1) die("Failed to load database.",conn);
}

struct Connection *Database_open(const char *filename, char mode)
{
    struct Connection *conn = malloc(sizeof(struct Connection));
    if(!conn) die("Memory error",conn);

    conn->db = malloc(sizeof(struct Database));
    if(!conn->db) die("Memory error",conn);

    if(mode == 'c') {
        conn->file = fopen(filename, "w");
    } else {
        conn->file = fopen(filename, "r+");

        if(conn->file) {
            Database_load(conn);
        }
    }

    if(!conn->file) die("Failed to open the file",NULL);

    return conn;
}

void Database_close(struct Connection *conn)
{
    if(conn) {
        if(conn->file) fclose(conn->file);
        if(conn->db) free(conn->db);
        free(conn);
    }
}

void Database_write(struct Connection *conn)
{
    rewind(conn->file); //设置文件位置为给定流的文件的开头

    int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
    printf("siezof Database is %ld Byte\n",sizeof(struct Database));
    if(rc != 1) die("Failed to write database.",conn);

    rc = fflush(conn->file); //刷新流的输出缓冲区
    if(rc == -1) die("Cannot flush database.",conn);
}

void Database_create(struct Connection *conn)
{
    int i = 0;

    for(i = 0; i < MAX_ROWS; i++) {
        // make a prototype to initialize it
        struct Address addr = {.id = i, .set = 0};
        // then just assign it
        conn->db->rows[i] = addr;
    }
}

//向数据库中添加一条数据
void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
    struct Address *addr = &conn->db->rows[id];
    if(addr->set) die("Already set, delete it first",conn);

    addr->set = 1;
    // WARNING: bug, read the "How To Break It" and fix this
    //strncpy没有自动加上终止符‘\n’，需要手动加上
    int length = sizeof(name)/sizeof(char);
    char *res = strncpy(addr->name, name, MAX_DATA);
    addr->name[length] = '\n';
    // demonstrate the strncpy bug
    if(!res) die("Name copy failed",conn); //复制姓名
    length = sizeof(email)/sizeof(char);
    res = strncpy(addr->email, email, MAX_DATA);
    addr->name[length] = '\n';
    if(!res) die("Email copy failed",conn); //复制邮箱
}

void Database_get(struct Connection *conn, int id)
{
    struct Address *addr = &conn->db->rows[id];

    if(addr->set) {
        Address_print(addr);
    } else {
        die("ID is not set",conn);
    }
}

void Database_delete(struct Connection *conn, int id)
{
    struct Address addr = {.id = id, .set = 0}; //除了ID和set标志，其他不扶植，默认为""
    conn->db->rows[id] = addr; //重置信息
}

//遍历数据库，打印所有存入的数据
void Database_list(struct Connection *conn)
{
    int i = 0;
    struct Database *db = conn->db;

    for(i = 0; i < MAX_ROWS; i++) {
        struct Address *cur = &db->rows[i];

        if(cur->set) {
            Address_print(cur);
        }
    }
}

void Database_find_id(struct Connection *conn,int id)
{
    struct Database *db = conn->db;
    for(int i = 0;i<MAX_ROWS;i++)
    {
        struct Address *cur = &db->rows[i];
        if(cur->set && cur->id == id)
        {
            printf("find result: ");
            Address_print(cur);
        }
        else if(i == MAX_ROWS-1)
        printf("your database have no one's id is %d\n",id);

    }

}

int main(int argc, char *argv[])
{
    if(argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]",NULL);

    char *filename = argv[1];
    char action = argv[2][0];
    struct Connection *conn = Database_open(filename, action);
    int id = 0;

    if(argc > 3) id = atoi(argv[3]); //atoi函数在命令行中接受作为id的字符串并把它转换为int id变量
    if(id >= MAX_ROWS) die("There's not that many records.",conn);

    switch(action) {
        case 'c':
            Database_create(conn);
            Database_write(conn);
            break;

        case 'g':
            if(argc != 4) die("Need an id to get",conn);

            Database_get(conn, id);
            break;

        case 's':
            if(argc != 6) die("Need id, name, email to set",conn);

            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;

        case 'd':
            if(argc != 4) die("Need id to delete",conn);

            Database_delete(conn, id);
            Database_write(conn);
            break;

        case 'l':
            Database_list(conn);
            break;
        case 'f':
            if(argc != 4) die("Need an id to get",conn);
            Database_find_id(conn,id);
            break;
        
        default:
            die("Invalid action, only: c=create, g=get, s=set, d=del, l=list",conn);
    }

    Database_close(conn);

    return 0;
}