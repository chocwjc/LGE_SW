#include <sys/cdefs.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <err.h>
#include <errno.h>
#include <fts.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

typedef unsigned long long uint64_t;
#define __UNCONST(a)	((void *)(unsigned long)(const void *)(a))

int	linkchk(dev_t, ino_t);
void	prstat(const char *, int64_t);
static void	usage(void);

long blocksize;

#define howmany(x, y)   (((x)+((y)-1))/(y))

int main(int argc, char *argv[])
{
	FTS *fts;
	FTSENT *p;
	int64_t totalblocks;
	int ftsoptions, listfiles;
	int depth;
	int Hflag, Lflag, aflag, ch, cflag, dflag, gkmflag, nflag, rval, sflag;
	const char *noargv[2];

	Hflag = Lflag = aflag = cflag = dflag = gkmflag = sflag = 0;
	totalblocks = 0;
	ftsoptions = FTS_PHYSICAL;
	depth = INT_MAX;
	while ((ch = getopt(argc, argv, "HLPacd:ghkmnrsx")) != -1)
		switch (ch) {
		case 'H':
			Hflag = 1;
			Lflag = 0;
			break;
		case 'L':
			Lflag = 1;
			Hflag = 0;
			break;
		case 'P':
			Hflag = Lflag = 0;
			break;
		case 'a':
			aflag = 1;
			break;
		case 'c':
			cflag = 1;
			break;
		case 'd':
			dflag = 1;
			depth = atoi(optarg);
			if (depth < 0 || depth > SHRT_MAX) {
				warnx("invalid argument to option d: %s", 
					optarg);
				usage();
			}
			break;
		case 'g':
			blocksize = 1024 * 1024 * 1024;
			gkmflag = 1;
			break;
		case 'k':
			blocksize = 1024;
			gkmflag = 1;
			break;
		case 'm':
			blocksize = 1024 * 1024;
			gkmflag = 1;
			break; 
		case 'r':
			break;
		case 's':
			sflag = 1;
			break;
		case 'x':
			ftsoptions |= FTS_XDEV;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (Hflag)
		ftsoptions |= FTS_COMFOLLOW;
	if (Lflag) {
		ftsoptions &= ~FTS_PHYSICAL;
		ftsoptions |= FTS_LOGICAL;
	}

	listfiles = 0;
	if (aflag) {
		if (sflag || dflag)
			usage();
		listfiles = 1;
	} else if (sflag) {
		if (dflag)
			usage();
		depth = 0;
	}

	if (!*argv) {
		noargv[0] = ".";
		noargv[1] = NULL;
		argv = __UNCONST(noargv);
	}

	if (!gkmflag)
		blocksize = 512;
	blocksize /= 512;

	if ((fts = fts_open(argv, ftsoptions, NULL)) == NULL)
		err(1, "fts_open `%s'", *argv);

	for (rval = 0; (p = fts_read(fts)) != NULL;) {
		switch (p->fts_info) {
		case FTS_D:			
			break;
		case FTS_DP:
			p->fts_parent->fts_number += 
			    p->fts_number += p->fts_statp->st_blocks;
			if (cflag)
				totalblocks += p->fts_statp->st_blocks;
			if (p->fts_level <= depth
			    || (!listfiles && !p->fts_level))
				prstat(p->fts_path, p->fts_number);
			break;
		case FTS_DC:	
			break;
		case FTS_DNR:
		case FTS_ERR:
		case FTS_NS:
			warnx("%s: %s", p->fts_path, strerror(p->fts_errno));
			rval = 1;
			break;
		default:
			if (p->fts_statp->st_nlink > 1 &&
			    linkchk(p->fts_statp->st_dev, p->fts_statp->st_ino))
				break;

			if (listfiles || !p->fts_level)
				prstat(p->fts_path, p->fts_statp->st_blocks);
			p->fts_parent->fts_number += p->fts_statp->st_blocks;
			if (cflag)
				totalblocks += p->fts_statp->st_blocks;
		}
	}
	if (errno)
		err(1, "fts_read");
	if (cflag)
		prstat("total", totalblocks);
	exit(rval);
}

void
prstat(const char *fname, int64_t blocks)
{
	(void)printf("%lld\t%s\n",
	    (long long)howmany(blocks, (int64_t)blocksize),
	    fname);
}

int
linkchk(dev_t dev, ino_t ino)
{
	static struct entry {
		dev_t	dev;
		ino_t	ino;
	} *htable;
	static int htshift;  
	static int htmask;   
	static int htused;   
	static int sawzero;  
	int h, h2;
	uint64_t tmp;

	const uint64_t HTCONST = 11400714819323198485ULL;
	const int HTBITS = CHAR_BIT * sizeof(tmp);

	if (dev == 0 && ino == 0) {
		h = sawzero;
		sawzero = 1;
		return h;
	}

	if (htused<<1 >= htmask) {
		struct entry *ohtable;

		if (!htable)
			htshift = 10;  
		else
			htshift++;   

		htmask  = (1 << htshift) - 1;
		htused = 0;

		ohtable = htable;
		htable = calloc(htmask+1, sizeof(*htable));
		if (!htable)
			err(1, "calloc");

		if (ohtable) {
			int i;
			for (i = 0; i <= htmask>>1; i++)
				if (ohtable[i].ino || ohtable[i].dev)
					linkchk(ohtable[i].dev, ohtable[i].ino);
			free(ohtable);
		}
	}

	tmp = dev;
	tmp <<= HTBITS>>1;
	tmp |=  ino;
	tmp *= HTCONST;
	h  = tmp >> (HTBITS - htshift);
	h2 = 1 | ( tmp >> (HTBITS - (htshift<<1) - 1)); 

	/* open address hashtable search with double hash probing */
	while (htable[h].ino || htable[h].dev) {
		if ((htable[h].ino == ino) && (htable[h].dev == dev))
			return 1;
		h = (h + h2) & htmask;
	}

	htable[h].dev = dev;
	htable[h].ino = ino;
	htused++;
	return 0;
}

static void
usage(void)
{

	(void)fprintf(stderr,
		"usage: du [-H | -L | -P] [-a | -d depth | -s] [-cgkmrx] [file ...]\n");
	exit(1);
}

