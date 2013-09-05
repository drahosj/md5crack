#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>

int check_equals(char * test, unsigned char * target) {
	MD5_CTX context;
	unsigned char raw_hash[MD5_DIGEST_LENGTH];

	MD5_Init(&context);
	MD5_Update(&context, test, strlen(test));
	MD5_Final(raw_hash, &context);

	/*int i;
	for (i = 0; i < MD5_DIGEST_LENGTH; i++) {
		printf("%02x", target[i]);
	}
	printf("\n");*/


	if (memcmp(target, raw_hash, MD5_DIGEST_LENGTH)) return 0;
	return -1;
}
int doBruteForce( 	char *namespace, 
			unsigned char *target, 
			int depth,
	       		char *str, 
			int max) {

	int i, p;
	for (i = 0; i < strlen(namespace); i++ ) {
		str[depth] = namespace[i];
		if (depth == max) {
			if (check_equals(str, target)) return -1;	
		} else {
			p = doBruteForce(namespace, target, depth + 1, str, max); 
			if (p == -1) return -1;
		}
	}
	return 0;
}
int main(int argc, char **argv) {
	unsigned char target_hash[MD5_DIGEST_LENGTH];
	
	char * target_string = argv[1];
	unsigned char *dst = target_hash;
	unsigned char *end = target_hash + strlen(target_string);
	unsigned int tmp;

	while (dst < end) {
		sscanf(target_string, "%2x", &tmp);
		
		*dst = tmp;
		dst++;
		target_string += 2;
	}
	//if (check_equals(argv[2], target_hash)) printf("Success!\n");
	
	char *namespace = "abcdefghijklmnopqrstuvwxyz";
	char test[atoi(argv[2])];

	test[0] = 0;
	int i;
	for(i = 0; i < atoi(argv[2]); i++) {
		test[i+1] = 0;
		if (doBruteForce(namespace, target_hash, 0, test, i)) {
		       	printf("Match found: %s\n", test);
			break;
		}
	}
/*	int i;
	for (i = 0; i < MD5_DIGEST_LENGTH; i++) {
		printf("%02x", target_hash[i]);
	}
	printf("\n");*/
	
}
