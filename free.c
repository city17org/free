/*
 * Copyright (c) 2018 Sean Davies <sean@city17.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <sys/types.h>
#include <sys/sysctl.h>

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FREE_VERSION "1.1"

#define scale(x) (((x) * (long long)uvmexp.pagesize) >> shift)

static void __dead usage(void);

int
main(int argc, char *argv[])
{
	struct uvmexp	uvmexp;
	int64_t		physmem;
	size_t		len;
	int		mib[2];
	int		ch;
	int		i = 0;
	int		shift = 10;
	int		vflag = 0;

	if (pledge("stdio vminfo ps", NULL) == -1)
		err(1, "pledge");

	while ((ch = getopt(argc, argv, "bgkmv")) != -1)
		switch (ch) {
		case 'b':
			if (i++)
				usage();
			shift = 0;
			break;
		case 'g':
			if (i++)
				usage();
			shift = 30;
			break;
		case 'k':
			/* default option */
			if (i++)
				usage();
			break;
		case 'm':
			if (i++)
				usage();
			shift = 20;
			break;
		case 'v':
			if (i++)
				usage();
			vflag = 1;
			break;
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc)
		usage();
	if (vflag) {
		printf("%s-%s\n", getprogname(), FREE_VERSION);
		return 0;
	}

	mib[0] = CTL_HW;
	mib[1] = HW_PHYSMEM64;
	len = sizeof(physmem);
	if (sysctl(mib, 2, &physmem, &len, NULL, 0) == -1)
		err(1, "sysctl");
	mib[0] = CTL_VM;
	mib[1] = VM_UVMEXP;
	len = sizeof(uvmexp);
	if (sysctl(mib, 2, &uvmexp, &len, NULL, 0) == -1)
		err(1, "sysctl");

	if (pledge("stdio", NULL) == -1)
		err(1, "pledge");

	printf("%19s %12s %12s\n", "total", "used", "free");
	printf("%-6s %12lld %12lld %12lld\n", "Mem:",
	    physmem >> shift,
	    scale(uvmexp.active),
	    scale(uvmexp.free));
	printf("%-6s %12lld %12lld %12lld\n", "Swap:",
	    scale(uvmexp.swpages),
	    scale(uvmexp.swpginuse),
	    scale(uvmexp.swpages - uvmexp.swpginuse));

	return 0;
}

static void __dead
usage(void)
{
	fprintf(stderr, "usage: %s [-b | -g | -k | -m | -v]\n",
	    getprogname());
	exit(1);
}
