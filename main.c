#include <stdio.h>
#include <string.h>

#define TABLE_SIZE 10

void remove_linefeed(char *buf)
{
  char *p = strchr(buf, '\n');
  if (p) {*p = '\0';}
}

int calc_hash(char *str)
{
    int sum = 0;
    while(*str){sum += *str++;}
    
    return sum % TABLE_SIZE; 
}

int main(int argc, char *argv[]) 
{
    char str[512];
    char hash_table[TABLE_SIZE][512];
    
    // テーブルの初期化
    for(int i = 0; i < TABLE_SIZE; i++){
        hash_table[i][0] = '\0';
    }
    
    while(fgets(str, sizeof(str), stdin)){
        remove_linefeed(str);
        if(str[0] == '\0'){
            // テーブルを表示
            for(int i = 0; i < TABLE_SIZE; i++){
                if(i != 0)printf(",");
                printf("%s", hash_table[i]);
            }
            printf("\n");
        }else{
            // データの格納
            int k = calc_hash(str);
            for(int i = 0; i < TABLE_SIZE; i++){
                if(hash_table[k][0] == '\0'){
                    strcpy(&hash_table[k][0], str);
                    break;
                }
                k = (TABLE_SIZE <= ++k) ? 0 : k;
            }
        }
    }

    return 0;
}
