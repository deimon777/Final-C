#ifndef _STRING_EXTRA_H
#define	_STRING_EXTRA_H

char * str_replace(char *orig, char *en, char *con);
void remove_spaces(char *source);
void str_lower(char *source);
char *read_line(FILE *fp);

#endif	/* _STRING_EXTRA_H */
