#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int links(char *arg) {
	DIR *dir = opendir(arg);
	struct dirent *entry = readdir(dir);
	char path[256];
	struct stat buf;
	while (entry != NULL) {
		if (entry->d_name[0] != '.') {
			strcpy(path, arg);
			strcat(path, "/");
			strcat(path, entry->d_name);
			stat(path, &buf);
			printf("%lu  %s\n", buf.st_nlink, path);
			if (entry->d_type == 4)
				links(path);
		}
		entry = readdir(dir);
	}
	return 0;
}

int main(int argc,char *argv[]) {
	if (argc < 2) {
		printf("Usage: ./links catalog\n");
		return -1;
	}
	links(argv[1]);
	return 0;
}
