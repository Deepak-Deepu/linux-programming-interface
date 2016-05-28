#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<malloc.h>

extern char **environ;


int setenv(const char *envname, const char *envval, int overwrite)
{
	char *Newentry;
	char **Enventry;

	if(envname == NULL || envname[0] == '\0') {
		errno = EINVAL;
		return -1;
	}

	if(strchr(nvname, '=') != NULL) {
		errno = EINVAL;
		return -1;
	}

	for(Enventry=environ; *Enventry != NULL; Envemtry++) {
		
		if(strcmp(*Enventry,envname,strlen(envname)) == 0 &&
 		*Enventry[strlen(envname)] == '=') {
			if(overwrite == 0)
				return 0;
			break;
		}
	}

	Newentry = malloc(strlen(envname) + strlen(envval) + 2);
	sprintf(Enventry, "%s=%s", envname,enval);
	Enventry = Newentry;
	(++Enventry) = NULL;
	return 0;
}
