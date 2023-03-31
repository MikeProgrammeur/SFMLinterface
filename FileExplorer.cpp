#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <iostream>
using namespace std;

void listFiles(DIR* dir) {
    

    struct dirent* entity;
    entity = readdir(dir);
    while (entity != NULL) {
        printf("%s \n",entity->d_name);
        entity = readdir(dir);
    }

    
}

int main(int argc, char* argv[]) {
    std::string request = "0";
    DIR* dir = opendir(".");
    if (dir == NULL) {
        return 0;
    }
    printf("Reading files in: %s\n", telldir(dir));
    for(int i = 0; i<2;i++){
        //rewinddir(dir);
        long int test = telldir(dir);
        listFiles(dir);
        //cin>>request;
        seekdir(dir,test);
        cout<<"!!!passage!!!\n";

    };
    closedir(dir);
    return 0;
}