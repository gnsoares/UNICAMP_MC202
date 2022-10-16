#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 50000
#define MAX_WORDS 1000
#define MAX_LEN 50

/* function that takes a substring from a source string to a destination string
 @param dest destination string
 @param src source string
 @param beg beginning inclusive index
 @param end end exclusive index
 @return destination string
 */
char * substr(char * dest, const char * src, int beg, int end) {
	int j = 0;
	
	for (int i = beg; i < end && src[i] != '\0'; i++)
		dest[j++] = src[i];
	for (; j < MAX_LEN; j++)
		dest[j] = '\0';

   return dest;
}

/* function that leaves only the letters and spaces from a source string
 in a destination string
 @param dest destination string
 @param src source string
 @return destination string
 */
char * rm_ponct(char * dest, const char * src) {
	int i;
	
	for (i = 0; src[i] != '\0'; i++)
		if ((src[i] >= 65 && src[i] <= 90) || (src[i] >= 97 && src[i] <= 122) || (src[i] == ' '))
			dest[i] = src[i];
		else
			dest[i] = ' ';
	dest[i] = '\0';

	return dest;
}

int main() {

	int msg_n, len, msg_index, n_words = 1;
	int * word_beg_arr, * word_end_arr; // holds indices of the beginning and end of words
	char * original_msg, * no_ponct_msg; // strings
	char ** words; // array of words

	// memory allocation
	original_msg = malloc(MAX_STR*sizeof(char)); if (!original_msg) exit(1);
	no_ponct_msg = malloc(MAX_STR*sizeof(char)); if (!no_ponct_msg) exit(1);

	// input reading
	fgets(original_msg, MAX_STR, stdin);
	for (int i = 0; i < MAX_STR; i++)
		if (original_msg[i] == '\n') {
			original_msg[i] = '\0';
			break;
		}
	scanf("%d", &msg_n);

	// processing of the input
	rm_ponct(no_ponct_msg, original_msg);
	len = strlen(no_ponct_msg);

	// establishment of control variables
	for (int i = 1; i < len; i++)
		// if this is a space and the next char is a letter a word is beginning
		if ((no_ponct_msg[i] == ' ')
			&& ((no_ponct_msg[i+1] >= 65 && no_ponct_msg[i+1] <= 90) || (no_ponct_msg[i+1] >= 97 && no_ponct_msg[i+1] <= 122)))
				n_words++;

	// more memory allocation
	word_beg_arr = malloc(n_words*sizeof(int)); if (!word_beg_arr) exit(1);
	word_end_arr = malloc(n_words*sizeof(int)); if (!word_end_arr) exit(1);
	words = malloc(n_words*sizeof(char *)); if (!words) exit(1);
	for (int i = 0; i < n_words; i++) {
		words[i] = malloc(MAX_LEN*sizeof(char)); if (!words[i]) exit(1);
	}

	word_beg_arr[0] = 0;
	word_end_arr[n_words-1] = len;
	for (int i = 1, j = 0; i < len && j < n_words; i++)
		// if this is a space we're between words
		if (no_ponct_msg[i] == ' ') {
			// if the previous char is a letter its an end
			if ((no_ponct_msg[i-1] >= 65 && no_ponct_msg[i-1] <= 90)
				|| (no_ponct_msg[i-1] >= 97 && no_ponct_msg[i-1] <= 122)) {
				word_end_arr[j++] = i;				
			}
			// if the next char is a letter its a beginning
			if ((no_ponct_msg[i+1] >= 65 && no_ponct_msg[i+1] <= 90)
				|| (no_ponct_msg[i+1] >= 97 && no_ponct_msg[i+1] <= 122)) {			
				word_beg_arr[j] = i + 1;
			}
		}

	// taking substrings
	for (int i = 0; i < n_words; i++)
		substr(words[i], no_ponct_msg, word_beg_arr[i], word_end_arr[i]);

	// printing the decoded message
	for (int i = 0; i < msg_n; i++) {
		scanf("%d", &msg_index);
		printf(i == msg_n - 1 ? "%s\n" : "%s ", words[msg_index]);
	}

	// memory liberation
	free(original_msg);
	free(no_ponct_msg);
	free(word_beg_arr);
	free(word_end_arr);
	for (int i = 0; i < n_words; free(words[i++]));
	free(words);

	return 0;
}
